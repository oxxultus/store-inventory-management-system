#ifndef UTILITY_H
#define UTILITY_H

#include "include.h"

// 문자열 좌우 공백 제거 함수 (char* 버전)
char* trim_whitespace(char *str);

// TODO: 실제 구현에서는 DB나 파일에서 조회해야 합니다.
int get_product_price(const char *barcode, char *product_name_out, double *price_out);


double calculate_total_cart_amount();

#endif // UTILITY_H