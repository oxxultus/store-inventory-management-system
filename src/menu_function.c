#include "menu_function.h"

// 1. 입고 관리 (등록/추가, 삭제, 조회)
void func_purchase_register(){
    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 입고 등록/추가를 진행중입니다... ");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 바코드, 수량, 입고단가, 카테고리ID를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);

    // ESC 공통 종료 부분
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
    
    // 1. console_win에 사용법 출력 및 안내

    // 2. [호출] 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 3. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[입고 등록 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 INSERT 로직 추가 후 결과 출력 필요

        // console_win에 성공 로그 출력
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 등록 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [입고 관리] 데이터베이스 INSERT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 등록 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
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

    // ESC 공통 종료 부분
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
    
    // 1. 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 2. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[입고 등록 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 DELETE 로직 추가 후 결과 출력 필요

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 삭제 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [입고 관리] 데이터베이스 DELETE 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 삭제 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
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

    // ESC 공통 종료 부분
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
    
    // 1. 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 2. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[입고 수정 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 MODIFY 로직 추가 후 결과 출력 필요

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 수정 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [입고 관리] 데이터베이스 MODIFY 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(tooltip_win);
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 수정 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
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
        mvwaddwstr(output_win, 5, 6, L"* 을 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        mvwaddwstr(output_win, 6, 2, L"- 특정 값을 찾는 경우: ");
        mvwaddwstr(output_win, 7, 6, L"컬럼명, 검색값 을 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        mvwaddwstr(output_win, 8, 2, L"- 조건으로 값을 찾는 경우: ");
        mvwaddwstr(output_win, 9, 6, L"컬럼명, 조건, 조건값 을 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);

    // ESC 공통 종료 부분
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
    
    // 1. 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 2. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[입고 조회 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 SELECT 로직 추가 후 결과 출력 필요

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 조회 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [입고 조회] 데이터베이스 SELECT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 조회 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}

// 2. 재고 관리
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

    // ESC 공통 종료 부분
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
    
    // 3. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[재고 등록 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 INSERT 로직 추가 후 결과 출력 필요

        // console_win에 성공 로그 출력
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 등록 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [재고 관리] 데이터베이스 INSERT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 등록 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
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

    // ESC 공통 종료 부분
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
    
    // 1. 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 2. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[재고 삭제 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 DELETE 로직 추가 후 결과 출력 필요

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 삭제 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [재고 관리] 데이터베이스 DELETE 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(tooltip_win);
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 삭제 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
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

    // ESC 공통 종료 부분
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
    
    // 1. 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 2. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[재고 수정 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 MODIFY 로직 추가 후 결과 출력 필요

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 수정 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [재고 관리] 데이터베이스 MODIFY 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 수정 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
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

    // ESC 공통 종료 부분
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
    
    // 1. 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 2. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[재고 검색 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 SELECT 로직 추가 후 결과 출력 필요

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 검색 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [재고 관리] 데이터베이스 SELECT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(tooltip_win);
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 조회 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(tooltip_win);
    wnoutrefresh(console_win);
    doupdate();
}

// 3. 상품 관리
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

    // ESC 공통 종료 부분
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
    
    // 3. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[상품 등록 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 INSERT 로직 추가 후 결과 출력 필요

        // console_win에 성공 로그 출력
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 등록 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 관리] 데이터베이스 INSERT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 등록 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
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

    // ESC 공통 종료 부분
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
    
    // 1. 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 2. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[상품 등록 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 DELETE 로직 추가 후 결과 출력 필요

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 삭제 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 관리] 데이터베이스 DELETE 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 삭제 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
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

    // ESC 공통 종료 부분
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
    
    // 1. 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 2. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[상품 수정 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 MODIFY 로직 추가 후 결과 출력 필요

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 수정 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 관리] 데이터베이스 MODIFY 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(tooltip_win);
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 수정 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
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

    // ESC 공통 종료 부분
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
    
    // 1. 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 2. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[상품 검색 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 SELECT 로직 추가 후 결과 출력 필요

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 검색 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 관리] 데이터베이스 SELECT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(tooltip_win);
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 조회 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}


// 4. 제조업체 관리
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

    // ESC 공통 종료 부분
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
    
    // 1. console_win에 사용법 출력 및 안내

    // 2. [호출] 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 3. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[제조업체 등록 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 INSERT 로직 추가 후 결과 출력 필요

        // console_win에 성공 로그 출력
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 등록 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [제조업체 관리] 데이터베이스 INSERT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(tooltip_win);
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 등록 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
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

    // ESC 공통 종료 부분
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
    
    // 1. 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 2. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[제조업체 삭제 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 DELETE 로직 추가 후 결과 출력 필요

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 삭제 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [제조업체 관리] 데이터베이스 DELETE 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 삭제 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
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

    // ESC 공통 종료 부분
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
    
    // 1. 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 2. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[제조업체 수정 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 MODIFY 로직 추가 후 결과 출력 필요

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 수정 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [제조업체 관리] 데이터베이스 MODIFY 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(tooltip_win);
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 수정 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(tooltip_win);
    wnoutrefresh(console_win);
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

    // ESC 공통 종료 부분
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
    
    // 1. 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 2. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[제조업체 검색 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 SELECT 로직 추가 후 결과 출력 필요

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 검색 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [제조업체 관리] 데이터베이스 SELECT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 조회 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}

// 5. 카테고리 관리
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

    // ESC 공통 종료 부분
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
    
    // 1. console_win에 사용법 출력 및 안내

    // 2. [호출] 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 3. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[카테고리 등록 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 INSERT 로직 추가 후 결과 출력 필요

        // console_win에 성공 로그 출력
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 카테고리 등록 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [카테고리 관리] 데이터베이스 INSERT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(tooltip_win);
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 카테고리 등록 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
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

    // ESC 공통 종료 부분
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
    
    // 1. 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 2. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[카테고리 삭제 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 DELETE 로직 추가 후 결과 출력 필요

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 카테고리 삭제 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [카테고리 관리] 데이터베이스 DELETE 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 카테고리 삭제 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
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

    // ESC 공통 종료 부분
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
    
    // 1. 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 2. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[카테고리 수정 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 MODIFY 로직 추가 후 결과 출력 필요

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 카테고리 수정 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [카테고리 관리] 데이터베이스 MODIFY 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 제조업체 수정 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(tooltip_win);
    wnoutrefresh(console_win);
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

    // ESC 공통 종료 부분
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
    
    // 1. 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // 2. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[카테고리 검색 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 데이터베이스 SELECT 로직 추가 후 결과 출력 필요

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 카테고리 검색 트랜잭션 준비 완료: %ls", input_buffer_w);
        wscrl(console_win, 1);
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [카테고리 관리] 데이터베이스 SELECT 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        werase(tooltip_win);
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);
        werase(tooltip_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 카테고리 조회 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate();
}

// 상품 판매
void func_cart_print(){
    display_cart_items_noInfo();
}
void func_cart_input(){

    if (sales_input_flag==1){ // 이미 장바구니에 상품이 추가된 상태에서 재진입 시 안내문구 출력
        display_cart_items();

    } else { // 최초 진입 시 안내문구 출력
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
    
    // ESC 공통 종료 안내 부분
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
    
    // 장바구니 상품 입력 함수 호출
    g_prev_num_items = NUM_ITEMS;
    input_success = get_wide_string_cart_input(command_win, input_buffer_w, max_len);
    
    // command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0);
    wnoutrefresh(command_win);

    if (input_success) {
        display_cart_items();

        // console_win에 성공 로그 출력
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
    
    // 5. UI 최종 갱신
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
            mvwaddwstr(output_win, 1, 2, L"[!] 장바구니 내여 삭제를 진행중입니다...");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
            mvwaddwstr(output_win, 4, 2, L"- 장바구니 내의 INDEX를 입력받아 해당 카테고리 기록을 삭제합니다.");
            mvwaddwstr(output_win, 5, 2, L"- 아래 입력 창에서 INDEX를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        wnoutrefresh(output_win);

        // ESC 공통 종료 부분
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
        
        // 1. 입력 루프 시작
        while (1) {
            input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

            if (input_success == 0) { // ESC 등으로 입력을 취소했을 경우
                delete_index = -1;
                break; 
            }

            // 3. 와이드 문자열을 일반 문자열 및 정수로 변환
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
                continue; // 재입력
            }

            // 4. 숫자 변환 및 유효성 검사
            
            // 문자열이 비어있는지 또는 숫자가 아닌 문자가 포함되어 있는지 검사 (선택적)
            // 여기서는 간단하게 atoi만 사용하며, 모든 오류는 범위 검사에서 처리한다고 가정
            
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
                continue; // 재입력
            }

            // 5. 유효성 검사 통과: 인덱스 저장 및 루프 탈출
            delete_index = index_to_check;
            break;
        }
        
        // 2. command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
        werase(command_win);
        box(command_win, 0, 0); 
        wnoutrefresh(command_win);

        if (input_success) {
            // [Enter 로직] 입력 완료 및 output_win 출력
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
            // [ESC 로직] 입력 취소
            werase(output_win);
            werase(tooltip_win);

            wscrl(console_win, 1);
            wmove(console_win, CONSOLE_HEIGHT - 2, 1);
            if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            wprintw(console_win, " [LOG] [상품 판매] 장바구니 상품 삭제 입력이 취소되었습니다.");
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        }
    }else{
        // 로그 출력
        wscrl(console_win, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 삭제 할 장바구니 내역이 존재하지 않습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wnoutrefresh(console_win);
                
        // output_win 피드백
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[!] 삭제할 장바구니 내역이 존재하지 않습니다.");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    }
    

    // 5. UI 최종 갱신
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

        // ESC 공통 종료 부분
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

        // --- 변수 선언 ---
        wchar_t input_buffer_w[256] = {0}; 
        int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
        int input_success = 0;
        
        // --- 입력 루프 시작 ---
        while (1) {
            input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

            if (input_success == 0) { // ESC 등으로 입력을 취소했을 경우
                break; 
            }

            // 3. 와이드 문자열을 일반 문자열로 변환
            char mb_buffer[256] = {0};
            // 최대 4글자(YES, NO)만 받으므로 size를 작게 지정해도 됨.
            if (wcstombs(mb_buffer, input_buffer_w, sizeof(mb_buffer)) == (size_t)-1) { 
                goto log_error_and_continue;
            }

            // 4. 입력 문자열 유효성 검사 (Y/y/YES/yes 확인)
            
            // trim_whitespace 함수가 외부에서 정의되어 있다고 가정하고 사용
            char *trimmed_input = trim_whitespace(mb_buffer); 
            
            if (strcmp(trimmed_input, "Y") == 0 || strcmp(trimmed_input, "y") == 0 || 
                strcmp(trimmed_input, "YES") == 0 || strcmp(trimmed_input, "yes") == 0) {
                
                // 유효성 검사 통과: 초기화 진행
                input_success = 2; // 진행 플래그 (1:ESC, 2:Y입력)
                break;
                
            } else if (strcmp(trimmed_input, "N") == 0 || strcmp(trimmed_input, "n") == 0 ||
                    strcmp(trimmed_input, "NO") == 0 || strcmp(trimmed_input, "no") == 0) {
                
                // 유효성 검사 통과: 초기화 중단
                input_success = 0; // 중단은 ESC와 동일하게 0으로 처리하여 루프 탈출
                break;
                
            } else {
                // 유효하지 않은 입력
                log_error_and_continue:
                wscrl(console_win, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [초기화] [ERROR] 잘못된 입력입니다. Y 또는 N을 입력하세요.");
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
                wnoutrefresh(console_win);
                continue; // 재입력
            }
        }
        
        // 2. command_win 정리
        werase(command_win);
        box(command_win, 0, 0); 
        wnoutrefresh(command_win);
        
        // --- 최종 처리 및 결과 출력 ---
        if (input_success == 2) { // 'Y' 입력 (초기화 진행)
            
            free_cart_items(); 
            
            // 로그 출력
            wscrl(console_win, 1);
            if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD); } // 성공 시 더 밝게
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [초기화] 장바구니 초기화가 완료되었습니다. (모든 상품 삭제)");
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD); }

            // output_win 피드백
            werase(output_win);
            box(output_win, 0, 0);
            if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
                mvwaddwstr(output_win, 1, 2, L"[!] 장바구니가 초기화되었습니다.");
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
            
        } else { // ESC 또는 'N' 입력 (중단)
            
            // 로그 출력
            wscrl(console_win, 1);
            if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [초기화] 장바구니 초기화가 사용자 요청으로 중단되었습니다.");
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            wnoutrefresh(console_win);
            
            // output_win 피드백
            werase(output_win);
            if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
                box(output_win, 0, 0);
                mvwaddwstr(output_win, 1, 2, L"[!] 장바구니 초기화가 중단되었습니다.");
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        }
    }else{
    // 로그 출력
        wscrl(console_win, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [초기화] 초기화 할 장바구니 내역이 존재하지 않습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wnoutrefresh(console_win);
                
        // output_win 피드백
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[!] 삭제할 장바구니 내역이 존재하지 않습니다.");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    }

    // 공통 정리
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

        // ESC 공통 종료 부분
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

        // --- 변수 선언 ---
        wchar_t input_buffer_w[256] = {0}; 
        int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
        int input_success = 0;
        
        // --- 입력 루프 시작 ---
        while (1) {
            input_success = get_wide_string_input(command_win, input_buffer_w, max_len);

            if (input_success == 0) { // ESC 등으로 입력을 취소했을 경우
                break; 
            }

            // 3. 와이드 문자열을 일반 문자열로 변환
            char mb_buffer[256] = {0};
            // 최대 4글자(YES, NO)만 받으므로 size를 작게 지정해도 됨.
            if (wcstombs(mb_buffer, input_buffer_w, sizeof(mb_buffer)) == (size_t)-1) { 
                goto log_error_and_continue;
            }

            // 4. 입력 문자열 유효성 검사 (Y/y/YES/yes 확인)
            
            // trim_whitespace 함수가 외부에서 정의되어 있다고 가정하고 사용
            char *trimmed_input = trim_whitespace(mb_buffer); 
            
            if (strcmp(trimmed_input, "Y") == 0 || strcmp(trimmed_input, "y") == 0 || 
                strcmp(trimmed_input, "YES") == 0 || strcmp(trimmed_input, "yes") == 0) {
                
                // 유효성 검사 통과: 초기화 진행
                input_success = 2; // 진행 플래그 (1:ESC, 2:Y입력)
                break;
                
            } else if (strcmp(trimmed_input, "N") == 0 || strcmp(trimmed_input, "n") == 0 ||
                    strcmp(trimmed_input, "NO") == 0 || strcmp(trimmed_input, "no") == 0) {
                
                // 유효성 검사 통과: 초기화 중단
                input_success = 0; // 중단은 ESC와 동일하게 0으로 처리하여 루프 탈출
                break;
                
            } else {
                // 유효하지 않은 입력
                log_error_and_continue:
                wscrl(console_win, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [ERROR] 잘못된 입력입니다. Y 또는 N을 입력하세요.");
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
                wnoutrefresh(console_win);
                continue; // 재입력
            }
        }
        
        // 2. command_win 정리
        werase(command_win);
        box(command_win, 0, 0); 
        wnoutrefresh(command_win);
        
        // --- 최종 처리 및 결과 출력 ---
        if (input_success == 2) { // 'Y' 입력 (결제 진행)
            // 영수증 정보 출력
            display_cart_checkout();

            // TODO: 장바구니의 내용을 자동으로 판매와 판매 상세정보 테이블에 입력하는 로직 필요


            // 장바구니 내역 초기화
            free_cart_items();
            
            // 로그 출력
            wscrl(console_win, 1);
            if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD); } // 성공 시 더 밝게
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 장바구니 내역 결제가 완료되었습니다.");
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD); }
            wscrl(console_win, 1);

            if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD); } // 성공 시 더 밝게
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 영수증 처리가 성공적으로 저장되었습니다.");
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD); }
            
        } else { // ESC 또는 'N' 입력 (중단)
            
            // 로그 출력
            wscrl(console_win, 1);
            if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 장바구니 내역 결제가 사용자 요청으로 중단되었습니다.");
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            wnoutrefresh(console_win);
            
            // output_win 피드백
            werase(output_win);
            if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
                box(output_win, 0, 0);
                mvwaddwstr(output_win, 1, 2, L"[!] 장바구니 내역 결제가 중단되었습니다.");
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        }
    }else{
        // 장바구니에 상품이 없는 경우
        wscrl(console_win, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 장바구니 내역 결제가 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wnoutrefresh(console_win);
                
        // output_win 피드백
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[!] 장바구니에 먼저 상품을 담아주세요. ");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    }

    // 공통 정리
    werase(tooltip_win);
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
}


// 재사용 가능한 와이드 문자열 입력 함수
int get_wide_string_input(WINDOW *win, wchar_t *buffer, int max_len) {

    wint_t wch;
    int index = 0;
    int input_success = 0;
    int start_x = 14; // "입력 > " 뒤 (1행, 9열)

    // 입력 필드 초기화
    werase(win);

    if (has_colors()) wattron(win, COLOR_PAIR(1));
    box(win, 0, 0);
    if (has_colors()) wattroff(win, COLOR_PAIR(1));

    if (has_colors()) {wattron(win, COLOR_PAIR(1) | A_BOLD); }
    mvwaddwstr(win, 1, 2, L"[!] 입력 > ");
    if (has_colors()) {wattroff(win, COLOR_PAIR(1) | A_BOLD); }
    
    noecho(); 
    curs_set(1); // 커서 보이기
    
    nodelay(win, TRUE); 
    wmove(win, 1, start_x); 

    // 핵심 입력 처리 루프
    while (1) {
        doupdate();
        int result = wget_wch(win, &wch); 
        
        if (result == ERR) {
            continue;
        }

        if (wch == 27) { // ESC 키 감지 (취소)
            input_success = 0;
            break;
        } 
        else if (wch == 10 || wch == '\n') { // ENTER 키 감지 (완료)
            buffer[index] = L'\0'; 
            input_success = 1;
            break;
        }
        else if (wch == KEY_BACKSPACE || wch == 127) { // Backspace 처리
            if (index > 0) {
                index--; 

                // 1. 현재 커서 위치 (지울 문자 시작 위치) 계산
                int current_cursor_x = start_x;
                for (int i = 0; i < index; i++) {
                    current_cursor_x += wcwidth(buffer[i]); 
                }
                
                // 2. 지우기: 공백으로 덮어쓰고 커서 되돌림
                wmove(win, 1, current_cursor_x); 
                for (int j = 0; j < wcwidth(buffer[index]); j++) { // 지울 너비만큼 공백
                    waddch(win, ' ');
                }
                wmove(win, 1, current_cursor_x); 
                
                buffer[index] = L'\0'; // 버퍼에서도 삭제
            }
        }
        // 일반 와이드 문자 입력 처리
        else if (result == OK && wch != '\t' && wch != '\r' && index < max_len) { 
            if (wcwidth(wch) <= 0) continue; 

            // 1. 버퍼에 문자 저장
            buffer[index] = (wchar_t)wch; 
            
            // 2. 화면에 출력할 위치 계산
            int current_cursor_x = start_x;
            for (int i = 0; i < index; i++) {
                current_cursor_x += wcwidth(buffer[i]);
            }
            
            // 3. 출력 및 인덱스 증가
            wmove(win, 1, current_cursor_x);
            waddnwstr(win, &buffer[index], 1); // 1문자만 출력
            
            index++; 
        }
        
        wnoutrefresh(win); // 입력 창만 갱신
    }
    
    // 비차단 모드 해제 및 커서/에코 원복
    nodelay(win, FALSE); 
    curs_set(0);

    return input_success;
}

// 장바구니를 위해 엔터로 값을 입력받아 임시로 저장하는 함수
int get_wide_string_cart_input(WINDOW *win, wchar_t *buffer, int max_len) {
    
    wint_t wch;
    int index = 0;
    int input_success = 0;
    int start_x = 14; // "입력 > " 뒤 (1행, 9열)

    // 입력 필드 초기화
    werase(win);
    if (has_colors()) wattron(win, COLOR_PAIR(1));
    box(win, 0, 0);
    if (has_colors()) wattroff(win, COLOR_PAIR(1));

    if (has_colors()) {wattron(win, COLOR_PAIR(1) | A_BOLD); }
    mvwaddwstr(win, 1, 2, L"[!] 입력 > ");
    if (has_colors()) {wattroff(win, COLOR_PAIR(1) | A_BOLD); }
    
    noecho(); 
    curs_set(1); // 커서 보이기
    
    nodelay(win, TRUE); 
    wmove(win, 1, start_x); 

    // 핵심 입력 처리 루프
    while (1) {
        doupdate();
        int result = wget_wch(win, &wch); 
        
        if (result == ERR) {
            continue;
        }


        if (wch == 27) { // ESC 키 감지 (입력완료)
            int result = check_change_in_cart();
            wscrl(console_win, 1);
            wmove(console_win, CONSOLE_HEIGHT - 2, 1);
            if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
            wprintw(console_win, " [LOG] [상품 판매] 수량 변환 정보 비교결과: %d, 이전수량: %d ,현재수량: %d", result, g_prev_num_items, NUM_ITEMS);
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }

            if (has_colors()) wattron(console_win, COLOR_PAIR(7));
            box(console_win, 0, 0);
            if (has_colors()) wattroff(console_win, COLOR_PAIR(7));

            wnoutrefresh(console_win); // 즉시 갱신

            if(check_change_in_cart() == 0){
                // 장바구니에 변화가 없는 상태에서 ESC 입력 시 입력 취소 처리
                input_success = 0;
            } else {
                // 장바구니에 변화가 있는 상태에서 ESC 입력 시 입력 완료 처리
                input_success = 1;
            }

            break;
        }
        else if (wch == 10 || wch == '\n') { // ENTER 키 감지 (입력 진행)
            
            // (1) 와이드 문자열 유효성 확보 및 일반 문자열 변환
            buffer[index] = L'\0'; // 널 종료 문자 추가 (문자열 완성)
            
            // 와이드 버퍼를 일반 문자열 버퍼로 변환 (최대 100바이트 가정)
            char temp_mb_buffer[100];
            // wcstombs를 사용하여 wchar_t -> char 변환
            if (wcstombs(temp_mb_buffer, buffer, sizeof(temp_mb_buffer)) == (size_t)-1) {
                wscrl(console_win, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [ERROR] 문자열 변환 실패.");
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                if (has_colors()) wattron(console_win, COLOR_PAIR(1));
                box(console_win, 0, 0);
                if (has_colors()) wattroff(console_win, COLOR_PAIR(1));
                wnoutrefresh(console_win); // 즉시 갱신
                goto cleanup;
            }
            
            // 좌우 공백 제거 함수
            char *input_str = trim_whitespace(temp_mb_buffer); 

            // (2) 쉼표 (,) 개수 확인 및 파싱
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
                // wprintw(win, "\n[ERROR] 입력 형식이 잘못되었습니다 (바코드,수량 형식 필요)."); 
                wnoutrefresh(console_win); // 즉시 갱신
                goto cleanup;
            }
            
            // 쉼표를 기준으로 두 부분 분리
            *comma_ptr = '\0'; // 쉼표 위치를 널 문자로 대체하여 문자열을 두 개로 나눔
            char *barcode_str = trim_whitespace(input_str); // 바코드 부분 (const char* 로 사용)
            char *quantity_str = trim_whitespace(comma_ptr + 1); // 수량 부분

            
            // (3) 수량 문자열 유효성 및 정수 변환 확인
            if (strlen(quantity_str) == 0) {
                wscrl(console_win, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [ERROR] 수량이 입력되지 않았습니다.");
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                if (has_colors()) wattron(console_win, COLOR_PAIR(7));
                box(console_win, 0, 0);
                if (has_colors()) wattroff(console_win, COLOR_PAIR(7));
                wnoutrefresh(console_win); // 즉시 갱신
                // wprintw(win, "\n[ERROR] 수량이 입력되지 않았습니다.");
                goto cleanup;
            }
            
            int quantity = atoi(quantity_str); // 문자열을 정수로 변환
            
            if (quantity <= 0) {
                wscrl(console_win, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [ERROR] 수량은 1 이상의 정수여야 합니다.");
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                if (has_colors()) wattron(console_win, COLOR_PAIR(7));
                box(console_win, 0, 0);
                if (has_colors()) wattroff(console_win, COLOR_PAIR(7));
                wnoutrefresh(console_win); // 즉시 갱신
                goto cleanup;
            }
            
            // TODO: 추후 데이터베이스 연결필요 
            // (4) 상품 조회 및 장바구니 추가
            char item_name[50];
            double price_value; // 조회된 가격
            
            // TODO: 상품 조회 함수는 바코드 기반으로 이름과 가격을 조회하는 역할을 수행해야 함.
            // get_product_price 함수는 바코드 문자열을 인수로 받아야 합니다.
            int result = get_product_price(barcode_str, item_name, &price_value);

            if (result == 0) { //상품이 없는 경우 0을 반환한다고 가정
                wscrl(console_win, 1);
                wmove(console_win, CONSOLE_HEIGHT - 2, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                wprintw(console_win, " [LOG] [상품 판매] [ERROR] 상품 코드(%s)를 찾을 수 없습니다.", barcode_str);
                if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                if (has_colors()) wattron(console_win, COLOR_PAIR(7));
                box(console_win, 0, 0);
                if (has_colors()) wattroff(console_win, COLOR_PAIR(7));
                wnoutrefresh(console_win); // 즉시 갱신
                goto cleanup;
            }
            
            // 입력이 정상적이라면 장바구니에 바코드, 이름, 수량, 가격을 추가
            // 함수 시그니처: add_cart_item(const char *barcode, const char *name, int qty, double prc);
            add_cart_item(barcode_str, item_name, quantity, price_value);
        
        cleanup:
            // (5) 버퍼 및 입력 상태 초기화
            // 버퍼 초기화 (wchar_t 배열이므로 L'\0' 사용)
            for (int j = 0; j < max_len; j++) {
                buffer[j] = L'\0';
            }

            // 다음 입력을 받을 준비
            index = 0; // 인덱스 초기화
            
            // 입력 필드 초기화
            werase(win);
            if (has_colors()) wattron(win, COLOR_PAIR(1));
            box(win, 0, 0);
            if (has_colors()) wattroff(win, COLOR_PAIR(1));

            if (has_colors()) {wattron(win, COLOR_PAIR(1) | A_BOLD); }
            mvwaddwstr(win, 1, 2, L"[!] 입력 > ");
            if (has_colors()) {wattroff(win, COLOR_PAIR(1) | A_BOLD); }
            
            noecho(); 
            curs_set(1); // 커서 보이기

            wmove(win, 1, start_x); // 커서를 입력 시작 위치로 이동
        }
        else if (wch == KEY_BACKSPACE || wch == 127) { // Backspace 처리
            if (index > 0) {
                index--; 

                // 1. 현재 커서 위치 (지울 문자 시작 위치) 계산
                int current_cursor_x = start_x;
                for (int i = 0; i < index; i++) {
                    current_cursor_x += wcwidth(buffer[i]); 
                }
                
                // 2. 지우기: 공백으로 덮어쓰고 커서 되돌림
                wmove(win, 1, current_cursor_x); 
                for (int j = 0; j < wcwidth(buffer[index]); j++) { // 지울 너비만큼 공백
                    waddch(win, ' ');
                }
                wmove(win, 1, current_cursor_x); 
                
                buffer[index] = L'\0'; // 버퍼에서도 삭제
            }
        }
        // 일반 와이드 문자 입력 처리
        else if (result == OK && wch != '\t' && wch != '\r' && index < max_len) { 
            if (wcwidth(wch) <= 0) continue; 

            // 1. 버퍼에 문자 저장
            buffer[index] = (wchar_t)wch; 
            
            // 2. 화면에 출력할 위치 계산
            int current_cursor_x = start_x;
            for (int i = 0; i < index; i++) {
                current_cursor_x += wcwidth(buffer[i]);
            }
            
            // 3. 출력 및 인덱스 증가
            wmove(win, 1, current_cursor_x);
            waddnwstr(win, &buffer[index], 1); // 1문자만 출력
            
            index++; 
        }
        
        wnoutrefresh(win); // 입력 창만 갱신
    }
    
    // 비차단 모드 해제 및 커서/에코 원복
    nodelay(win, FALSE);
    curs_set(0);

    return input_success;
}