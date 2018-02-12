# Abstract-VM

Sujet de 42, le programme permet de faire un interpreteur de pseudo ASM 
- voir pdf: [abstract-vm.en.pdf](abstract-vm.en.pdf)

## Creer un script:

push type(value)
>push permet de rajouter une variable sur la stack (pile)
les type:
- int8: caractere textuel, equivalent au char
- int16: entier de 16bits, equivalent au int
- int32: entier de 32bits, equivalent au long
- float, nombre flotant de 16bit
- double, nombre flotant de 32bit

pop
>pop permet de supprimer le premier element de la stack (le dernier push)

dump
>permet d'afficher toutes les valeurs de la stack du plus recent au plus vieux

assert type(value)
>compare le premier element de la stack a la valeur entre
>si celui-ci n'est pas identique cela leve une exception.

add / sub / mul / div / mod
>addition/soustreis/multiplie/divise/modulo les deux elements les plus recent de la stack
>[plus recent][operateur][plus recent]

print
>affiche l'element le plus recent de la stack
>si c'est un int8, affiche sont caractere ascii

exit
>termine le programme, le reste des instruction ne sont pas traite

## Exemple:

```c
%> cat exemple.avm
push int8(33) ;!
push int8(112) ;p
push int8(111) ;o
push int8(108) ;l
push int8(112) ;p
print
pop
print
pop
print
pop
print
pop
print
pop
exit
%> ./avm exemple.avm
plop!
```
