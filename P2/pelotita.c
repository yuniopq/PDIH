#include <ncurses.h>
#include <unistd.h> // Para usleep

int main() {
    int x = 10, y = 10;       // Posición inicial
    int dx = 1, dy = 1;       // Dirección (1 adelante, -1 atrás)
    int max_x, max_y;         // Límites de la pantalla

    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    while (1) {
        getmaxyx(stdscr, max_y, max_x); // Obtiene tamaño actual de ventana

        clear(); // Borra la pantalla anterior

        // 1. Dibujar la "pelota"
        mvprintw(y, x, "O");

        // 2. Lógica de rebote
        // Si toca bordes verticales (arriba/abajo)
        if (y <= 0 || y >= max_y - 1) dy *= -1;
        
        // Si toca bordes horizontales (izq/der)
        if (x <= 0 || x >= max_x - 1) dx *= -1;

        // 3. Actualizar posición
        y += dy;
        x += dx;

        refresh();
        usleep(50000); // 50ms

        // Salir si se pulsa 'q'
        if (getch() == 'q') break;
    }

    endwin();
    return 0;
}