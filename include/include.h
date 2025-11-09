#ifndef INCLUDE_H
#define INCLUDE_H

// POSIX 및 X/Open 표준 매크로 정의
#define _XOPEN_SOURCE 600
#define _XOPEN_SOURCE_EXTENDED 1

// 표준 라이브러리
#include <curses.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <wctype.h>
#include <string.h>
#include <ctype.h>

// 프로젝트 내부 헤더 파일
#include "menu.h" // 데이터 관련 구조체 및 상수 포함
#include "cart.h" // 장바구니 관련 구조체 및 함수 포함
#include "menu_function.h" // 메뉴 기능 함수 포함
#include "ui.h" // UI 관련 함수 및 전역 변수 포함
#include "utility.h" // 사용자 설정 유틸리티 함수 포함

#endif // INCLUDE_H