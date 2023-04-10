ORG 100H
 MOV SI,1000H
 MOV CL,[SI]
 DEC CL
 
 G3:
 MOV SI,1000H
 MOV CH,[SI]
 DEC CH 
 INC SI
 
 G2:
 MOV AL ,[SI]
 INC SI                          ASCENDING USER INPUT
 CMP AL,[SI]
 JC G1
 XCHG AL,[SI]
 XCHG AL,[SI-1]
 
 G1:
 DEC CH
 JNZ G2
 DEC CL
 JNZ G3