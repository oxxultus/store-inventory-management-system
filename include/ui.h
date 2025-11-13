#ifndef UI_H
#define UI_H

#include "include.h"

// 창 포인터 선언: 모든 창 포인터를 전역으로 선언
extern WINDOW *title_win;
extern WINDOW *status_win;
extern WINDOW *last_command_win;
extern WINDOW *menu_win;
extern WINDOW *output_win;
extern WINDOW *tooltip_win;
extern WINDOW *command_win;
extern WINDOW *console_win;
extern WINDOW *listbar_win;

// 화면 분할을 위한 상수 정의
#define TITLE_HEIGHT 6          // 상단바 높이 (6줄)
#define STATUS_HEIGHT 3         // DB 상태 창 높이 (3줄)
#define LAST_COMMAND_HEIGHT 3   // 마지막 명령 실행 기록 창 높이(3줄)
#define LISTBAR_WIDTH 5         // 좌우 리스트 전환 창 너비
#define MENU_WIDTH 25           // 왼쪽 메뉴의 너비
#define TOOLTIP_HEIGHT 3        // 툴팁 창 높이 (3줄)
#define COMMAND_HEIGHT 3        // 명령 창 높이 (3줄)
#define CONSOLE_HEIGHT 8        // 콘솔 창 높이 (3줄)  

// 함수 프로토타입 선언 (ui.c 구현)
extern void initialize_ncurses();
void delete_windows();
void create_windows(int rows, int cols);

// 창을 그리는 함수 (ui.c 구현)
void draw_outline_all();                    // 모든 창 테두리 그리는 함수
void draw_menu();                           // 메뉴를 그리는 함수 (태두리 포함)
void set_window_print(int rows, int cols);  // 각 창의 초기 값을 그리는 함수
void refresh_all_win();                     // 모든 창을 갱신하는 함수
void draw_ui(int rows, int cols);           // 모든 창을 그리는 함수

// 창 크기 변경 감지 함수 (ui.c 구현)
void resize_handler();

// 메인 루프 함수 프로토타입 (event_handler.c 구현)
void run_main_loop();

#endif