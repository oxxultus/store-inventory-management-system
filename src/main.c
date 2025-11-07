#include "ui.h" // UI 관련 함수 및 전역 변수 선언을 가져옴

// ======================= Main 함수 =========================

int main() {
    // 1. Ncurses 초기화 (로케일 설정 및 기본 모드 설정)
    initialize_ncurses();
    
    // 2. 최초 화면 크기 설정 및 UI 구성
    int rows, cols;
    // stdscr의 크기를 가져와서 창 생성 함수에 전달합니다.
    getmaxyx(stdscr, rows, cols); 
    create_windows(rows, cols);
    draw_ui(rows, cols);
    
    // 3. 메인 루프 함수 호출 (모든 키 입력 및 이벤트 처리)
    run_main_loop();

    // 4. 프로그램 종료 및 메모리 해제
    delete_windows(); // 생성된 모든 Ncurses 창 메모리 해제
    endwin();         // Ncurses 모드 종료 및 터미널 복구
    return 0;         // 프로그램 종료
}