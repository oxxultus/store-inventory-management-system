#ifndef SQL_H
#define SQL_H

#include "include.h"

// 바코드 유효성 검사 및 이름 반환 및 가격 반환 (상품이 없으면: 0 있으면 1)
int get_product_price(const char *barcode, char *product_name_out, double *price_out);

#endif // SQL_H