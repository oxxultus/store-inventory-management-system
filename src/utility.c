#include "utility.h"

// 문자열 좌우 공백 제거 함수 (char* 버전)
char* trim_whitespace(char *str) {
    char *end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0) return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
    return str;
}

// 숫자로만 구성되어 있는지 확인
int is_numeric(const char *str) {
    if (str == NULL || *str == '\0') return 0;
    while (*str) {
        if (!isdigit((unsigned char)*str) && *str != '.') { // 소수점 허용
            return 0;
        }
        str++;
    }
    return 1;
}

// 사용자 입력 처리
int get_user_input(WINDOW *win, char *buffer, int maxlen) {
    int ch;
    int index = 0;
    
    // 비차단 모드 시작: 입력이 없으면 즉시 ERR(-1) 반환
    nodelay(win, TRUE);
    curs_set(1); // 커서 보이기
    echo(); // 입력 내용 화면에 표시
    
    werase(win);
    box(win, 0, 0);
    mvwaddwstr(win, 1, 1, L"입력 > ");
    wmove(win, 1, 8); // 입력 시작 위치

    while (1) {
        ch = wgetch(win);
        
        if (ch == 27) { // ESC 키 (ASCII 27) 감지
            nodelay(win, FALSE); // 비차단 모드 해제
            curs_set(0); 
            noecho();
            return 0; // 취소 (0 반환)
        } 
        else if (ch == 10) { // Enter 키 감지 (ASCII 10)
            buffer[index] = '\0';
            nodelay(win, FALSE); // 비차단 모드 해제
            curs_set(0);
            noecho();
            return 1; // 완료 (1 반환)
        }
        else if (ch != ERR && index < maxlen - 1) {
            // 일반 문자 입력 처리 (여기에 복잡한 유효성 검사 로직이 들어감)
            // 현재 Ncurses는 기본적으로 입력 버퍼링을 처리해줌.
        }
        
        // 화면 갱신: 입력 모드에서도 UI가 응답하도록 doupdate 필요
        doupdate();
    }
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
            // TODO: 먼저 데이터 베이스에 해당 항목이 있는 지 검사
            // TODO: 수량을 포함시켜서 테이블에서 같이 수량을 검사 해야함  -> quintity
            // get_product_price 함수는 바코드 문자열을 인수로 받아야 합니다.
            int result = get_product_price(barcode_str, &quantity, item_name, &price_value);

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
            } else if(result == -1){
                wscrl(console_win, 1);
                if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
                mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] [ERROR] 남아있는 상품 재고가 부족합니다.");
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

// 1