#ifndef MENU_H
#define MENU_H

#include <wchar.h>

// 프로그램 상태 정의
typedef enum {
    STATE_MAIN_MENU,        // 0: 메인 메뉴 화면
    STATE_SUB_PURCHASE,     // 1: 입고 관리 서브 메뉴
    STATE_SUB_INVENTORY,    // 2: 재고 관리 서브 메뉴
    STATE_SUB_PRODUCT,      // 3: 상품 관리 서브 메뉴
    STATE_SUB_SUPPLIER,     // 4: 공급업체 관리 서브 메뉴
    STATE_SUB_CATEGORY,     // 5: 카테고리 관리 서브 메뉴
    STATE_SUB_SALES,     // 5: 카테고리 관리 서브 메뉴
    STATE_FUNCTION_RUNNING  // 99: 기능 실행 중 (입력 폼, 조회 결과 등)
} Program_State;

// 메뉴 항목 구조체
typedef struct {
    const wchar_t *label;
    int function_id;      
} Menu_Item;

// 전역 데이터 선언
#define MAX_MAIN_MENU_ITEMS 7
extern Menu_Item main_menu_items[MAX_MAIN_MENU_ITEMS];
extern int current_menu_selection; 

// 서브 메뉴 항목 개수 정의
#define MAX_SUB_MENU_ITEMS 4
#define MAX_SALES_SUB_ITEMS 2 // 상품 판매 서브 메뉴 항목 개수
extern Menu_Item sub_menu_template[MAX_SUB_MENU_ITEMS]; // 등록/삭제/조회 템플릿
extern Menu_Item sales_sub_menu[MAX_SALES_SUB_ITEMS];   // 상품 판매 서브 메뉴 정의

extern int program_exit_flag; 
extern Program_State current_state; // 현재 프로그램 상태
extern Program_State previous_state; // 이전 프로그램 상태 저장

extern int sales_input_flag; // 상품 판매 입력 플래그

// 현재 메뉴 항목 개수를 동적으로 가져오는 함수
extern int current_max_items;

// 서브 메뉴 이름 출력을 위한 함수
const wchar_t *get_current_menu_title();

// 장바구니 데이터 구조 상수
#define CART_COLUMNS 2 // 바코드, 수량 (2열)
#define MAX_CART_ROWS 50 // 최대 50줄의 장바구니 항목 가정

#endif // MENU_H