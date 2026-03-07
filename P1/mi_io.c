#include <stdio.h>
#include <dos.h>
#include "mi_io.h"

unsigned char TEXT_COLOR = 0x07; 
unsigned char BACKGROUND_COLOR = 0x00;

void gotoxy(unsigned char x, unsigned char y) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x02;
    inregs.h.bh = 0x00;
    inregs.h.dl = x;
    inregs.h.dh = y;
    int86(0x10, &inregs, &outregs);
}

void setcursortype(unsigned char modo) {
    union REGS inregs, outregs;
    inregs.h.ah = 001;
    if (modo==0) {
        inregs.h.ch = 010;
        inregs.h.cl = 000;
    } else if (modo==1) {
        inregs.h.ch = 010;
        inregs.h.cl = 010;
    } else if (modo==2) {
        inregs.h.ch = 000;
        inregs.h.cl = 010;
    } else {
        printf("modo 0 = INVISIBLE, modo 1 = NORMAL, modo 2 = GRUESO");
        return;
    }
    int86(0x10, &inregs, &outregs);
}

void setvideomode(unsigned char modo) {
    union REGS inregs, outregs;
    inregs.h.ah = 000;
    if (modo > 0x13) {
        printf("Modo de video no valido. Use un valor entre 0x00 y 0x13.");
        return;
    }
    inregs.h.al = modo;
    int86(0x10, &inregs, &outregs);
}

unsigned char getvideomode() {
    union REGS inregs, outregs;
    unsigned char modo;
    inregs.h.ah = 0x0F;
    int86(0x10, &inregs, &outregs);
    modo = outregs.h.al;
    return modo;
}

void textcolor(unsigned char color) {
    TEXT_COLOR = color;
}

void textbackground(unsigned char color) {
    BACKGROUND_COLOR = color;
}

void clrscr() {
    union REGS inregs, outregs;
    textcolor(0x07); 
    textbackground(0x00);
    inregs.h.ah = 0x06; 
    inregs.h.al = 0;    
    inregs.h.bh = (BACKGROUND_COLOR << 4) | TEXT_COLOR; 
    inregs.h.ch = 0;    
    inregs.h.cl = 0;    
    inregs.h.dh = 24;   
    inregs.h.dl = 79;   
    int86(0x10, &inregs, &outregs);
    gotoxy(0, 0);
}

void cputchar(unsigned char c) {
    union REGS inregs, outregs;
    unsigned char x, y;
    inregs.h.ah = 011;
    inregs.h.al = c;
    inregs.h.bl = (BACKGROUND_COLOR << 4) | TEXT_COLOR;
    inregs.h.bh = 0;
    inregs.x.cx = 1; 
    int86(0x10, &inregs, &outregs);

    inregs.h.ah = 3;
    int86(0x10, &inregs, &outregs);
    
    x = outregs.h.dl;
    y = outregs.h.dh;
    x++;
    if (x >= 80) {
        x = 0;
        y++;
    }
    gotoxy(x, y);
}

unsigned char getche() {
    union REGS inregs, outregs;
    
    inregs.h.ah = 0; 
    int86(0x16, &inregs, &outregs);
    
    cputchar(outregs.h.al);
    
    return outregs.h.al; 
}

void pausa() {
    union REGS inregs, outregs;
    inregs.h.ah = 0x00;
    int86(0x16, &inregs, &outregs);
}

void pixel(int x, int y, unsigned char color) {
    union REGS inregs, outregs;
    inregs.h.ah = 014;
    inregs.h.al = color;
    inregs.x.cx = x;
    inregs.x.dx = y;
    int86(0x10, &inregs, &outregs);
}

void dibujar_cuadrado(int x1, int y1, int x2, int y2, unsigned char color_texto, unsigned char color_fondo) {
    int i, j;
    textcolor(color_texto);
    textbackground(color_fondo);
    gotoxy(x1, y1);
    for (i = y1; i <= y2; i++) {
        gotoxy(x1, i);
        for (j = x1; j <= x2; j++) {
            if (j == x1 && i == y1) cputchar(218);
            else if (j == x2 && i == y1) cputchar(191);
            else if (j == x1 && i == y2) cputchar(192);
            else if (j == x2 && i == y2) cputchar(217);
            else if (i == y1 || i == y2) cputchar(196);
            else if (j == x1 || j == x2) cputchar(179);
            else cputchar(' ');
        }
    }
}

void dibujar_dibujo() {
    int x, y;
    setvideomode(4);
    for (x = 120; x <= 200; x++) {
        pixel(x, 100, 1); 
        pixel(x, 160, 1); 
    }
    for (y = 100; y <= 160; y++) {
        pixel(120, y, 1); 
        pixel(200, y, 1); 
    }
    y = 100;
    for (x = 120; x <= 160; x++) {
        pixel(x, y, 2);           
        pixel(320 - x, y, 2);     
        y--;                      
    }
    for (x = 150; x <= 170; x++) {
        pixel(x, 130, 3); 
    }
    for (y = 130; y <= 160; y++) {
        pixel(150, y, 3); 
        pixel(170, y, 3); 
    }
    pixel(165, 145, 2); 
    pausa(); 
    setvideomode(3); 
}

void dibujar_gato_gigante(int x, int y, unsigned char color_gato) {
    char *lineas[] = {
        "                      ,",
        "                      \\`-._            __",
        "                       \\\\  `-..____,.'  `.",
        "                        :`.         /    \\`.",
        "                        :  )       :      : \\",
        "                         ;'        '   ;  |  :",
        "                         )..      .. .:.`.;  :",
        "                        /::...  .:::...   ` ;",
        "                        ; _ '    __        /:\\",
        "                        `:o>   /\\o_>      ;:. `.",
        "                       `-`.__ ;   __..--- /:.   \\",
        "                       === \\_/   ;=====_.':.     ;",
        "                        ,/'`--'...`--....        ;",
        "                             ;                    ;",
        "                           .'                      ;",
        "                         .'                        ;",
        "                       .'     ..     ,      .       ;",
        "                      :       ::..  /      ;::.     |",
        "                     /      `.;::.  |       ;:..    ;",
        "                    :         |:.   :       ;:.    ;",
        "                    :         ::     ;:..   |.    ;",
        "                     :       :;      :::....|     |",
        "                     /\\     ,/ \\      ;:::::;     ;",
        "                   .:. \\:..|    :     ; '.--|     ;",
        "                  ::.  :''  `-.,,;     ;'   ;     ;"
    };
    int num_lineas = 24; 
    int i, j;
    textcolor(color_gato);
    textbackground(0);
    for (i = 0; i < num_lineas; i++) {
        gotoxy(x, y + i);
        j = 0;
        while (lineas[i][j] != '\0') {
            cputchar(lineas[i][j]);
            j++;
        }
    }
}