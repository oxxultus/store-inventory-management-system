#include "menu_function.h"

void func_purchase_register(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 입고 등록/추가를 진행중입니다... ");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 바코드, 입고수량, 입고단가, 카테고리ID, 상품명칭을 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        mvwaddwstr(output_win, 5, 2, L"[카테고리ID]");
        mvwaddwstr(output_win, 6, 2, L"(1:패션/의류) (2:잡화/액세서리) (3:뷰티/화장품) (4:식품/신선) (5:가전/디지털)");
        mvwaddwstr(output_win, 7, 2, L"(6:가구/인테리어) (7:생활/주방) (8:스포츠/레저) (9:유아/출산) (10:도서/음반/미디어)");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        int rows, cols;
        box(tooltip_win, 0, 0);
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);

    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[입고 등록 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        int insert_result=inbound_insert(input_buffer_w);
        if( insert_result == 0){
            werase(output_win);
            werase(tooltip_win);

            wscrl(console_win, 1);
            wmove(console_win, CONSOLE_HEIGHT - 2, 1);
            if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            wprintw(console_win, " [LOG] [데이터베이스] 값이 올바르지 않아 입고 등록 입력이 취소되었습니다.");
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }

            wnoutrefresh(output_win);
            wnoutrefresh(console_win);
            wnoutrefresh(tooltip_win);
            doupdate();
            return;
        }

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 등록 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [입고 관리] 데이터베이스 INSERT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 등록 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}
void func_purchase_delete(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 입고 삭제를 진행중입니다...");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 입고ID를 입력받아 해당 입고 기록을 삭제합니다.");
        mvwaddwstr(output_win, 5, 2, L"- 아래 입력 창에서 입고ID를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        int rows, cols;
        box(tooltip_win, 0, 0);
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);


    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[입고 등록 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        int insert_result=inbound_delete(input_buffer_w);
        if( insert_result == 0){
            werase(output_win);
            werase(tooltip_win);

            wscrl(console_win, 1);
            wmove(console_win, CONSOLE_HEIGHT - 2, 1);
            if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            wprintw(console_win, " [LOG] [데이터베이스] 값이 올바르지 않아 삭제가 취소되었습니다.");
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }

            wnoutrefresh(output_win);
            wnoutrefresh(console_win);
            wnoutrefresh(tooltip_win);
            doupdate();
            return;
        }

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 삭제 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [입고 관리] 데이터베이스 DELETE 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 삭제 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}
void func_purchase_modify(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 입고 수정를 진행중입니다...");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 입고ID를 입력받아 해당 입고 기록을 수정합니다.");
        mvwaddwstr(output_win, 5, 2, L"- 입고ID, 상품ID, 제조업체ID, 카테고리ID, 입고일자, 입고수량, 입고단가");
        mvwaddwstr(output_win, 6, 2, L"를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        mvwaddwstr(output_win, 7, 2, L"- 입고ID를 제외한 수정하지 않을 항목은 '@'를 입력하세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        int rows, cols;
        box(tooltip_win, 0, 0);
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);


    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[입고 수정 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        int insert_result=inbound_modify(input_buffer_w);
        if( insert_result == 0){
            werase(output_win);
            werase(tooltip_win);

            wscrl(console_win, 1);
            wmove(console_win, CONSOLE_HEIGHT - 2, 1);
            if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            wprintw(console_win, " [LOG] [데이터베이스] 값이 올바르지 않아 수정이 취소되었습니다.");
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }

            wnoutrefresh(output_win);
            wnoutrefresh(console_win);
            wnoutrefresh(tooltip_win);
            doupdate();
            return;
        }

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 수정 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [입고 관리] 데이터베이스 MODIFY 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(tooltip_win);
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 수정 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}
void func_purchase_query(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 입고 조회를 진행중입니다...");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 전체 조회를 원할 경우:");
        mvwaddwstr(output_win, 5, 6, L" 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        int rows, cols;
        box(tooltip_win, 0, 0);
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);


    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {

        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [입고 조회] 데이터베이스 SELECT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }

        LineBuffer print_buffer;

        int select_result=inbound_select(input_buffer_w);

        if(select_result == 0){
            werase(output_win);
            if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[입고 조회 실패 결과]");
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
            if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            werase(tooltip_win);
            wnoutrefresh(output_win);
            wnoutrefresh(console_win);
            wnoutrefresh(tooltip_win);
            doupdate();
            return;
        }


        werase(tooltip_win);
    } else {
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 조회 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}

void func_inventory_register(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 재고 등록/추가를 진행중입니다... ");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 상품ID, 현재수량, 최근입고일, 보관위치를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

      wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        int rows, cols;
        box(tooltip_win, 0, 0);
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);

    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[재고 등록 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 등록 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [재고 관리] 데이터베이스 INSERT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 등록 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}
void func_inventory_delete(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 재고 삭제를 진행중입니다...");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 재고ID를 입력받아 해당 재고 기록을 삭제합니다.");
        mvwaddwstr(output_win, 5, 2, L"- 아래 입력 창에서 재고ID를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

      wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        int rows, cols;
        box(tooltip_win, 0, 0);
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);


    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[재고 삭제 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 삭제 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [재고 관리] 데이터베이스 DELETE 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(tooltip_win);
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 삭제 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}
void func_inventory_modify(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 재고 수정를 진행중입니다...");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 재고ID를 입력받아 해당 입고 기록을 수정합니다.");
        mvwaddwstr(output_win, 5, 2, L"- 재고ID, 상품ID, 현재수량, 최근입고일, 보관위치");
        mvwaddwstr(output_win, 6, 2, L"를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        mvwaddwstr(output_win, 7, 2, L"- 재고ID를 제외한 수정하지 않을 항목은 '@'를 입력하세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        int rows, cols;
        box(tooltip_win, 0, 0);
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);


    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[재고 수정 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 수정 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [재고 관리] 데이터베이스 MODIFY 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 수정 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}
void func_inventory_query(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 재고 조회를 진행중입니다...");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 전체 조회를 원할 경우:");
        mvwaddwstr(output_win, 5, 6, L"* 을 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        mvwaddwstr(output_win, 6, 2, L"- 특정 값을 찾는 경우: ");
        mvwaddwstr(output_win, 7, 6, L"컬럼명, 검색값 을 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        mvwaddwstr(output_win, 8, 2, L"- 조건으로 값을 찾는 경우: ");
        mvwaddwstr(output_win, 9, 6, L"컬럼명, 조건, 조건값 을 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        int rows, cols;
        box(tooltip_win, 0, 0);
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);


    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[재고 검색 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 검색 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [재고 관리] 데이터베이스 SELECT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(tooltip_win);
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 조회 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(tooltip_win);
    wnoutrefresh(console_win);
    doupdate();
}

void func_product_register(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 상품 등록/추가를 진행중입니다... ");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 상품ID, 카테고리ID, 상품명, 판매가격, 바코드");
        mvwaddwstr(output_win, 5, 2, L"를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        int rows, cols;
        box(tooltip_win, 0, 0);
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);

    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[상품 등록 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 등록 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 관리] 데이터베이스 INSERT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 등록 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(tooltip_win);
    wnoutrefresh(console_win);
    doupdate();
}
void func_product_delete(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 상품 삭제를 진행중입니다...");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 상품ID를 입력받아 해당 상품 기록을 삭제합니다.");
        mvwaddwstr(output_win, 5, 2, L"- 아래 입력 창에서 상품ID를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        int rows, cols;
        box(tooltip_win, 0, 0);
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);


    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[상품 등록 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 삭제 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 관리] 데이터베이스 DELETE 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 삭제 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}
void func_product_modify(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 상품 수정를 진행중입니다...");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 상품ID를 입력받아 해당 상품을 수정합니다.");
        mvwaddwstr(output_win, 5, 2, L"- 상품ID, 카테고리ID, 상품명, 판매가격, 바코드");
        mvwaddwstr(output_win, 6, 2, L"를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        mvwaddwstr(output_win, 7, 2, L"- 상품ID를 제외한 수정하지 않을 항목은 '@'를 입력하세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        int rows, cols;
        box(tooltip_win, 0, 0);
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);


    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[상품 수정 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 수정 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 관리] 데이터베이스 MODIFY 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(tooltip_win);
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 수정 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}
void func_product_query(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 상품 조회를 진행중입니다...");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 전체 조회를 원할 경우:");
        mvwaddwstr(output_win, 5, 6, L"* 을 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        mvwaddwstr(output_win, 6, 2, L"- 특정 값을 찾는 경우: ");
        mvwaddwstr(output_win, 7, 6, L"컬럼명, 검색값 을 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        mvwaddwstr(output_win, 8, 2, L"- 조건으로 값을 찾는 경우: ");
        mvwaddwstr(output_win, 9, 6, L"컬럼명, 조건, 조건값 을 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        int rows, cols;
        box(tooltip_win, 0, 0);
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);


    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[상품 검색 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 검색 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 관리] 데이터베이스 SELECT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(tooltip_win);
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 조회 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}

void func_supplier_register(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 제조업체 등록/추가를 진행중입니다... ");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 제조업체ID, 제조업체명, 연락처, 담당자명를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        int rows, cols;
        box(tooltip_win, 0, 0);
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);

    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[제조업체 등록 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 등록 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [제조업체 관리] 데이터베이스 INSERT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(tooltip_win);
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 등록 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}
void func_supplier_delete(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 제조업체 삭제를 진행중입니다...");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 제조업체ID를 입력받아 해당 제조업체 기록을 삭제합니다.");
        mvwaddwstr(output_win, 5, 2, L"- 아래 입력 창에서 제조업체ID를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        int rows, cols;
        box(tooltip_win, 0, 0);
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);


    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[제조업체 삭제 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 삭제 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [제조업체 관리] 데이터베이스 DELETE 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 삭제 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}
void func_supplier_modify(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 제조업체 수정를 진행중입니다...");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 제조업체ID를 입력받아 해당 입고 기록을 수정합니다.");
        mvwaddwstr(output_win, 5, 2, L"- 제조업체ID, 제조업체명, 연락처, 담당자명");
        mvwaddwstr(output_win, 6, 2, L"를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        mvwaddwstr(output_win, 7, 2, L"- 제조업체ID를 제외한 수정하지 않을 항목은 '@'를 입력하세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        int rows, cols;
        box(tooltip_win, 0, 0);
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);


    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[제조업체 수정 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 수정 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [제조업체 관리] 데이터베이스 MODIFY 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(tooltip_win);
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 수정 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}
void func_supplier_query(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 제조업체 조회를 진행중입니다...");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 전체 조회를 원할 경우:");
        mvwaddwstr(output_win, 5, 6, L"* 을 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        mvwaddwstr(output_win, 6, 2, L"- 특정 값을 찾는 경우: ");
        mvwaddwstr(output_win, 7, 6, L"컬럼명, 검색값 을 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        mvwaddwstr(output_win, 8, 2, L"- 조건으로 값을 찾는 경우: ");
        mvwaddwstr(output_win, 9, 6, L"컬럼명, 조건, 조건값 을 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        int rows, cols;
        box(tooltip_win, 0, 0);
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);


    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[제조업체 검색 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 검색 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [제조업체 관리] 데이터베이스 SELECT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 조회 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}

void func_category_register(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 카테고리 등록/추가를 진행중입니다... ");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 카테고리ID, 카테고리명를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);

    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[카테고리 등록 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 카테고리 등록 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [카테고리 관리] 데이터베이스 INSERT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(tooltip_win);
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 카테고리 등록 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}
void func_category_delete(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 카테고리 삭제를 진행중입니다...");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 카테고리ID를 입력받아 해당 카테고리 기록을 삭제합니다.");
        mvwaddwstr(output_win, 5, 2, L"- 아래 입력 창에서 카테고리ID를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);


    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[카테고리 삭제 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 카테고리 삭제 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [카테고리 관리] 데이터베이스 DELETE 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 카테고리 삭제 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}
void func_category_modify(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 카테고리 수정를 진행중입니다...");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 카테고리ID를 입력받아 해당 입고 기록을 수정합니다.");
        mvwaddwstr(output_win, 5, 2, L"- 카테고리ID, 카테고리명를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        mvwaddwstr(output_win, 6, 2, L"- 카테고리ID를 제외한 수정하지 않을 항목은 '@'를 입력하세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);


    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[카테고리 수정 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 카테고리 수정 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [카테고리 관리] 데이터베이스 MODIFY 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 제조업체 수정 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}
void func_category_query(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 카테고리 조회를 진행중입니다...");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 전체 조회를 원할 경우:");
        mvwaddwstr(output_win, 5, 6, L"* 을 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        mvwaddwstr(output_win, 6, 2, L"- 특정 값을 찾는 경우: ");
        mvwaddwstr(output_win, 7, 6, L"컬럼명, 검색값 을 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        mvwaddwstr(output_win, 8, 2, L"- 조건으로 값을 찾는 경우: ");
        mvwaddwstr(output_win, 9, 6, L"컬럼명, 조건, 조건값 을 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);


    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[카테고리 검색 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 카테고리 검색 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [카테고리 관리] 데이터베이스 SELECT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 카테고리 조회 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}

void func_cart_print(){
    display_cart_items_scroll();
}
void func_cart_input(){

    if (sales_input_flag==1){
        display_cart_items_addinfo();

    } else {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[!] 장바구니 상품 등록을 진행중입니다... ");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
            mvwaddwstr(output_win, 4, 2, L"- 바코드, 수량 를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
            mvwaddwstr(output_win, 5, 2, L"- 🅴 🅽 🆃 🅴 🆁 를 누를 때 마다 장바구니에 상품이 추가 됩니다.");
            mvwaddwstr(output_win, 6, 2, L"- 🅴 🆂 🅲 를 누르면 장바구니 입력이 종료됩니다.");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    }
    wnoutrefresh(output_win);

    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        box(tooltip_win, 0, 0);
        int rows, cols;
        getmaxyx(tooltip_win, rows, cols);
        mvwaddwstr(tooltip_win, 1, cols/2-34, L" 🅴 🅽 🆃 🅴 🆁 ");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2-23, L"를 누르면 항목 추가,");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        mvwaddwstr(tooltip_win, 1, cols/2-3, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(tooltip_win, 1, cols/2+4, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(tooltip_win);

    wchar_t input_buffer_w[256] = {0};
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    g_prev_num_items = NUM_ITEMS;
    input_success = get_wide_string_cart_input(command_win, input_buffer_w, max_len);

    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        display_cart_items_addinfo();

        wscrl(console_win, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 장바구니에 상품 추가 완료");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
        werase(output_win);
    } else {
        werase(tooltip_win);
        werase(output_win);
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 판매] 장바구니 등록 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }

    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}
void func_cart_delete(){

    if(sales_input_flag == 1){

        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[!] 장바구니 내역 삭제를 진행중입니다...");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
            mvwaddwstr(output_win, 4, 2, L"- 장바구니 내의 INDEX를 입력받아 해당 장바구니 기록을 삭제합니다.");
            mvwaddwstr(output_win, 5, 2, L"- 아래 입력 창에서 INDEX를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        wnoutrefresh(output_win);

        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
            int rows, cols;
            getmaxyx(tooltip_win, rows, cols);
            box(tooltip_win, 0 ,0 );
            mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        wnoutrefresh(tooltip_win);


        wchar_t input_buffer_w[256] = {0};
        int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
        int input_success = 0;
        int delete_index = -1;
        int index;

        while (1) {
            input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

            if (input_success == 0) {
                delete_index = -1;
                break;
            }

            char mb_buffer[256] = {0};
            if (wcstombs(mb_buffer, input_buffer_w, sizeof(mb_buffer)) == (size_t)-1) {
                wscrl(console_win, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [ERROR] 잘못된 문자열 입력입니다. 다시 입력하세요.");
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
                if (has_colors()) {wattron(console_win, COLOR_PAIR(7) | A_BOLD); }
                    box(console_win,0,0);
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(7) | A_BOLD); }
                wnoutrefresh(console_win);
                continue;
            }

            int index_to_check = atoi(mb_buffer);

            if (index_to_check < 0 || index_to_check >= NUM_ITEMS) {
                wscrl(console_win, 1);
                wmove(console_win, CONSOLE_HEIGHT - 2, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
                wprintw(console_win, " [LOG] [상품 판매] [ERROR] 인덱스 (%d)가 유효 범위를 벗어났습니다. (0 ~ %d)", index_to_check, NUM_ITEMS - 1);
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
                if (has_colors()) {wattron(console_win, COLOR_PAIR(7) | A_BOLD); }
                    box(console_win,0,0);
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(7) | A_BOLD); }
                wnoutrefresh(console_win);
                continue;
            }

            delete_index = index_to_check;
            break;
        }

        werase(command_win);
        box(command_win, 0, 0);
        wnoutrefresh(command_win);

        if (input_success) {
            display_cart_items_deleteinfo(delete_index);

            wscrl(console_win, 1);
            if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
            mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 장바구니 상품 삭제 로직 실행");
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }

            int result = delete_cart_item(delete_index);
            if(result == 1){
                wscrl(console_win, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                    mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 장바구니 상품 삭제가 완료되었습니다.");
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
            }else{
                wscrl(console_win, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
                    mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 장바구니 상품 삭제가 실패하였습니다.");
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            }

            werase(tooltip_win);
        } else {
            werase(output_win);
            werase(tooltip_win);

            wscrl(console_win, 1);
            wmove(console_win, CONSOLE_HEIGHT - 2, 1);
            if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            wprintw(console_win, " [LOG] [상품 판매] 장바구니 상품 삭제 입력이 취소되었습니다.");
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        }
    }else{
        wscrl(console_win, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 삭제 할 장바구니 내역이 존재하지 않습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wnoutrefresh(console_win);

        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[!] 삭제할 장바구니 내역이 존재하지 않습니다.");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    }


    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}
void func_cart_reset(){
    if(sales_input_flag == 1){
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[!] 장바구니 초기화를 진행중입니다...");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
            mvwaddwstr(output_win, 4, 2, L"- 장바구니의 모든 상품을 삭제합니다.");
            mvwaddwstr(output_win, 5, 2, L"- 아래 입력 창에서 Y혹은N 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
            mvwaddwstr(output_win, 6, 2, L"- 진행: Y, y, YES, yes");
            mvwaddwstr(output_win, 7, 2, L"- 중단: N, n, NO, no");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        wnoutrefresh(output_win);

        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
            int rows, cols;
            getmaxyx(tooltip_win, rows, cols);
            box(tooltip_win, 0 ,0 );
            mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        wnoutrefresh(tooltip_win);

        wchar_t input_buffer_w[256] = {0};
        int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
        int input_success = 0;

        while (1) {
            input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

            if (input_success == 0) {
                break;
            }

            char mb_buffer[256] = {0};
            if (wcstombs(mb_buffer, input_buffer_w, sizeof(mb_buffer)) == (size_t)-1) {
                goto log_error_and_continue;
            }

            char *trimmed_input = trim_whitespace(mb_buffer);

            if (strcmp(trimmed_input, "Y") == 0 || strcmp(trimmed_input, "y") == 0 ||
                strcmp(trimmed_input, "YES") == 0 || strcmp(trimmed_input, "yes") == 0) {

                input_success = 2;
                break;

            } else if (strcmp(trimmed_input, "N") == 0 || strcmp(trimmed_input, "n") == 0 ||
                    strcmp(trimmed_input, "NO") == 0 || strcmp(trimmed_input, "no") == 0) {

                input_success = 0;
                break;

            } else {
                log_error_and_continue:
                wscrl(console_win, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [초기화] [ERROR] 잘못된 입력입니다. Y 또는 N을 입력하세요.");
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
                wnoutrefresh(console_win);
                continue;
            }
        }

        werase(command_win);
        box(command_win, 0, 0);
        wnoutrefresh(command_win);

        if (input_success == 2) {

            free_cart_items();

            wscrl(console_win, 1);
            if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [초기화] 장바구니 초기화가 완료되었습니다. (모든 상품 삭제)");
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD); }

            werase(output_win);
            box(output_win, 0, 0);
            if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
                mvwaddwstr(output_win, 1, 2, L"[!] 장바구니가 초기화되었습니다.");
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }

        } else {
            wscrl(console_win, 1);
            if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [초기화] 장바구니 초기화가 사용자 요청으로 중단되었습니다.");
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            wnoutrefresh(console_win);

            werase(output_win);
            if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
                box(output_win, 0, 0);
                mvwaddwstr(output_win, 1, 2, L"[!] 장바구니 초기화가 중단되었습니다.");
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        }
    }else{
        wscrl(console_win, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [초기화] 초기화 할 장바구니 내역이 존재하지 않습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wnoutrefresh(console_win);

        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[!] 삭제할 장바구니 내역이 존재하지 않습니다.");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    }

    werase(tooltip_win);
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
}
void func_cart_checkout(){
    if(sales_input_flag == 1){
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[!] 장바구니 내열 결제를 진행중입니다...");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
            mvwaddwstr(output_win, 4, 2, L"- 장바구니의 모든 상품을 결제하여 영수증 처리 합니다.");
            mvwaddwstr(output_win, 5, 2, L"- 아래 입력 창에서 Y혹은 N을 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
            mvwaddwstr(output_win, 6, 2, L"- 진행: Y, y, YES, yes");
            mvwaddwstr(output_win, 7, 2, L"- 중단: N, n, NO, no");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        wnoutrefresh(output_win);

        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
            int rows, cols;
            getmaxyx(tooltip_win, rows, cols);
            box(tooltip_win, 0 ,0 );
            mvwaddwstr(tooltip_win, 1, cols/2-18, L" 🅴 🆂 🅲");
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(tooltip_win, 1, cols/2-11, L"를 누르면 입력이 종료됩니다.");
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        wnoutrefresh(tooltip_win);

        wchar_t input_buffer_w[256] = {0};
        int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
        int input_success = 0;

        while (1) {
            input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

            if (input_success == 0) {
                break;
            }

            char mb_buffer[256] = {0};
            if (wcstombs(mb_buffer, input_buffer_w, sizeof(mb_buffer)) == (size_t)-1) {
                goto log_error_and_continue;
            }

            char *trimmed_input = trim_whitespace(mb_buffer);

            if (strcmp(trimmed_input, "Y") == 0 || strcmp(trimmed_input, "y") == 0 ||
                strcmp(trimmed_input, "YES") == 0 || strcmp(trimmed_input, "yes") == 0) {

                input_success = 2;
                break;

            } else if (strcmp(trimmed_input, "N") == 0 || strcmp(trimmed_input, "n") == 0 ||
                    strcmp(trimmed_input, "NO") == 0 || strcmp(trimmed_input, "no") == 0) {

                input_success = 0;
                break;

            } else {
                log_error_and_continue:
                wscrl(console_win, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [ERROR] 잘못된 입력입니다. Y 또는 N을 입력하세요.");
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
                wnoutrefresh(console_win);
                continue;
            }
        }

        werase(command_win);
        box(command_win, 0, 0);
        wnoutrefresh(command_win);

        if (input_success == 2) {
            display_checkout_items_scroll();

            double grand_total = calculate_total_cart_amount();
            const char *payment = "CARD";

            char *sale_number_str = insert_sale_record(grand_total, payment);

            if (strcmp(sale_number_str, "-1") == 0) {
                wscrl(console_win, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD); }
                    mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [ERROR] 판매 기록 생성 실패. 데이터베이스 추가 작업을 중지합니다.");
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD); }
            } else {

                char final_sale_num[16];
                int item_insert_result = 1;

                strcpy(final_sale_num, sale_number_str);

                for (int i = 0; i < NUM_ITEMS; i++) {

                    const char *barcode = cartitems[i].barcode;
                    int quantity = cartitems[i].quantity;
                    double price = cartitems[i].price;

                    item_insert_result = insert_sale_detail_item(
                        final_sale_num,
                        barcode,
                        quantity,
                        price
                    );

                    if (item_insert_result == -1) {

                        wscrl(console_win, 1);
                        wmove(console_win,-2, 1);
                        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD); }
                            wprintw(console_win, " [LOG] [ERROR] 항목(%s) 삽입 중 DB 오류 발생. 결제 중단.", barcode);
                        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD); }

                        break;
                    }
                }

                if (item_insert_result == 1) {
                    wscrl(console_win, 1);
                    if (has_colors()) {wattron(console_win, COLOR_PAIR(3) | A_BOLD); }
                        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 장바구니 내역 결제가 완료되었습니다.");
                    if (has_colors()) {wattroff(console_win, COLOR_PAIR(3) | A_BOLD); }

                    wscrl(console_win, 1);
                    if (has_colors()) {wattron(console_win, COLOR_PAIR(3) | A_BOLD); }
                        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 영수증 처리가 성공적으로 저장되었습니다.");
                    if (has_colors()) {wattroff(console_win, COLOR_PAIR(3) | A_BOLD); }

                    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
                        box(output_win, 0, 0);
                        mvwaddwstr(output_win, 1, 2, L"[!] 장바구니 내역 결제가 완료되었습니다.");
                    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
                }
            }

            free_cart_items();

        } else {
            wscrl(console_win, 1);
            if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 장바구니 내역 결제가 사용자 요청으로 중단되었습니다.");
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            wnoutrefresh(console_win);

            werase(output_win);
            if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
                box(output_win, 0, 0);
                mvwaddwstr(output_win, 1, 2, L"[!] 장바구니 내역 결제가 중단되었습니다.");
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        }
    }else{
        wscrl(console_win, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 장바구니 내역 결제가 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wnoutrefresh(console_win);

        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[!] 장바구니에 먼저 상품을 담아주세요. ");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    }

    werase(tooltip_win);
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
}