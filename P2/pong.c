#include <ncurses.h>
#include <unistd.h>

#define ANCHO 60
#define ALTO 20
#define PALA_TAM 4

void pantalla_bienvenida() {
    clear();
    move(ALTO/2 - 2, (ANCHO/2) - 10);
    printw("===  PONG PDIH ===");
    move(ALTO/2, (ANCHO/2) - 12);
    printw("Controles: Flechas ARRIBA/ABAJO");
    move(ALTO/2 + 2, (ANCHO/2) - 8);
    printw("Pulsa una tecla para empezar...");
    refresh();
    nodelay(stdscr, FALSE);
    getch();
}

int main() {
    int x = 10, y = 10;      // Pelota
    int dx = 1, dy = 1;      
    int pala_y = ALTO / 2;   // Posición pala
    int puntuacion = 0;
    int tecla;

    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);     
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Color pelota
    init_pair(2, COLOR_CYAN, COLOR_BLUE);    // Color pala

    pantalla_bienvenida();
    nodelay(stdscr, TRUE);

    // Crear ventana de juego con borde
    WINDOW *win = newwin(ALTO, ANCHO, 1, 1);
    box(win, 0, 0);

    while (1) {
        tecla = getch();
        
        // 1. Control de la pala
        if (tecla == KEY_UP && pala_y > 1) pala_y--;
        if (tecla == KEY_DOWN && pala_y < ALTO - PALA_TAM - 1) pala_y++;
        if (tecla == 'q') break;

        // 2. Lógica de la pelota y rebotes
        if (y <= 1 || y >= ALTO - 2) dy *= -1; // Rebote techo/suelo
        
        // Rebote en pared derecha
        if (x >= ANCHO - 2) dx *= -1;

        // 3. COLISIÓN CON LA PALA (Pared izquierda)
        if (x == 2) {
            if (y >= pala_y && y < pala_y + PALA_TAM) {
                dx *= -1;
                puntuacion++;
            } else {
                // GAME OVER
                break; 
            }
        }

        x += dx; y += dy;

        // 4. DIBUJAR TODO
        werase(win);
        box(win, 0, 0);
        
        // Dibujar pala
        wattron(win, COLOR_PAIR(2));
        for(int i=0; i < PALA_TAM; i++) mvwaddch(win, pala_y + i, 1, '|');
        wattroff(win, COLOR_PAIR(2));

        // Dibujar pelota
        wattron(win, COLOR_PAIR(1));
        mvwaddch(win, y, x, 'O');
        wattroff(win, COLOR_PAIR(1));

        // Actualizar marcador en la pantalla principal
        move(0, 2);
        printw("Puntos: %d  |  'q' para salir", puntuacion);
        
        wrefresh(win);
        refresh();
        usleep(30000); // Velocidad del juego
    }

    // Pantalla Final
    nodelay(stdscr, FALSE);
    clear();
    mvprintw(ALTO/2, ANCHO/2 - 10, "GAME OVER - Puntos: %d", puntuacion);
    mvprintw(ALTO/2 + 2, ANCHO/2 - 10, "Pulsa tecla para salir");
    refresh();
    getch();

    endwin();
    return 0;
}