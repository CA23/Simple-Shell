# Simple-Shell

A simple, minimalistic implementation of a shell based on a tutorial using the C language.

Changes made: Implemented the shell using the 'getline()' function in <stdio.h> to read a line of input instead of using malloc() and realloc() with buffer size. 

getline() expands the block of memory as needed.

main.c compiles successfully, but the shell loop breaks randomly. 

Yet to test the original code and compare changes to identify the fault. Hope to fix issues, add additional functionality and expand the shell when time permits.
