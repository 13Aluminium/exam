
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h 

mov si, 1000h
mov al,01h
mov [si],00h
mov cx, 05h

xx:  
  
add al, [si-1]
inc si
mov [si], al 

loop xx

ret

