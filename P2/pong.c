#include <ncurses.h>
#include <unistd.h>

#define ANCHO 60
#define ALTO 20
#define PALA_TAM 4

void pantalla_bienvenida() {
    clear();
    move(ALTO/2 - 2, (ANCHO/2) - 10);
    printw("===  PONG PDIH ===");
    move(ALTO/2, (ANCHO/2) - 15);
    printw("Controles: Flechas ARRIBA/ABAJO");
    move(ALTO/2 + 2, (ANCHO/2) - 15);
    printw("Pulsa una tecla para empezar...");
    refresh();
    nodelay(stdscr, FALSE);
    getch();
}

int main() {
    int opcion_final;

    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);     
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Color pelota
    init_pair(2, COLOR_CYAN, COLOR_BLUE);    // Color pala

    do {
        int x = 10, y = 10;      // Pelota
        int dx = 1, dy = 1;      
        int pala_y = ALTO / 2;   // Posición pala
        int puntuacion = 0;
        int tecla;

        pantalla_bienvenida();
        nodelay(stdscr, TRUE); // Modo no bloqueante para que la pelota se mueva sola

        WINDOW *win = newwin(ALTO, ANCHO, 1, 1);
        box(win, 0, 0);

        while (1) {
            tecla = getch();
            flushinp();
            // Control de la pala
            if (tecla == KEY_UP && pala_y > 1) pala_y--;
            if (tecla == KEY_DOWN && pala_y < ALTO - PALA_TAM - 1) pala_y++;
            if (tecla == 'q') break; 
            
            // Lógica de la pelota y rebotes
            if (y <= 1 || y >= ALTO - 2) dy *= -1; // Rebote techo/suelo
            if (x >= ANCHO - 2) dx *= -1;          // Rebote en pared derecha

            // COLISIÓN CON LA PALA (Pared izquierda)
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

            move(0, 2);
            printw("Puntos: %d  |  'q' para salir", puntuacion);
            
            wrefresh(win);
            refresh();
            usleep(30000); 
        }

        delwin(win); 
        nodelay(stdscr, FALSE); 
        clear();
        
        mvprintw(ALTO/2 - 1, ANCHO/2 - 15, "GAME OVER - Puntos totales: %d", puntuacion);
        mvprintw(ALTO/2 + 1, ANCHO/2 - 17, "¿Volver a jugar? ('v' = Sí, 'q' = Salir)");
        refresh();

        do {
            opcion_final = getch();
        } while (opcion_final != 'v' && opcion_final != 'q');

    } while (opcion_final == 'v'); 

    endwin();
    return 0;
}
