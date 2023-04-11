
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h 

mov cx,05h;
mov al,1h;  
l1:  
mul cx;
loop l1
ret

