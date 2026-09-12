global main
extern printf

section .data
    mensaje db "Hola Mundo desde Ensamblador!", 10, 0   ; 10 es salto de linea, 0 es el fin de cadena

section .text

main:
    sub rsp, 40                 ; Reservar espacio en la pila (sombra de 32 bytes + alineacion de 8 bytes)
    
    mov rcx, mensaje            ; En Windows x64, el primer argumento de una función se pasa en RCX
    call printf                 ; Llama a la función printf de C

    add rsp, 40                 ; Restaurar la pila
    mov rax, 0                  ; Retornar 0 (sin errores)
    ret