# Makefile for C/C++ Project with Oracle Pro*C/C++ 

# ──────────────────────────────────────────────────────────────────────────
# 환경 변수 및 경로 설정 
# Oracle Instant Client SDK 경로 및 라이브러리 설정
ORACLE_INCLUDE = -I$(ORACLE_HOME)/sdk/include
ORACLE_LIB = -L$(ORACLE_HOME)
ORACLE_LINK = -lclntsh

# 프로젝트 디렉터리 정의
INCLUDE_DIR = ./include
SOURCE_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# C 컴파일러 플래그 설정
# -I$(INCLUDE_DIR): 사용자 정의 헤더 경로
# -Wall: 모든 경고 활성화
# -Wno-unused: 사용되지 않는 변수 경고 비활성화 (개발 편의성 증진)
CFLAGS = -I$(INCLUDE_DIR) $(ORACLE_INCLUDE) -Wall -Wno-unused

# 링커 플래그 설정
# -lncursesw: ncursesw 라이브러리 링크 (한글/와이드 문자 지원 TUI)
LDFLAGS = -lncursesw $(ORACLE_LIB) $(ORACLE_LINK)

# ──────────────────────────────────────────────────────────────────────────
# 파일 목록 및 경로 정의

# Pro*C 원본 파일 (프리컴파일 대상)
PC_SOURCE = $(SOURCE_DIR)/sql.pc

# Pro*C에 의해 생성될 C 파일
SQL_C_FILE = $(SOURCE_DIR)/sql.c

# C 소스 파일 (수동 작성 파일 목록)
C_SOURCES = $(SOURCE_DIR)/main.c \
            $(SOURCE_DIR)/ui.c \
            $(SOURCE_DIR)/menu.c \
            $(SOURCE_DIR)/event_handler.c \
            $(SOURCE_DIR)/menu_function.c \
            $(SOURCE_DIR)/line_buffer.c \
            $(SOURCE_DIR)/utility.c \
            $(SOURCE_DIR)/cart.c

# 모든 C 소스 파일 (.c 확장자)
ALL_C_SOURCES = $(C_SOURCES) $(SQL_C_FILE)

# 오브젝트 파일 목록 (build/src/ 디렉터리에 생성될 경로 지정)
# patsubst: src/%.c 패턴을 build/src/%.o 패턴으로 변환
OBJECTS = $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/$(SOURCE_DIR)/%.o, $(ALL_C_SOURCES))

# 최종 실행 파일 경로
TARGET = $(BIN_DIR)/main
# ──────────────────────────────────────────────────────────────────────────
# 기본 타겟 

# 'make' 실행 시 기본 동작 (prepare -> bin/main 생성)
all: prepare $(TARGET)


# ──────────────────────────────────────────────────────────────────────────
# 디렉터리 준비 타겟

# 빌드 및 바이너리 디렉터리가 존재하도록 보장
prepare:
	@mkdir -p $(BUILD_DIR)/$(SOURCE_DIR) # build/src 디렉터리 생성
	@mkdir -p $(BIN_DIR)                # bin 디렉터리 생성


# ──────────────────────────────────────────────────────────────────────────
# 링킹 타겟

# 모든 오브젝트 파일(.o)이 준비되면 최종 실행 파일 생성
# OBJECTS 변수에 build/src/*.o 파일 경로들이 담겨 있음
$(TARGET): $(OBJECTS)
	@echo "───────────────────────────────── 실행파일 생성 ─────────────────────────────────"
	@echo ""
	@echo "실행 파일 경로: $(TARGET)..."
	@gcc $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo ""
	@echo "─────────────────────────────────────────────────────────────────────────────────"


# ──────────────────────────────────────────────────────────────────────────
# Pro*C 프리컴파일 규칙

# src/sql.pc가 변경되면 src/sql.c를 생성 (PROC의 최신 glibc의 헤더를 해석하지 못하는 오류 출력 제거)
$(SQL_C_FILE): $(PC_SOURCE)
	@echo ""
	@echo "────────────────────────────── Pro*C 컴파일러 실행 ──────────────────────────────"
	@echo ""
	@proc iname=$(PC_SOURCE) include=$(INCLUDE_DIR) > /dev/null 2>&1


# ──────────────────────────────────────────────────────────────────────────
# 컴파일 규칙 (모든 .o 파일을 build/src/에 넣습니다)

# 1. 사용자 C 파일 규칙: src/%.c -> build/src/%.o
$(BUILD_DIR)/$(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.c
	@echo "컴파일 $< -> $@"
	@gcc $(CFLAGS) -c $< -o $@


# 2. Pro*C 생성 C 파일 규칙: src/sql.c -> build/src/sql.o (특수 의존성 처리)
$(BUILD_DIR)/$(SOURCE_DIR)/sql.o: $(SQL_C_FILE)
	@echo "Pro*C 로 생성된 파일 컴파일 진행 ($<)..."
	@echo "컴파일 $< -> $@"
	@gcc $(CFLAGS) -c $< -o $@
	@echo ""


# ──────────────────────────────────────────────────────────────────────────
# 정리 (Cleanup)

clean:
	@echo "───────────────────────────────── 빌드 파일 정리 ────────────────────────────────"
	@echo "프로젝트 빌드파일 정리 시작"
	@echo "  1. 생성된 실행 파일 삭제 (bin 폴더)"
	@rm -f $(TARGET)
	@echo "  2. 생성된 오브젝트 파일 및 빌드 디렉터리 전체 삭제"
	@rm -rf $(BUILD_DIR)
	@echo "  3. Pro*C 생성 C 파일 삭제 (재빌드를 위해 원본 .pc만 남김)"
	@rm -f $(SQL_C_FILE) $(SOURCE_DIR)/sql.lis
	@echo "정리 완료"
	@echo "─────────────────────────────────────────────────────────────────────────────────"

.PHONY: all clean prepare
# ──────────────────────────────────────────────────────────────────────────