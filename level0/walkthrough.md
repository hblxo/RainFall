  
## Démarche

- Lancer le binaire : `./level0`
   > Segmentation fault (core dumped)
- Lancer le binaire avec des arguments : `./level0 aaa` ou `./level0 1`
   > No !
   
- Lancer le binaire `level0` avec gdb et peda :
  - Depuis l'host, copier peda dans le `/tmp` de la VM :
    - `scp -P 4242 -r ~/peda/ level0@192.168.0.16:/tmp`
  - Depuis la VM :
    - `gdb level0`
  - Dans gdb :
    - `source /tmp/peda/peda.py` : ajouter peda à gdb
    - `br main` : placer un breakpoint au commencement de la fonction main
    - `run` : lancer le programme, puis `n` pour avancer étape par étape après le breakpoint
    - Le segfault apparait lors d'un appel à atoi :
      >   0x8048ed4 <main+20>:	call   0x8049710 <atoi>
    - `set args 0` : définir des arguments
    - `run` : lancer le programme, puis `n` pour avancer étape par étape après le breakpoint
    - Le programme fait une comparaison de l'argument  `0x1a7`, soit 423 en décimal
       >    0x8048ed9 <main+25>:	cmp    eax,0x1a7
     - Si le paramètre n'est pas `423`, le programme print `No !\n` puis exit
     - `set args 423`
    - `run` : lancer le programme, puis `n` pour avancer étape par étape après le breakpoint
      >  0x8048ee7 <main+39>:	call   0x8050bf0 <strdup>
   
      >  0xbffff6c0 --> 0x80c5348 ("/bin/sh")

      Le programme fait un strdup de la chaine `"/bin/sh"`
      > 0x8048ef8 <main+56>:	call   0x8054680 <getegid>

      > 0x8048f01 <main+65>:	call   0x8054670 <geteuid>

      Puis un appel à `getegid` et `geteuid`
      > 0x8048f21 <main+97>:	call   0x8054700 <setresgid>

      > 0x8048f3d <main+125>:	call   0x8054690 <setresuid>
      Puis `setresgid` et `setresuid`

      > call   0x8054640 <execv>

      Puis un appel à `execv` avec `0x80f2718 ("/bin/sh")` et `arg[0]: 0x7e4`, `arg[1]: 0x7e4`, `arg[2]: 0x7e4` en arguments

- Dans la VM, lancer le programme avec le bon argument : `./level0 423`
   - Dans le sh ouvert par le programme avec les bons droits d'accès :
     - `cat /home/user/level1/.pass` *(commande en exemple dans le sujet du projet)*
      > 1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a



<br>
----
## Ressources
- [Man execv -- Overlay Calling Process and Run New Program](https://support.sas.com/documentation/onlinedoc/sasc/doc/lr2/execv.htm)