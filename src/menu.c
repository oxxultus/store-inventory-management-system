#include "menu.h"

// 메인 메뉴 항목 목록 정의 (7개 항목) ①②③④⑤⑥⑦⑧⑨
Menu_Item main_menu_items[MAX_MAIN_MENU_ITEMS] = {
    { L"①  입고 관리 (F1)", 1 },
    { L"②  재고 관리 (F2)", 2 },
    { L"③  상품 관리 (F3)", 3 },
    { L"④  공급업체 관리 (F4)", 4 },
    { L"⑤  카테고리 관리 (F5)", 5 },
    { L"⑥  상품 판매 (F6)", 6 },
    { L"⑦  종료 (ESC)", 0 }
};

// 서브 메뉴 템플릿 정의 (등록, 삭제, 조회)
Menu_Item sub_menu_template[MAX_SUB_MENU_ITEMS] = {
    { L"①  등록/추가", 100 },
    { L"②  삭제", 200 },
    { L"③  수정", 300 },
    { L"④  조회", 400 }
};

// [추가] 상품 판매 서브 메뉴 정의 (2개 항목)
Menu_Item sales_sub_menu[MAX_SALES_SUB_ITEMS] = {
    { L"①  장바구니", 610 },
    { L"②  결제", 620 }
};

// 현재 선택 인덱스 초기값
int current_menu_selection = 0; 

// 프로그램 종료 플래그 정의 및 초기화
int program_exit_flag = 0; 

// 상품 판매 입력 플래그 초기화
int sales_input_flag = 0;

// 현재 프로그램 상태 초기값: 메인 메뉴
Program_State current_state = STATE_MAIN_MENU; 

// 이전 프로그램 상태 초기값: 메인 메뉴
Program_State previous_state = STATE_MAIN_MENU;

// 현재 메뉴 항목 개수 정의 (메인 메뉴 항목 개수로 초기화)
int current_max_items = MAX_MAIN_MENU_ITEMS;

// 서브 메뉴 이름 출력을 위한 함수 정의
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

// (현재는 빈 함수이지만, 모듈 구조 유지를 위해 정의)
void init_menu_data() {
    // 향후 DB 연결 후 초기 데이터 로드 등에 사용 가능
}