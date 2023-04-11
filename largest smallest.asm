
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h
 mov [2000h],05h;
mov [2001h],08h;
mov [2002h],02h;
mov [2003h],01h;
mov [2004h],06h;
mov si,[2000h];
mov bx,1000h;  
mov cx,5h;
l1:
mov ax,si;
cmp ax,bx;
jng next
inc si;


next:
mov ax,si;
inc si;
loop l1 

ret



MOV [3000H],25H
MOV [3001H],15H
MOV [3002H],45H
MOV [3003H],35H
MOV [3004H],55H 

MOV SI,3000H
MOV DI,3001H
MOV CL,04

Back: MOV AL,[SI]
      MOV BL,[DI]
      CMP AL,BL
      JNC Next    /// for finding smallest just do change it with jc
      MOV [SI],BL
      MOV [DI],AL
Next: INC DI
      DEC CL
      JNZ Back

MOV BH,[3000H]

ret




