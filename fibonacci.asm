ORG 100H
mov ax, 0
mov bx, 1
mov cx, 4H
fibo: add ax, bx
      add bx, ax
loop fibo
ret
