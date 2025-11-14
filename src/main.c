#include "include.h"

int main() {
    initialize_ncurses();

    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    create_windows(rows, cols);
    draw_ui(rows, cols);

    run_main_loop();

    free_cart_items();
    delete_windows();
    endwin();
    return 0;
}