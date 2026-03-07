#include <stdio.h>
#include "mi_io.h"

void mostrar_menu() {
    unsigned char opcion;
    do {
        setvideomode(0x03);   
        textbackground(0);    
        textcolor(15);        
        clrscr();             

        gotoxy(20, 5);
        printf("=========================================");
        gotoxy(20, 6);
        printf("      MENU DE PRUEBAS - PRACTICA 1       ");
        gotoxy(20, 7);
        printf("=========================================");
        
        gotoxy(20, 9);
        printf("1. Probar Modos de Video y Cursor");
        gotoxy(20, 10);
        printf("2. Probar Colores y Texto (cputchar)");
        gotoxy(20, 11);
        printf("3. Dibujar Recuadro (Modo Texto)");
        gotoxy(20, 12);
        printf("4. Dibujar Casa (Modo Grafico CGA)");
        gotoxy(20, 13);
        printf("5. Dibujar Gato Gigante (ASCII Art)");
        gotoxy(20, 15);
        printf("0. Salir");

        gotoxy(20, 17);
        printf("Elige una opcion: ");
        
        opcion = getche(); 

        switch(opcion) {
            case '1':
                clrscr();
                printf("\n--- PRUEBA DE CURSOR ---\n");
                printf("Cursor Invisible...\n");
                setcursortype(0);
                pausa();
                printf("Cursor Grueso...\n");
                setcursortype(2);
                pausa();
                printf("Cursor Normal...\n");
                setcursortype(1);
                pausa();
                break;
                
            case '2':
                clrscr();
                gotoxy(10, 5);
                textcolor(4); 
                textbackground(1); 
                cputchar('H'); cputchar('O'); cputchar('L'); cputchar('A');
                printf("\n\nPulsa una tecla para volver...");
                pausa();
                break;
                
            case '3':
                clrscr();
                dibujar_cuadrado(15, 5, 65, 15, 14, 2); 
                gotoxy(25, 10);
                printf("Recuadro en modo texto!");
                pausa();
                break;
                
            case '4':
                dibujar_dibujo(); 
                break;
                
            case '5':
                clrscr();
                dibujar_gato_gigante(0, 0, 10);
                pausa();
                break;
                
            case '0':
                clrscr();
                break;
                
            default:
                gotoxy(20, 19);
                printf("Opcion no valida. Pulsa una tecla...");
                pausa();
                break;
        }
    } while(opcion != '0'); 
}

int main() {
    mostrar_menu();
    return 0;
}