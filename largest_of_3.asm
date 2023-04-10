org 100h
MOV SI,2000H 
MOV [2000H],12H
MOV [2001H],15H
MOV [2002H],10H
MOV DH,00H
MOV CX,03H
L1:
MOV Ah,[SI]
CMP Ah,dh
Jg L2  
INC SI
LOOP L1
HLT                                   
L2:
mov dh,[si]  
INC SI
LOOP L1
HLT
ret
