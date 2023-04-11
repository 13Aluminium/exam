
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

mov cx,03h;
mov al,01h; 
mov bl,2h; 
l1: 

mul bl;
loop l1
ret

ret




