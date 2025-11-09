#include "cart.h"

// 전역 변수로 구조체 배열의 시작을 가리킬 포인터를 선언
CartItems *cartitems = NULL;
int NUM_ITEMS = 0; // 현재 아이템(행)의 개수를 저장할 변수
int g_prev_num_items = 0; // 이전 항목 개수 저장 변수

// 새로운 항목을 추가하고 동적으로 장바구니 배열 크기를 늘리는 함수
void add_cart_item(const char *barcode, const char *name, int qty, double prc) {
    // 1. realloc을 사용하여 배열의 크기를 1칸 확장
    CartItems *temp_cartitems = (CartItems *)realloc(
        cartitems, 
        (NUM_ITEMS + 1) * sizeof(CartItems)
    );

    if (temp_cartitems == NULL) {
        // perror("장바구니 배열 확장(realloc) 실패");
        return; 
    }
    
    // realloc 성공 시 포인터 업데이트
    cartitems = temp_cartitems;

    // 2. 새로 추가된 마지막 위치(NUM_ITEMS)에 데이터 설정
    
    // 바코드 문자열 복사 (새로 추가된 부분)
    strncpy(cartitems[NUM_ITEMS].barcode, barcode, sizeof(cartitems[NUM_ITEMS].barcode) - 1);
    cartitems[NUM_ITEMS].barcode[sizeof(cartitems[NUM_ITEMS].barcode) - 1] = '\0';

    // 상품 이름 문자열 복사
    strncpy(cartitems[NUM_ITEMS].name, name, sizeof(cartitems[NUM_ITEMS].name) - 1);
    cartitems[NUM_ITEMS].name[sizeof(cartitems[NUM_ITEMS].name) - 1] = '\0';
    
    // 수량 및 가격 설정
    cartitems[NUM_ITEMS].quantity = qty;
    cartitems[NUM_ITEMS].price = prc;

    // 3. 항목 개수 증가
    NUM_ITEMS++;
    sales_input_flag = 1; // 장바구니에 상품이 추가되었음을 표시

    wscrl(console_win, 1);
    wmove(console_win, CONSOLE_HEIGHT - 2, 1);
    if (has_colors()) {wattron(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    wprintw(console_win, " [LOG] [상품 판매] [바코드: %s] '%s' 항목이 장바구니에 추가됨 (총 %d개)", barcode, name, NUM_ITEMS);
    if (has_colors()) {wattroff(console_win, COLOR_PAIR(1) | A_BOLD | A_DIM); }
    if (has_colors()) wattron(console_win, COLOR_PAIR(7));
    box(console_win, 0, 0);
    if (has_colors()) wattroff(console_win, COLOR_PAIR(7));
    display_cart_items(); // 장바구니 출력 갱신
    wnoutrefresh(output_win);
    wnoutrefresh(console_win); // 즉시 갱신
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
        // printf("장바구니 메모리 해제 완료.\n");
    }
}

// 장바구니 내역을 출력하는 함수
void display_cart_items() {

    werase(output_win);
    int start_y = 3; // 출력 시작 행

    if(sales_input_flag == 1){
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[장바구니 상품 내역]");
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwaddwstr(output_win, 1, 22, L" - 바코드, 수량 를 입력하고 🅴 🅽 🆃 🅴 🆁 를 누르세요.");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        start_y = 4; // 출력 시작 행
    }else {
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
        box(output_win, 0, 0);
        mvwaddwstr(output_win, 1, 2, L"[장바구니 상품 내역]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }

        start_y = 3; // 출력 시작 행
    }
    int current_y = start_y; // 현재 출력할 행

    if (NUM_ITEMS == 0) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[장바구니 상품 내역]");
            if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
                mvwaddwstr(output_win, 1, 22, L" - 장바구니가 비어 있습니다.");
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); } 
        wnoutrefresh(output_win);
        
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

        } else {
            // 1. 헤더 
            if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
            mvwprintw(output_win, current_y++, 2, "%-5s %-10s %-20s %8s %8s", 
              "Idx", "바코드", "상품명", "수량", "단가");
            mvwprintw(output_win, current_y++, 2, "----- -------------------- -------------------- -------- --------");

            // 2. 모든 장바구니 항목 순회하며 출력
            for (int i = 0; i < NUM_ITEMS; i++) {
                
                // 인덱스를 출력할 때, 먼저 인덱스 번호를 화면에 표시합니다.
                // 예를 들어, [0] [1] [2] ... 
                mvwprintw(output_win, current_y, 2, "[%d]", i);
                
                if(i == NUM_ITEMS-1 && check_change_in_cart() == 1){ 
                    if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
                    int rows, cols;
                    getmaxyx(output_win, rows, cols);
                    // [+ 추가됨] 문구가 인덱스 출력 후에 나타나도록 y, x 좌표 조정이 필요할 수 있습니다.
                    // 여기서는 출력 행의 맨 오른쪽 근처에 표시합니다.
                    mvwaddwstr(output_win, current_y, cols-12, L"[+ 추가됨]"); 
                    if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
                }
                
                // 각 항목의 가격을 최종 금액으로 계산하여 출력
                double total_price = cartitems[i].quantity * cartitems[i].price; 
                
                // 🌟 수정: 인덱스 출력 공간 5칸 다음인 7열부터 나머지 항목을 출력
                mvwprintw(output_win, current_y++, 7, // 7열에서 출력 시작 (인덱스 [0]이 2열부터 5열까지 차지했다고 가정)
                        "%-10s %-20s %8d %8.2f (합: %.2f)", 
                        cartitems[i].barcode,   // 바코드
                        cartitems[i].name,      // 상품명
                        cartitems[i].quantity,  // 수량
                        cartitems[i].price,     // 단가
                        total_price);           // 해당 항목의 합계 금액
                                
                // 윈도우 크기를 초과하지 않도록 추가적인 크기 검사 로직이 필요할 수 있습니다.
                // if (current_y >= MAX_WINDOW_HEIGHT - 2) break; // 예시 방지 로직
            }
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }
            wnoutrefresh(console_win);
        }
        // 장바구니 출력 로직 끝

        // 합계를 출력할 수 있습니다.
        //if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
          //   mvwprintw(output_win, current_y + 1, 2, "총 합계: %.2f", calculate_total_cart_amount());
        //if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }
}

// 장바구니 내역 추가 정보를 출력하는 함수
void display_cart_items_noInfo() {

    werase(output_win);
    int start_y = 3; // 출력 시작 행

    if(sales_input_flag == 1){
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[장바구니 상품 내역]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        start_y = 3; // 출력 시작 행
    }else {
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[장바구니 상품 내역]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        start_y = 4; // 출력 시작 행
    }
    int current_y = start_y; // 현재 출력할 행

    if (NUM_ITEMS == 0) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[장바구니 상품 내역]");
            if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
                mvwaddwstr(output_win, 1, 22, L" - 장바구니가 비어 있습니다.");
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); } 
        wnoutrefresh(output_win);
        
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

        } else {
            // 1. 헤더 
            if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
            mvwprintw(output_win, current_y++, 2, "%-5s %-10s %-20s %8s %8s", 
              "Idx", "바코드", "상품명", "수량", "단가");
            mvwprintw(output_win, current_y++, 2, "----- -------------------- -------------------- -------- --------");

            // 2. 모든 장바구니 항목 순회하며 출력
            for (int i = 0; i < NUM_ITEMS; i++) {
                
                // 인덱스를 출력할 때, 먼저 인덱스 번호를 화면에 표시합니다.
                // 예를 들어, [0] [1] [2] ... 
                mvwprintw(output_win, current_y, 2, "[%d]", i);
                
                // 각 항목의 가격을 최종 금액으로 계산하여 출력
                double total_price = cartitems[i].quantity * cartitems[i].price; 
                
                // 🌟 수정: 인덱스 출력 공간 5칸 다음인 7열부터 나머지 항목을 출력
                mvwprintw(output_win, current_y++, 7, // 7열에서 출력 시작 (인덱스 [0]이 2열부터 5열까지 차지했다고 가정)
                        "%-10s %-20s %8d %8.2f (합: %.2f)", 
                        cartitems[i].barcode,   // 바코드
                        cartitems[i].name,      // 상품명
                        cartitems[i].quantity,  // 수량
                        cartitems[i].price,     // 단가
                        total_price);           // 해당 항목의 합계 금액
                                
                // 윈도우 크기를 초과하지 않도록 추가적인 크기 검사 로직이 필요할 수 있습니다.
                // if (current_y >= MAX_WINDOW_HEIGHT - 2) break; // 예시 방지 로직
            }
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }
            wnoutrefresh(console_win);
            wnoutrefresh(output_win);
        }
        // 장바구니 출력 로직 끝

        // 합계를 출력할 수 있습니다.
        //if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
          //   mvwprintw(output_win, current_y + 1, 2, "총 합계: %.2f", calculate_total_cart_amount());
        //if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }
}

// 장바구니 삭제 정보를 출력하는 함수
void display_cart_items_deleteinfo(int index) {

    werase(output_win);
    int start_y = 3; // 출력 시작 행

    if(sales_input_flag == 1){
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[장바구니 상품 삭제 내역]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        start_y = 3; // 출력 시작 행
    }else {
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[장바구니 상품 삭제 내역]");
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        start_y = 4; // 출력 시작 행
    }
    int current_y = start_y; // 현재 출력할 행

    if (NUM_ITEMS == 0) {
        werase(output_win);
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwaddwstr(output_win, 1, 2, L"[장바구니 상품 삭제 내역]");
            if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
                mvwaddwstr(output_win, 1, 22, L" - 장바구니가 비어 있습니다.");
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); } 
        wnoutrefresh(output_win);
        
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

        } else {
            // 1. 헤더 
            if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
            mvwprintw(output_win, current_y++, 2, "%-5s %-10s %-20s %8s %8s", 
              "Idx", "바코드", "상품명", "수량", "단가");
            mvwprintw(output_win, current_y++, 2, "----- -------------------- -------------------- -------- --------");

            // 2. 모든 장바구니 항목 순회하며 출력
            for (int i = 0; i < NUM_ITEMS; i++) {
                
                // 인덱스를 출력할 때, 먼저 인덱스 번호를 화면에 표시합니다.
                mvwprintw(output_win, current_y, 2, "[%d]", i);
                
                if(i == index && check_change_in_cart() == 1){ 
                    if (has_colors()) {wattron(output_win, COLOR_PAIR(4) | A_BOLD); }
                    int rows, cols;
                    getmaxyx(output_win, rows, cols);
                    mvwaddwstr(output_win, current_y, cols-12, L"[- 제거됨]"); 
                }
                
                // 각 항목의 가격을 최종 금액으로 계산하여 출력
                double total_price = cartitems[i].quantity * cartitems[i].price;
                
                // 🌟 수정: 인덱스 출력 공간 5칸 다음인 7열부터 나머지 항목을 출력
                mvwprintw(output_win, current_y++, 7, // 7열에서 출력 시작 (인덱스 [0]이 2열부터 5열까지 차지했다고 가정)
                        "%-10s %-20s %8d %8.2f (합: %.2f)", 
                        cartitems[i].barcode,   // 바코드
                        cartitems[i].name,      // 상품명
                        cartitems[i].quantity,  // 수량
                        cartitems[i].price,     // 단가
                        total_price);           // 해당 항목의 합계 금액
                                
                // 윈도우 크기를 초과하지 않도록 추가적인 크기 검사 로직이 필요할 수 있습니다.
                // if (current_y >= MAX_WINDOW_HEIGHT - 2) break; // 예시 방지 로직
                
                if(i == index && check_change_in_cart() == 1){ 
                    if (has_colors()) {wattroff(output_win, COLOR_PAIR(4) | A_BOLD); }
                }

            }
            if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }
            wnoutrefresh(console_win);
        }
        // 장바구니 출력 로직 끝

        // 합계를 출력할 수 있습니다.
        //if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
          //   mvwprintw(output_win, current_y + 1, 2, "총 합계: %.2f", calculate_total_cart_amount());
        //if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }
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
// 112