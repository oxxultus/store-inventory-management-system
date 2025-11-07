#include "menu_function.h"

// 1. 입고 관리 (등록/추가, 삭제, 조회)
// purchase_func.c - func_purchase_register 함수

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

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);

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
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 등록 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
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
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);


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
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 삭제 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
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
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);


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
    } else {
        // [ESC 로직] 입력 취소
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
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);


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
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 관리] 입고 조회 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
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

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);

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
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 등록 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
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
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);


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
    } else {
        // [ESC 로직] 입력 취소
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
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);


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
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 수정 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
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
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);


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
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [재고 관리] 재고 조회 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
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

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);

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
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 등록 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
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
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);


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
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 관리] 상품 삭제 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
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
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);


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
    } else {
        // [ESC 로직] 입력 취소
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
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);


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
    } else {
        // [ESC 로직] 입력 취소
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

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);

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
    } else {
        // [ESC 로직] 입력 취소
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
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);


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
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 삭제 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
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
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);


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
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 수정 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
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
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);


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
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [제조업체 관리] 제조업체 조회 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
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

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);

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
    } else {
        // [ESC 로직] 입력 취소
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
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);


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
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 카테고리 삭제 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
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
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);


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
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 제조업체 수정 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
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
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);


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
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [카테고리 관리] 카테고리 조회 입력이 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    doupdate();
}

// 상품 판매
void func_sales_input(){
    // TODO: 전역변수로 선언된 임시 장바구니 배열 필요
    // TODO: 장바구니 배열 초기화 필요

    werase(output_win);
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 장바구니 상품 등록을 진행중입니다... ");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 3, 2, L"[상세 입력 양식]");
        mvwaddwstr(output_win, 4, 2, L"- 바코드, 수량 (반복)를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        mvwaddwstr(output_win, 5, 2, L"- 여러개일 경우 바코드, 수량, 바코드, 수량 형식으로 입력하세요.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-11, L"를 누르면 입력이 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);

    wchar_t input_buffer_w[256] = {0}; 
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;
    
    // 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 2, 2, L"[장바구니 등록 내역]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");
            mvwaddwstr(output_win, 4, 2, input_buffer_w); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 입력된 내용을 기반으로 전역변수로 선언된 임시 장바구니 배열에 데이터 추가 로직 구현 필요
        
        sales_input_flag = 1; // 장바구니에 상품이 추가되었음을 표시


        // console_win에 성공 로그 출력
        wscrl(console_win, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 장바구니에 상품 추가 완료");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    } else {
        // [ESC 로직] 입력 취소
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
    doupdate();
}
void func_sales_checkout(){
    if(sales_input_flag == 0){
        // 장바구니에 상품이 없는 경우
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[!] 장바구니에 먼저 상품을 담아주세요. ");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        wprintw(console_win, " [LOG] [상품 판매] 결제가 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wnoutrefresh(console_win);
        wnoutrefresh(output_win);
        doupdate();
        return;
    }

    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[!] 결제를 진행중입니다... ");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }

    // ENTER 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        int rows, cols;
        getmaxyx(output_win, rows, cols);
        mvwaddwstr(output_win, 10, cols/2-20, L" 🅴 🅽 🆃 🅴 🆁");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 10, cols/2-9, L"를 누르면 결제가 진행됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

    // ESC 공통 종료 부분
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 11, cols/2-18, L" 🅴 🆂 🅲");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 11, cols/2-11, L"를 누르면 결제가 종료됩니다.");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    wnoutrefresh(output_win);

    wchar_t input_buffer_w[256] = {0}; 
    int max_len = sizeof(input_buffer_w) / sizeof(wchar_t);
    int input_success = 0;

    // 분리된 입력 함수 호출
    input_success = get_wide_string_input(command_win, input_buffer_w, max_len);
    
    // command_win 정리 (입력 함수에서 이미 처리되지만 안전을 위해)
    werase(command_win);
    box(command_win, 0, 0); 
    wnoutrefresh(command_win);

    if (input_success) {
        // [Enter 로직] 입력 완료 및 output_win 출력
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[결제 결과]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(output_win, 3, 2, L"- 입력된 내용:");

        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // TODO: 여기에 실제 결제 처리 로직 추가 후 데이터베이스 재고 감소 및 결과 출력 필요

        sales_input_flag = 0;

        // console_win에 성공 로그 출력
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 데이터베이스 MODIFY 로직 실행");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    } else {
        // [ESC 로직] 입력 취소
        werase(output_win);

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [상품 판매] 결제가 취소되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    }
    
    // 5. UI 최종 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(console_win);
    doupdate();
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