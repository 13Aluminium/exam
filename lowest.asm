org 100h 

MOV SI, 1400H

MOV CL ,[SI]

MOV AX, 0000H 

INC SI


MOV AL, [SI]

OP: 

INC SI

MOV BL, [SI] 

CMP AL, BL

JC GO

MOV AL, BL

GO: 

DEC CL

JNZ OP


MOV BL, AL

ret