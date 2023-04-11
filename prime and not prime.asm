
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

mov [2000h],4

mov ax,[2000h]
 
cmp ax,02h
jz l3  

mov si,02h
div si 
mov cx,ax

l1:
mov al,[2000h]
div si
cmp ah,00h
jz l2
inc si
loop l1 

cmp cx,00h
jz l3: 

l2:
lea dx,STRING
MOV AH,09H
INT 21H
ret 

l3: 
lea dx,STRING1
MOV AH,09H
INT 21H
ret 



STRING  DB 'not prime','$' 
STRING1 DB 'prime','$'
ret




