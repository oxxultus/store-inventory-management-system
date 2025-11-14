#include "include.h"

// Enter 키를 눌렀을 때 상태를 전환하는 함수
void handle_enter_key() {

    werase(tooltip_win);
    wnoutrefresh(tooltip_win);

    Program_State old_state = current_state;

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

        if (current_state != STATE_MAIN_MENU) {
            if (current_state == STATE_SUB_SALES) {
                 current_max_items = MAX_SALES_SUB_ITEMS;
            } else if (current_state >= STATE_SUB_PURCHASE && current_state <= STATE_SUB_CATEGORY) {
                 current_max_items = MAX_SUB_MENU_ITEMS;
            }
        }

    }
    // 2. 서브 메뉴 상태 처리 (등록, 삭제, 조회 중 하나 선택)
    else if (current_state >= STATE_SUB_PURCHASE && current_state <= STATE_SUB_SALES) {

        Menu_Item *current_list = (current_state == STATE_SUB_SALES) ? sales_sub_menu : sub_menu_template;

        int sub_id = current_list[current_menu_selection].function_id;
        const wchar_t *action = current_list[current_menu_selection].label;
        const wchar_t *menu_name = get_current_menu_title();

        if (current_state == STATE_SUB_PURCHASE) {
            if (sub_id == 100) { func_purchase_register();}
            else if (sub_id == 200) { func_purchase_delete(); }
            else if (sub_id == 300) { func_purchase_modify(); }
            else if (sub_id == 400) { func_purchase_query(); }
        }
        else if (current_state == STATE_SUB_INVENTORY) {
            if (sub_id == 100) { func_inventory_register(); }
            else if (sub_id == 200) { func_inventory_delete(); }
            else if (sub_id == 300) { func_inventory_modify(); }
            else if (sub_id == 400) { func_inventory_query(); }
        }
        else if (current_state == STATE_SUB_PRODUCT) {
            if (sub_id == 100) { func_product_register(); }
            else if (sub_id == 200) { func_product_delete(); }
            else if (sub_id == 300) { func_product_modify(); }
            else if (sub_id == 400) { func_product_query(); }
        }
        else if (current_state == STATE_SUB_SUPPLIER) {
            if (sub_id == 100) { func_supplier_register(); }
            else if (sub_id == 200) { func_supplier_delete(); }
            else if (sub_id == 300) { func_supplier_modify(); }
            else if (sub_id == 400) { func_supplier_query(); }
        }
        else if (current_state == STATE_SUB_CATEGORY) {
            if (sub_id == 100) { func_category_register(); }
            else if (sub_id == 200) { func_category_delete(); }
            else if (sub_id == 300) { func_category_modify(); }
            else if (sub_id == 400) { func_category_query(); }
        }
        else if (current_state == STATE_SUB_SALES) {
            if (sub_id == 610) { func_cart_print(); }
            else if (sub_id == 620) { func_cart_input(); }
            else if (sub_id == 630) { func_cart_delete(); }
            else if (sub_id == 640) { func_cart_reset(); }
            else if (sub_id == 650) { func_cart_checkout(); }
        }


        werase(last_command_win);
        if (has_colors()) {wattron(last_command_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
        mvwprintw(last_command_win, 1, 2, "마지막 작업: [%ls] 메뉴의 [%ls]",menu_name ,action);
        if (has_colors()) {wattroff(last_command_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
    }

    // 3. 기능 실행 상태에서는 Enter 키 입력 처리 (현재는 무시)
    else if (current_state == STATE_FUNCTION_RUNNING) {
    }

    if (current_state != old_state) {
        previous_state = old_state;
    }
}

// 키보드 입력을 받아 메뉴를 이동시키고 기능을 실행하는 로직
void handle_menu_input(int key) {
    int old_selection = current_menu_selection;

    int max_items = (current_state == STATE_MAIN_MENU) ? MAX_MAIN_MENU_ITEMS :
                    (current_state == STATE_SUB_SALES) ? MAX_SALES_SUB_ITEMS : MAX_SUB_MENU_ITEMS;

    Program_State old_state = current_state;

    if (current_state == STATE_FUNCTION_RUNNING && (key == 27 || key == 'b' || key == 'B')) {
        current_state = previous_state;

        if (current_state != old_state) {
            current_menu_selection = 0;
            current_max_items = MAX_MAIN_MENU_ITEMS;
        }
        werase(tooltip_win);
        werase(output_win);
        werase(command_win);
        return;
    }

    switch (key) {
        case KEY_UP:
            if (current_state != STATE_FUNCTION_RUNNING) {
                current_menu_selection = (current_menu_selection - 1 + max_items) % max_items;
            }
            break;
        case KEY_DOWN:
            if (current_state != STATE_FUNCTION_RUNNING) {
                current_menu_selection = (current_menu_selection + 1) % max_items;
            }
            break;
        case 10:
            handle_enter_key();
            break;

        case 27:
        case 'b':
        case 'B':
            if (current_state == STATE_MAIN_MENU) {
                program_exit_flag = 1;
                return;
            }

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

    if (old_selection != current_menu_selection || key == 10 || key == 27 || key == 'b' || key == 'B') {
    }
}

// 메인 루프 함수 구현
void run_main_loop() {
    int rows, cols;
    int ch;

    while(program_exit_flag == 0) {

        ch = getch();

        if (ch == ERR) {
            continue;
        }

        getmaxyx(stdscr, rows, cols);

        switch (ch) {
            case KEY_RESIZE:
                resize_handler();
                break;

            case 27:
            case KEY_UP:
            case KEY_DOWN:
            case 10:
            case 'b':
            case 'B':
            case KEY_F(1):
            case KEY_F(2):
            case KEY_F(3):
            case KEY_F(4):
            case KEY_F(5):
            case KEY_F(6):

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