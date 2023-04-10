MOV SI,2000H
MOV Dh,00H
MOV CX,0AH;
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
