#ifndef CART_H
#define CART_H

#include "include.h"

typedef struct {
    char barcode[20]; // 1열: 문자열 (바코드, 최대 19글자)
    char name[50]; // 2열: 문자열 (상품 이름, 최대 49글자)
    int quantity;  // 3열: 수량 (정수)
    double price;  // 4열: 개당 가격 (실수)
} CartItems;

extern CartItems *cartitems;    // 장바구니를 위한 전역 변수 선언
extern int NUM_ITEMS;           // 상품 수량
extern int g_prev_num_items;    // 장바구니 크기 비교를 위한 이전 항목 개수
extern int modify_carttiems_index;

// 상품 판매 메뉴를 위한 함수 (cart.c 에 구현)
void add_cart_item(const char *barcode, const char *name, int qty, double prc); // 장바구니 상품 추가하는 함수
void free_cart_items();                         // 장바구니 메모리 해제해서 초기화 하는 함수
int check_change_in_cart();                     // 장바구니 변경 내역을 확인하는 함수
void display_cart_items_scroll();               // 장바구니 내역 출력 함수
void display_checkout_items_scroll();           // 결제 내역 출력 함수
void display_cart_items_addinfo();              // 추가된 상품 내역을 표시 장바구니 내역 출력 함수
void display_cart_items_deleteinfo(int index);  // 삭제된 상품 내역을 표시 장바구니 내역 출력 함수
int delete_cart_item(int index);                // 장바구니 상품을 삭제하는 함수
void display_cart_checkout();                   // 장바구니 내역을 바탕으로 결제를 진행하는 함수
double calculate_total_cart_amount();           // 장바구니 내역에서 총 가격을 계산하는 함수*/

#endif // CART_H