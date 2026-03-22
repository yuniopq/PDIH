#include <ncurses.h>

int main() {
    // 1. Inicializa el modo ncurses
    initscr();

    // 2. Escribe el mensaje en el buffer (memoria)
    // No aparecerá en pantalla todavía
    printw("¡Hola! Si ves esto, ncurses funciona perfectamente.");

    // 3. Refresca la pantalla física para mostrar lo que hay en el buffer
    refresh();

    // 4. Espera a que el usuario pulse una tecla para no cerrar de golpe
    printw("\nPresiona cualquier tecla para salir...");
    getch();

    // 5. Finaliza el modo ncurses y devuelve la terminal a su estado normal
    endwin();

    return 0;
}