#ifndef CART_H
#define CART_H

#include "include.h"

typedef struct {
    char barcode[20]; // 1열: 문자열 (바코드, 최대 19글자)
    char name[50]; // 2열: 문자열 (상품 이름, 최대 49글자)
    int quantity;  // 3열: 수량 (정수)
    double price;  // 4열: 개당 가격 (실수)
} CartItems;

// 장바구니를 위한 전역 변수 선언
extern CartItems *cartitems;
extern int NUM_ITEMS;

// 장바구니 크기 비교를 위한 이전 항목 개수
extern int g_prev_num_items;

void add_cart_item(const char *barcode, const char *name, int qty, double prc);
void free_cart_items();
int check_change_in_cart();
void display_cart_items();
void display_cart_items_noInfo();
void display_cart_items_deleteinfo(int index);
int delete_cart_item(int index);
void display_cart_checkout();

#endif // CART_H