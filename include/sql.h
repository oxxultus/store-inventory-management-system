#ifndef SQL_H
#define SQL_H

#include "line_buffer.h"
#include "include.h"

// ProC 전역 오류 처리 함수
extern void sql_error(char *msg);

// 입고 관리 (F1)
extern int inbound_insert(wchar_t* input_buffer_w);
extern int inbound_delete(wchar_t* input_buffer_w);
extern int inbound_modify(wchar_t* input_buffer_w);
extern int inbound_select(wchar_t* input_buffer_w);

char* insert_sale_record(double total_amount, const char *payment_type);
int insert_sale_detail_item(const char *sale_num, const char *barcode, int quantity, double price);

// 바코드 유효성 검사 및 이름 반환 및 가격 반환 (상품이 없으면: 0 있으면 1)
extern int get_product_price(const char *barcode, int *quantity, char *product_name_out, double *price_out);

#endif