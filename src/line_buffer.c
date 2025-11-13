#include "line_buffer.h"

#define INITIAL_CAPACITY 50 // 초기 할당할 라인의 개수

/**
 * @brief LineBuffer 구조체를 초기화합니다.
 */
void init_buffer(LineBuffer *buffer) {
    buffer->count = 0;
    buffer->capacity = INITIAL_CAPACITY;
    // 초기 메모리 할당
    buffer->lines = (char **)malloc(buffer->capacity * sizeof(char *));
    if (buffer->lines == NULL) {
        perror("Error: Initial buffer allocation failed");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief 버퍼에 새 라인을 동적으로 추가합니다. (printf 형식 지원)
 */
void add_line(LineBuffer *buffer, const char *format, ...) {
    // 1. 용량 확인 및 확장 (필요 시 realloc)
    if (buffer->count >= buffer->capacity) {
        buffer->capacity *= 2;
        char **new_lines = (char **)realloc(buffer->lines, buffer->capacity * sizeof(char *));
        if (new_lines == NULL) {
            perror("Error: Buffer realloc failed");
            return;
        }
        buffer->lines = new_lines;
    }

    // 2. 새 문자열을 위한 메모리 할당 (MAX_LINE_LENGTH만큼)
    char *new_line = (char *)malloc(MAX_LINE_LENGTH);
    if (new_line == NULL) {
        perror("Error: New line allocation failed");
        return;
    }

    // 3. 가변 인수를 받아 문자열 포맷팅
    va_list args;
    va_start(args, format);
    vsnprintf(new_line, MAX_LINE_LENGTH, format, args);
    va_end(args);

    // 4. 버퍼에 추가하고 카운트 증가
    buffer->lines[buffer->count] = new_line;
    buffer->count++;
}

/**
 * @brief 버퍼의 모든 문자열 메모리를 해제하고 구조체를 초기 상태로 되돌립니다.
 */
void clear_buffer(LineBuffer *buffer) {
    if (buffer->lines != NULL) {
        // 각 라인 문자열 메모리 해제
        for (int i = 0; i < buffer->count; i++) {
            free(buffer->lines[i]);
        }
        // 라인 포인터 배열 자체 메모리 해제
        free(buffer->lines);
    }
    // 상태 초기화
    buffer->lines = NULL;
    buffer->count = 0;
    buffer->capacity = 0;
}

int display_scroll_output(LineBuffer *buffer) {
    
    // --- 변수 선언 및 초기화 ---
    int max_rows, max_cols;
    getmaxyx(output_win, max_rows, max_cols);
    
    // 🌟 데이터 출력 행 수 계산: max_rows - 6 (테두리 2 + 제목 1 + 고정 헤더 2 + 여유 공간 1)
    int output_rows = max_rows - 6; 
    if (output_rows <= 0) output_rows = 1;

    int start_line_index = 0; // 데이터의 출력 시작 인덱스 (스크롤 위치)
    int ch; // 키 입력 변수
    
    // LineBuffer의 헤더 2줄(index 0, 1)을 제외한 실제 데이터 라인 수
    int total_data_lines = buffer->count - 2; 
    
    int max_page_start_index;
    int total_pages;
    
    // 페이지 계산 로직
    if (total_data_lines > output_rows) {
        // 스크롤 시작 인덱스 최대값: 전체 라인 수에서 output_rows를 뺀 값
        max_page_start_index = buffer->count - output_rows; 
        // 총 페이지 수 계산 (데이터 라인 / 출력 행 수)
        total_pages = (total_data_lines + output_rows - 1) / output_rows;
    } else {
        max_page_start_index = 0;
        total_pages = 1;
    }

    // --- 1. 입력 루프 및 출력 시작 ---
    
    // command_win에서 블록킹 입력 받을 준비
    nodelay(command_win, FALSE); 
    keypad(command_win, TRUE);   
    curs_set(0);            

    while (1) {
        werase(output_win);
        
        // 1-1. 윈도우 테두리 및 제목 출력
        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwprintw(output_win, 1, 2, "[입고 내역 조회 결과] (총 %d 항목)", total_data_lines);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }
        
        // 1-2. 🌟 헤더 고정 출력 (스크롤되지 않음 - Buffer index 0, 1)
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
            // 3행: 헤더 제목 (Buffer index 0)
            mvwprintw(output_win, 3, 2, "%s", buffer->lines[0]); 
            // 4행: 구분선 (Buffer index 1)
            mvwprintw(output_win, 4, 2, "%s", buffer->lines[1]); 
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }

        // 1-3. 스크롤 위치 및 도움말 출력 (페이지 상태)
        
        // 현재 페이지 상태 표시
        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            int page_info_x = max_cols - 20;
            if (total_pages > 1) { 
                 mvwprintw(output_win, 1, page_info_x, "페이지: %d / %d", 
                           (start_line_index / output_rows) + 1, 
                           total_pages);
            }
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        // 1-4. LineBuffer 클리핑 및 데이터 출력
        int current_y = 5; // 🌟 데이터 출력 시작 Y 위치 (5행)
        
        for (int i = 0; i < output_rows; i++) {
            // 2 (고정 헤더)를 건너뛰고 데이터 시작
            int buffer_index = 2 + start_line_index + i; 
            if (buffer_index >= buffer->count) break;

            const char *line = buffer->lines[buffer_index];
            mvwprintw(output_win, current_y++, 2, "%s", line);
        }

        // 1-5. Tooltip 출력 (ESC, 좌/우 키 안내)
        int tooltip_rows, tooltip_cols;
        getmaxyx(tooltip_win, tooltip_rows, tooltip_cols);
        
        werase(tooltip_win);
        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
            box(tooltip_win, 0, 0);
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
        
        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(tooltip_win, 1, 2, L"◀/▶ 키로 스크롤 | 🅴 🆂 🅲 로 종료");
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        // 1-6. command_win을 입력 대기 상태로 표시
        werase(command_win);
        if (has_colors()) {wattron(command_win, COLOR_PAIR(1) | A_BOLD); }
            box(command_win, 0, 0);
            mvwaddwstr(command_win, 1, 2, L"[!] 키보드 명령 대기중 (스크롤 화면)");
        if (has_colors()) {wattroff(command_win, COLOR_PAIR(1) | A_BOLD); }

        wnoutrefresh(output_win);
        wnoutrefresh(tooltip_win);
        wnoutrefresh(command_win); 
        doupdate();

        // 1-7. 키 입력 대기 및 처리
        ch = wgetch(command_win); // command_win에서 블록킹 입력 받기

        switch (ch) {
            case KEY_LEFT: // 좌측 키 (이전 페이지)
                if (start_line_index > 0) {
                    start_line_index -= output_rows;
                    if (start_line_index < 0) start_line_index = 0;
                }
                break;

            case KEY_RIGHT: // 우측 키 (다음 페이지)
                if (total_data_lines > output_rows && start_line_index < max_page_start_index) {
                    start_line_index += output_rows;
                    if (start_line_index > max_page_start_index) {
                        start_line_index = max_page_start_index;
                    }
                }
                break;

            case 27: // ESC 키 감지
                goto exit_loop;

            default:
                break;
        }
    }

exit_loop:
    // --- 2. Ncurses 상태 원복 ---
    
    // 상태 원복
    nodelay(command_win, TRUE); 
    keypad(command_win, FALSE);
    curs_set(0);       

    // 윈도우 정리
    werase(output_win);
    werase(tooltip_win);
    werase(command_win); 
    doupdate(); 
    
    return 1; // 성공적으로 출력을 마쳤음을 반환
}
