#include "ui.h"

// 전역 창 포인터 정의 (ui.h에서 extern으로 선언됨)
WINDOW *title_win = NULL;
WINDOW *status_win = NULL;
WINDOW *last_command_win = NULL;
WINDOW *menu_win = NULL;
WINDOW *output_win = NULL;
WINDOW *tooltip_win = NULL;
WINDOW *command_win = NULL;
WINDOW *console_win = NULL;


// --- [메뉴 그리기 함수] ---
void draw_menu() {
    if (has_colors()) {wattron(menu_win, COLOR_PAIR(7) | A_BOLD); }
    int i;
    Menu_Item *current_menu_list;
    
    // 1. 현재 상태에 따라 출력할 메뉴 리스트와 최대 항목 수를 설정합니다.
    if (current_state == STATE_MAIN_MENU) {
        current_menu_list = main_menu_items;
        current_max_items = MAX_MAIN_MENU_ITEMS; 
    } else if (current_state >= STATE_SUB_PURCHASE && current_state <= STATE_SUB_CATEGORY) {
        current_menu_list = sub_menu_template;
        current_max_items = MAX_SUB_MENU_ITEMS; 
    } else if (current_state == STATE_SUB_SALES) { 
        // ID 6 (상품 판매 메뉴: 상품 입력/결제 템플릿 사용)
        current_menu_list = sales_sub_menu;
        current_max_items = MAX_SALES_SUB_ITEMS; // <--- 상품 판매 항목 수 사용
    } else {
        // [수정된 로직] STATE_FUNCTION_RUNNING 상태일 경우:
        // 메뉴 선택은 막고(event_handler.c에서 처리), 창에는 비활성 상태임을 표시합니다.
        werase(menu_win);
        box(menu_win, 0, 0);
        mvwaddwstr(menu_win, 1, 1, L"--- 기능 실행 중 ---");
        mvwaddwstr(menu_win, 2, 1, L"[B]를 눌러 복귀하세요.");
        return;
    }
    
    // 메뉴 창을 지우고 테두리를 다시 그림
    werase(menu_win);
    box(menu_win, 0, 0); 
    
    // 메뉴 타이틀을 동적으로 가져옴
    mvwaddwstr(menu_win, 1, 2, get_current_menu_title()); 
    mvwaddwstr(menu_win, 2, 1, L"───────────────────────");

    // 메뉴 항목들을 순회하며 출력 
    for (i = 0; i < current_max_items; ++i) { 
        // 현재 선택된 항목에만 A_REVERSE (반전) 속성 적용
        if (i == current_menu_selection) {
            wattron(menu_win, A_REVERSE); 
        }

        // 메뉴 항목 출력 (3행부터 시작, 2열 들여쓰기)
        mvwaddwstr(menu_win, 3 + i, 2, current_menu_list[i].label);
        
        if (i == current_menu_selection) {
            wattroff(menu_win, A_REVERSE); 
        }
    }
    
    // 서브 메뉴일 경우 뒤로 가기 안내 추가
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


// --- [UI 코어 함수] ---

// Ncurses 초기화 및 로케일 설정 함수
void initialize_ncurses() {
    setlocale(LC_ALL, ""); 
    initscr();              
    cbreak();               
    noecho();               
    keypad(stdscr, TRUE);   
    curs_set(0);
    
    if (has_colors()) { 
        start_color();  
        // 1번 색상 쌍: 테두리 강조색 (파랑)
        init_pair(1, COLOR_BLUE, COLOR_BLACK);     // 1번 색상 쌍: 테두리 강조색 (파랑)
        init_pair(2, COLOR_YELLOW, COLOR_BLACK); // 2번 색상 쌍: 경고 메시지 (노랑)
        init_pair(3, COLOR_GREEN, COLOR_BLACK);  // 3번 색상 쌍: 성공 메시지 (초록)
        init_pair(4, COLOR_RED, COLOR_BLACK);    // 4번 색상 쌍: 오류 메시지 (빨강)
        init_pair(5, COLOR_CYAN, COLOR_BLACK);   // 5번 색상 쌍: 정보 메시지 (청록)
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK); // 6번 색상 쌍: 강조 메시지 (자홍)
        init_pair(7, COLOR_WHITE, COLOR_BLACK);  // 7번 색상 쌍: 기본 텍스트 (흰색)
    }
}

// 모든 창을 삭제하여 메모리 누수를 방지
void delete_windows() {
    if (title_win != NULL) delwin(title_win);
    if (status_win != NULL) delwin(status_win); 
    if (last_command_win != NULL) delwin(last_command_win); 
    if (command_win != NULL) delwin(command_win); 
    if (console_win != NULL) delwin(console_win);
    if (menu_win != NULL) delwin(menu_win);
    if (output_win != NULL) delwin(output_win);
    if (tooltip_win != NULL) delwin(tooltip_win);
    // 삭제 후 포인터 초기화 (안전성 확보)
    title_win = console_win = menu_win = output_win = status_win = command_win = last_command_win = tooltip_win = NULL;
}

// 각각의 창을 생성하는 부분 주어진 크기(rows, cols)에 맞춰 모든 창을 새로 생성
void create_windows(int rows, int cols) {
    // 모든 바(Bar)와 힌트 창이 차지하는 총 높이를 계산합니다.
    int total_fixed_height = TITLE_HEIGHT + STATUS_HEIGHT + COMMAND_HEIGHT + CONSOLE_HEIGHT;
    // 중앙 콘텐츠 영역이 사용할 수 있는 높이를 계산합니다.
    int content_height = rows - total_fixed_height;
    int output_width = cols - MENU_WIDTH;
    
    // 최소한의 공간을 확보하지 못하면 창을 만들지 않습니다.
    if (content_height < 1 || output_width < 1 || rows < total_fixed_height) {
        return;
    }
    
    int current_y = 0; // 현재 창이 시작될 y 좌표

    // 1. 상단 타이틀 (높이 3)
    title_win = newwin(TITLE_HEIGHT, cols, current_y, 0);
    current_y += TITLE_HEIGHT;

    // 2. DB 상태 창, 마지막 명령 실행 기록 창 (높이 3)
    status_win = newwin(STATUS_HEIGHT, MENU_WIDTH, current_y, 0);
    last_command_win = newwin(LAST_COMMAND_HEIGHT, output_width, current_y, MENU_WIDTH);
    current_y += STATUS_HEIGHT;

    // 3. 왼쪽 메뉴 및 오른쪽 출력 창 (높이: 중앙 영역)
    menu_win = newwin(content_height, MENU_WIDTH, current_y, 0);

    output_win = newwin(content_height-TOOLTIP_HEIGHT, output_width, current_y, MENU_WIDTH);
    scrollok(output_win, TRUE); // 출력 창 스크롤 활성화
    current_y += content_height;
    
    // 4. 명령 창 (높이 3)
    command_win = newwin(COMMAND_HEIGHT, cols, current_y, 0);
    // 툴팁 창 (높이 3)
    tooltip_win = newwin(TOOLTIP_HEIGHT, output_width, current_y-TOOLTIP_HEIGHT, MENU_WIDTH);
    current_y += COMMAND_HEIGHT;


    // 5. 콘솔/로그 창 (높이 8)
    console_win = newwin(CONSOLE_HEIGHT, cols, current_y, 0);
    scrollok(console_win, TRUE); // 콘솔 창 스크롤 활성화

    // 스크롤 영역을 테두리를 제외한 내부 전체 영역으로 설정
    // 윗 테두리(0행)와 아랫 테두리(7행)를 제외한 1행부터 6행까지 (총 6줄)
    wsetscrreg(console_win, 1, CONSOLE_HEIGHT - 2); // 1행부터 6행 (8 - 2)

    // 콘솔 창의 내용을 지우고, 커서를 맨 위 줄의 첫 열로 이동시킵니다.
    werase(console_win); 
    wmove(console_win, 1, 1); // 커서를 [내부]의 시작점(1행, 1열)으로 이동
}

// 모든 창의 테두리와 내용을 다시 그림
void draw_ui(int rows, int cols) {
    if (title_win == NULL || console_win == NULL) return;
    
    // 1. 모든 창에 테두리 그리기
    werase(stdscr); 
    //box(title_win, 0, 0);
    if (has_colors()) wattron(status_win, COLOR_PAIR(4));
    box(status_win, 0, 0); 
    if (has_colors()) wattroff(status_win, COLOR_PAIR(4));

    if (has_colors()) {wattron(last_command_win, COLOR_PAIR(7) | A_BOLD); }
    box(last_command_win, 0, 0);
    if (has_colors()) {wattroff(last_command_win, COLOR_PAIR(7) | A_BOLD); }

    // 커맨드 창 테두리 강조색 적용
    if (has_colors()) {wattron(last_command_win, COLOR_PAIR(7) | A_BOLD); }
    box(command_win, 0, 0);
    if (has_colors()) {wattroff(last_command_win, COLOR_PAIR(7) | A_BOLD); }

    box(console_win, 0, 0);

    box(output_win, 0, 0);

    box(tooltip_win, 0, 0);
    
    draw_menu(); // 메뉴 창 그리기 (테두리 및 내용 모두 처리)

    // 2. 제목 창 제목 출력
    mvwaddwstr(title_win, 1, 1, L"▗▄▄▄▖▗▖  ▗▖▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖▗▄▖ ▗▄▄▖▗▖  ▗▖    ▗▖  ▗▖ ▗▄▖ ▗▖  ▗▖ ▗▄▖  ▗▄▄▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖");
    mvwaddwstr(title_win, 2, 1, L"  █  ▐▛▚▖▐▌▐▌  ▐▌▐▌   ▐▛▚▖▐▌  █ ▐▌ ▐▌▐▌ ▐▌▝▚▞▘     ▐▛▚▞▜▌▐▌ ▐▌▐▛▚▖▐▌▐▌ ▐▌▐▌   ▐▌   ▐▛▚▞▜▌▐▌   ▐▛▚▖▐▌  █  ");
    mvwaddwstr(title_win, 3, 1, L"  █  ▐▌ ▝▜▌▐▌  ▐▌▐▛▀▀▘▐▌ ▝▜▌  █ ▐▌ ▐▌▐▛▀▚▖ ▐▌      ▐▌  ▐▌▐▛▀▜▌▐▌ ▝▜▌▐▛▀▜▌▐▌▝▜▌▐▛▀▀▘▐▌  ▐▌▐▛▀▀▘▐▌ ▝▜▌  █  ");
    mvwaddwstr(title_win, 4, 1, L"▗▄█▄▖▐▌  ▐▌ ▝▚▞▘ ▐▙▄▄▖▐▌  ▐▌  █ ▝▚▄▞▘▐▌ ▐▌ ▐▌      ▐▌  ▐▌▐▌ ▐▌▐▌  ▐▌▐▌ ▐▌▝▚▄▞▘▐▙▄▄▖▐▌  ▐▌▐▙▄▄▖▐▌  ▐▌  █  ");
    
    // 3. DB 상태 창 내용 출력
    if (has_colors()) {wattron(status_win, COLOR_PAIR(4) | A_BOLD); }
    mvwaddwstr(status_win, 1, 2, L"▮▮▯▯▯ ");
    if (has_colors()) {wattroff(status_win, COLOR_PAIR(4) | A_BOLD);}
    if (has_colors()) {wattron(status_win, COLOR_PAIR(4) | A_BOLD); }
    mvwaddwstr(status_win, 1, 8, L"Con");
    if (has_colors()) {wattroff(status_win, COLOR_PAIR(4) | A_BOLD);}
    if (has_colors()) {wattron(status_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
    mvwaddwstr(status_win, 1, 11, L"necting... ");
    if (has_colors()) {wattroff(status_win, COLOR_PAIR(4) | A_BOLD | A_DIM);}
    
    // 4. 출력 창 제목
    //mvwaddwstr(output_win, 1, 1, L"출력");
    
    // 5. 명령 창 내용 출력 (단축키 안내)
    //mvwaddwstr(command_win, 1, 1, L"[명령] F1: 입고 등록 | F2: 재고 조회 | F3: 상품 관리 | [B] 뒤로가기 | ESC: 종료");
    
    // 7. 화면 갱신 
    wnoutrefresh(stdscr); 
    wnoutrefresh(title_win); 
    wnoutrefresh(status_win);
    wnoutrefresh(last_command_win);
    wnoutrefresh(menu_win); 
    wnoutrefresh(output_win);
    wnoutrefresh(command_win);
    wnoutrefresh(console_win);
    wnoutrefresh(tooltip_win);
    doupdate(); 
}

// 화면 크기 변경(KEY_RESIZE) 이벤트 핸들러
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