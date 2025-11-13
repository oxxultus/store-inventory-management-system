-----

# 📁 디렉토리 구조 (Directory Structure)

본 프로젝트는 일관성 있는 빌드 및 유지보수를 위해 표준 C 프로젝트 구조를 따릅니다.

| 디렉토리 | 목적 | 내용물 |
| :--- | :--- | :--- |
| **`src/`** | **소스 코드** | 프로그램의 핵심 로직(`.c`, `.cpp`)을 포함합니다. |
| **`include/`** | **공개 헤더 파일** | 외부에 공개되는 함수, 구조체 등의 선언(`.h`, `.hpp`)을 포함합니다. 컴파일 시 `-I` 옵션으로 참조됩니다. |
| **`lib/`** | **외부 라이브러리 (선택적)** | 프로젝트가 의존하는 외부 바이너리 라이브러리(`.a`, `.so`, `.lib` 등)를 보관합니다. (시스템 라이브러리는 제외) |
| **`test/`** | **테스트 코드** | 각 모듈의 기능 검증을 위한 단위 테스트 코드를 포함합니다. |
| **`docs/`** | **문서** | 프로젝트 설명서, API 레퍼런스 등 기타 문서를 포함합니다. |
| **`build/`** | **빌드 임시 파일** | GCC/Make 등의 빌드 시스템이 생성하는 오브젝트 파일(`.o`) 및 임시 파일이 저장되는 공간입니다. (Git 관리 대상 제외) |
| **`bin/`** | **최종 실행 파일** | 빌드 완료 후 생성되는 최종 실행 파일 또는 라이브러리 파일이 저장됩니다. (Git 관리 대상 제외) |

-----

## 🛠️ 빌드 방법 (Building the Project)

### 요구사항 (Prerequisites)

  * GCC (GNU Compiler Collection)
  * Make (또는 CMake)

### 빌드 단계 (Build Steps)

1.  **빌드 디렉토리 생성 및 이동** (Clean Build를 권장합니다.)

    ```bash
    mkdir build
    cd build
    ```

2.  **빌드 실행** (예시: `make` 사용 시)

    ```bash
    make
    ```

    *프로젝트에 `Makefile`이 포함되어 있지 않다면, 직접 GCC 명령을 사용해야 합니다.*

3.  **실행 파일 확인**

    빌드에 성공하면, 최종 실행 파일은 `../bin/` 디렉토리에 생성됩니다.

    ```bash
    ../bin/[프로그램_이름]
    ```

    현제 빌드 명령어 (계속 업데이트 중)
    ```bash
    gcc -I../include main.c ui.c data.c event_handler.c -o inventory_manager -lncursesw -std=c11 -D_XOPEN_SOURCE_EXTENDED=1

    gcc -I../include main.c ui.c menu.c event_handler.c menu_function.c line_buffer.c utility.c cart.c sql.c -o main -lncursesw -I$ORACLE_HOME/sdk/include -L$ORACLE_HOME -lclntsh

    # test 파일 빌드 명령어
    # gcc main.c -o main -I/opt/oracle/instantclient_21_20/sdk/include -L/opt/oracle/instantclient_21_20 -lclntsh
    gcc main.c -o main -I$ORACLE_HOME/sdk/include -L$ORACLE_HOME -lclntsh

    # 11 13 갱신
    proc sql.pc include=../include
    gcc -I../include main.c ui.c menu.c event_handler.c menu_function.c line_buffer.c utility.c cart.c sql.c -o main -lncursesw -I$ORACLE_HOME/sdk/include -L$ORACLE_HOME -lclntsh

    ```

-----