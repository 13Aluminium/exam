org 100h
MOV BL,02H
MOV SI,2000H
MOV [2000H],1
MOV [2001H],2
MOV [2002H],3
MOV [2003H],4
MOV [2004H],5
MOV [2005H],6
MOV CX,06H
MOV DL,00H
L1:
MOV AL,[SI]
DIV BL
CMP AH,00H 
JZ L2
JNZ L3    
JMP EXIT
L2:
 SUB DL,[SI]  
 INC SI
 LOOP L1 
 JMP EXIT
L3:
MOV BH,[SI]
MOV AX, 0001H
LOOP_START:
MUL BH       ; Multiply AX by CX
DEC BH       ; Decrement CX
JNZ LOOP_START 
ADD DX,AX  
INC SI 
LOOP L1   
EXIT:
Ret
