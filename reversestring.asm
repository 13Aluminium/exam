ORG 100H
org 100h
include emu8086.inc
.DATA
  STR1 DB 0DH,0AH, 'Input: $'
  STR2 DB 0DH,0AH, 'Output: $'
  nl db 0dh,0ah,'$'
.CODE
  START:
    MOV AX, @DATA
    MOV DS, AX
    cmp al, 0x41h
    JGE IsInLowerCaseRange
  Disp:
    LEA DX,STR1
    MOV AH,09H
    INT 21H
 MOV CL,00
    MOV AH,01H
Read:
    INT 21
 MOV BL,AL
 PUSH BX
    inc cx
    CMP AL,0DH
JZ DISPLAY
    JMP READ
Display:
    LEA DX,STR2
    MOV AH,09H
    INT 21H
 lea dx, nl
    mov ah,09h
    int 21h
ANS:
    MOV AH,02H
    POP BX
    MOV DL,BL
    INT 21H
    LOOP ANS
IsInLowerCaseRange:
    cmp al, 0x5Ah
    jle DisplayLowerCaseLetter
    cmp al, 0x61h
    jge IsInUpperCaseRange
    jmp NotALetter

 DisplayLowerCaseLetter:
    add al, 0x20h
    mov ah, 0xEh
    int 10h
    jmp exit
IsInUpperCaseRange:
    cmp al, 0x7Ah
    jle DisplayUpperCaseLetter
    jmp NotALetter
DisplayUpperCaseLetter:
    sub al, 0x20h
    mov ah, 0xEh
    int 10h
    jmp exit 
 NotALetter:
    printn
    print "The input character is not a letter."
    exit:
    hlt 
.EXIT
END  START
