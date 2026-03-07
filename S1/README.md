# Seminario 1: Programación de dispositivos a bajo nivel

## Descripción
En este seminario se ha configurado el entorno de desarrollo utilizando **DOSBox** para emular un sistema de 16 bits. El objetivo ha sido familiarizarse con las herramientas de Borland (**TASM** y **TLINK**) y el uso de interrupciones de software de MS-DOS.

## Desarrollo
Se ha implementado un programa en ensamblador x86 que utiliza la interrupción `int 21h` (función `09h`) para imprimir una cadena de texto. Para cumplir con el requisito del seminario, se ha añadido un bucle controlado por el registro `CX`.

### Código del bucle
```asm
        mov cx, 0           ; Inicializamos contador
bucle:
        mov dx,OFFSET msg   ; Cargamos mensaje
        mov ah,9            ; Función de impresión
        int 21h             ; Llamada al sistema
        inc cx              ; Incrementamos contador
        cmp cx, 7           ; ¿Llegamos a 7?
        jne bucle           ; Si no, repetimos
