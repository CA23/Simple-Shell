# Simple-Shell

A simple, minimalistic implementation of a shell using the C language.

Changes made: Implemented the shell using the 'getline()' function in <stdio.h> to read a line of input instead of using malloc() and realloc() with buffer size. 

getline() expands the block of memory as needed.

main.c compiles successfully, but the shell loop breaks randomly. 

I suggest taking a look at the original tutorial at https://brennan.io/2015/01/16/write-a-shell-in-c/ with its freely available code on Github. 
