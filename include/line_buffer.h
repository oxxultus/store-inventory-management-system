#ifndef LINE_BUFFER_H
#define LINE_BUFFER_H

#include "include.h"

#define MAX_LINE_LENGTH 512 // 각 라인의 최대 문자열 길이 (넉넉하게 설정)

typedef struct {
    char **lines;       // 문자열 포인터 배열 (각 라인을 저장)
    int count;          // 현재 저장된 라인 수
    int capacity;       // 현재 lines 배열이 저장할 수 있는 최대 라인 수
} LineBuffer;

// 함수 선언
void init_buffer(LineBuffer *buffer);
void add_line(LineBuffer *buffer, const char *format, ...);
void clear_buffer(LineBuffer *buffer);
int display_scroll_output(LineBuffer *buffer);

#endif