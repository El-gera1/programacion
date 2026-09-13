default rel
global main

cte equ 10

section .data
    codsal db 0
    dato1  db 5
    dato2  db 20
    resul  db 0

section .text

main:
    mov al, [dato1]
    add al, [dato2]
    add al, cte
    mov [resul], al

salir:
    movzx rax, byte [resul]
    ret