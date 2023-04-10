Org 100h

Move si,1400h

Move cl,[si ]

DEC CL

Mov ax,0000h

INC SI

MOV AL, [SI]

OP:

INC SI

MOV BL, [SI]

CMP AL, BL
JNC GO

MOV AL, BL

GO:

DEC CL

JNZ OP 

MOV BL, AL

ret