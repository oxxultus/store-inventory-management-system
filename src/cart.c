#include "cart.h"

CartItems *cartitems = NULL;     // 전역 변수로 구조체 배열의 시작을 가리킬 포인터를 선언
int NUM_ITEMS = 0;               // 현재 아이템(행)의 개수를 저장할 변수
int g_prev_num_items = 0;        // 이전 항목 개수 저장 변수
int modify_carttiems_index = -1; // 수정된 인덱스위치를 저장하는 변수

// 새로운 항목을 추가하고 동적으로 장바구니 배열 크기를 늘리는 함수
void add_cart_item(const char *barcode, const char *name, int qty, double prc) {

    // 0. 기존 항목 검색
    int found_index = -1;
    for (int i = 0; i < NUM_ITEMS; i++) {
        // strncmp을 사용하여 바코드가 동일한지 확인
        if (strncmp(cartitems[i].barcode, barcode, sizeof(cartitems[i].barcode)) == 0) {
            found_index = i;
            break;
        }
    }

    if (found_index != -1) {
        // 항목을 찾은 경우: 수량 증가 로직
        
        // 1. 수량 증가 및 가격 업데이트
        cartitems[found_index].quantity += qty;
        cartitems[found_index].price = prc; 
        
        // 2. 수정된 인덱스 값 설정
        modify_carttiems_index = found_index; // 찾은 인덱스를 설정
        
        // 3. 로그 및 UI 갱신
        sales_input_flag = 1;

        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(3) | A_BOLD); } 
        // 로그 메시지 수정: '총 %d개'는 NUM_ITEMS를 출력
        wprintw(console_win, " [LOG] [상품 판매] [바코드: %s] '%s' 수량 (%d)이 장바구니에서 증가됨 (총 %d개)", 
                barcode, name, qty, NUM_ITEMS);
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(3) | A_BOLD); }
        
    } else {
        // 항목을 찾지 못한 경우: 새로운 항목 추가 로직
        
        // 1. realloc을 위한 이전 NUM_ITEMS를 새 인덱스로 사용
        int new_item_index = NUM_ITEMS; 

        // 2. realloc을 사용하여 배열의 크기를 1칸 확장
        CartItems *temp_cartitems = (CartItems *)realloc(
            cartitems, 
            (NUM_ITEMS + 1) * sizeof(CartItems)
        );

        if (temp_cartitems == NULL) {
            return; 
        }
        
        cartitems = temp_cartitems;

        // 3. 새로 추가된 마지막 위치(new_item_index)에 데이터 설정
        
        // 바코드 문자열 복사
        strncpy(cartitems[new_item_index].barcode, barcode, sizeof(cartitems[new_item_index].barcode) - 1);
        cartitems[new_item_index].barcode[sizeof(cartitems[new_item_index].barcode) - 1] = '\0';

        // 상품 이름 문자열 복사
        strncpy(cartitems[new_item_index].name, name, sizeof(cartitems[new_item_index].name) - 1);
        cartitems[new_item_index].name[sizeof(cartitems[new_item_index].name) - 1] = '\0';
        
        // 수량 및 가격 설정
        cartitems[new_item_index].quantity = qty;
        cartitems[new_item_index].price = prc;

        // 4. 항목 개수 증가
        NUM_ITEMS++;
        
        // 5. 수정된 인덱스 값 설정
        modify_carttiems_index = new_item_index; // 새로 추가된 인덱스를 설정

        // 6. 로그 및 UI 갱신
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
        // 로그 메시지 수정: '총 %d개'는 NUM_ITEMS를 출력
        wprintw(console_win, " [LOG] [상품 판매] [바코드: %s] '%s' 항목이 장바구니에 추가됨 (총 %d개)", barcode, name, NUM_ITEMS);
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    }

    // 공통 UI 갱신 및 플래그 설정
    sales_input_flag = 1; 

    if (has_colors()) wattron(console_win, COLOR_PAIR(7));
    box(console_win, 0, 0);
    if (has_colors()) wattroff(console_win, COLOR_PAIR(7));
    display_cart_items_addinfo(); // 장바구니 출력 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(console_win); 
}

// 이전 장바구니 개수와 현재 개수를 비교하는 함수
int check_change_in_cart(){
    if(g_prev_num_items == NUM_ITEMS){
        return 0; // no change
    }
    return 1; // change
}

// 장바구니 배열 메모리 해제 함수
void free_cart_items() {
    if (cartitems != NULL) {
        free(cartitems);
        cartitems = NULL;
        NUM_ITEMS = 0;
        sales_input_flag = 0; // 장바구니에 상품이 추가되었음을 표시
        g_prev_num_items = 0; // 이전 항목 개수 초기화
        modify_carttiems_index = -1; 
        // printf("장바구니 메모리 해제 완료.\n");
    }
}

// 장바구니 내역 정보를 출력을 위한 핵심 함수 TODO: 페이지 값이 변경되지 않음
void display_cart_items_scroll() {
    
    // --- 변수 선언 및 초기화 ---
    int start_y_offset = 3; 
    int max_rows, max_cols;
    getmaxyx(output_win, max_rows, max_cols);
    
    // 🌟 스크롤 가능한 데이터 출력 행 수 계산: max_rows - 5 (테두리 2 + 제목 1 + 고정 헤더 2)
    int output_rows = max_rows - 6; 
    if (output_rows <= 0) output_rows = 1;

    int start_line_index = 0; // 데이터의 출력 시작 인덱스
    int ch; // 키 입력 변수
    int max_page_start_index;
    int total_data_lines; // 헤더 제외 실제 데이터 라인 수
    int total_pages;      // 총 페이지 수

    LineBuffer print_buffer;
    init_buffer(&print_buffer);
    
    // --- 1. 장바구니 내용을 LineBuffer에 저장 (헤더 2줄 포함) ---
    
    // 0번 인덱스: 헤더 제목 (고정 출력용)
    add_line(&print_buffer, "%-5s %-10s %-20s %8s %10s", 
             "Idx", "바코드", "상품명", "수량", "합계 금액"); 
    // 1번 인덱스: 구분선 (고정 출력용)
    add_line(&print_buffer, "----- -------------------- -------------------- -------- ----------");

    if (NUM_ITEMS > 0) {
        for (int i = 0; i < NUM_ITEMS; i++) {
            double total_price = cartitems[i].quantity * cartitems[i].price; 
            char item_line[MAX_LINE_LENGTH]; 
            
            // 데이터 포맷팅
            snprintf(item_line, MAX_LINE_LENGTH, "[%d] %-10s %-20s %8d %10.2f", 
                     i, cartitems[i].barcode, cartitems[i].name, 
                     cartitems[i].quantity, total_price);
            
            if(i == modify_carttiems_index && check_change_in_cart() == 1 && modify_carttiems_index != -1){
                 strcat(item_line, " [+ 추가됨]");
            }
            
            add_line(&print_buffer, "%s", item_line);
        }
        
        // 총합계 및 구분선 추가
        double grand_total = calculate_total_cart_amount();
        add_line(&print_buffer, "--------------------------------------------------------------------");
        add_line(&print_buffer, "장바구니 내역 금액: KRW %.2f", grand_total); 
    } else {
        add_line(&print_buffer, "장바구니가 비어 있습니다.");
    }
    
    // 페이지 계산 로직
    total_data_lines = print_buffer.count - 2; // 전체 라인 수에서 고정 헤더 2줄 제외
    
    if (total_data_lines > output_rows) {
        // 스크롤 시작 인덱스 최대값: 전체 라인 수에서 output_rows를 뺀 값
        max_page_start_index = print_buffer.count - output_rows; 
        // 총 페이지 수 계산
        total_pages = (total_data_lines + output_rows - 1) / output_rows;
    } else {
        max_page_start_index = 0;
        total_pages = 1;
    }

    // --- 2. 입력 루프 및 출력 시작 ---
    
    // command_win에서 블록킹 입력 받을 준비
    nodelay(command_win, FALSE); 
    keypad(command_win, TRUE);   
    curs_set(0);            

    while (1) {
        werase(output_win);
        
        // 2-1. 윈도우 테두리 및 제목 출력
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwprintw(output_win, 1, 2, "[장바구니 상품 내역] - (총 %d 항목)", NUM_ITEMS);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        
        // 2-2. 🌟 헤더 고정 출력 (스크롤되지 않음)
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
            // 3행: 헤더 제목 (Buffer index 0)
            mvwprintw(output_win, 3, 2, "%s", print_buffer.lines[0]); 
            // 4행: 구분선 (Buffer index 1)
            mvwprintw(output_win, 4, 2, "%s", print_buffer.lines[1]); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }

        // 2-3. 스크롤 위치 및 도움말 출력 (페이지 상태)
        int current_y = 5; // 🌟 데이터 출력 시작 Y 위치 (5행)
        
        // 현재 페이지 상태 표시
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            int page_info_y = 1;
            int page_info_x = max_cols - 20;
            if (total_pages > 1) { 
                 mvwprintw(output_win, page_info_y, page_info_x, "페이지: %d / %d", 
                           (start_line_index / output_rows) + 1, 
                           total_pages);
            }
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // 2-4. LineBuffer 클리핑 및 데이터 출력
        for (int i = 0; i < output_rows; i++) {
            int buffer_index = 2 + start_line_index + i; // 2 (고정 헤더)를 건너뛰고 데이터 시작
            if (buffer_index >= print_buffer.count) break;

            const char *line = print_buffer.lines[buffer_index];
            mvwprintw(output_win, current_y++, 2, "%s", line);
        }

        // 2-4. Tooltip 출력 (ESC, 좌/우 키 안내)
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

        // 2-5. command_win을 입력 대기 상태로 표시
        werase(command_win);
        if (has_colors()) {wattron(command_win, COLOR_PAIR(1) | A_BOLD); }
            box(command_win, 0, 0);
            mvwaddwstr(command_win, 1, 2, L"[!] 키보드 명령 대기중 키보드 좌우 버튼으로 스크롤 (◀ ▶ 스크롤)");
        if (has_colors()) {wattroff(command_win, COLOR_PAIR(1) | A_BOLD); }

        wnoutrefresh(output_win);
        wnoutrefresh(tooltip_win);
        wnoutrefresh(listbar_win);
        wnoutrefresh(command_win); // command_win 갱신
        doupdate();

        // 2-6. 키 입력 대기 및 처리
        ch = wgetch(command_win); // command_win에서 블록킹 입력 받기

        switch (ch) {
            case KEY_LEFT: // 좌측 키 (이전 페이지)
                if (start_line_index > 0) {
                    start_line_index -= output_rows;
                    if (start_line_index < 0) start_line_index = 0;
                }
                break;

            case KEY_RIGHT: // 우측 키 (다음 페이지)
                if (start_line_index < max_page_start_index) {
                    start_line_index += output_rows;
                    if (start_line_index > max_page_start_index) {
                        start_line_index = max_page_start_index;
                    }
                }
                break;

            case 27: // ESC 키 감지
                goto exit_loop;

            default:
                break;
        }
    }

exit_loop:
    // --- 3. 메모리 해제 및 Ncurses 상태 원복 ---
    clear_buffer(&print_buffer); 

    // 상태 원복
    nodelay(command_win, TRUE); 
    keypad(command_win, FALSE);
    curs_set(0);       

    // 윈도우 정리
    werase(output_win);
    werase(tooltip_win);
    werase(listbar_win);
    werase(command_win); 
    doupdate(); 
}

// 장바구니 내역 정보를 출력하는 함수 TODO: 페이지 값이 변경되지 않음
void display_checkout_items_scroll() {
    
    // --- 변수 선언 및 초기화 ---
    int start_y_offset = 3; 
    int max_rows, max_cols;
    getmaxyx(output_win, max_rows, max_cols);
    
    // 🌟 스크롤 가능한 데이터 출력 행 수 계산: max_rows - 5 (테두리 2 + 제목 1 + 고정 헤더 2)
    int output_rows = max_rows - 6; 
    if (output_rows <= 0) output_rows = 1;

    int start_line_index = 0; // 데이터의 출력 시작 인덱스
    int ch; // 키 입력 변수
    int max_page_start_index;
    int total_data_lines; // 헤더 제외 실제 데이터 라인 수
    int total_pages;      // 총 페이지 수

    LineBuffer print_buffer;
    init_buffer(&print_buffer);
    
    // --- 1. 장바구니 내용을 LineBuffer에 저장 (헤더 2줄 포함) ---
    
    // 0번 인덱스: 헤더 제목 (고정 출력용)
    add_line(&print_buffer, "%-5s %-10s %-20s %8s %10s", 
             "Idx", "바코드", "상품명", "수량", "합계 금액"); 
    // 1번 인덱스: 구분선 (고정 출력용)
    add_line(&print_buffer, "----- -------------------- -------------------- -------- ----------");

    if (NUM_ITEMS > 0) {
        for (int i = 0; i < NUM_ITEMS; i++) {
            double total_price = cartitems[i].quantity * cartitems[i].price; 
            char item_line[MAX_LINE_LENGTH]; 
            
            // 데이터 포맷팅
            snprintf(item_line, MAX_LINE_LENGTH, "[%d] %-10s %-20s %8d %10.2f", 
                     i, cartitems[i].barcode, cartitems[i].name, 
                     cartitems[i].quantity, total_price);
            add_line(&print_buffer, "%s", item_line);
        }
        
        // 총합계 및 구분선 추가
        double grand_total = calculate_total_cart_amount();
        add_line(&print_buffer, "--------------------------------------------------------------------");
        add_line(&print_buffer, "결제 내역 금액: KRW %.2f", grand_total); 
    } else {
        add_line(&print_buffer, "장바구니가 비어 있습니다.");
    }
    
    // 페이지 계산 로직
    total_data_lines = print_buffer.count - 2; // 전체 라인 수에서 고정 헤더 2줄 제외
    
    if (total_data_lines > output_rows) {
        // 스크롤 시작 인덱스 최대값: 전체 라인 수에서 output_rows를 뺀 값
        max_page_start_index = print_buffer.count - output_rows; 
        // 총 페이지 수 계산
        total_pages = (total_data_lines + output_rows - 1) / output_rows;
    } else {
        max_page_start_index = 0;
        total_pages = 1;
    }

    // --- 2. 입력 루프 및 출력 시작 ---
    
    // command_win에서 블록킹 입력 받을 준비
    nodelay(command_win, FALSE); 
    keypad(command_win, TRUE);   
    curs_set(0);            

    while (1) {
        werase(output_win);
        
        // 2-1. 윈도우 테두리 및 제목 출력
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwprintw(output_win, 1, 2, "[결제 내역] - (총 %d 항목)", NUM_ITEMS);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        
        // 2-2. 🌟 헤더 고정 출력 (스크롤되지 않음)
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
            // 3행: 헤더 제목 (Buffer index 0)
            mvwprintw(output_win, 3, 2, "%s", print_buffer.lines[0]); 
            // 4행: 구분선 (Buffer index 1)
            mvwprintw(output_win, 4, 2, "%s", print_buffer.lines[1]); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }

        // 2-3. 스크롤 위치 및 도움말 출력 (페이지 상태)
        int current_y = 5; // 데이터 출력 시작 Y 위치 (5행)
        
        // 현재 페이지 상태 표시
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            int page_info_y = 1;
            int page_info_x = max_cols - 20;
            if (total_pages > 1) { 
                 mvwprintw(output_win, page_info_y, page_info_x, "페이지: %d / %d", 
                           (start_line_index / output_rows) + 1, 
                           total_pages);
            }
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // 2-4. LineBuffer 클리핑 및 데이터 출력
        for (int i = 0; i < output_rows; i++) {
            int buffer_index = 2 + start_line_index + i; // 2 (고정 헤더)를 건너뛰고 데이터 시작
            if (buffer_index >= print_buffer.count) break;

            const char *line = print_buffer.lines[buffer_index];
            mvwprintw(output_win, current_y++, 2, "%s", line);
        }

        // 2-4. Tooltip 출력 (ESC, 좌/우 키 안내)
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

        // 2-5. command_win을 입력 대기 상태로 표시
        werase(command_win);
        if (has_colors()) {wattron(command_win, COLOR_PAIR(1) | A_BOLD); }
            box(command_win, 0, 0);
            mvwaddwstr(command_win, 1, 2, L"[!] 좌우 버튼으로 스크롤 해서 영수증을 확인하세요. (◀ ▶ 스크롤)");
        if (has_colors()) {wattroff(command_win, COLOR_PAIR(1) | A_BOLD); }

        wnoutrefresh(output_win);
        wnoutrefresh(tooltip_win);
        wnoutrefresh(listbar_win);
        wnoutrefresh(command_win); // command_win 갱신
        doupdate();

        // 2-6. 키 입력 대기 및 처리
        ch = wgetch(command_win); // command_win에서 블록킹 입력 받기

        switch (ch) {
            case KEY_LEFT: // 좌측 키 (이전 페이지)
                if (start_line_index > 0) {
                    start_line_index -= output_rows;
                    if (start_line_index < 0) start_line_index = 0;
                }
                break;

            case KEY_RIGHT: // 우측 키 (다음 페이지)
                if (start_line_index < max_page_start_index) {
                    start_line_index += output_rows;
                    if (start_line_index > max_page_start_index) {
                        start_line_index = max_page_start_index;
                    }
                }
                break;

            case 10: // ESC 키 감지
                goto exit_loop;

            default:
                break;
        }
    }

exit_loop:
    // --- 3. 메모리 해제 및 Ncurses 상태 원복 ---
    clear_buffer(&print_buffer); 

    // 상태 원복
    nodelay(command_win, TRUE); 
    keypad(command_win, FALSE);
    curs_set(0);       

    // 윈도우 정리
    werase(output_win);
    werase(tooltip_win);
    werase(listbar_win);
    werase(command_win); 
    doupdate(); 
}

// 장바구니 내역을 추가 정보를 출력하는 함수
void display_cart_items_addinfo() {

    // --- 1. 창 크기 계산 및 초기 설정 ---
    werase(output_win);
    int max_rows, max_cols;
    getmaxyx(output_win, max_rows, max_cols);
    
    // 출력 가능 데이터 행 수 계산: max_rows - 5 (테두리 2 + 제목 2 + 헤더 2)
    int output_rows = max_rows - 6; 
    if (output_rows <= 0) output_rows = 1; // 최소 1줄 보장

    int current_y = 5; // 데이터 출력 시작 Y 위치 (5행)

    // --- 2. 비어있음 처리 ---
    if (NUM_ITEMS == 0) {
        // 장바구니가 비어있는 경우 (기존 로직 유지)
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[장바구니 상품 내역]");
            if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
                mvwaddwstr(output_win, 1, 22, L" - 장바구니가 비어 있습니다.");
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); } 
        
        // 툴팁 출력 (기존 로직 유지)
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
    
    // --- 3. 출력 범위 계산 (modify_carttiems_index 중앙 정렬) ---
    
    // 포커스 중심 행 계산 (예: 10행 중 5, 9행 중 4)
    int focus_offset = output_rows / 2;
    
    // 출력 시작 인덱스: modify_carttiems_index가 중앙에 오도록 조정
    int start_index = modify_carttiems_index - focus_offset;
    
    // 경계 처리 (최소 인덱스가 0 미만이 되지 않도록)
    if (start_index < 0) {
        start_index = 0;
    } 
    // 경계 처리 (마지막 항목이 출력 범위 내에 들어오도록)
    if (start_index + output_rows > NUM_ITEMS) {
        start_index = NUM_ITEMS - output_rows;
        if (start_index < 0) start_index = 0; // 다시 0 미만이 되는 경우 방지
    }
    
    // --- 4. 고정 요소 및 헤더 출력 ---

    // 4-1. 제목/테두리
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[장바구니 상품 내역]");
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            // 안내 메시지 출력
            if (sales_input_flag == 1) {
                mvwaddwstr(output_win, 1, 22, L" - 바코드, 수량 를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
            }
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    
    // 4-2. 헤더
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
        mvwprintw(output_win, 3, 2, "%-5s %-10s %-20s %8s %8s", 
          "Idx", "바코드", "상품명", "수량", "단가");
        mvwprintw(output_win, 4, 2, "----- -------------------- -------------------- -------- --------");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }


    // --- 5. 데이터 순회 및 출력 (계산된 범위 사용) ---
    
    // start_index 부터 output_rows 개수만큼 출력
    for (int i = 0; i < output_rows; i++) {
        int item_index = start_index + i; // 실제로 출력할 장바구니의 인덱스

        if (item_index >= NUM_ITEMS) {
            break; // 데이터가 끝났다면 종료
        }
        
        // 5-1. 현재 항목 인덱스 출력
        mvwprintw(output_win, current_y, 2, "[%d]", item_index);
        
        // 5-2. 수정/추가된 항목 하이라이트
        if (item_index == modify_carttiems_index && sales_input_flag == 1){ 
            if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD | A_REVERSE); } // 강조 효과 시작
            int rows_win, cols_win;
            getmaxyx(output_win, rows_win, cols_win);
            mvwaddwstr(output_win, current_y, cols_win-12, L"[+ 변경됨]"); 
        }

        // 5-3. 항목 데이터 출력
        double total_price = cartitems[item_index].quantity * cartitems[item_index].price; 
        
        mvwprintw(output_win, current_y++, 7, 
                "%-10s %-20s %8d %8.2f (합: %.2f)", 
                cartitems[item_index].barcode,
                cartitems[item_index].name,
                cartitems[item_index].quantity,
                cartitems[item_index].price,
                total_price);
                
        // 5-4. 하이라이트 종료
        if (item_index == modify_carttiems_index && sales_input_flag == 1) {
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD | A_REVERSE); }
        }
    }
    
    // 6. UI 갱신
    // 툴팁 출력은 이미 2번에서 처리됨
    
    wnoutrefresh(output_win);
}

// 장바구니 삭제 정보를 출력하는 함수
void display_cart_items_deleteinfo(int index) { // index: 삭제될 항목의 위치
    
    // --- 1. 창 크기 계산 및 초기 설정 ---
    werase(output_win);
    int max_rows, max_cols;
    getmaxyx(output_win, max_rows, max_cols);
    
    // 출력 가능 데이터 행 수 계산: max_rows - 5
    int output_rows = max_rows - 5; 
    if (output_rows <= 0) output_rows = 1;

    int current_y = 5; // 데이터 출력 시작 Y 위치 (5행)

    // --- 2. 비어있음 처리 ---
    // 이 함수는 삭제 직전에 호출되므로, NUM_ITEMS == 0 일 때 실행될 확률은 낮습니다.
    if (NUM_ITEMS == 0) {
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[장바구니 상품 내역]");
            if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
                mvwaddwstr(output_win, 1, 22, L" - 장바구니가 비어 있습니다.");
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); } 
        
        // 툴팁 출력 (생략 없이 유지)
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
    
    // --- 3. 출력 범위 계산 (창 크기에 맞춰 시작 인덱스 계산) ---
    
    // index를 화면 중앙에 오도록 계산
    int focus_offset = output_rows / 2;
    int start_index = index - focus_offset; 
    
    // 경계 처리 (최소)
    if (start_index < 0) start_index = 0;
    // 경계 처리 (최대) - 삭제되기 전의 NUM_ITEMS 기준으로 계산
    if (start_index + output_rows > NUM_ITEMS) {
        start_index = NUM_ITEMS - output_rows;
        if (start_index < 0) start_index = 0;
    }
    
    // --- 4. 고정 요소 및 헤더 출력 ---

    // 4-1. 제목/테두리
    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[장바구니 상품 삭제 내역]");
        // 삭제될 항목의 인덱스를 안내
        if (has_colors()) {wattron(output_win, COLOR_PAIR(4) | A_BOLD); }
            mvwprintw(output_win, 1, 28, " - [인덱스 %d] 항목이 삭제됩니다.", index);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(4) | A_BOLD); }
        
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
    
    // 4-2. 헤더
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
        mvwprintw(output_win, 3, 2, "%-5s %-10s %-20s %8s %8s", 
          "Idx", "바코드", "상품명", "수량", "단가");
        mvwprintw(output_win, 4, 2, "----- -------------------- -------------------- -------- --------");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }


    // --- 5. 데이터 순회 및 출력 (삭제 항목 강조) ---
    
    for (int i = 0; i < output_rows; i++) {
        int item_index = start_index + i; // 배열에서 참조할 인덱스 (삭제 전 상태)

        if (item_index >= NUM_ITEMS) {
            break; 
        }
        
        // 5-2. 삭제 항목 강조 (빨간색)
        if (item_index == index) {
            // COLOR_PAIR(4)는 보통 빨간색이나 오류 색상에 할당됨
            if (has_colors()) {wattron(output_win, COLOR_PAIR(4) | A_BOLD | A_REVERSE); } 
            mvwaddwstr(output_win, current_y, 2, L"[-]");
            // [- 제거됨] 플래그 출력
            int rows_win, cols_win;
            getmaxyx(output_win, rows_win, cols_win);
            mvwaddwstr(output_win, current_y, cols_win - 12, L"[- 제거됨]"); 
        }else if(item_index > index){
            mvwprintw(output_win, current_y, 2, "[%d]", item_index-1);
        }else{
            mvwprintw(output_win, current_y, 2, "[%d]", item_index);
        }

        // 5-3. 항목 데이터 출력
        double total_price = cartitems[item_index].quantity * cartitems[item_index].price; 
        
        mvwprintw(output_win, current_y++, 7, 
                "%-10s %-20s %8d %8.2f (합: %.2f)", 
                cartitems[item_index].barcode,
                cartitems[item_index].name,
                cartitems[item_index].quantity,
                cartitems[item_index].price,
                total_price);
                
        // 5-4. 강조 종료
        if (item_index == index) {
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(4) | A_BOLD | A_REVERSE); }
        }
    }
    
    // 6. UI 갱신
    // 툴팁 출력 (생략 없이 유지)
    
    wnoutrefresh(output_win);
}

// 인덱스로 상품을 삭제하는 로직 반환값: 1 (삭제 성공), 0 (인덱스 오류 또는 삭제 실패)
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

    // 1. 항목 이동 로직 (생략)
    for (int i = index; i < NUM_ITEMS - 1; i++) {
        cartitems[i] = cartitems[i + 1]; 
    }

    // 2. 항목 개수 감소
    NUM_ITEMS--;

    if (NUM_ITEMS == 0) {
        // 배열의 모든 값이 사라진 경우, 중앙 함수를 호출하여 해제 및 전역 상태 초기화
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
        // 항목이 남아있다면 realloc으로 크기만 감소
        CartItems *temp_cartitems = (CartItems *)realloc(
            cartitems, 
            NUM_ITEMS * sizeof(CartItems)
        );
        
        if (temp_cartitems != NULL) {
            cartitems = temp_cartitems;
        } 
        // realloc 실패 시 처리 로직은 생략
    }
    
    return 1; // 삭제 성공
}

// 최종 결제 내역 영수증을 출력해주는 함수
void display_cart_checkout(){

    // 1. 윈도우 초기화 및 제목 설정
    werase(output_win);
    int start_y = 3; 

    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[최종 결제 영수증 내역]");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }

    int current_y = start_y; 

    // 2. 장바구니가 비어있는지 확인
    if (NUM_ITEMS == 0) {
        mvwaddwstr(output_win, current_y, 2, L"장바구니가 비어있습니다. 결제할 상품이 없습니다.");
    } else {
        
        // 3. 헤더 출력
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
            mvwprintw(output_win, current_y++, 2, "%-5s %-10s %-20s %8s %10s", 
                      "Idx", "바코드", "상품명", "수량", "합계 금액"); 
            mvwprintw(output_win, current_y++, 2, "----- -------------------- -------------------- -------- ----------");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }

        // 4. 모든 장바구니 항목 순회하며 출력
        for (int i = 0; i < NUM_ITEMS; i++) {
            
            double total_price = cartitems[i].quantity * cartitems[i].price; 
            
            mvwprintw(output_win, current_y, 2, "[%d]", i);
            
            mvwprintw(output_win, current_y++, 7, 
                      "%-10s %-20s %8d %10.2f", 
                      cartitems[i].barcode,   // 바코드
                      cartitems[i].name,      // 상품명
                      cartitems[i].quantity,  // 수량
                      total_price);           // 해당 항목의 합계 금액 출력
        }

        // 5. 총합계 출력
        double grand_total = calculate_total_cart_amount(); // 구현한 함수 호출

        current_y += 2; 

        // 구분선 출력
        mvwprintw(output_win, current_y++, 2, "--------------------------------------------------------------------");
        
        // 총합계를 강조하여 출력
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            mvwprintw(output_win, current_y++, 2, "총 결제 금액:");
            // 우측 정렬
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
    
    // 장바구니 배열이 NULL이거나 비어있으면 0.0을 반환
    if (cartitems == NULL || NUM_ITEMS == 0) {
        return 0.0;
    }
    
    // 모든 항목을 순회하며 (수량 * 가격)을 총 합계에 더합니다.
    for (int i = 0; i < NUM_ITEMS; i++) {
        // 현재 항목의 총 금액을 계산
        double item_total = cartitems[i].quantity * cartitems[i].price;
        
        // 최종 합계에 추가
        grand_total += item_total;
    }
    
    return grand_total;
}

// 112