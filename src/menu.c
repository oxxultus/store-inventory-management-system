#include "menu.h"

Menu_Item main_menu_items[MAX_MAIN_MENU_ITEMS] = {
    { L"①  입고 관리 (F1)", 1 },
    { L"②  재고 관리 (F2)", 2 },
    { L"③  상품 관리 (F3)", 3 },
    { L"④  공급업체 관리 (F4)", 4 },
    { L"⑤  카테고리 관리 (F5)", 5 },
    { L"⑥  상품 판매 (F6)", 6 },
    { L"⑦  종료 (ESC)", 0 }
};

Menu_Item sub_menu_template[MAX_SUB_MENU_ITEMS] = {
    { L"①  등록/추가", 100 },
    { L"②  삭제", 200 },
    { L"③  수정", 300 },
    { L"④  조회", 400 }
};

Menu_Item sales_sub_menu[MAX_SALES_SUB_ITEMS] = {
    { L"①  장바구니 상품 출력", 610 },
    { L"②  장바구니 상품 추가", 620 },
    { L"③  장바구니 상품 삭제", 630 },
    { L"④  장바구니 초기화", 640 },
    { L"⑤  결제", 650 }
};

int current_menu_selection = 0;

int program_exit_flag = 0;

int sales_input_flag = 0;

Program_State current_state = STATE_MAIN_MENU;

Program_State previous_state = STATE_MAIN_MENU;

int current_max_items = MAX_MAIN_MENU_ITEMS;

const wchar_t *get_current_menu_title() {
    switch (current_state) {
        case STATE_MAIN_MENU: return L"메인";
        case STATE_SUB_PURCHASE: return L"입고 관리";
        case STATE_SUB_INVENTORY: return L"재고 관리";
        case STATE_SUB_PRODUCT: return L"상품 관리";
        case STATE_SUB_SUPPLIER: return L"공급업체 관리";
        case STATE_SUB_CATEGORY: return L"카테고리 관리";
        case STATE_SUB_SALES: return L"상품 판매";
        default: return L"";
    }
}

void init_menu_data() {
}