
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

org 100h
mov [1000h],05h;       
mov [1001h],02h;
mov [1002h],01h;
mov [1003h],08h;
mov [1004h],06h;
mov si,1000h;
mov cx,05h;
mov dl,02h;
mov bl,00h;
l1:
mov bh,[si];   
mov al,bh;
div dl;
cmp ah,01h;
jz exit:
add bl,bh;
exit:
inc si;
loop l1
ret

ret




