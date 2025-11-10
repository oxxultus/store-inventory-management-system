#include "include.h" 

// Enter 키를 눌렀을 때 상태를 전환하는 함수
void handle_enter_key() {

    werase(tooltip_win);
    wnoutrefresh(tooltip_win);
    
    Program_State old_state = current_state; 
    
    // 1. 메인 메뉴 상태 처리 (이전 코드와 동일)
    if (current_state == STATE_MAIN_MENU) {
        int id = main_menu_items[current_menu_selection].function_id;

        if (id == 0) { 
            program_exit_flag = 1;
            return;
        }

        if (id >= 1 && id <= 5) {
            current_state = (Program_State)id; 
        } else if (id == 6) {
             current_state = STATE_SUB_SALES; 
             current_menu_selection = 0;
        }

        // 서브 메뉴로 진입했을 때 current_max_items 업데이트
        if (current_state != STATE_MAIN_MENU) {
            if (current_state == STATE_SUB_SALES) {
                 current_max_items = MAX_SALES_SUB_ITEMS; // 상품 판매 항목 수
            } else if (current_state >= STATE_SUB_PURCHASE && current_state <= STATE_SUB_CATEGORY) {
                 current_max_items = MAX_SUB_MENU_ITEMS; // 일반 서브 메뉴 항목 수
            }
        }

    }
    // 2. 서브 메뉴 상태 처리 (등록, 삭제, 조회 중 하나 선택)
    else if (current_state >= STATE_SUB_PURCHASE && current_state <= STATE_SUB_SALES) {

        // 현재 상태에 맞는 메뉴 리스트를 선택합니다.
        Menu_Item *current_list = (current_state == STATE_SUB_SALES) ? sales_sub_menu : sub_menu_template;
        
        int sub_id = current_list[current_menu_selection].function_id;
        const wchar_t *action = current_list[current_menu_selection].label;
        const wchar_t *menu_name = get_current_menu_title();
        
        // TODO: 실제 기능 호출 부분 (DB 연동 및 기능 구현 필요)
        if (current_state == STATE_SUB_PURCHASE) { // 입고 관리 (ID 1)
            if (sub_id == 100) { func_purchase_register();}
            else if (sub_id == 200) { func_purchase_delete(); }
            else if (sub_id == 300) { func_purchase_modify(); }
            else if (sub_id == 400) { func_purchase_query(); }
        }
        else if (current_state == STATE_SUB_INVENTORY) { // 재고 관리 (ID 2)
            if (sub_id == 100) { func_inventory_register(); }
            else if (sub_id == 200) { func_inventory_delete(); }
            else if (sub_id == 300) { func_inventory_modify(); }
            else if (sub_id == 400) { func_inventory_query(); }
        }
        else if (current_state == STATE_SUB_PRODUCT) { // 상품 관리 (ID 3)
            if (sub_id == 100) { func_product_register(); }
            else if (sub_id == 200) { func_product_delete(); }
            else if (sub_id == 300) { func_product_modify(); }
            else if (sub_id == 400) { func_product_query(); }
        }
        else if (current_state == STATE_SUB_SUPPLIER) { // 공급업체 관리 (ID 4)
            if (sub_id == 100) { func_supplier_register(); }
            else if (sub_id == 200) { func_supplier_delete(); }
            else if (sub_id == 300) { func_supplier_modify(); }
            else if (sub_id == 400) { func_supplier_query(); }
        }
        else if (current_state == STATE_SUB_CATEGORY) { // 카테고리 관리 (ID 5)
            if (sub_id == 100) { func_category_register(); }
            else if (sub_id == 200) { func_category_delete(); }
            else if (sub_id == 300) { func_category_modify(); }
            else if (sub_id == 400) { func_category_query(); }
        } 
        else if (current_state == STATE_SUB_SALES) { // 상품 판매 (ID 6)
            if (sub_id == 610) { func_cart_print(); } // 상품/수량 입력
            else if (sub_id == 620) { func_cart_input(); } // 상품/수량 입력
            else if (sub_id == 630) { func_cart_delete(); } // 장바구니 상품 삭제
            else if (sub_id == 640) { func_cart_reset(); } // 장바구니 초기화
            else if (sub_id == 650) { func_cart_checkout(); } // 결제
        }
        
        // ---------------------------------------------------------------------

        // A. console_win에 진행 결과 메시지 출력
        // wscrl(console_win, 1);
        // wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        // wprintw(console_win, " [LOG] [%ls] 메뉴에서 [%ls] 기능이 실행되었습니다.", menu_name, action);

        // B. output_win에 실제 기능 화면 출력 (여기에 입력 폼 또는 조회 결과가 출력됨)
        werase(last_command_win);
        if (has_colors()) {wattron(last_command_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwprintw(last_command_win, 1, 2, "마지막 작업: [%ls] 메뉴의 [%ls]",menu_name ,action);
        if (has_colors()) {wattroff(last_command_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    }

    // 3. 기능 실행 상태에서는 Enter 키 입력 처리 (현재는 무시)
    else if (current_state == STATE_FUNCTION_RUNNING) {
        // 기능 실행 중 Enter 처리 로직
    }
    
    // 상태가 실제로 바뀌었을 경우에만 이전 상태를 갱신
    if (current_state != old_state) {
        previous_state = old_state;
    }
}

// 키보드 입력을 받아 메뉴를 이동시키고 기능을 실행하는 로직
void handle_menu_input(int key) {
    int old_selection = current_menu_selection;

    // 현재 메뉴 항목 개수를 동적으로 가져옵니다.
    int max_items = (current_state == STATE_MAIN_MENU) ? MAX_MAIN_MENU_ITEMS : 
                    (current_state == STATE_SUB_SALES) ? MAX_SALES_SUB_ITEMS : MAX_SUB_MENU_ITEMS;

    Program_State old_state = current_state; 
    
    // 1. 함수 실행 중 (STATE_FUNCTION_RUNNING)인 경우 ESC, B/b 처리
    if (current_state == STATE_FUNCTION_RUNNING && (key == 27 || key == 'b' || key == 'B')) {
        // 함수 실행 상태만 취소하고 이전 상태로 복귀
        current_state = previous_state; 
        
        // UI 초기화 및 상태 복구
        if (current_state != old_state) {
            current_menu_selection = 0;
            // 복귀 시 메인 메뉴 개수로 설정 (또는 previous_state에 맞는 값으로 설정)
            current_max_items = MAX_MAIN_MENU_ITEMS; 
        }
        werase(tooltip_win);
        werase(output_win);
        werase(command_win);
        return; // 다른 switch 로직을 실행하지 않고 복귀
    }

    switch (key) {
        case KEY_UP:
            if (current_state != STATE_FUNCTION_RUNNING) {
                // 위로 이동 (인덱스 감소)
                current_menu_selection = (current_menu_selection - 1 + max_items) % max_items;
            }
            break;
        case KEY_DOWN:
            if (current_state != STATE_FUNCTION_RUNNING) {
                // 아래로 이동 (인덱스 증가)
                current_menu_selection = (current_menu_selection + 1) % max_items;
            }
            break;
        case 10: // Enter 키
            handle_enter_key();
            break;
            
        case 27: // ESC 키
        case 'b': // 'B' 키 (뒤로 가기)
        case 'B':
            if (current_state == STATE_MAIN_MENU) {
                // 🌟 홈 메뉴일 때 ESC/B를 누르면 프로그램 종료
                program_exit_flag = 1; 
                return; // 메인 루프 종료를 위해 즉시 반환
            } 
            
            // 서브 메뉴 상태에서 메인 메뉴로 복귀 (뒤로 가기)
            if (current_state >= STATE_SUB_PURCHASE && current_state <= STATE_SUB_SALES) {
                current_state = STATE_MAIN_MENU; 
            }
            
            if (current_state != old_state) {
                current_menu_selection = 0;
                current_max_items = MAX_MAIN_MENU_ITEMS; 
            }
            werase(tooltip_win);
            werase(output_win);
            werase(command_win);
            break;
        
        // F1~F6 키를 이용한 빠른 이동 (메인 메뉴 항목과 매칭)
        case KEY_F(1): 
        case KEY_F(2): 
        case KEY_F(3):
        case KEY_F(4):
        case KEY_F(5):
        case KEY_F(6): 
            if (current_state == STATE_MAIN_MENU) {
                int f_key_index = key - KEY_F(1);
                current_menu_selection = f_key_index;
                handle_enter_key();
            }
            break;
        default:
            break;
    }

    // 상태나 선택이 변경되었을 경우 UI 갱신 필요 신호
    if (old_selection != current_menu_selection || key == 10 || key == 27 || key == 'b' || key == 'B') {
        // UI 갱신은 run_main_loop에서 처리합니다.
    }
}

// 메인 루프 함수 구현
void run_main_loop() {
    int rows, cols;
    int ch;

    // 수정: ESC(27)를 루프 종료 조건에서 제외하고, 입력으로 처리하도록 함.
    while(program_exit_flag == 0) { 
        
        // 수정: getch()를 루프 내부에서 호출하여 ch에 저장
        ch = getch(); 

        if (ch == ERR) { // 입력 오류 또는 Nodelay 모드일 경우 (참고용)
            continue;
        }

        getmaxyx(stdscr, rows, cols); 
        
        switch (ch) {
            case KEY_RESIZE:
                resize_handler();
                break;
            
            // 🌟 ESC 키(27)를 handle_menu_input으로 전달하여 처리 (추가)
            case 27: // ESC
            case KEY_UP:
            case KEY_DOWN:
            case 10: // Enter
            case 'b':
            case 'B':
            case KEY_F(1):
            case KEY_F(2):
            case KEY_F(3):
            case KEY_F(4):
            case KEY_F(5):
            case KEY_F(6):
                
                // 🌟 handle_menu_input에서 ESC를 받으면 해당 기능만 종료되도록 구현해야 함.
                handle_menu_input(ch);
                
                if (program_exit_flag) {
                    return; 
                }
                break;
            
            default:
                break;
        }
        
        draw_ui(rows, cols);
    }
}
// 1