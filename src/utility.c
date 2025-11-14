#include "utility.h"

char* trim_whitespace(char *str) {
    char *end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0) return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
    return str;
}

int is_numeric(const char *str) {
    if (str == NULL || *str == '\0') return 0;
    while (*str) {
        if (!isdigit((unsigned char)*str) && *str != '.') {
            return 0;
        }
        str++;
    }
    return 1;
}

int get_user_input(WINDOW *win, char *buffer, int maxlen) {
    int ch;
    int index = 0;

    nodelay(win, TRUE);
    curs_set(1);
    echo();

    werase(win);
    box(win, 0, 0);
    mvwaddwstr(win, 1, 1, L"입력 > ");
    wmove(win, 1, 8);

    while (1) {
        ch = wgetch(win);

        if (ch == 27) {
            nodelay(win, FALSE);
            curs_set(0);
            noecho();
            return 0;
        }
        else if (ch == 10) {
            buffer[index] = '\0';
            nodelay(win, FALSE);
            curs_set(0);
            noecho();
            return 1;
        }
        else if (ch != ERR && index < maxlen - 1) {
        }

        doupdate();
    }
}

int get_wide_string_input(WINDOW *win, wchar_t *buffer, int max_len) {

    wint_t wch;
    int index = 0;
    int input_success = 0;
    int start_x = 14;

    werase(win);

    if (has_colors()) wattron(win, COLOR_PAIR(1));
    box(win, 0, 0);
    if (has_colors()) wattroff(win, COLOR_PAIR(1));

    if (has_colors()) {wattron(win, COLOR_PAIR(1) | A_BOLD); }
    mvwaddwstr(win, 1, 2, L"[!] 입력 > ");
    if (has_colors()) {wattroff(win, COLOR_PAIR(1) | A_BOLD); }

    noecho();
    curs_set(1);

    nodelay(win, TRUE);
    wmove(win, 1, start_x);

    while (1) {
        doupdate();
        int result = wget_wch(win, &wch);

        if (result == ERR) {
            continue;
        }

        if (wch == 27) {
            input_success = 0;
            break;
        }
        else if (wch == 10 || wch == '\n') {
            buffer[index] = L'\0';
            input_success = 1;
            break;
        }
        else if (wch == KEY_BACKSPACE || wch == 127) {
            if (index > 0) {
                index--;

                int current_cursor_x = start_x;
                for (int i = 0; i < index; i++) {
                    current_cursor_x += wcwidth(buffer[i]);
                }

                wmove(win, 1, current_cursor_x);
                for (int j = 0; j < wcwidth(buffer[index]); j++) {
                    waddch(win, ' ');
                }
                wmove(win, 1, current_cursor_x);

                buffer[index] = L'\0';
            }
        }
        else if (result == OK && wch != '\t' && wch != '\r' && index < max_len) {
            if (wcwidth(wch) <= 0) continue;

            buffer[index] = (wchar_t)wch;

            int current_cursor_x = start_x;
            for (int i = 0; i < index; i++) {
                current_cursor_x += wcwidth(buffer[i]);
            }

            wmove(win, 1, current_cursor_x);
            waddnwstr(win, &buffer[index], 1);

            index++;
        }

        wnoutrefresh(win);
    }

    nodelay(win, FALSE);
    curs_set(0);

    return input_success;
}

int get_wide_string_cart_input(WINDOW *win, wchar_t *buffer, int max_len) {


    wint_t wch;
    int index = 0;
    int input_success = 0;
    int start_x = 14;

    werase(win);
    if (has_colors()) wattron(win, COLOR_PAIR(1));
    box(win, 0, 0);
    if (has_colors()) wattroff(win, COLOR_PAIR(1));

    if (has_colors()) {wattron(win, COLOR_PAIR(1) | A_BOLD); }
    mvwaddwstr(win, 1, 2, L"[!] 입력 > ");
    if (has_colors()) {wattroff(win, COLOR_PAIR(1) | A_BOLD); }

    noecho();
    curs_set(1);

    nodelay(win, TRUE);
    wmove(win, 1, start_x);

    while (1) {
        doupdate();
        int result = wget_wch(win, &wch);

        if (result == ERR) {
            continue;
        }


        if (wch == 27) {
            int result = check_change_in_cart();
            wscrl(console_win, 1);
            wmove(console_win, CONSOLE_HEIGHT - 2, 1);
            if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
            wprintw(console_win, " [LOG] [상품 판매] 수량 변환 정보 비교결과: %d, 이전수량: %d ,현재수량: %d", result, g_prev_num_items, NUM_ITEMS);
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }

            if (has_colors()) wattron(console_win, COLOR_PAIR(7));
            box(console_win, 0, 0);
            if (has_colors()) wattroff(console_win, COLOR_PAIR(7));

            wnoutrefresh(console_win);

            if(check_change_in_cart() == 0){
                input_success = 0;
            } else {
                input_success = 1;
            }

            break;
        }
        else if (wch == 10 || wch == '\n') {
            buffer[index] = L'\0';

            char temp_mb_buffer[100];
            if (wcstombs(temp_mb_buffer, buffer, sizeof(temp_mb_buffer)) == (size_t)-1) {
                wscrl(console_win, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [ERROR] 문자열 변환 실패.");
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                if (has_colors()) wattron(console_win, COLOR_PAIR(1));
                box(console_win, 0, 0);
                if (has_colors()) wattroff(console_win, COLOR_PAIR(1));
                wnoutrefresh(console_win);
                goto cleanup;
            }

            char *input_str = trim_whitespace(temp_mb_buffer);

            char *comma_ptr = strchr(input_str, ',');
            int comma_count = 0;
            for (char *p = input_str; *p; p++) {
                if (*p == ',') comma_count++;
            }

            if (comma_count != 1 || comma_ptr == NULL) {
                wscrl(console_win, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [ERROR] 입력 형식이 잘못되었습니다 (바코드,수량 형식 필요).");
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                if (has_colors()) wattron(console_win, COLOR_PAIR(7));
                box(console_win, 0, 0);
                if (has_colors()) wattroff(console_win, COLOR_PAIR(7));
                wnoutrefresh(console_win);
                goto cleanup;
            }

            *comma_ptr = '\0';
            char *barcode_str = trim_whitespace(input_str);
            char *quantity_str = trim_whitespace(comma_ptr + 1);


            if (strlen(quantity_str) == 0) {
                wscrl(console_win, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [ERROR] 수량이 입력되지 않았습니다.");
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                if (has_colors()) wattron(console_win, COLOR_PAIR(7));
                box(console_win, 0, 0);
                if (has_colors()) wattroff(console_win, COLOR_PAIR(7));
                wnoutrefresh(console_win);
                goto cleanup;
            }

            int quantity = atoi(quantity_str);

            if (quantity <= 0) {
                wscrl(console_win, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [ERROR] 수량은 1 이상의 정수여야 합니다.");
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                if (has_colors()) wattron(console_win, COLOR_PAIR(7));
                box(console_win, 0, 0);
                if (has_colors()) wattroff(console_win, COLOR_PAIR(7));
                wnoutrefresh(console_win);
                goto cleanup;
            }


            char item_name[50];
            double price_value;

            int result = get_product_price(barcode_str, &quantity, item_name, &price_value);

            if (result == 0) {
                wscrl(console_win, 1);
                wmove(console_win, CONSOLE_HEIGHT - 2, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                wprintw(console_win, " [LOG] [상품 판매] [ERROR] 상품 코드(%s)를 찾을 수 없습니다.", barcode_str);
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                if (has_colors()) wattron(console_win, COLOR_PAIR(7));
                box(console_win, 0, 0);
                if (has_colors()) wattroff(console_win, COLOR_PAIR(7));
                wnoutrefresh(console_win);
                goto cleanup;
            } else if(result == -1){
                wscrl(console_win, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [ERROR] 남아있는 상품 재고가 부족합니다.");
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                if (has_colors()) wattron(console_win, COLOR_PAIR(7));
                box(console_win, 0, 0);
                if (has_colors()) wattroff(console_win, COLOR_PAIR(7));
                wnoutrefresh(console_win);
                goto cleanup;
            }

            add_cart_item(barcode_str, item_name, quantity, price_value);

        cleanup:
            for (int j = 0; j < max_len; j++) {
                buffer[j] = L'\0';
            }

            index = 0;

            werase(win);
            if (has_colors()) wattron(win, COLOR_PAIR(1));
            box(win, 0, 0);
            if (has_colors()) wattroff(win, COLOR_PAIR(1));

            if (has_colors()) {wattron(win, COLOR_PAIR(1) | A_BOLD); }
            mvwaddwstr(win, 1, 2, L"[!] 입력 > ");
            if (has_colors()) {wattroff(win, COLOR_PAIR(1) | A_BOLD); }

            noecho();
            curs_set(1);

            wmove(win, 1, start_x);
        }
        else if (wch == KEY_BACKSPACE || wch == 127) {
            if (index > 0) {
                index--;

                int current_cursor_x = start_x;
                for (int i = 0; i < index; i++) {
                    current_cursor_x += wcwidth(buffer[i]);
                }

                wmove(win, 1, current_cursor_x);
                for (int j = 0; j < wcwidth(buffer[index]); j++) {
                    waddch(win, ' ');
                }
                wmove(win, 1, current_cursor_x);

                buffer[index] = L'\0';
            }
        }
        else if (result == OK && wch != '\t' && wch != '\r' && index < max_len) {
            if (wcwidth(wch) <= 0) continue;

            buffer[index] = (wchar_t)wch;

            int current_cursor_x = start_x;
            for (int i = 0; i < index; i++) {
                current_cursor_x += wcwidth(buffer[i]);
            }

            wmove(win, 1, current_cursor_x);
            waddnwstr(win, &buffer[index], 1);

            index++;
        }

        wnoutrefresh(win);
    }

    nodelay(win, FALSE);
    curs_set(0);

    return input_success;
}