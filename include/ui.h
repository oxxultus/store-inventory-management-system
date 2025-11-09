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

// 화면 분할을 위한 상수 정의
#define TITLE_HEIGHT 6   // 상단바 높이 (6줄)
#define STATUS_HEIGHT 3   // DB 상태 창 높이 (3줄)
#define LAST_COMMAND_HEIGHT 3   // 마지막 명령 실행 기록 창 높이(3줄)
#define MENU_WIDTH 25     // 왼쪽 메뉴의 너비
#define TOOLTIP_HEIGHT 3 // 툴팁 창 높이 (3줄)
#define COMMAND_HEIGHT 3  // 명령 창 높이 (3줄)
#define CONSOLE_HEIGHT 8   // 콘솔 창 높이 (3줄)  

// 함수 프로토타입 선언
void initialize_ncurses();
void delete_windows();
void create_windows(int rows, int cols);
void draw_ui(int rows, int cols);
void resize_handler();

// 창에 따른 그리기 함수 선언
void draw_menu(); // 메뉴

// 메인 루프 함수 프로토타입 (event_handler.c에 구현됨)
void run_main_loop();

int get_user_input(WINDOW *win, char *buffer, int maxlen);

#endif // UI_H