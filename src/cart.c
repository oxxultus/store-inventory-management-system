#include "cart.h"

CartItems *cartitems = NULL;
int NUM_ITEMS = 0;
int g_prev_num_items = 0;
int modify_carttiems_index = -1;

void add_cart_item(const char *barcode, const char *name, int qty, double prc) {

    int found_index = -1;
    for (int i = 0; i < NUM_ITEMS; i++) {
        if (strncmp(cartitems[i].barcode, barcode, sizeof(cartitems[i].barcode)) == 0) {
            found_index = i;
            break;
        }
    }

    if (found_index != -1) {

        cartitems[found_index].quantity += qty;
        cartitems[found_index].price = prc;

        modify_carttiems_index = found_index;

        sales_input_flag = 1;

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(3) | A_BOLD); }
        wprintw(console_win, " [LOG] [상품 판매] [바코드: %s] '%s' 수량 (%d)이 장바구니에서 증가됨 (총 %d개)",
                barcode, name, qty, NUM_ITEMS);
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(3) | A_BOLD); }

    } else {

        int new_item_index = NUM_ITEMS;

        CartItems *temp_cartitems = (CartItems *)realloc(
            cartitems,
            (NUM_ITEMS + 1) * sizeof(CartItems)
        );

        if (temp_cartitems == NULL) {
            return;
        }

        cartitems = temp_cartitems;

        strncpy(cartitems[new_item_index].barcode, barcode, sizeof(cartitems[new_item_index].barcode) - 1);
        cartitems[new_item_index].barcode[sizeof(cartitems[new_item_index].barcode) - 1] = '\0';

        strncpy(cartitems[new_item_index].name, name, sizeof(cartitems[new_item_index].name) - 1);
        cartitems[new_item_index].name[sizeof(cartitems[new_item_index].name) - 1] = '\0';

        cartitems[new_item_index].quantity = qty;
        cartitems[new_item_index].price = prc;

        NUM_ITEMS++;

        modify_carttiems_index = new_item_index;

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 판매] [바코드: %s] '%s' 항목이 장바구니에 추가됨 (총 %d개)", barcode, name, NUM_ITEMS);
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    }

    sales_input_flag = 1;

    if (has_colors()) wattron(console_win, COLOR_PAIR(7));
    box(console_win, 0, 0);
    if (has_colors()) wattroff(console_win, COLOR_PAIR(7));
    display_cart_items_addinfo();
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
}

int check_change_in_cart(){
    if(g_prev_num_items == NUM_ITEMS){
        return 0;
    }
    return 1;
}

void free_cart_items() {
    if (cartitems != NULL) {
        free(cartitems);
        cartitems = NULL;
        NUM_ITEMS = 0;
        sales_input_flag = 0;
        g_prev_num_items = 0;
        modify_carttiems_index = -1;
    }
}

void display_cart_items_scroll() {

    int start_y_offset = 3;
    int max_rows, max_cols;
    getmaxyx(output_win, max_rows, max_cols);

    int output_rows = max_rows - 6;
    if (output_rows <= 0) output_rows = 1;

    int start_line_index = 0;
    int ch;
    int max_page_start_index;
    int total_data_lines;
    int total_pages;

    LineBuffer print_buffer;
    init_buffer(&print_buffer);

    add_line(&print_buffer, "%-5s %-10s %-20s %8s %10s",
             "Idx", "바코드", "상품명", "수량", "합계 금액");
    add_line(&print_buffer, "----- -------------------- -------------------- -------- ----------");

    if (NUM_ITEMS > 0) {
        for (int i = 0; i < NUM_ITEMS; i++) {
            double total_price = cartitems[i].quantity * cartitems[i].price;
            char item_line[MAX_LINE_LENGTH];

            snprintf(item_line, MAX_LINE_LENGTH, "[%d] %-10s %-20s %8d %10.2f",
                     i, cartitems[i].barcode, cartitems[i].name,
                     cartitems[i].quantity, total_price);

            if(i == modify_carttiems_index && check_change_in_cart() == 1 && modify_carttiems_index != -1){
                 strcat(item_line, " [+ 추가됨]");
            }

            add_line(&print_buffer, "%s", item_line);
        }

        double grand_total = calculate_total_cart_amount();
        add_line(&print_buffer, "--------------------------------------------------------------------");
        add_line(&print_buffer, "장바구니 내역 금액: KRW %.2f", grand_total);
    } else {
        add_line(&print_buffer, "장바구니가 비어 있습니다.");
    }

    total_data_lines = print_buffer.count - 2;

    if (total_data_lines > output_rows) {
        max_page_start_index = print_buffer.count - output_rows;
        total_pages = (total_data_lines + output_rows - 1) / output_rows;
    } else {
        max_page_start_index = 0;
        total_pages = 1;
    }

    nodelay(command_win, FALSE);
    keypad(command_win, TRUE);
    curs_set(0);

    while (1) {
        werase(output_win);

        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwprintw(output_win, 1, 2, "[장바구니 상품 내역] - (총 %d 항목)", NUM_ITEMS);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }

        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
            mvwprintw(output_win, 3, 2, "%s", print_buffer.lines[0]);
            mvwprintw(output_win, 4, 2, "%s", print_buffer.lines[1]);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }

        int current_y = 5;

        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            int page_info_y = 1;
            int page_info_x = max_cols - 20;
            if (total_pages > 1) {
                 mvwprintw(output_win, page_info_y, page_info_x, "페이지: %d / %d",
                           (start_line_index / output_rows) + 1,
                           total_pages);
            }
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        for (int i = 0; i < output_rows; i++) {
            int buffer_index = 2 + start_line_index + i;
            if (buffer_index >= print_buffer.count) break;

            const char *line = print_buffer.lines[buffer_index];
            mvwprintw(output_win, current_y++, 2, "%s", line);
        }

        if (has_colors()) {wattron(listbar_win, COLOR_PAIR(1) | A_BOLD); }
            box(listbar_win, 0, 0);
        if (has_colors()) {wattron(listbar_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
            int rows, cols;
            getmaxyx(tooltip_win, rows, cols);
            mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
            box(tooltip_win, 0, 0);
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 출력이 종료됩니다.");
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        werase(command_win);
        if (has_colors()) {wattron(command_win, COLOR_PAIR(1) | A_BOLD); }
            box(command_win, 0, 0);
            mvwaddwstr(command_win, 1, 2, L"[!] 키보드 명령 대기중 (스크롤 화면)");
        if (has_colors()) {wattroff(command_win, COLOR_PAIR(1) | A_BOLD); }

        wnoutrefresh(output_win);
        wnoutrefresh(tooltip_win);
        wnoutrefresh(listbar_win);
        wnoutrefresh(command_win);
        doupdate();

        ch = wgetch(command_win);

        switch (ch) {
            case KEY_LEFT:
                if (start_line_index > 0) {
                    start_line_index -= output_rows;
                    if (start_line_index < 0) start_line_index = 0;
                }
                break;

            case KEY_RIGHT:
                if (start_line_index < max_page_start_index) {
                    start_line_index += output_rows;
                    if (start_line_index > max_page_start_index) {
                        start_line_index = max_page_start_index;
                    }
                }
                break;

            case 27:
                goto exit_loop;

            default:
                break;
        }
    }

exit_loop:
    clear_buffer(&print_buffer);

    nodelay(command_win, TRUE);
    keypad(command_win, FALSE);
    curs_set(0);

    werase(output_win);
    werase(tooltip_win);
    werase(listbar_win);
    werase(command_win);
    doupdate();
}

void display_checkout_items_scroll() {

    int start_y_offset = 3;
    int max_rows, max_cols;
    getmaxyx(output_win, max_rows, max_cols);

    int output_rows = max_rows - 6;
    if (output_rows <= 0) output_rows = 1;

    int start_line_index = 0;
    int ch;
    int max_page_start_index;
    int total_data_lines;
    int total_pages;

    LineBuffer print_buffer;
    init_buffer(&print_buffer);

    add_line(&print_buffer, "%-5s %-10s %-20s %8s %10s",
             "Idx", "바코드", "상품명", "수량", "합계 금액");
    add_line(&print_buffer, "----- -------------------- -------------------- -------- ----------");

    if (NUM_ITEMS > 0) {
        for (int i = 0; i < NUM_ITEMS; i++) {
            double total_price = cartitems[i].quantity * cartitems[i].price;
            char item_line[MAX_LINE_LENGTH];

            snprintf(item_line, MAX_LINE_LENGTH, "[%d] %-10s %-20s %8d %10.2f",
                     i, cartitems[i].barcode, cartitems[i].name,
                     cartitems[i].quantity, total_price);
            add_line(&print_buffer, "%s", item_line);
        }

        double grand_total = calculate_total_cart_amount();
        add_line(&print_buffer, "--------------------------------------------------------------------");
        add_line(&print_buffer, "결제 내역 금액: KRW %.2f", grand_total);
    } else {
        add_line(&print_buffer, "장바구니가 비어 있습니다.");
    }

    total_data_lines = print_buffer.count - 2;

    if (total_data_lines > output_rows) {
        max_page_start_index = print_buffer.count - output_rows;
        total_pages = (total_data_lines + output_rows - 1) / output_rows;
    } else {
        max_page_start_index = 0;
        total_pages = 1;
    }

    nodelay(command_win, FALSE);
    keypad(command_win, TRUE);
    curs_set(0);

    while (1) {
        werase(output_win);

        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwprintw(output_win, 1, 2, "[결제 내역] - (총 %d 항목)", NUM_ITEMS);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }

        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
            mvwprintw(output_win, 3, 2, "%s", print_buffer.lines[0]);
            mvwprintw(output_win, 4, 2, "%s", print_buffer.lines[1]);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }

        int current_y = 5;

        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            int page_info_y = 1;
            int page_info_x = max_cols - 20;
            if (total_pages > 1) {
                 mvwprintw(output_win, page_info_y, page_info_x, "페이지: %d / %d",
                           (start_line_index / output_rows) + 1,
                           total_pages);
            }
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        for (int i = 0; i < output_rows; i++) {
            int buffer_index = 2 + start_line_index + i;
            if (buffer_index >= print_buffer.count) break;

            const char *line = print_buffer.lines[buffer_index];
            mvwprintw(output_win, current_y++, 2, "%s", line);
        }

        if (has_colors()) {wattron(listbar_win, COLOR_PAIR(1) | A_BOLD); }
            box(listbar_win, 0, 0);
        if (has_colors()) {wattron(listbar_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
            int rows, cols;
            getmaxyx(tooltip_win, rows, cols);
            mvwaddwstr(tooltip_win, 1, cols/2-21, L" 🅴 🅽 🆃 🅴 🆁 ");
            box(tooltip_win, 0, 0);
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(tooltip_win, 1, cols/2-10, L"를 누르면 결제가 완료됩니다.");
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        werase(command_win);
        if (has_colors()) {wattron(command_win, COLOR_PAIR(1) | A_BOLD); }
            box(command_win, 0, 0);
            mvwaddwstr(command_win, 1, 2, L"[!] 좌우 버튼으로 스크롤 해서 영수증을 확인하세요. (◀ ▶ 스크롤)");
        if (has_colors()) {wattroff(command_win, COLOR_PAIR(1) | A_BOLD); }

        wnoutrefresh(output_win);
        wnoutrefresh(tooltip_win);
        wnoutrefresh(listbar_win);
        wnoutrefresh(command_win);
        doupdate();

        ch = wgetch(command_win);

        switch (ch) {
            case KEY_LEFT:
                if (start_line_index > 0) {
                    start_line_index -= output_rows;
                    if (start_line_index < 0) start_line_index = 0;
                }
                break;

            case KEY_RIGHT:
                if (start_line_index < max_page_start_index) {
                    start_line_index += output_rows;
                    if (start_line_index > max_page_start_index) {
                        start_line_index = max_page_start_index;
                    }
                }
                break;

            case 10:
                goto exit_loop;

            default:
                break;
        }
    }

exit_loop:
    clear_buffer(&print_buffer);

    nodelay(command_win, TRUE);
    keypad(command_win, FALSE);
    curs_set(0);

    werase(output_win);
    werase(tooltip_win);
    werase(listbar_win);
    werase(command_win);
    doupdate();
}

void display_cart_items_addinfo() {

    werase(output_win);
    int max_rows, max_cols;
    getmaxyx(output_win, max_rows, max_cols);

    int output_rows = max_rows - 6;
    if (output_rows <= 0) output_rows = 1;

    int current_y = 5;


    if (NUM_ITEMS == 0) {
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[장바구니 상품 내역]");
            if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
                mvwaddwstr(output_win, 1, 22, L" - 장바구니가 비어 있습니다.");
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }

        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
            int rows, cols;
            box(tooltip_win, 0, 0);
            getmaxyx(tooltip_win, rows, cols);
            mvwaddwstr(tooltip_win, 1, cols/4-6, L" 장바구니 상품 추가");
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(tooltip_win, 1, cols/4+13, L"을 통해 상품을 추가해주세요.");
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        wnoutrefresh(tooltip_win);

        wnoutrefresh(output_win);
        return;
    }

    int focus_offset = output_rows / 2;

    int start_index = modify_carttiems_index - focus_offset;

    if (start_index < 0) {
        start_index = 0;
    }
    if (start_index + output_rows > NUM_ITEMS) {
        start_index = NUM_ITEMS - output_rows;
        if (start_index < 0) start_index = 0;
    }

    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[장바구니 상품 내역]");
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            if (sales_input_flag == 1) {
                mvwaddwstr(output_win, 1, 22, L" - 바코드, 수량 를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
            }
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }

    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
        mvwprintw(output_win, 3, 2, "%-5s %-10s %-20s %8s %8s",
          "Idx", "바코드", "상품명", "수량", "단가");
        mvwprintw(output_win, 4, 2, "----- -------------------- -------------------- -------- --------");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }


    for (int i = 0; i < output_rows; i++) {
        int item_index = start_index + i;

        if (item_index >= NUM_ITEMS) {
            break;
        }

        mvwprintw(output_win, current_y, 2, "[%d]", item_index);

        if (item_index == modify_carttiems_index && sales_input_flag == 1){
            if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_REVERSE); }
            int rows_win, cols_win;
            getmaxyx(output_win, rows_win, cols_win);
            mvwaddwstr(output_win, current_y, cols_win-12, L"[+ 변경됨]");
        }

        double total_price = cartitems[item_index].quantity * cartitems[item_index].price;

        mvwprintw(output_win, current_y++, 7,
                "%-10s %-20s %8d %8.2f (합: %.2f)",
                cartitems[item_index].barcode,
                cartitems[item_index].name,
                cartitems[item_index].quantity,
                cartitems[item_index].price,
                total_price);

        if (item_index == modify_carttiems_index && sales_input_flag == 1) {
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_REVERSE); }
        }
    }

    wnoutrefresh(output_win);
}

void display_cart_items_deleteinfo(int index) {

    werase(output_win);
    int max_rows, max_cols;
    getmaxyx(output_win, max_rows, max_cols);

    int output_rows = max_rows - 5;
    if (output_rows <= 0) output_rows = 1;

    int current_y = 5;

    if (NUM_ITEMS == 0) {
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[장바구니 상품 내역]");
            if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
                mvwaddwstr(output_win, 1, 22, L" - 장바구니가 비어 있습니다.");
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }

        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
            int rows, cols;
            box(tooltip_win, 0, 0);
            getmaxyx(tooltip_win, rows, cols);
            mvwaddwstr(tooltip_win, 1, cols/4-6, L" 장바구니 상품 추가");
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(tooltip_win, 1, cols/4+13, L"을 통해 상품을 추가해주세요.");
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        wnoutrefresh(tooltip_win);

        wnoutrefresh(output_win);
        return;
    }

    int focus_offset = output_rows / 2;
    int start_index = index - focus_offset;

    if (start_index < 0) start_index = 0;
    if (start_index + output_rows > NUM_ITEMS) {
        start_index = NUM_ITEMS - output_rows;
        if (start_index < 0) start_index = 0;
    }

    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[장바구니 상품 삭제 내역]");
        if (has_colors()) {wattron(output_win, COLOR_PAIR(4) | A_BOLD); }
            mvwprintw(output_win, 1, 28, " - [인덱스 %d] 항목이 삭제됩니다.", index);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(4) | A_BOLD); }

    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }

    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
        mvwprintw(output_win, 3, 2, "%-5s %-10s %-20s %8s %8s",
          "Idx", "바코드", "상품명", "수량", "단가");
        mvwprintw(output_win, 4, 2, "----- -------------------- -------------------- -------- --------");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }


    for (int i = 0; i < output_rows; i++) {
        int item_index = start_index + i;

        if (item_index >= NUM_ITEMS) {
            break;
        }

        if (item_index == index) {
            if (has_colors()) {wattron(output_win, COLOR_PAIR(4) | A_BOLD | A_REVERSE); }
            mvwaddwstr(output_win, current_y, 2, L"[-]");
            int rows_win, cols_win;
            getmaxyx(output_win, rows_win, cols_win);
            mvwaddwstr(output_win, current_y, cols_win - 12, L"[- 제거됨]");
        }else if(item_index > index){
            mvwprintw(output_win, current_y, 2, "[%d]", item_index-1);
        }else{
            mvwprintw(output_win, current_y, 2, "[%d]", item_index);
        }

        double total_price = cartitems[item_index].quantity * cartitems[item_index].price;

        mvwprintw(output_win, current_y++, 7,
                "%-10s %-20s %8d %8.2f (합: %.2f)",
                cartitems[item_index].barcode,
                cartitems[item_index].name,
                cartitems[item_index].quantity,
                cartitems[item_index].price,
                total_price);

        if (item_index == index) {
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(4) | A_BOLD | A_REVERSE); }
        }
    }

    wnoutrefresh(output_win);
}

int delete_cart_item(int index) {
    if (index < 0 || index >= NUM_ITEMS) {
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 올바르지 않은 인덱스 범위 입니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            if (has_colors()) {wattron(console_win, COLOR_PAIR(7) | A_BOLD); }
                box(console_win,0,0);
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(7) | A_BOLD); }
            wnoutrefresh(console_win);
        return 0;
    }

    g_prev_num_items = NUM_ITEMS;

    for (int i = index; i < NUM_ITEMS - 1; i++) {
        cartitems[i] = cartitems[i + 1];
    }

    NUM_ITEMS--;

    if (NUM_ITEMS == 0) {
        free_cart_items();
        wscrl(console_win, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 장바구니가 비어 메모리를 완전히 해제했습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        if (has_colors()) {wattron(console_win, COLOR_PAIR(7) | A_BOLD); }
            box(console_win,0,0);
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(7) | A_BOLD); }
        wnoutrefresh(console_win);
    } else {
        CartItems *temp_cartitems = (CartItems *)realloc(
            cartitems,
            NUM_ITEMS * sizeof(CartItems)
        );

        if (temp_cartitems != NULL) {
            cartitems = temp_cartitems;
        }
    }

    return 1;
}

void display_cart_checkout(){

    werase(output_win);
    int start_y = 3;

    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[최종 결제 영수증 내역]");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }

    int current_y = start_y;

    if (NUM_ITEMS == 0) {
        mvwaddwstr(output_win, current_y, 2, L"장바구니가 비어있습니다. 결제할 상품이 없습니다.");
    } else {

        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
            mvwprintw(output_win, current_y++, 2, "%-5s %-10s %-20s %8s %10s",
                      "Idx", "바코드", "상품명", "수량", "합계 금액");
            mvwprintw(output_win, current_y++, 2, "----- -------------------- -------------------- -------- ----------");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }

        for (int i = 0; i < NUM_ITEMS; i++) {

            double total_price = cartitems[i].quantity * cartitems[i].price;

            mvwprintw(output_win, current_y, 2, "[%d]", i);

            mvwprintw(output_win, current_y++, 7,
                      "%-10s %-20s %8d %10.2f",
                      cartitems[i].barcode,
                      cartitems[i].name,
                      cartitems[i].quantity,
                      total_price);
        }

        double grand_total = calculate_total_cart_amount();

        current_y += 2;

        mvwprintw(output_win, current_y++, 2, "--------------------------------------------------------------------");

        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            mvwprintw(output_win, current_y++, 2, "총 결제 금액:");
            mvwprintw(output_win, current_y, 50, "KRW %.2f", grand_total);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    }

    wnoutrefresh(output_win);
}

/**
 * @brief 장바구니에 있는 모든 항목의 총 합계 금액을 계산합니다.
 * @return double: 모든 상품 금액의 총합 (KRW)
 */
double calculate_total_cart_amount() {
    double grand_total = 0.0;

    if (cartitems == NULL || NUM_ITEMS == 0) {
        return 0.0;
    }

    for (int i = 0; i < NUM_ITEMS; i++) {
        double item_total = cartitems[i].quantity * cartitems[i].price;
        grand_total += item_total;
    }

    return grand_total;
}

/*
 * 장바구니 배열에서 특정 바코드의 현재 수량을 찾습니다.
 * @param barcode: 조회할 바코드 문자열
 * @return 현재 장바구니에 담긴 해당 상품의 수량. 없으면 0을 반환합니다.
 */
int get_current_cart_quantity(const char *barcode) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        if (strncmp(cartitems[i].barcode, barcode, sizeof(cartitems[i].barcode)) == 0) {
            return cartitems[i].quantity;
        }
    }
    return 0;
}