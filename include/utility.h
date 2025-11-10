#ifndef UTILITY_H
#define UTILITY_H

#include "include.h"

// 문자열 좌우 공백 제거 함수 (char* 버전) (utility.c 구현)
char* trim_whitespace(char *str);

// 재사용 가능한 와이드 문자열 입력 함수 (utility.c 구현)
int get_wide_string_input(WINDOW *win, wchar_t *buffer, int max_len);       // 값을 한번 입력 받는 함수
int get_wide_string_cart_input(WINDOW *win, wchar_t *buffer, int max_len);  // 값을 여러번 입력 받아 장바구니에 추가하는 함수
int get_user_input(WINDOW *win, char *buffer, int maxlen);                  // 메뉴 입력을 처리하는 함수

#endif // UTILITY_H