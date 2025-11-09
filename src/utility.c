#include "utility.h"

char* trim_whitespace(char *str) {
    char *end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0) return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
    return str;
}

int get_product_price(const char *barcode, char *product_name_out, double *price_out) {
    if (strcmp(barcode, "A100") == 0) {
        strcpy(product_name_out, "델몬트 바나나");
        *price_out = 500.0;
        return 1;
    } else if (strcmp(barcode, "B200") == 0) {
        strcpy(product_name_out, "오렌지 주스");
        *price_out = 1000.0;
        return 1;
    } else {
        strcpy(product_name_out, "알 수 없는 상품");
        *price_out = 0.0;
        return 0;
    }
}

/**
 * @brief 장바구니에 있는 모든 항목의 총 합계 금액을 계산합니다.
 * @return double: 모든 상품 금액의 총합 (KRW)
 */
double calculate_total_cart_amount() {
    double grand_total = 0.0;
    
    // 장바구니 배열이 NULL이거나 비어있으면 0.0을 반환
    if (cartitems == NULL || NUM_ITEMS == 0) {
        return 0.0;
    }
    
    // 모든 항목을 순회하며 (수량 * 가격)을 총 합계에 더합니다.
    for (int i = 0; i < NUM_ITEMS; i++) {
        // 현재 항목의 총 금액을 계산
        double item_total = cartitems[i].quantity * cartitems[i].price;
        
        // 최종 합계에 추가
        grand_total += item_total;
    }
    
    return grand_total;
}