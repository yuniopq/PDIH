#include <ncurses.h>

int main() {
    WINDOW *mi_win;
    int alto = 10, ancho = 40;
    int inicio_y = 5, inicio_x = 10;

    initscr();            // Inicia ncurses
    cbreak();             // Captura teclas al instante (sin esperar al Enter)
    noecho();             // No muestra lo que el usuario escribe
    curs_set(0);          // Esconde el cursor para que quede más limpio

    // 1. Verificar y activar colores
    if (has_colors() == FALSE) {
        endwin();
        printf("Tu terminal no soporta colores\n");
        return 1;
    }
    start_color();

    // 2. Definir una pareja de colores: ID, Texto, Fondo
    init_pair(1, COLOR_WHITE, COLOR_BLUE);

    // 3. Crear la ventana: alto, ancho, y_inicial, x_inicial
    mi_win = newwin(alto, ancho, inicio_y, inicio_x);

    // 4. Aplicar el color y dibujar el borde
    wbkgd(mi_win, COLOR_PAIR(1)); // Fondo azul para la ventana
    box(mi_win, 0, 0);            // Dibuja el marco automático

    // 5. Escribir dentro de la ventana (y, x relativo a la ventana)
    mvwprintw(mi_win, 2, 2, "Ventana de la Practica 2");
    mvwprintw(mi_win, 4, 2, "Pulsa cualquier tecla...");

    // 6. Refrescar la ventana específica (no solo la estándar)
    wrefresh(mi_win);

    getch();
    endwin();
    return 0;
}