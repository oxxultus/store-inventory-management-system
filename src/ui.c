#include "ui.h"

WINDOW *title_win = NULL;
WINDOW *status_win = NULL;
WINDOW *last_command_win = NULL;
WINDOW *menu_win = NULL;
WINDOW *output_win = NULL;
WINDOW *listbar_win = NULL;
WINDOW *tooltip_win = NULL;
WINDOW *command_win = NULL;
WINDOW *console_win = NULL;

void initialize_ncurses() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_BLUE, COLOR_BLACK);
        init_pair(2, COLOR_YELLOW, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
        init_pair(4, COLOR_RED, COLOR_BLACK);
        init_pair(5, COLOR_CYAN, COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_WHITE, COLOR_BLACK);
    }
}

void delete_windows() {
    if (title_win != NULL) delwin(title_win);
    if (status_win != NULL) delwin(status_win);
    if (last_command_win != NULL) delwin(last_command_win);
    if (command_win != NULL) delwin(command_win);
    if (console_win != NULL) delwin(console_win);
    if (menu_win != NULL) delwin(menu_win);
    if (output_win != NULL) delwin(output_win);
    if (tooltip_win != NULL) delwin(tooltip_win);
    if (listbar_win != NULL) delwin(listbar_win);
    title_win = console_win = menu_win = output_win = status_win = command_win = last_command_win = tooltip_win = listbar_win = NULL;
}

void create_windows(int rows, int cols) {
    int total_fixed_height = TITLE_HEIGHT + STATUS_HEIGHT + COMMAND_HEIGHT + CONSOLE_HEIGHT;
    int content_height = rows - total_fixed_height;
    int output_width = cols - MENU_WIDTH;

    if (content_height < 1 || output_width < 1 || rows < total_fixed_height) {
        return;
    }

    int current_y = 0;

    title_win = newwin(TITLE_HEIGHT, cols, current_y, 0);
    current_y += TITLE_HEIGHT;

    status_win = newwin(STATUS_HEIGHT, MENU_WIDTH, current_y, 0);
    last_command_win = newwin(LAST_COMMAND_HEIGHT, output_width-LISTBAR_WIDTH, current_y, MENU_WIDTH);
    listbar_win = newwin(LAST_COMMAND_HEIGHT, LISTBAR_WIDTH, current_y, cols-LISTBAR_WIDTH);
    current_y += STATUS_HEIGHT;

    menu_win = newwin(content_height, MENU_WIDTH, current_y, 0);
    output_win = newwin(content_height-TOOLTIP_HEIGHT, output_width, current_y, MENU_WIDTH);
    scrollok(output_win, TRUE);
    current_y += content_height;

    command_win = newwin(COMMAND_HEIGHT, cols, current_y, 0);

    tooltip_win = newwin(TOOLTIP_HEIGHT, output_width, current_y-TOOLTIP_HEIGHT, MENU_WIDTH);
    current_y += COMMAND_HEIGHT;

    console_win = newwin(CONSOLE_HEIGHT, cols, current_y, 0);
    scrollok(console_win, TRUE);

    wsetscrreg(console_win, 1, CONSOLE_HEIGHT - 2);

    werase(console_win);
    wmove(console_win, 1, 1);
}

void draw_ui(int rows, int cols) {
    if (title_win == NULL || console_win == NULL) return;

    draw_outline_all();

    set_window_print(rows, cols);

    refresh_all_win();
}

void draw_outline_all(){
    werase(stdscr);

    if (has_colors()) wattron(status_win, COLOR_PAIR(4));
    box(status_win, 0, 0);
    if (has_colors()) wattroff(status_win, COLOR_PAIR(4));

    if (has_colors()) {wattron(last_command_win, COLOR_PAIR(7) | A_BOLD); }
    box(last_command_win, 0, 0);
    if (has_colors()) {wattroff(last_command_win, COLOR_PAIR(7) | A_BOLD); }

    if (has_colors()) {wattron(listbar_win, COLOR_PAIR(7) | A_BOLD); }
    box(listbar_win, 0, 0);
    if (has_colors()) {wattroff(listbar_win, COLOR_PAIR(7) | A_BOLD); }

    if (has_colors()) {wattron(last_command_win, COLOR_PAIR(7) | A_BOLD); }
    box(command_win, 0, 0);
    if (has_colors()) {wattroff(last_command_win, COLOR_PAIR(7) | A_BOLD); }

    box(console_win, 0, 0);

    box(output_win, 0, 0);

    box(tooltip_win, 0, 0);

    draw_menu();
}

void draw_menu() {
    if (has_colors()) {wattron(menu_win, COLOR_PAIR(7) | A_BOLD); }
    int i;
    Menu_Item *current_menu_list;

    if (current_state == STATE_MAIN_MENU) {
        current_menu_list = main_menu_items;
        current_max_items = MAX_MAIN_MENU_ITEMS;
    } else if (current_state >= STATE_SUB_PURCHASE && current_state <= STATE_SUB_CATEGORY) {
        current_menu_list = sub_menu_template;
        current_max_items = MAX_SUB_MENU_ITEMS;
    } else if (current_state == STATE_SUB_SALES) {
        current_menu_list = sales_sub_menu;
        current_max_items = MAX_SALES_SUB_ITEMS;
    } else {
        werase(menu_win);
        box(menu_win, 0, 0);
        mvwaddwstr(menu_win, 1, 1, L"--- 기능 실행 중 ---");
        mvwaddwstr(menu_win, 2, 1, L"[B]를 눌러 복귀하세요.");
        return;
    }

    werase(menu_win);
    box(menu_win, 0, 0);

    mvwaddwstr(menu_win, 1, 2, get_current_menu_title());
    mvwaddwstr(menu_win, 2, 1, L"───────────────────────");

    for (i = 0; i < current_max_items; ++i) {
        if (i == current_menu_selection) {
            wattron(menu_win, A_REVERSE);
        }

        mvwaddwstr(menu_win, 3 + i, 2, current_menu_list[i].label);

        if (i == current_menu_selection) {
            wattroff(menu_win, A_REVERSE);
        }
    }

    if (current_state != STATE_MAIN_MENU) {
        if (has_colors()) {wattron(menu_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        mvwaddwstr(menu_win, 3 + current_max_items + 1, 2, L"🅱 ");
        if (has_colors()) {wattroff(menu_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        if (has_colors()) {wattron(menu_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(menu_win, 3 + current_max_items + 1, 5, L"뒤로 가기");
        if (has_colors()) {wattroff(menu_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    }

    if (has_colors()) {wattroff(menu_win, COLOR_PAIR(7) | A_BOLD); }
}

void set_window_print(int rows, int cols){

    mvwaddwstr(title_win, 1, 1, L"▗▄▄▄▖▗▖  ▗▖▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖▗▄▖ ▗▄▄▖▗▖  ▗▖    ▗▖  ▗▖ ▗▄▖ ▗▖  ▗▖ ▗▄▖  ▗▄▄▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖");
    mvwaddwstr(title_win, 2, 1, L"  █  ▐▛▚▖▐▌▐▌  ▐▌▐▌   ▐▛▚▖▐▌  █ ▐▌ ▐▌▐▌ ▐▌▝▚▞▘     ▐▛▚▞▜▌▐▌ ▐▌▐▛▚▖▐▌▐▌ ▐▌▐▌   ▐▌   ▐▛▚▞▜▌▐▌   ▐▛▚▖▐▌  █  ");
    mvwaddwstr(title_win, 3, 1, L"  █  ▐▌ ▝▜▌▐▌  ▐▌▐▛▀▀▘▐▌ ▝▜▌  █ ▐▌ ▐▌▐▛▀▚▖ ▐▌      ▐▌  ▐▌▐▛▀▜▌▐▌ ▝▜▌▐▛▀▜▌▐▌▝▜▌▐▛▀▀▘▐▌  ▐▌▐▛▀▀▘▐▌ ▝▜▌  █  ");
    mvwaddwstr(title_win, 4, 1, L"▗▄█▄▖▐▌  ▐▌ ▝▚▞▘ ▐▙▄▄▖▐▌  ▐▌  █ ▝▚▄▞▘▐▌ ▐▌ ▐▌      ▐▌  ▐▌▐▌ ▐▌▐▌  ▐▌▐▌ ▐▌▝▚▄▞▘▐▙▄▄▖▐▌  ▐▌▐▙▄▄▖▐▌  ▐▌  █  ");

    /*
    if (has_colors()) {wattron(status_win, COLOR_PAIR(4) | A_BOLD); }
    mvwaddwstr(status_win, 1, 2, L"▮▮▯▯▯ ");
    if (has_colors()) {wattroff(status_win, COLOR_PAIR(4) | A_BOLD);}
    if (has_colors()) {wattron(status_win, COLOR_PAIR(4) | A_BOLD); }
    mvwaddwstr(status_win, 1, 8, L"Con");
    if (has_colors()) {wattroff(status_win, COLOR_PAIR(4) | A_BOLD);}
    if (has_colors()) {wattron(status_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    mvwaddwstr(status_win, 1, 11, L"necting... ");
    if (has_colors()) {wattroff(status_win, COLOR_PAIR(4) | A_BOLD | A_DIM);}

    if (has_colors()) {wattron(listbar_win, COLOR_PAIR(7) | A_BOLD); }
    int listbar_rows, listbar_cols;
    getmaxyx(listbar_win, listbar_rows, listbar_cols);
    mvwaddwstr(listbar_win, 1, listbar_cols/2-1, L"◀ ▶");
    if (has_colors()) {wattron(listbar_win, COLOR_PAIR(7) | A_BOLD); }
    */
    if (has_colors()) {wattron(status_win, COLOR_PAIR(3) | A_BOLD); }
        box(status_win, 0,0);
    if (has_colors()) {wattroff(status_win, COLOR_PAIR(3) | A_BOLD);}
    if (has_colors()) {wattron(status_win, COLOR_PAIR(3) | A_BOLD); }
        mvwaddwstr(status_win, 1, 2, L"▮▮▮▮▮ ");
    if (has_colors()) {wattroff(status_win, COLOR_PAIR(3) | A_BOLD);}
    if (has_colors()) {wattron(status_win, COLOR_PAIR(3) | A_BOLD); }
        mvwaddwstr(status_win, 1, 8, L"Con");
    if (has_colors()) {wattroff(status_win, COLOR_PAIR(3) | A_BOLD);}
    if (has_colors()) {wattron(status_win, COLOR_PAIR(3) | A_BOLD | A_DIM); }
        mvwaddwstr(status_win, 1, 11, L"necting... ");
    if (has_colors()) {wattroff(status_win, COLOR_PAIR(3) | A_BOLD | A_DIM);}
}

void refresh_all_win(){
    wnoutrefresh(stdscr);
    wnoutrefresh(title_win);
    wnoutrefresh(status_win);
    wnoutrefresh(last_command_win);
    wnoutrefresh(listbar_win);
    wnoutrefresh(menu_win);
    wnoutrefresh(output_win);
    wnoutrefresh(command_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}

void resize_handler() {
    endwin();

    if (is_term_resized(LINES, COLS)) {
        resize_term(LINES, COLS);
    }

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    delete_windows();
    create_windows(rows, cols);

    draw_ui(rows, cols);
}