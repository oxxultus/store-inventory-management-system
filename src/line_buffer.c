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