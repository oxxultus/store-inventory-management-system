#include "line_buffer.h"

#define INITIAL_CAPACITY 50

/**
 * @brief LineBuffer 구조체를 초기화합니다.
 */
void init_buffer(LineBuffer *buffer) {
    buffer->count = 0;
    buffer->capacity = INITIAL_CAPACITY;
    buffer->lines = (char **)malloc(buffer->capacity * sizeof(char *));
    if (buffer->lines == NULL) {
        perror("초기 버퍼 할당 실패");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief 버퍼에 새 라인을 동적으로 추가합니다.
 */
void add_line(LineBuffer *buffer, const char *format, ...) {
    if (buffer->count >= buffer->capacity) {
        buffer->capacity *= 2;
        char **new_lines = (char **)realloc(buffer->lines, buffer->capacity * sizeof(char *));
        if (new_lines == NULL) {
            perror("버퍼 realloc 실패");
            return;
        }
        buffer->lines = new_lines;
    }

    char *new_line = (char *)malloc(MAX_LINE_LENGTH);
    if (new_line == NULL) {
        perror("새로운 라인 메모리 할당 실패");
        return;
    }

    va_list args;
    va_start(args, format);
    vsnprintf(new_line, MAX_LINE_LENGTH, format, args);
    va_end(args);

    buffer->lines[buffer->count] = new_line;
    buffer->count++;
}

/**
 * @brief 버퍼의 모든 문자열 메모리를 해제하고 구조체를 초기 상태로 되돌립니다.
 */
void clear_buffer(LineBuffer *buffer) {
    if (buffer->lines != NULL) {
        for (int i = 0; i < buffer->count; i++) {
            free(buffer->lines[i]);
        }
        free(buffer->lines);
    }
    buffer->lines = NULL;
    buffer->count = 0;
    buffer->capacity = 0;
}

int display_scroll_output(LineBuffer *buffer) {

    int max_rows, max_cols;
    getmaxyx(output_win, max_rows, max_cols);

    int output_rows = max_rows - 6;
    if (output_rows <= 0) output_rows = 1;

    int start_line_index = 0;
    int ch;

    int total_data_lines = buffer->count - 2;

    int max_page_start_index;
    int total_pages;

    if (total_data_lines > output_rows) {
        max_page_start_index = buffer->count - output_rows;
        total_pages = (total_data_lines + output_rows - 1) / output_rows;
    } else {
        max_page_start_index = 0;
        total_pages = 1;
    }

    nodelay(command_win, FALSE);
    keypad(command_win, TRUE);
    curs_set(0);

    while (1) {
        werase(output_win);

        if (has_colors()) {wattron(output_win, COLOR_PAIR(1) | A_BOLD); }
            box(output_win, 0, 0);
            mvwprintw(output_win, 1, 2, "[입고 내역 조회 결과] (총 %d 항목)", total_data_lines);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(1) | A_BOLD); }

        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
            mvwprintw(output_win, 3, 2, "%s", buffer->lines[0]);
            mvwprintw(output_win, 4, 2, "%s", buffer->lines[1]);
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }

        if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            int page_info_x = max_cols - 20;
            if (total_pages > 1) {
                 mvwprintw(output_win, 1, page_info_x, "페이지: %d / %d",
                           (start_line_index / output_rows) + 1,
                           total_pages);
            }
        if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }

        int current_y = 5;

        for (int i = 0; i < output_rows; i++) {
            int buffer_index = 2 + start_line_index + i;
            if (buffer_index >= buffer->count) break;

            const char *line = buffer->lines[buffer_index];
            mvwprintw(output_win, current_y++, 2, "%s", line);
        }

        int tooltip_rows, tooltip_cols;
        getmaxyx(tooltip_win, tooltip_rows, tooltip_cols);

        werase(tooltip_win);
        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(1) | A_BOLD); }
            box(tooltip_win, 0, 0);
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(1) | A_BOLD); }

        if (has_colors()) {wattron(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }
            mvwaddwstr(tooltip_win, 1, 2, L"◀/▶ 키로 스크롤 | 🅴 🆂 🅲 로 종료");
        if (has_colors()) {wattroff(tooltip_win, COLOR_PAIR(7) | A_BOLD | A_DIM); }


        werase(command_win);
        if (has_colors()) {wattron(command_win, COLOR_PAIR(1) | A_BOLD); }
            box(command_win, 0, 0);
            mvwaddwstr(command_win, 1, 2, L"[!] 키보드 명령 대기중 (스크롤 화면)");
        if (has_colors()) {wattroff(command_win, COLOR_PAIR(1) | A_BOLD); }

        wnoutrefresh(output_win);
        wnoutrefresh(tooltip_win);
        wnoutrefresh(command_win);
        doupdate();

        ch = wgetch(command_win);

        switch (ch) {
            case KEY_LEFT:
                if (start_line_index > 0) {
                    start_line_index -= output_rows;
                    if (start_line_index < 0) start_line_index = 0;
                }
                break;

            case KEY_RIGHT:
                if (total_data_lines > output_rows && start_line_index < max_page_start_index) {
                    start_line_index += output_rows;
                    if (start_line_index > max_page_start_index) {
                        start_line_index = max_page_start_index;
                    }
                }
                break;

            case 27:
                goto exit_loop;

            default:
                break;
        }
    }

exit_loop:

    nodelay(command_win, TRUE);
    keypad(command_win, FALSE);
    curs_set(0);

    werase(output_win);
    werase(tooltip_win);
    werase(command_win);
    doupdate();

    return 1;
}