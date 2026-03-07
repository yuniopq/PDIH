#ifndef MI_IO_H
#define MI_IO_H

// Funciones base de Entrada/Salida
void gotoxy(unsigned char x, unsigned char y);
void setcursortype(unsigned char modo);
void setvideomode(unsigned char modo);
unsigned char getvideomode();
void textcolor(unsigned char color);
void textbackground(unsigned char color);
void clrscr();
void cputchar(unsigned char c);
unsigned char getche();
void pausa();
void pixel(int x, int y, unsigned char color);

void dibujar_cuadrado(int x1, int y1, int x2, int y2, unsigned char color_texto, unsigned char color_fondo);
void dibujar_dibujo();
void dibujar_gato_gigante(int x, int y, unsigned char color_gato);

#endif