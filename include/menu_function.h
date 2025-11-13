#ifndef MENU_FUNCTION_H
#define MENU_FUNCTION_H

#include "include.h"

// 1. 입고 관리 (등록/추가, 삭제, 조회)
void func_purchase_register();
void func_purchase_delete();
void func_purchase_modify();
void func_purchase_query();

// 2. 재고 관리
void func_inventory_register();
void func_inventory_delete();
void func_inventory_modify();
void func_inventory_query();

// 3. 상품 관리
void func_product_register();
void func_product_delete();
void func_product_modify();
void func_product_query();

// 4. 공급업체 관리
void func_supplier_register();
void func_supplier_delete();
void func_supplier_modify();
void func_supplier_query();

// 5. 카테고리 관리
void func_category_register();
void func_category_delete();
void func_category_modify();
void func_category_query();

// 상품 판매
void func_cart_print();
void func_cart_input();
void func_cart_delete();
void func_cart_reset();
void func_cart_checkout();

#endif