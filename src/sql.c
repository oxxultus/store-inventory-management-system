#include "sql.h"

// TODO: 실제 구현에서는 DB나 파일에서 조회해야 합니다.
int get_product_price(const char *barcode, char *product_name_out, double *price_out) {
    if (strcmp(barcode, "A100") == 0) {
        strcpy(product_name_out, "델몬트 바나나");
        *price_out = 500.0;
        return 1;
    } else if (strcmp(barcode, "A200") == 0) {
        strcpy(product_name_out, "오렌지 1");
        *price_out = 1000.0;
        return 1;
    } else if (strcmp(barcode, "A300") == 0) {
        strcpy(product_name_out, "오렌지 2");
        *price_out = 1000.0;
        return 1;
    } else if (strcmp(barcode, "A400") == 0) {
        strcpy(product_name_out, "오렌지 3");
        *price_out = 1000.0;
        return 1;
    } else if (strcmp(barcode, "A500") == 0) {
        strcpy(product_name_out, "오렌지 4");
        *price_out = 1000.0;
        return 1;
    } else if (strcmp(barcode, "A600") == 0) {
        strcpy(product_name_out, "오렌지 5");
        *price_out = 1000.0;
        return 1;
    } else if (strcmp(barcode, "A700") == 0) {
        strcpy(product_name_out, "오렌지 6");
        *price_out = 1000.0;
        return 1;
    } else if (strcmp(barcode, "A800") == 0) {
        strcpy(product_name_out, "오렌지 7");
        *price_out = 1000.0;
        return 1;
    } else if (strcmp(barcode, "A900") == 0) {
        strcpy(product_name_out, "오렌지 8");
        *price_out = 1000.0;
        return 1;
    } else if (strcmp(barcode, "B200") == 0) {
        strcpy(product_name_out, "오렌지 9");
        *price_out = 1000.0;
        return 1;
    } else {
        strcpy(product_name_out, "알 수 없는 상품");
        *price_out = 0.0;
        return 0;
    }
}
