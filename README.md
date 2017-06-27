# Simple-Shell

A simple, minimalistic implementation of a shell based using the C language.

Changes made: Implemented the shell using the 'getline()' function in <stdio.h> to read a line of input instead of using malloc() and realloc() with buffer size. 

getline() expands the block of memory as needed.

main.c compiles successfully, but the shell loop breaks randomly. 

Yet to test the original code and compare changes to identify the fault. Hope to fix issues, add additional functionality and expand the shell when time permits.

Acknowledgement: Although, I have made my own changes and used different functionality from the original tutorial, this code compiles but does not run as intended. If you need working code for a shell, I suggest taking a look at the original tutorial at https://brennan.io/2015/01/16/write-a-shell-in-c/. The author has made his code freely available on Github but I would rather suggest giving the tutorial a read. It is definitely worth it. I have not yet compiled the author's code as is, but I intend to do so to identify the problem with mine. 
