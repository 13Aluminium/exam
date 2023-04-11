
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

MOV CL,100
SUB CL,32H
MOV AX,5H   
MUL CL 
MOV CL,9H
DIV CL



ret




