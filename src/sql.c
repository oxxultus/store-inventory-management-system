
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
  struct sql_cursor
  {
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned int magic;
  };
  typedef struct sql_cursor sql_cursor;
  typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
  unsigned char *tvnvsn; 
  unsigned short tvnvsnl; 
  unsigned char *tvnnm;
  unsigned short tvnnml; 
  unsigned char *tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
  unsigned int adtvsn; 
  unsigned short adtmode; 
  unsigned short adtnum;  
  sqltvn adttvn[1];       
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
  1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss
{
  unsigned int tdsvsn; 
  unsigned short tdsnum; 
  unsigned char *tdsval[1]; 
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
{
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp
{
  unsigned short fillen;
           char  filnam[7];
};
static struct sqlcxp sqlfpn =
{
    6,
    "sql.pc"
};


static unsigned int sqlctx = 4971;


static struct sqlexd {
   unsigned long  sqlvsn;
   unsigned int   arrsiz;
   unsigned int   iters;
   unsigned int   offset;
   unsigned short selerr;
   unsigned short sqlety;
   unsigned int   occurs;
            short *cud;
   unsigned char  *sqlest;
            char  *stmt;
   sqladts *sqladtp;
   sqltdss *sqltdsp;
   unsigned char  **sqphsv;
   unsigned long  *sqphsl;
            int   *sqphss;
            short **sqpind;
            int   *sqpins;
   unsigned long  *sqparm;
   unsigned long  **sqparc;
   unsigned short  *sqpadto;
   unsigned short  *sqptdso;
   unsigned int   sqlcmax;
   unsigned int   sqlcmin;
   unsigned int   sqlcincr;
   unsigned int   sqlctimeout;
   unsigned int   sqlcnowait;
            int   sqfoff;
   unsigned int   sqcmod;
   unsigned int   sqfmod;
   unsigned int   sqlpfmem;
   unsigned char  *sqhstv[7];
   unsigned long  sqhstl[7];
            int   sqhsts[7];
            short *sqindv[7];
            int   sqinds[7];
   unsigned long  sqharm[7];
   unsigned long  *sqharc[7];
   unsigned short  sqadto[7];
   unsigned short  sqtdso[7];
} sqlstm = {13,7};

/* SQLLIB Prototypes */
extern void sqlcxt (/*_ void **, unsigned int *,
                    struct sqlexd *, struct sqlcxp * _*/);
extern void sqlcx2t(/*_ void **, unsigned int *,
                    struct sqlexd *, struct sqlcxp * _*/);
extern void sqlbuft(/*_ void **, char * _*/);
extern void sqlgs2t(/*_ void **, char * _*/);
extern void sqlorat(/*_ void **, unsigned int *, void * _*/);

/* Forms Interface */
static int IAPSUCC = 0;
static int IAPFAIL = 1403;
static int IAPFTL  = 535;
extern void sqliem(/*_ unsigned char *, signed int * _*/);

 static char *sq0027 = 
"select I.INB_ID ,P.PROD_NAME ,D.DIST_NAME ,C.CATE_NAME ,TO_CHAR(I.INB_DATE,\
'YYYY-MM-DD') ,I.INB_QTY ,I.INB_COST  from SYSTEM.INBOUND I ,SYSTEM.PRODUCT P\
 ,SYSTEM.DISTRIBUTOR D ,SYSTEM.CATEGORY C where ((I.PROD_ID=P.PROD_ID and I.D\
IST_ID=D.DIST_ID) and I.CATE_ID=C.CATE_ID) order by I.INB_ID desc            \
 ";

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* CUD (Compilation Unit Data) Array */
static short sqlcud0[] =
{13,4130,873,0,0,
5,0,0,1,0,0,32,33,0,0,0,0,0,1,0,
20,0,0,0,0,0,27,105,0,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,10,0,0,
51,0,0,3,68,0,4,200,0,0,2,1,0,1,0,2,3,0,0,1,9,0,0,
74,0,0,4,65,0,4,213,0,0,2,1,0,1,0,2,3,0,0,1,9,0,0,
97,0,0,5,69,0,4,226,0,0,2,1,0,1,0,2,3,0,0,1,9,0,0,
120,0,0,6,102,0,3,229,0,0,5,5,0,1,0,1,9,0,0,1,9,0,0,1,9,0,0,1,9,0,0,1,4,0,0,
155,0,0,7,54,0,4,241,0,0,1,0,0,1,0,2,3,0,0,
174,0,0,8,126,0,3,247,0,0,6,6,0,1,0,1,9,0,0,1,9,0,0,1,9,0,0,1,9,0,0,1,3,0,0,1,
4,0,0,
213,0,0,9,98,0,5,257,0,0,2,2,0,1,0,1,3,0,0,1,9,0,0,
236,0,0,10,54,0,4,264,0,0,1,0,0,1,0,2,3,0,0,
255,0,0,11,100,0,3,269,0,0,3,3,0,1,0,1,9,0,0,1,9,0,0,1,3,0,0,
282,0,0,12,0,0,30,293,0,0,0,0,0,1,0,
297,0,0,13,0,0,32,300,0,0,0,0,0,1,0,
312,0,0,0,0,0,27,334,0,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,10,0,0,
343,0,0,15,45,0,2,381,0,0,1,1,0,1,0,1,9,0,0,
362,0,0,16,0,0,30,413,0,0,0,0,0,1,0,
377,0,0,17,0,0,32,420,0,0,0,0,0,1,0,
392,0,0,0,0,0,27,460,0,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,10,0,0,
423,0,0,19,148,0,4,507,0,0,7,1,0,1,0,2,9,0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,3,0,0,2,
4,0,0,1,9,0,0,
466,0,0,20,64,0,4,530,0,0,2,1,0,1,0,2,3,0,0,1,97,0,0,
489,0,0,21,68,0,4,544,0,0,2,1,0,1,0,2,3,0,0,1,97,0,0,
512,0,0,22,65,0,4,558,0,0,2,1,0,1,0,2,3,0,0,1,97,0,0,
535,0,0,23,137,0,5,613,0,0,7,7,0,1,0,1,9,0,0,1,9,0,0,1,9,0,0,1,9,0,0,1,3,0,0,1,
4,0,0,1,9,0,0,
578,0,0,24,0,0,30,649,0,0,0,0,0,1,0,
593,0,0,25,0,0,32,655,0,0,0,0,0,1,0,
608,0,0,0,0,0,27,695,0,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,10,0,0,
639,0,0,27,307,0,9,721,0,0,0,0,0,1,0,
654,0,0,27,0,0,13,740,0,0,7,0,0,1,0,2,9,0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,9,0,0,2,
3,0,0,2,4,0,0,
697,0,0,27,0,0,15,763,0,0,0,0,0,1,0,
712,0,0,28,0,0,30,793,0,0,0,0,0,1,0,
727,0,0,29,0,0,32,795,0,0,0,0,0,1,0,
742,0,0,0,0,0,27,829,0,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,10,0,0,
773,0,0,31,160,0,4,846,0,0,4,1,0,1,0,2,9,0,0,2,4,0,0,2,3,0,0,1,9,0,0,
804,0,0,32,0,0,30,888,0,0,0,0,0,1,0,
819,0,0,33,0,0,32,890,0,0,0,0,0,1,0,
834,0,0,0,0,0,27,925,0,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,10,0,0,
865,0,0,35,56,0,4,930,0,0,1,0,0,1,0,2,3,0,0,
884,0,0,36,110,0,3,944,0,0,4,4,0,1,0,1,9,0,0,1,4,0,0,1,9,0,0,1,9,0,0,
915,0,0,37,0,0,30,947,0,0,0,0,0,1,0,
930,0,0,38,0,0,32,953,0,0,0,0,0,1,0,
945,0,0,0,0,0,27,983,0,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,10,0,0,
976,0,0,40,62,0,4,988,0,0,1,0,0,1,0,2,3,0,0,
995,0,0,41,127,0,3,1004,0,0,6,6,0,1,0,1,9,0,0,1,9,0,0,1,9,0,0,1,3,0,0,1,4,0,0,
1,4,0,0,
1034,0,0,42,108,0,5,1010,0,0,3,2,0,1,0,1,3,0,0,1,9,0,0,2,3,0,0,
1061,0,0,43,48,0,2,1019,0,0,1,1,0,1,0,1,9,0,0,
1080,0,0,44,0,0,30,1029,0,0,0,0,0,1,0,
1095,0,0,45,0,0,32,1034,0,0,0,0,0,1,0,
};


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <ctype.h>
#include <sqlca.h>
#include <sqlcpr.h>
#include "sql.h"

// Pro*C 전역 오류 처리 함수
void sql_error(char *msg){
    // C 컴파일러 오류를 피하기 위해 함수 내에서 SQLCA 오류 처리를 인라인합니다.
    /* EXEC SQL WHENEVER SQLERROR CONTINUE; */ 
 

    // ncursesw 출력 로직 적용
    wscrl(console_win, 1);
    wmove(console_win, CONSOLE_HEIGHT - 2, 1);
    if (has_colors()) { wattron(console_win, COLOR_PAIR(1) | A_BOLD); } // COLOR_PAIR(1)을 오류 색상으로 가정
    wprintw(console_win, " [FATAL] Oracle Error during C call: %s", msg);
    if (has_colors()) { wattroff(console_win, COLOR_PAIR(1) | A_BOLD); }

    // SQLCA 오류 메시지 출력
    if (sqlca.sqlerrm.sqlerrml > 0) {
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 1, 1);
        if (has_colors()) { wattron(console_win, COLOR_PAIR(1)); }
        wprintw(console_win, " [DETAIL] (%.*s)", sqlca.sqlerrm.sqlerrml, sqlca.sqlerrm.sqlerrmc);
        if (has_colors()) { wattroff(console_win, COLOR_PAIR(1)); }
    }
    wrefresh(console_win); // 화면 갱신

    // 오류 발생 시 ROLLBACK하고 연결 해제 (RELEASE 옵션으로)
    /* EXEC SQL ROLLBACK RELEASE; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 0;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )5;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


    exit(1);
}

// Pro*C 호스트 변수 선언 영역
/* EXEC SQL BEGIN DECLARE SECTION; */ 

    // C에서 SQL로 전달 및 SQL에서 C로 수신될 변수
    /* VARCHAR barcode_hv[21]; */ 
struct { unsigned short len; unsigned char arr[21]; } barcode_hv;
       // char[20] 바코드
    /* VARCHAR dist_id_hv[4]; */ 
struct { unsigned short len; unsigned char arr[4]; } dist_id_hv;
        // char[3] 유통업체 ID
    /* VARCHAR prod_id_hv[5]; */ 
struct { unsigned short len; unsigned char arr[5]; } prod_id_hv;
        // char[4] 상품 ID
    /* VARCHAR prod_name_hv[101]; */ 
struct { unsigned short len; unsigned char arr[101]; } prod_name_hv;
    // char[100] 상품 명칭
    /* VARCHAR cate_id_hv[11]; */ 
struct { unsigned short len; unsigned char arr[11]; } cate_id_hv;
       // char[10] 카테고리 ID
    
    // 숫자로 변환된 입고 수량 및 단가 (DB NUMBER 형식에 맞춤)
    int inb_qty_num_hv;           // char[10] 입고 수량 (NUMBER)
    float inb_cost_num_hv;        // char[12] 입고 단가 (NUMBER(10,2))
    
    // DB ID 생성용 변수
    /* VARCHAR inb_id_hv[16]; */ 
struct { unsigned short len; unsigned char arr[16]; } inb_id_hv;
        // char[15] 입고 ID
    /* VARCHAR inv_id_hv[16]; */ 
struct { unsigned short len; unsigned char arr[16]; } inv_id_hv;
        // char[15] 재고 ID

    // DB 조회용 변수
    int count_hv;                 // COUNT(*) 결과 저장
    char exist_prod_id_hv[1];     // 상품 존재 여부 확인용
    
    // 기존 값 조회 및 날짜 처리를 위해 필요
    /* VARCHAR old_prod_id_hv[5]; */ 
struct { unsigned short len; unsigned char arr[5]; } old_prod_id_hv;
    // 기존 상품 ID
    /* VARCHAR old_dist_id_hv[4]; */ 
struct { unsigned short len; unsigned char arr[4]; } old_dist_id_hv;
    // 기존 유통업체 ID
    /* VARCHAR old_cate_id_hv[11]; */ 
struct { unsigned short len; unsigned char arr[11]; } old_cate_id_hv;
   // 기존 카테고리 ID
    /* VARCHAR old_inb_date_hv[9]; */ 
struct { unsigned short len; unsigned char arr[9]; } old_inb_date_hv;
   // 기존 입고 일자 (YYYYMMDD)
    int old_inb_qty_num_hv;       // 기존 입고 수량
    float old_inb_cost_num_hv;    // 기존 입고 단가

    /* VARCHAR final_inb_date_hv[9]; */ 
struct { unsigned short len; unsigned char arr[9]; } final_inb_date_hv;
 // 최종 UPDATE에 사용될 날짜
    
    // get_product_price 함수를 위해 추가된 변수
    int current_qty_hv;           // 현재 재고 수량
    float sell_price_hv;          // 판매 가격 (PRODUCT.SELL_PRICE)
    int requested_qty_hv;         // 요청 수량 (함수 인자)
    
    // DB 접속 정보 (환경에 맞게 수정 필요)
    char db_user[] = "SYSTEM";
    char db_pass[] = "epdlxjqpdltmdmddyd"; // 실제 비밀번호로 변경하세요
    char db_connect_string[] = "XE_DOCKER"; // SID 또는 서비스 이름
    
    // PL/SQL의 SYSDATE 값을 문자열로 받기 위한 변수 (필요시)
    char sysdate_str[20];
/* EXEC SQL END DECLARE SECTION; */ 


// ①  입고 관리 (F1)
// insert
int inbound_insert(wchar_t* input_buffer_w) {
    
    char input_buffer_c[512] = {0};
    char *token_arr[5]; 
    char temp_input[512];
    char *current_token;
    char *saveptr;
    int field_count = 0;
    int return_status = 0; 

    /* EXEC SQL WHENEVER SQLERROR DO sql_error("Oracle Error during C call"); */ 

    
    // ------------------------------------------------------------
    // 1. DB 접속 (함수 시작)
    // ------------------------------------------------------------
    wscrl(console_win, 1);
    wmove(console_win, CONSOLE_HEIGHT - 2, 1);
    if (has_colors()) {wattron(console_win, COLOR_PAIR(2)); } 
    wprintw(console_win, " [INFO] Attempting to connect to DB: %s", db_connect_string);
    if (has_colors()) {wattroff(console_win, COLOR_PAIR(2)); }

    /* EXEC SQL CONNECT :db_user IDENTIFIED BY :db_pass USING :db_connect_string; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )10;
    sqlstm.offset = (unsigned int  )20;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)db_user;
    sqlstm.sqhstl[0] = (unsigned long )0;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)db_pass;
    sqlstm.sqhstl[1] = (unsigned long )0;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (unsigned char  *)db_connect_string;
    sqlstm.sqhstl[2] = (unsigned long )0;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         short *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned long )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlstm.sqlcmax = (unsigned int )100;
    sqlstm.sqlcmin = (unsigned int )2;
    sqlstm.sqlcincr = (unsigned int )1;
    sqlstm.sqlctimeout = (unsigned int )0;
    sqlstm.sqlcnowait = (unsigned int )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call");
}


    
    wscrl(console_win, 1);
    wmove(console_win, CONSOLE_HEIGHT - 2, 1);
    if (has_colors()) {wattron(console_win, COLOR_PAIR(3)); } 
    wprintw(console_win, " [INFO] DB connection established.");
    if (has_colors()) {wattroff(console_win, COLOR_PAIR(3)); }
    wrefresh(console_win);

    // ------------------------------------------------------------
    // 2. 문자열 파싱 및 C 변수 준비
    // ------------------------------------------------------------
    
    if (wcstombs(input_buffer_c, input_buffer_w, sizeof(input_buffer_c)) == (size_t)-1) {
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); } 
        wprintw(console_win, " [LOG] [입고 관리] 입력 오류: 와이드 문자열 변환 실패.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        return_status = 0;
        goto cleanup;
    }

    strcpy(temp_input, input_buffer_c);
    
    current_token = strtok_r(temp_input, ",", &saveptr);
    while (current_token != NULL && field_count < 5) {
        token_arr[field_count] = trim_whitespace(current_token);
        field_count++;
        current_token = strtok_r(NULL, ",", &saveptr);
    }
    
    if (field_count != 5) {
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); } 
        wprintw(console_win, " [LOG] [입고 관리] 입력 오류: 필드 개수 불일치 (%d개).", field_count);
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        return_status = 0;
        goto cleanup;
    }
    
    // ------------------------------------------------------------
    // 3. 입력 값 유효성 검사 (C 레벨)
    // ------------------------------------------------------------

    if (strlen(token_arr[0]) != 7 || !is_numeric(token_arr[0])) {
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); } 
        wprintw(console_win, " [LOG] [입고 관리] 입력 오류: 바코드는 7자리 숫자여야 합니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        return_status = 0;
        goto cleanup;
    }
    
    if (!is_numeric(token_arr[1]) || !is_numeric(token_arr[2])) {
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); } 
        wprintw(console_win, " [LOG] [입고 관리] 입력 오류: 수량 또는 단가가 숫자가 아닙니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        return_status = 0;
        goto cleanup;
    }

    // 호스트 변수에 값 설정 및 바코드 분리
    strcpy((char*)barcode_hv.arr, token_arr[0]);
    barcode_hv.len = strlen(token_arr[0]);
    
    // 유통업체 ID (DIST_ID) 분리
    strncpy((char*)dist_id_hv.arr, token_arr[0], 3);
    dist_id_hv.arr[3] = '\0';
    dist_id_hv.len = 3;
    
    // 상품 ID (PROD_ID) 분리
    strncpy((char*)prod_id_hv.arr, token_arr[0] + 3, 4);
    prod_id_hv.arr[4] = '\0';
    prod_id_hv.len = 4;
    
    strcpy((char*)cate_id_hv.arr, token_arr[3]);
    cate_id_hv.len = strlen(token_arr[3]);
    
    strcpy((char*)prod_name_hv.arr, token_arr[4]);
    prod_name_hv.len = strlen(token_arr[4]);
    
    inb_qty_num_hv = atoi(token_arr[1]);
    inb_cost_num_hv = atof(token_arr[2]);

    // ------------------------------------------------------------
    // 4. DB 유효성 검사 및 트랜잭션 로직 (SQL 레벨)
    // ------------------------------------------------------------

    // A. 유통업체 ID 존재 확인 (SYSTEM.DISTRIBUTOR 테이블 사용)
    count_hv = 0;
    /* EXEC SQL SELECT COUNT(*) INTO :count_hv FROM SYSTEM.DISTRIBUTOR WHERE DIST_ID = :dist_id_hv; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from SYSTEM.DISTRIBUTOR where\
 DIST_ID=:b1";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )51;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.sqlpfmem = (unsigned int  )0;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&count_hv;
    sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)&dist_id_hv;
    sqlstm.sqhstl[1] = (unsigned long )6;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call");
}


    if (count_hv == 0) {
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); } 
        wprintw(console_win, " [LOG] [입고 관리] 유통업체 ID (%.*s)가 존재하지 않습니다.", dist_id_hv.len, dist_id_hv.arr);
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        return_status = 0;
        goto cleanup;
    }

    // B. 카테고리 ID 존재 확인 (SYSTEM.CATEGORY 테이블 사용)
    count_hv = 0;
    /* EXEC SQL SELECT COUNT(*) INTO :count_hv FROM SYSTEM.CATEGORY WHERE CATE_ID = :cate_id_hv; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from SYSTEM.CATEGORY where CA\
TE_ID=:b1";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )74;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.sqlpfmem = (unsigned int  )0;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&count_hv;
    sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)&cate_id_hv;
    sqlstm.sqhstl[1] = (unsigned long )13;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call");
}


    if (count_hv == 0) {
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); } 
        wprintw(console_win, " [LOG] [입고 관리] 카테고리 ID (%.*s)가 존재하지 않습니다.", cate_id_hv.len, cate_id_hv.arr);
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        return_status = 0;
        goto cleanup;
    }

    // C. 상품 등록 (PRODUCT)
    count_hv = 0;
    /* EXEC SQL SELECT COUNT(PROD_ID) INTO :count_hv FROM SYSTEM.PRODUCT WHERE PROD_ID = :prod_id_hv; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(PROD_ID) into :b0  from SYSTEM.PRODUCT wher\
e PROD_ID=:b1";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )97;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.sqlpfmem = (unsigned int  )0;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&count_hv;
    sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)&prod_id_hv;
    sqlstm.sqhstl[1] = (unsigned long )7;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call");
}



    if (count_hv == 0) {
        /* EXEC SQL INSERT INTO SYSTEM.PRODUCT (PROD_ID, CATE_ID, PROD_NAME, BARCODE, SELL_PRICE)
        VALUES (:prod_id_hv, :cate_id_hv, :prod_name_hv, :barcode_hv, :inb_cost_num_hv); */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 5;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "insert into SYSTEM.PRODUCT (PROD_ID,CATE_ID,PROD_NAM\
E,BARCODE,SELL_PRICE) values (:b0,:b1,:b2,:b3,:b4)";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )120;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)&prod_id_hv;
        sqlstm.sqhstl[0] = (unsigned long )7;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (unsigned char  *)&cate_id_hv;
        sqlstm.sqhstl[1] = (unsigned long )13;
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         short *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned long )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqhstv[2] = (unsigned char  *)&prod_name_hv;
        sqlstm.sqhstl[2] = (unsigned long )103;
        sqlstm.sqhsts[2] = (         int  )0;
        sqlstm.sqindv[2] = (         short *)0;
        sqlstm.sqinds[2] = (         int  )0;
        sqlstm.sqharm[2] = (unsigned long )0;
        sqlstm.sqadto[2] = (unsigned short )0;
        sqlstm.sqtdso[2] = (unsigned short )0;
        sqlstm.sqhstv[3] = (unsigned char  *)&barcode_hv;
        sqlstm.sqhstl[3] = (unsigned long )23;
        sqlstm.sqhsts[3] = (         int  )0;
        sqlstm.sqindv[3] = (         short *)0;
        sqlstm.sqinds[3] = (         int  )0;
        sqlstm.sqharm[3] = (unsigned long )0;
        sqlstm.sqadto[3] = (unsigned short )0;
        sqlstm.sqtdso[3] = (unsigned short )0;
        sqlstm.sqhstv[4] = (unsigned char  *)&inb_cost_num_hv;
        sqlstm.sqhstl[4] = (unsigned long )sizeof(float);
        sqlstm.sqhsts[4] = (         int  )0;
        sqlstm.sqindv[4] = (         short *)0;
        sqlstm.sqinds[4] = (         int  )0;
        sqlstm.sqharm[4] = (unsigned long )0;
        sqlstm.sqadto[4] = (unsigned short )0;
        sqlstm.sqtdso[4] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call");
}


        
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(2)); }
        wprintw(console_win, " [INFO] 신규 상품 (%.*s)이 PRODUCT 테이블에 등록되었습니다.", prod_id_hv.len, prod_id_hv.arr);
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(2)); }
    }
    
    // D. 입고 데이터 추가 (INBOUND)
    long next_inb_val;
    /* EXEC SQL SELECT SYSTEM.INB_ID_SEQ.NEXTVAL INTO :next_inb_val FROM DUAL; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 5;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select SYSTEM.INB_ID_SEQ.nextval  into :b0  from DUAL ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )155;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.sqlpfmem = (unsigned int  )0;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&next_inb_val;
    sqlstm.sqhstl[0] = (unsigned long )sizeof(long);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call");
}


    
    sprintf((char*)inb_id_hv.arr, "%015ld", next_inb_val);
    inb_id_hv.len = strlen((char*)inb_id_hv.arr);
    
    // DIST_ID 컬럼 사용
    /* EXEC SQL INSERT INTO SYSTEM.INBOUND (INB_ID, PROD_ID, DIST_ID, CATE_ID, INB_DATE, INB_QTY, INB_COST)
    VALUES (:inb_id_hv, :prod_id_hv, :dist_id_hv, :cate_id_hv, SYSDATE, :inb_qty_num_hv, :inb_cost_num_hv); */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 6;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "insert into SYSTEM.INBOUND (INB_ID,PROD_ID,DIST_ID,CATE_\
ID,INB_DATE,INB_QTY,INB_COST) values (:b0,:b1,:b2,:b3,SYSDATE,:b4,:b5)";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )174;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&inb_id_hv;
    sqlstm.sqhstl[0] = (unsigned long )18;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)&prod_id_hv;
    sqlstm.sqhstl[1] = (unsigned long )7;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (unsigned char  *)&dist_id_hv;
    sqlstm.sqhstl[2] = (unsigned long )6;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         short *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned long )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqhstv[3] = (unsigned char  *)&cate_id_hv;
    sqlstm.sqhstl[3] = (unsigned long )13;
    sqlstm.sqhsts[3] = (         int  )0;
    sqlstm.sqindv[3] = (         short *)0;
    sqlstm.sqinds[3] = (         int  )0;
    sqlstm.sqharm[3] = (unsigned long )0;
    sqlstm.sqadto[3] = (unsigned short )0;
    sqlstm.sqtdso[3] = (unsigned short )0;
    sqlstm.sqhstv[4] = (unsigned char  *)&inb_qty_num_hv;
    sqlstm.sqhstl[4] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[4] = (         int  )0;
    sqlstm.sqindv[4] = (         short *)0;
    sqlstm.sqinds[4] = (         int  )0;
    sqlstm.sqharm[4] = (unsigned long )0;
    sqlstm.sqadto[4] = (unsigned short )0;
    sqlstm.sqtdso[4] = (unsigned short )0;
    sqlstm.sqhstv[5] = (unsigned char  *)&inb_cost_num_hv;
    sqlstm.sqhstl[5] = (unsigned long )sizeof(float);
    sqlstm.sqhsts[5] = (         int  )0;
    sqlstm.sqindv[5] = (         short *)0;
    sqlstm.sqinds[5] = (         int  )0;
    sqlstm.sqharm[5] = (unsigned long )0;
    sqlstm.sqadto[5] = (unsigned short )0;
    sqlstm.sqtdso[5] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call");
}



    wscrl(console_win, 1);
    wmove(console_win, CONSOLE_HEIGHT - 2, 1);
    if (has_colors()) {wattron(console_win, COLOR_PAIR(2)); }
    wprintw(console_win, " [INFO] 입고 레코드 (%.*s)가 INBOUND 테이블에 삽입되었습니다.", inb_id_hv.len, inb_id_hv.arr);
    if (has_colors()) {wattroff(console_win, COLOR_PAIR(2)); }

    // E. 재고 추가/갱신 (INVENTORY)
    /* EXEC SQL UPDATE SYSTEM.INVENTORY 
        SET CURRENT_QTY = CURRENT_QTY + :inb_qty_num_hv, 
            LAST_INB_DATE = SYSDATE 
        WHERE PROD_ID = :prod_id_hv; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 6;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "update SYSTEM.INVENTORY  set CURRENT_QTY=(CURRENT_QTY+:b\
0),LAST_INB_DATE=SYSDATE where PROD_ID=:b1";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )213;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&inb_qty_num_hv;
    sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)&prod_id_hv;
    sqlstm.sqhstl[1] = (unsigned long )7;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call");
}


    
    if (sqlca.sqlerrd[2] == 0) {
        long next_inv_val;
        /* EXEC SQL SELECT SYSTEM.INV_ID_SEQ.NEXTVAL INTO :next_inv_val FROM DUAL; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 6;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "select SYSTEM.INV_ID_SEQ.nextval  into :b0  from DUA\
L ";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )236;
        sqlstm.selerr = (unsigned short)1;
        sqlstm.sqlpfmem = (unsigned int  )0;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)&next_inv_val;
        sqlstm.sqhstl[0] = (unsigned long )sizeof(long);
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call");
}


        
        sprintf((char*)inv_id_hv.arr, "%015ld", next_inv_val);
        inv_id_hv.len = strlen((char*)inv_id_hv.arr);
        
        /* EXEC SQL INSERT INTO SYSTEM.INVENTORY (INV_ID, PROD_ID, CURRENT_QTY, LAST_INB_DATE)
        VALUES (:inv_id_hv, :prod_id_hv, :inb_qty_num_hv, SYSDATE); */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 6;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "insert into SYSTEM.INVENTORY (INV_ID,PROD_ID,CURRENT\
_QTY,LAST_INB_DATE) values (:b0,:b1,:b2,SYSDATE)";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )255;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)&inv_id_hv;
        sqlstm.sqhstl[0] = (unsigned long )18;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (unsigned char  *)&prod_id_hv;
        sqlstm.sqhstl[1] = (unsigned long )7;
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         short *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned long )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqhstv[2] = (unsigned char  *)&inb_qty_num_hv;
        sqlstm.sqhstl[2] = (unsigned long )sizeof(int);
        sqlstm.sqhsts[2] = (         int  )0;
        sqlstm.sqindv[2] = (         short *)0;
        sqlstm.sqinds[2] = (         int  )0;
        sqlstm.sqharm[2] = (unsigned long )0;
        sqlstm.sqadto[2] = (unsigned short )0;
        sqlstm.sqtdso[2] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call");
}


        
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(2)); }
        wprintw(console_win, " [INFO] 신규 재고 레코드 (%.*s)가 INVENTORY 테이블에 삽입되었습니다.", inv_id_hv.len, inv_id_hv.arr);
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(2)); }
    } else {
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(2)); }
        wprintw(console_win, " [INFO] 상품 (%.*s)의 기존 재고가 갱신되었습니다.", prod_id_hv.len, prod_id_hv.arr);
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(2)); }
    }
    
    // ------------------------------------------------------------
    // 5. 최종 커밋 및 성공 반환 (return_status를 1로 설정)
    // ------------------------------------------------------------
    return_status = 1;

cleanup:
    
    if (return_status == 1) {
        /* EXEC SQL COMMIT WORK RELEASE; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 6;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )282;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call");
}

 
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(3) | A_BOLD); } 
        wprintw(console_win, " [SUCCESS] 트랜잭션 커밋 및 연결 종료. 입고 등록 완료.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(3) | A_BOLD); }
    } else {
        /* EXEC SQL ROLLBACK RELEASE; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 6;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )297;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call");
}

 
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 1, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD); } 
        wprintw(console_win, " [ERROR] 트랜잭션 롤백 및 연결 종료. 입고 등록 실패.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD); }
    }
    wrefresh(console_win);
    
    return return_status;
}

// delete
int inbound_delete(wchar_t* input_buffer_w) {
    
    char input_buffer_c[512] = {0};
    char *token;
    int return_status = 0; 
    int delete_count = 0; // 삭제된 행의 개수 저장용

    // DB 오류 발생 시 sql_error 호출
    /* EXEC SQL WHENEVER SQLERROR DO sql_error("Oracle Error during C call (DELETE)"); */ 

    // 삭제된 행이 없더라도 오류로 처리하지 않고 계속 진행
    /* EXEC SQL WHENEVER NOT FOUND CONTINUE; */ 
 

    // ------------------------------------------------------------
    // 1. DB 접속
    // ------------------------------------------------------------
    wscrl(console_win, 1);
    wmove(console_win, CONSOLE_HEIGHT - 2, 1);
    if (has_colors()) {wattron(console_win, COLOR_PAIR(2)); }
    wprintw(console_win, " [INFO] Attempting to connect to DB: %s", db_connect_string);
    if (has_colors()) {wattroff(console_win, COLOR_PAIR(2)); }

    /* EXEC SQL CONNECT :db_user IDENTIFIED BY :db_pass USING :db_connect_string; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 6;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )10;
    sqlstm.offset = (unsigned int  )312;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)db_user;
    sqlstm.sqhstl[0] = (unsigned long )0;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)db_pass;
    sqlstm.sqhstl[1] = (unsigned long )0;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (unsigned char  *)db_connect_string;
    sqlstm.sqhstl[2] = (unsigned long )0;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         short *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned long )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlstm.sqlcmax = (unsigned int )100;
    sqlstm.sqlcmin = (unsigned int )2;
    sqlstm.sqlcincr = (unsigned int )1;
    sqlstm.sqlctimeout = (unsigned int )0;
    sqlstm.sqlcnowait = (unsigned int )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (DELETE)");
}


    
    wscrl(console_win, 1);
    wmove(console_win, CONSOLE_HEIGHT - 2, 1);
    if (has_colors()) {wattron(console_win, COLOR_PAIR(3)); }
    wprintw(console_win, " [INFO] DB connection established.");
    if (has_colors()) {wattroff(console_win, COLOR_PAIR(3)); }
    wrefresh(console_win);

    // ------------------------------------------------------------
    // 2. 입력 파싱 (입고 ID 1개만 입력받는다고 가정)
    // ------------------------------------------------------------

    if (wcstombs(input_buffer_c, input_buffer_w, sizeof(input_buffer_c)) == (size_t)-1) {
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 삭제] 입력 오류: 와이드 문자열 변환 실패.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        return_status = 0;
        goto cleanup;
    }

    token = trim_whitespace(input_buffer_c);
    if (strlen(token) == 0) {
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 삭제] 입력 오류: 삭제할 입고 ID를 입력하세요.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        return_status = 0;
        goto cleanup;
    }
    
    // inb_id_hv 호스트 변수에 ID 저장
    strcpy((char*)inb_id_hv.arr, token);
    inb_id_hv.len = strlen(token);

    // ------------------------------------------------------------
    // 3. 입고 (INBOUND) 레코드만 삭제 (재고 수정 로직 없음)
    // ------------------------------------------------------------
    wscrl(console_win, 1);
    wmove(console_win, CONSOLE_HEIGHT - 2, 1);
    if (has_colors()) {wattron(console_win, COLOR_PAIR(2)); }
    wprintw(console_win, " [INFO] 입고 ID (%.*s) 레코드 삭제 명령 실행...", inb_id_hv.len, inb_id_hv.arr);
    if (has_colors()) {wattroff(console_win, COLOR_PAIR(2)); }

    /* EXEC SQL DELETE FROM SYSTEM.INBOUND
             WHERE INB_ID = :inb_id_hv; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 6;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "delete  from SYSTEM.INBOUND  where INB_ID=:b0";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )343;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&inb_id_hv;
    sqlstm.sqhstl[0] = (unsigned long )18;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (DELETE)");
}


             
    // 삭제된 행의 개수 확인
    delete_count = sqlca.sqlerrd[2];

    if (delete_count == 0) {
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 삭제] 오류: 입고 ID (%.*s)를 찾을 수 없습니다.", 
                inb_id_hv.len, inb_id_hv.arr);
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        return_status = 0;
    } else {
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(2)); }
        wprintw(console_win, " [INFO] 입고 레코드 %d건이 성공적으로 삭제되었습니다.", delete_count);
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(2)); }
        return_status = 1;
    }

    goto cleanup;

// ------------------------------------------------------------
// 4. 최종 커밋 및 연결 해제
// ------------------------------------------------------------
cleanup:
    // **성공 또는 실패 여부와 관계없이 연결 해제**
    
    if (return_status == 1) {
        /* EXEC SQL COMMIT WORK RELEASE; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 6;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )362;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (DELETE)");
}

 
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(3) | A_BOLD); }
        wprintw(console_win, " [SUCCESS] 트랜잭션 커밋 및 연결 종료. 입고 삭제 완료.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(3) | A_BOLD); }
    } else {
        /* EXEC SQL ROLLBACK RELEASE; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 6;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )377;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (DELETE)");
}

 
        wscrl(console_win, 1);
        wmove(console_win, CONSOLE_HEIGHT - 1, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD); }
        wprintw(console_win, " [ERROR] 트랜잭션 롤백 및 연결 종료. 입고 삭제 실패.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD); }
    }
    wrefresh(console_win);
    
    return return_status;
}

// modify
int inbound_modify(wchar_t* input_buffer_w) {
    
    char input_buffer_c[512] = {0};
    // 입고ID, 상품ID, 제조업체ID, 카테고리ID, 입고일자, 입고수량, 입고단가 (총 7개)
    char *token_arr[7]; 
    char temp_input[512];
    char *current_token;
    char *saveptr;
    int field_count = 0;
    int return_status = 0; 
    
    // DB에서 조회할 기존 값들을 저장할 임시 호스트 변수 (global DECLARE SECTION에 정의되어야 함)
    // old_prod_id_hv, old_dist_id_hv, old_cate_id_hv, old_inb_date_hv, old_inb_qty_num_hv, old_inb_cost_num_hv
    // 최종 UPDATE에 사용될 날짜 호스트 변수 (final_inb_date_hv)

    /* EXEC SQL WHENEVER SQLERROR DO sql_error("Oracle Error during C call (MODIFY)"); */ 

    
    // ------------------------------------------------------------
    // 1. DB 접속
    // ------------------------------------------------------------
    wscrl(console_win, 1);
    wmove(console_win, CONSOLE_HEIGHT - 2, 1);
    if (has_colors()) {wattron(console_win, COLOR_PAIR(2)); }
    wprintw(console_win, " [INFO] Attempting to connect to DB: %s", db_connect_string);
    if (has_colors()) {wattroff(console_win, COLOR_PAIR(2)); }
    wrefresh(console_win);

    /* EXEC SQL CONNECT :db_user IDENTIFIED BY :db_pass USING :db_connect_string; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 6;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )10;
    sqlstm.offset = (unsigned int  )392;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)db_user;
    sqlstm.sqhstl[0] = (unsigned long )0;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)db_pass;
    sqlstm.sqhstl[1] = (unsigned long )0;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (unsigned char  *)db_connect_string;
    sqlstm.sqhstl[2] = (unsigned long )0;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         short *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned long )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlstm.sqlcmax = (unsigned int )100;
    sqlstm.sqlcmin = (unsigned int )2;
    sqlstm.sqlcincr = (unsigned int )1;
    sqlstm.sqlctimeout = (unsigned int )0;
    sqlstm.sqlcnowait = (unsigned int )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (MODIFY)");
}


    
    wscrl(console_win, 1);
    wmove(console_win, CONSOLE_HEIGHT - 2, 1);
    if (has_colors()) {wattron(console_win, COLOR_PAIR(3)); }
    wprintw(console_win, " [INFO] DB connection established.");
    if (has_colors()) {wattroff(console_win, COLOR_PAIR(3)); }
    wrefresh(console_win);

    // ------------------------------------------------------------
    // 2. 문자열 파싱 및 입력 유효성 검사 (7개 필드)
    // ------------------------------------------------------------
    if (wcstombs(input_buffer_c, input_buffer_w, sizeof(input_buffer_c)) == (size_t)-1) {
        wscrl(console_win, 1); wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 수정] 입력 오류: 와이드 문자열 변환 실패.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        return_status = 0; goto cleanup;
    }

    strcpy(temp_input, input_buffer_c);
    
    current_token = strtok_r(temp_input, ",", &saveptr);
    while (current_token != NULL && field_count < 7) {
        token_arr[field_count] = trim_whitespace(current_token);
        field_count++;
        current_token = strtok_r(NULL, ",", &saveptr);
    }
    
    if (field_count != 7) {
        wscrl(console_win, 1); wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 수정] 입력 오류: 필드 개수 불일치 (%d개, 예상 7개).", field_count);
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        return_status = 0; goto cleanup;
    }
    
    // 입고 ID 설정 (필수)
    strcpy((char*)inb_id_hv.arr, token_arr[0]);
    inb_id_hv.len = strlen(token_arr[0]);
    
    // ------------------------------------------------------------
    // 3. 기존 데이터 조회 (UPDATE를 위한 초기값 설정)
    // ------------------------------------------------------------
    
    // [SELECT INTO] 수정할 기존 레코드의 모든 현재 값들을 가져옴
    // NOTE: old_inb_date_hv에 YYYYMMDD 형식의 문자열로 날짜를 가져옵니다.
    /* EXEC SQL SELECT PROD_ID, DIST_ID, CATE_ID, TO_CHAR(INB_DATE, 'YYYYMMDD'), INB_QTY, INB_COST
    INTO :old_prod_id_hv, :old_dist_id_hv, :old_cate_id_hv, :old_inb_date_hv, :old_inb_qty_num_hv, :old_inb_cost_num_hv
    FROM SYSTEM.INBOUND
    WHERE INB_ID = :inb_id_hv; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select PROD_ID ,DIST_ID ,CATE_ID ,TO_CHAR(INB_DATE,'YYYY\
MMDD') ,INB_QTY ,INB_COST into :b0,:b1,:b2,:b3,:b4,:b5  from SYSTEM.INBOUND w\
here INB_ID=:b6";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )423;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.sqlpfmem = (unsigned int  )0;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&old_prod_id_hv;
    sqlstm.sqhstl[0] = (unsigned long )7;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)&old_dist_id_hv;
    sqlstm.sqhstl[1] = (unsigned long )6;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (unsigned char  *)&old_cate_id_hv;
    sqlstm.sqhstl[2] = (unsigned long )13;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         short *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned long )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqhstv[3] = (unsigned char  *)&old_inb_date_hv;
    sqlstm.sqhstl[3] = (unsigned long )11;
    sqlstm.sqhsts[3] = (         int  )0;
    sqlstm.sqindv[3] = (         short *)0;
    sqlstm.sqinds[3] = (         int  )0;
    sqlstm.sqharm[3] = (unsigned long )0;
    sqlstm.sqadto[3] = (unsigned short )0;
    sqlstm.sqtdso[3] = (unsigned short )0;
    sqlstm.sqhstv[4] = (unsigned char  *)&old_inb_qty_num_hv;
    sqlstm.sqhstl[4] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[4] = (         int  )0;
    sqlstm.sqindv[4] = (         short *)0;
    sqlstm.sqinds[4] = (         int  )0;
    sqlstm.sqharm[4] = (unsigned long )0;
    sqlstm.sqadto[4] = (unsigned short )0;
    sqlstm.sqtdso[4] = (unsigned short )0;
    sqlstm.sqhstv[5] = (unsigned char  *)&old_inb_cost_num_hv;
    sqlstm.sqhstl[5] = (unsigned long )sizeof(float);
    sqlstm.sqhsts[5] = (         int  )0;
    sqlstm.sqindv[5] = (         short *)0;
    sqlstm.sqinds[5] = (         int  )0;
    sqlstm.sqharm[5] = (unsigned long )0;
    sqlstm.sqadto[5] = (unsigned short )0;
    sqlstm.sqtdso[5] = (unsigned short )0;
    sqlstm.sqhstv[6] = (unsigned char  *)&inb_id_hv;
    sqlstm.sqhstl[6] = (unsigned long )18;
    sqlstm.sqhsts[6] = (         int  )0;
    sqlstm.sqindv[6] = (         short *)0;
    sqlstm.sqinds[6] = (         int  )0;
    sqlstm.sqharm[6] = (unsigned long )0;
    sqlstm.sqadto[6] = (unsigned short )0;
    sqlstm.sqtdso[6] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (MODIFY)");
}



    // NOT FOUND 처리
    if (sqlca.sqlcode == 1403) { // ORA-01403: no data found
        wscrl(console_win, 1); wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 수정] 오류: 입고 ID (%.*s)를 찾을 수 없습니다.", inb_id_hv.len, inb_id_hv.arr);
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        return_status = 0; goto cleanup;
    }

    // ------------------------------------------------------------
    // 4. 입력 값 기반으로 호스트 변수 덮어쓰기 (유효성 검사 포함)
    // ------------------------------------------------------------
    
    int is_actually_updated = 0; 

    // A. 상품 ID (PROD_ID, token_arr[1])
    if (strcmp(token_arr[1], "@") != 0) {
        if (strlen(token_arr[1]) > 4) { return_status = 0; goto cleanup; }
        /* EXEC SQL SELECT COUNT(*) INTO :count_hv FROM SYSTEM.PRODUCT WHERE PROD_ID = :token_arr[1]; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 7;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "select count(*)  into :b0  from SYSTEM.PRODUCT where\
 PROD_ID=:b1";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )466;
        sqlstm.selerr = (unsigned short)1;
        sqlstm.sqlpfmem = (unsigned int  )0;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)&count_hv;
        sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (unsigned char  *)token_arr[1];
        sqlstm.sqhstl[1] = (unsigned long )7;
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         short *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned long )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (MODIFY)");
}


        if (count_hv == 0) { wprintw(console_win, " [LOG] [입고 수정] 오류: 상품 ID가 DB에 존재하지 않습니다."); return_status = 0; goto cleanup; }
        
        strcpy((char*)prod_id_hv.arr, token_arr[1]);
        prod_id_hv.len = strlen(token_arr[1]);
        is_actually_updated = 1;
    } else {
        // '@'이면 기존 값 사용
        strcpy((char*)prod_id_hv.arr, (char*)old_prod_id_hv.arr);
        prod_id_hv.len = old_prod_id_hv.len;
    }

    // B. 유통업체 ID (DIST_ID, token_arr[2])
    if (strcmp(token_arr[2], "@") != 0) {
        /* EXEC SQL SELECT COUNT(*) INTO :count_hv FROM SYSTEM.DISTRIBUTOR WHERE DIST_ID = :token_arr[2]; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 7;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "select count(*)  into :b0  from SYSTEM.DISTRIBUTOR w\
here DIST_ID=:b1";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )489;
        sqlstm.selerr = (unsigned short)1;
        sqlstm.sqlpfmem = (unsigned int  )0;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)&count_hv;
        sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (unsigned char  *)token_arr[2];
        sqlstm.sqhstl[1] = (unsigned long )7;
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         short *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned long )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (MODIFY)");
}


        if (count_hv == 0) { wprintw(console_win, " [LOG] [입고 수정] 오류: 유통업체 ID가 DB에 존재하지 않습니다."); return_status = 0; goto cleanup; }

        strcpy((char*)dist_id_hv.arr, token_arr[2]);
        dist_id_hv.len = strlen(token_arr[2]);
        is_actually_updated = 1;
    } else {
        // '@'이면 기존 값 사용
        strcpy((char*)dist_id_hv.arr, (char*)old_dist_id_hv.arr);
        dist_id_hv.len = old_dist_id_hv.len;
    }

    // C. 카테고리 ID (CATE_ID, token_arr[3])
    if (strcmp(token_arr[3], "@") != 0) {
        /* EXEC SQL SELECT COUNT(*) INTO :count_hv FROM SYSTEM.CATEGORY WHERE CATE_ID = :token_arr[3]; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 7;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "select count(*)  into :b0  from SYSTEM.CATEGORY wher\
e CATE_ID=:b1";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )512;
        sqlstm.selerr = (unsigned short)1;
        sqlstm.sqlpfmem = (unsigned int  )0;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)&count_hv;
        sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (unsigned char  *)token_arr[3];
        sqlstm.sqhstl[1] = (unsigned long )7;
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         short *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned long )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (MODIFY)");
}


        if (count_hv == 0) { wprintw(console_win, " [LOG] [입고 수정] 오류: 카테고리 ID가 DB에 존재하지 않습니다."); return_status = 0; goto cleanup; }

        strcpy((char*)cate_id_hv.arr, token_arr[3]);
        cate_id_hv.len = strlen(token_arr[3]);
        is_actually_updated = 1;
    } else {
        // '@'이면 기존 값 사용
        strcpy((char*)cate_id_hv.arr, (char*)old_cate_id_hv.arr);
        cate_id_hv.len = old_cate_id_hv.len;
    }

    // D. 입고 일자 (INB_DATE, token_arr[4]) - **오류 해결 지점**
    if (strcmp(token_arr[4], "@") != 0) {
        // 새 날짜가 입력된 경우, 최종 변수에 새 날짜 저장
        strcpy((char*)final_inb_date_hv.arr, token_arr[4]);
        final_inb_date_hv.len = strlen(token_arr[4]);
        is_actually_updated = 1;
    } else {
        // '@'이면 조회된 기존 날짜 문자열 사용
        strcpy((char*)final_inb_date_hv.arr, (char*)old_inb_date_hv.arr);
        final_inb_date_hv.len = old_inb_date_hv.len;
    }

    // E. 입고 수량 (INB_QTY, token_arr[5])
    if (strcmp(token_arr[5], "@") != 0) {
        if (!is_numeric(token_arr[5])) { wprintw(console_win, " [LOG] [입고 수정] 오류: 수량은 숫자여야 합니다."); return_status = 0; goto cleanup; }
        inb_qty_num_hv = atoi(token_arr[5]);
        is_actually_updated = 1;
    } else {
        // '@'이면 기존 값 사용
        inb_qty_num_hv = old_inb_qty_num_hv;
    }

    // F. 입고 단가 (INB_COST, token_arr[6])
    if (strcmp(token_arr[6], "@") != 0) {
        if (!is_numeric(token_arr[6])) { wprintw(console_win, " [LOG] [입고 수정] 오류: 단가는 숫자여야 합니다."); return_status = 0; goto cleanup; }
        inb_cost_num_hv = atof(token_arr[6]);
        is_actually_updated = 1;
    } else {
        // '@'이면 기존 값 사용
        inb_cost_num_hv = old_inb_cost_num_hv;
    }


    // ------------------------------------------------------------
    // 5. 정적 UPDATE 실행
    // ------------------------------------------------------------
    if (is_actually_updated) {
        wscrl(console_win, 1); wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(2)); }
        wprintw(console_win, " [INFO] 입고 (%.*s) 정보 업데이트 실행 중...", inb_id_hv.len, inb_id_hv.arr);
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(2)); }

        // [UPDATE] 모든 필드를 호스트 변수로 갱신 (새 값 또는 기존 값)
        /* EXEC SQL UPDATE SYSTEM.INBOUND SET
            PROD_ID = :prod_id_hv,
            DIST_ID = :dist_id_hv,
            CATE_ID = :cate_id_hv,
            INB_DATE = TO_DATE(:final_inb_date_hv, 'YYYYMMDD'), // 수정된 final_inb_date_hv 사용
            INB_QTY = :inb_qty_num_hv,
            INB_COST = :inb_cost_num_hv
        WHERE INB_ID = :inb_id_hv; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 7;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "update SYSTEM.INBOUND  set PROD_ID=:b0,DIST_ID=:b1,C\
ATE_ID=:b2,INB_DATE=TO_DATE(:b3,'YYYYMMDD'),INB_QTY=:b4,INB_COST=:b5 where IN\
B_ID=:b6";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )535;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)&prod_id_hv;
        sqlstm.sqhstl[0] = (unsigned long )7;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (unsigned char  *)&dist_id_hv;
        sqlstm.sqhstl[1] = (unsigned long )6;
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         short *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned long )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqhstv[2] = (unsigned char  *)&cate_id_hv;
        sqlstm.sqhstl[2] = (unsigned long )13;
        sqlstm.sqhsts[2] = (         int  )0;
        sqlstm.sqindv[2] = (         short *)0;
        sqlstm.sqinds[2] = (         int  )0;
        sqlstm.sqharm[2] = (unsigned long )0;
        sqlstm.sqadto[2] = (unsigned short )0;
        sqlstm.sqtdso[2] = (unsigned short )0;
        sqlstm.sqhstv[3] = (unsigned char  *)&final_inb_date_hv;
        sqlstm.sqhstl[3] = (unsigned long )11;
        sqlstm.sqhsts[3] = (         int  )0;
        sqlstm.sqindv[3] = (         short *)0;
        sqlstm.sqinds[3] = (         int  )0;
        sqlstm.sqharm[3] = (unsigned long )0;
        sqlstm.sqadto[3] = (unsigned short )0;
        sqlstm.sqtdso[3] = (unsigned short )0;
        sqlstm.sqhstv[4] = (unsigned char  *)&inb_qty_num_hv;
        sqlstm.sqhstl[4] = (unsigned long )sizeof(int);
        sqlstm.sqhsts[4] = (         int  )0;
        sqlstm.sqindv[4] = (         short *)0;
        sqlstm.sqinds[4] = (         int  )0;
        sqlstm.sqharm[4] = (unsigned long )0;
        sqlstm.sqadto[4] = (unsigned short )0;
        sqlstm.sqtdso[4] = (unsigned short )0;
        sqlstm.sqhstv[5] = (unsigned char  *)&inb_cost_num_hv;
        sqlstm.sqhstl[5] = (unsigned long )sizeof(float);
        sqlstm.sqhsts[5] = (         int  )0;
        sqlstm.sqindv[5] = (         short *)0;
        sqlstm.sqinds[5] = (         int  )0;
        sqlstm.sqharm[5] = (unsigned long )0;
        sqlstm.sqadto[5] = (unsigned short )0;
        sqlstm.sqtdso[5] = (unsigned short )0;
        sqlstm.sqhstv[6] = (unsigned char  *)&inb_id_hv;
        sqlstm.sqhstl[6] = (unsigned long )18;
        sqlstm.sqhsts[6] = (         int  )0;
        sqlstm.sqindv[6] = (         short *)0;
        sqlstm.sqinds[6] = (         int  )0;
        sqlstm.sqharm[6] = (unsigned long )0;
        sqlstm.sqadto[6] = (unsigned short )0;
        sqlstm.sqtdso[6] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (MODIFY)");
}



        if (sqlca.sqlerrd[2] == 0) {
            wscrl(console_win, 1); wmove(console_win, CONSOLE_HEIGHT - 2, 1);
            if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            wprintw(console_win, " [LOG] [입고 수정] 오류: 입고 ID (%.*s)를 찾을 수 없습니다 (UPDATE 실패).", inb_id_hv.len, inb_id_hv.arr);
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
            return_status = 0;
        } else {
            wscrl(console_win, 1); wmove(console_win, CONSOLE_HEIGHT - 2, 1);
            if (has_colors()) {wattron(console_win, COLOR_PAIR(3) | A_BOLD); }
            wprintw(console_win, " [SUCCESS] 입고 ID (%.*s) 정보가 성공적으로 수정되었습니다.", inb_id_hv.len, inb_id_hv.arr);
            if (has_colors()) {wattroff(console_win, COLOR_PAIR(3) | A_BOLD); }
            return_status = 1;
        }
    } else {
        wscrl(console_win, 1); wmove(console_win, CONSOLE_HEIGHT - 2, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        wprintw(console_win, " [LOG] [입고 수정] 오류: 수정할 항목이 없습니다 ('@'만 입력됨).");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD | A_DIM); }
        return_status = 0;
    }

// ------------------------------------------------------------
// 6. 최종 커밋 및 연결 해제
// ------------------------------------------------------------
cleanup:
    
    if (return_status == 1) {
        /* EXEC SQL COMMIT WORK RELEASE; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 7;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )578;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (MODIFY)");
}

 
        wscrl(console_win, 1); wmove(console_win, CONSOLE_HEIGHT - 1, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(3) | A_BOLD); }
        wprintw(console_win, " [SUCCESS] 트랜잭션 커밋 및 연결 종료.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(3) | A_BOLD); }
    } else {
        /* EXEC SQL ROLLBACK RELEASE; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 7;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )593;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (MODIFY)");
}

 
        wscrl(console_win, 1); wmove(console_win, CONSOLE_HEIGHT - 1, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(4) | A_BOLD); }
        wprintw(console_win, " [ERROR] 트랜잭션 롤백 및 연결 종료.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(4) | A_BOLD); }
    }
    wrefresh(console_win);
    
    return return_status;
}

// select
int inbound_select(wchar_t* input_buffer_w) {
    
    // LineBuffer를 사용하지 않고 바로 화면 출력 (스크롤 기능 배제)
    
    /* EXEC SQL WHENEVER SQLERROR DO sql_error("Oracle Error during C call (SELECT)"); */ 

    /* EXEC SQL WHENEVER NOT FOUND GOTO no_data_found; */ 


    int return_status = 0;

    /* VARCHAR inb_id_hv[16]; */ 
struct { unsigned short len; unsigned char arr[16]; } inb_id_hv;

    /* VARCHAR prod_name_hv[101]; */ 
struct { unsigned short len; unsigned char arr[101]; } prod_name_hv;

    /* VARCHAR dist_name_hv[51]; */ 
struct { unsigned short len; unsigned char arr[51]; } dist_name_hv;
 
    /* VARCHAR cate_name_hv[51]; */ 
struct { unsigned short len; unsigned char arr[51]; } cate_name_hv;
 
    /* VARCHAR inb_date_hv[11]; */ 
struct { unsigned short len; unsigned char arr[11]; } inb_date_hv;
 
    int inb_qty_hv;
    float inb_cost_hv;
    
    // FETCH 루프에서 사용할 로컬 변수
    char line[MAX_LINE_LENGTH];
    
    // ncursesw 변수
    int max_rows, max_cols;
    int data_rows; 
    int current_y = 5; // 데이터 출력 시작 Y 위치 (헤더 아래)
    
    // ------------------------------------------------------------
    // 1. DB 접속 및 화면 크기 측정
    // ------------------------------------------------------------
    /* EXEC SQL CONNECT :db_user IDENTIFIED BY :db_pass USING :db_connect_string; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )10;
    sqlstm.offset = (unsigned int  )608;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)db_user;
    sqlstm.sqhstl[0] = (unsigned long )0;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)db_pass;
    sqlstm.sqhstl[1] = (unsigned long )0;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (unsigned char  *)db_connect_string;
    sqlstm.sqhstl[2] = (unsigned long )0;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         short *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned long )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlstm.sqlcmax = (unsigned int )100;
    sqlstm.sqlcmin = (unsigned int )2;
    sqlstm.sqlcincr = (unsigned int )1;
    sqlstm.sqlctimeout = (unsigned int )0;
    sqlstm.sqlcnowait = (unsigned int )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (SELECT)");
}


    
    // output_win 윈도우 크기 측정
    getmaxyx(output_win, max_rows, max_cols);
    // 데이터 출력 가능한 실제 행 수 계산 (테두리, 제목, 헤더 5줄 제외)
    data_rows = max_rows - 5; 
    if (data_rows <= 0) data_rows = 1;

    // ------------------------------------------------------------
    // 2. 정적 커서 선언 및 실행 (전체 조회)
    // ------------------------------------------------------------
    
    // 정적 쿼리를 위한 커서 선언
    /* EXEC SQL DECLARE inbound_cursor CURSOR FOR
        SELECT 
            I.INB_ID, P.PROD_NAME, D.DIST_NAME, C.CATE_NAME, 
            TO_CHAR(I.INB_DATE, 'YYYY-MM-DD'), I.INB_QTY, I.INB_COST
        FROM 
            SYSTEM.INBOUND I, 
            SYSTEM.PRODUCT P, 
            SYSTEM.DISTRIBUTOR D, 
            SYSTEM.CATEGORY C
        WHERE 
            I.PROD_ID = P.PROD_ID AND I.DIST_ID = D.DIST_ID AND I.CATE_ID = C.CATE_ID
        ORDER BY I.INB_ID DESC; */ 
 
        
    /* EXEC SQL OPEN inbound_cursor; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = sq0027;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )639;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.sqlpfmem = (unsigned int  )0;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqcmod = (unsigned int )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (SELECT)");
}

 
    
    // ------------------------------------------------------------
    // 3. UI 헤더 출력 및 데이터 페치 (화면 크기만큼)
    // ------------------------------------------------------------
    
    werase(output_win);
    // UI 테두리 및 제목 출력 로직은 생략하고 헤더만 출력합니다.
    
    // 고정 헤더 출력 (Y=3, Y=4)
    if (has_colors()) {wattron(output_win, COLOR_PAIR(7) | A_BOLD); }
        // 포맷 너비 재조정 (20s, 25s, 18s)
        mvwprintw(output_win, 3, 2, "%-20s %-25s %-18s %-15s %-10s %8s %12s", 
                 "입고ID", "상품명", "유통업체", "카테고리", "입고일자", "수량", "단가"); 
        mvwprintw(output_win, 4, 2, "-------------------- ------------------------- ------------------ --------------- ---------- -------- ------------");
    if (has_colors()) {wattroff(output_win, COLOR_PAIR(7) | A_BOLD); }

    // 데이터 출력 루프: 화면에 출력 가능한 행 수만큼만 FETCH
    for (int i = 0; i < data_rows; i++) {
        /* EXEC SQL FETCH inbound_cursor INTO 
            :inb_id_hv, :prod_name_hv, :dist_name_hv, :cate_name_hv, 
            :inb_date_hv, :inb_qty_hv, :inb_cost_hv; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 7;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )654;
        sqlstm.selerr = (unsigned short)1;
        sqlstm.sqlpfmem = (unsigned int  )0;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqfoff = (         int )0;
        sqlstm.sqfmod = (unsigned int )2;
        sqlstm.sqhstv[0] = (unsigned char  *)&inb_id_hv;
        sqlstm.sqhstl[0] = (unsigned long )18;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (unsigned char  *)&prod_name_hv;
        sqlstm.sqhstl[1] = (unsigned long )103;
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         short *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned long )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqhstv[2] = (unsigned char  *)&dist_name_hv;
        sqlstm.sqhstl[2] = (unsigned long )53;
        sqlstm.sqhsts[2] = (         int  )0;
        sqlstm.sqindv[2] = (         short *)0;
        sqlstm.sqinds[2] = (         int  )0;
        sqlstm.sqharm[2] = (unsigned long )0;
        sqlstm.sqadto[2] = (unsigned short )0;
        sqlstm.sqtdso[2] = (unsigned short )0;
        sqlstm.sqhstv[3] = (unsigned char  *)&cate_name_hv;
        sqlstm.sqhstl[3] = (unsigned long )53;
        sqlstm.sqhsts[3] = (         int  )0;
        sqlstm.sqindv[3] = (         short *)0;
        sqlstm.sqinds[3] = (         int  )0;
        sqlstm.sqharm[3] = (unsigned long )0;
        sqlstm.sqadto[3] = (unsigned short )0;
        sqlstm.sqtdso[3] = (unsigned short )0;
        sqlstm.sqhstv[4] = (unsigned char  *)&inb_date_hv;
        sqlstm.sqhstl[4] = (unsigned long )13;
        sqlstm.sqhsts[4] = (         int  )0;
        sqlstm.sqindv[4] = (         short *)0;
        sqlstm.sqinds[4] = (         int  )0;
        sqlstm.sqharm[4] = (unsigned long )0;
        sqlstm.sqadto[4] = (unsigned short )0;
        sqlstm.sqtdso[4] = (unsigned short )0;
        sqlstm.sqhstv[5] = (unsigned char  *)&inb_qty_hv;
        sqlstm.sqhstl[5] = (unsigned long )sizeof(int);
        sqlstm.sqhsts[5] = (         int  )0;
        sqlstm.sqindv[5] = (         short *)0;
        sqlstm.sqinds[5] = (         int  )0;
        sqlstm.sqharm[5] = (unsigned long )0;
        sqlstm.sqadto[5] = (unsigned short )0;
        sqlstm.sqtdso[5] = (unsigned short )0;
        sqlstm.sqhstv[6] = (unsigned char  *)&inb_cost_hv;
        sqlstm.sqhstl[6] = (unsigned long )sizeof(float);
        sqlstm.sqhsts[6] = (         int  )0;
        sqlstm.sqindv[6] = (         short *)0;
        sqlstm.sqinds[6] = (         int  )0;
        sqlstm.sqharm[6] = (unsigned long )0;
        sqlstm.sqadto[6] = (unsigned short )0;
        sqlstm.sqtdso[6] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode == 1403) goto no_data_found;
        if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (SELECT)");
}


        
        if (sqlca.sqlcode == 1403) break; // NOT FOUND (데이터 끝)
        
        // 널 문자 처리
        inb_id_hv.arr[inb_id_hv.len] = '\0';
        prod_name_hv.arr[prod_name_hv.len] = '\0';
        dist_name_hv.arr[dist_name_hv.len] = '\0';
        cate_name_hv.arr[cate_name_hv.len] = '\0';
        inb_date_hv.arr[inb_date_hv.len] = '\0';

        // 데이터 출력 (Y=5부터 시작)
        // 포맷 너비 재조정
        mvwprintw(output_win, current_y++, 2, "%-20s %-25s %-18s %-15s %-10s %8d %12.2f",
                 inb_id_hv.arr, prod_name_hv.arr, dist_name_hv.arr, cate_name_hv.arr,
                 inb_date_hv.arr, inb_qty_hv, inb_cost_hv);
    }
    
    // ------------------------------------------------------------
    // 4. 정리 및 출력 완료
    // ------------------------------------------------------------
    /* EXEC SQL CLOSE inbound_cursor; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )697;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (SELECT)");
}


    
    if (sqlca.sqlerrd[2] == 0) { // FETCH된 행이 없으면 (초기 데이터 없음)
        wscrl(output_win, 1); wprintw(output_win, " [INFO] 조회된 입고 내역이 없습니다.");
        return_status = 0;
    } else {
        wscrl(output_win, 1); wprintw(output_win, " [INFO] 총 %d건의 입고 내역을 출력했습니다.", sqlca.sqlerrd[2]);
        return_status = 1;
    }

    goto cleanup;

// ------------------------------------------------------------
// 오류 처리 레이블 및 Cleanup
// ------------------------------------------------------------
query_error:
    wscrl(output_win, 1);
    wprintw(output_win, " [ERROR] 입고 내역 조회 중 DB 오류 발생.");
    wrefresh(output_win);
    return_status = 0;
    goto cleanup;
    
no_data_found:
    // FETCH 루프가 break로 종료되었으므로, 성공으로 간주하고 최종 출력을 실행합니다.
    return_status = 1; 
    goto cleanup;

cleanup:
    // DB 연결 종료
    if (return_status == 1) {
        /* EXEC SQL COMMIT WORK RELEASE; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 7;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )712;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (SELECT)");
}

 
    } else {
        /* EXEC SQL ROLLBACK RELEASE; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 7;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )727;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) sql_error("Oracle Error during C call (SELECT)");
}


    }
    
    // 최종 화면 갱신
    wrefresh(output_win); 
    return return_status;
}

/*
 * 바코드를 기반으로 상품 정보와 재고를 조회하고 장바구니 수량을 고려하여 검증합니다.
 * * @param barcode: 조회할 바코드 문자열 (const char*)
 * @param quantity: 판매를 요청한 수량 (int*)
 * @param product_name_out: 조회된 상품 이름을 저장할 버퍼 (char*)
 * @param price_out: 조회된 판매 가격을 저장할 포인터 (double*)
 * @return 1 (상품 존재 및 재고 충분), -1 (재고 부족), 0 (상품 없음 또는 오류)
 */
int get_product_price(const char *barcode, int *quantity, char *product_name_out, double *price_out) {

    // NOTE: SQLERROR 발생 시 sql_error 함수에서 이미 exit(1)이 호출됩니다.
    /* EXEC SQL WHENEVER SQLERROR GOTO query_error; */ 

    /* EXEC SQL WHENEVER NOT FOUND GOTO not_found; */ 


    int requested_qty = *quantity;
    int return_status = 0; // 최종 반환 상태 (0으로 초기화)
    
    // 장바구니에 이미 담겨있는 수량 조회 (외부 함수 호출)
    int current_cart_qty = get_current_cart_quantity(barcode);
    
    // 최종적으로 장바구니에 담기게 될 예상 수량
    int final_total_qty = current_cart_qty + requested_qty;
    
    // ------------------------------------------------------------
    // 1. DB 접속
    // ------------------------------------------------------------
    /* EXEC SQL CONNECT :db_user IDENTIFIED BY :db_pass USING :db_connect_string; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )10;
    sqlstm.offset = (unsigned int  )742;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)db_user;
    sqlstm.sqhstl[0] = (unsigned long )0;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)db_pass;
    sqlstm.sqhstl[1] = (unsigned long )0;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (unsigned char  *)db_connect_string;
    sqlstm.sqhstl[2] = (unsigned long )0;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         short *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned long )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlstm.sqlcmax = (unsigned int )100;
    sqlstm.sqlcmin = (unsigned int )2;
    sqlstm.sqlcincr = (unsigned int )1;
    sqlstm.sqlctimeout = (unsigned int )0;
    sqlstm.sqlcnowait = (unsigned int )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) goto query_error;
}


    
    // 1. 입력 바코드를 호스트 변수에 설정
    if (strlen(barcode) > 20 || requested_qty <= 0) {
        return_status = 0;
        goto cleanup;
    }
    
    // 호스트 변수 바인딩 설정
    size_t input_len = strlen(barcode);
    strcpy((char*)barcode_hv.arr, barcode);
    barcode_hv.arr[input_len] = '\0';
    barcode_hv.len = (unsigned short)input_len;

    // ------------------------------------------------------------
    // 2. DB 조회 (PRODUCT와 INVENTORY 조인)
    // ------------------------------------------------------------
    /* EXEC SQL SELECT P.PROD_NAME, P.SELL_PRICE, I.CURRENT_QTY
             INTO :prod_name_hv, :sell_price_hv, :current_qty_hv
             FROM SYSTEM.PRODUCT P, SYSTEM.INVENTORY I
             WHERE RTRIM(P.BARCODE) = :barcode_hv
               AND P.PROD_ID = I.PROD_ID; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select P.PROD_NAME ,P.SELL_PRICE ,I.CURRENT_QTY into :b0\
,:b1,:b2  from SYSTEM.PRODUCT P ,SYSTEM.INVENTORY I where (RTRIM(P.BARCODE)=:\
b3 and P.PROD_ID=I.PROD_ID)";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )773;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.sqlpfmem = (unsigned int  )0;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&prod_name_hv;
    sqlstm.sqhstl[0] = (unsigned long )103;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)&sell_price_hv;
    sqlstm.sqhstl[1] = (unsigned long )sizeof(float);
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (unsigned char  *)&current_qty_hv;
    sqlstm.sqhstl[2] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         short *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned long )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqhstv[3] = (unsigned char  *)&barcode_hv;
    sqlstm.sqhstl[3] = (unsigned long )23;
    sqlstm.sqhsts[3] = (         int  )0;
    sqlstm.sqindv[3] = (         short *)0;
    sqlstm.sqinds[3] = (         int  )0;
    sqlstm.sqharm[3] = (unsigned long )0;
    sqlstm.sqadto[3] = (unsigned short )0;
    sqlstm.sqtdso[3] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode == 1403) goto not_found;
    if (sqlca.sqlcode < 0) goto query_error;
}


             
    // 3. 최종 재고 수량 검사 (DB 총재고 vs. 장바구니+요청 수량)
    if (final_total_qty > current_qty_hv) {
        return_status = -1; // 재고 부족 (요청한 수량을 담을 수 없음)
        goto cleanup;
    }

    // 4. 결과 복사 및 반환 준비 (성공)
    strncpy(product_name_out, (char*)prod_name_hv.arr, prod_name_hv.len);
    product_name_out[prod_name_hv.len] = '\0';
    *price_out = (double)sell_price_hv;
    
    return_status = 1; // 성공 상태 설정
    goto cleanup;


// ------------------------------------------------------------
// 오류 처리 레이블 (DB 쿼리 실행 실패/NOT FOUND 시 진입)
// ------------------------------------------------------------
query_error:
    return_status = 0;
    goto cleanup;
    
not_found:
    // NOT FOUND (상품 없음/재고 정보 없음)
    return_status = 0;
    goto cleanup;


// ------------------------------------------------------------
// 5. 최종 정리 및 연결 해제
// ------------------------------------------------------------
cleanup:
    // NOTE: SQLERROR 발생 시 sql_error에서 ROLLBACK RELEASE를 이미 수행하고 exit(1)로 종료되므로,
    // 이곳은 NOT FOUND나 C 코드 유효성 검사 실패 시에만 도달합니다.
    
    if (return_status == 1) {
        /* EXEC SQL COMMIT WORK RELEASE; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 7;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )804;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) goto query_error;
}

 // 성공 시 커밋 및 연결 해제
    } else {
        /* EXEC SQL ROLLBACK RELEASE; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 7;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )819;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) goto query_error;
}

 // 실패 시 롤백 및 연결 해제
    }
    
    return return_status;
}


// 인자로 total_amount, paymeny_type 를 전달받아서
// 시퀀스가 적용된 SALE_NUM에 insert into sale values(SALE_NUM, DATE=SYSDATE, TOTAL_AMOUNT=total_amount, PAYMENT_TYPE=paymeny_type, EMP_ID=1) 을 처리하는 함수
// 성공적으로 넣으면 SALE_NUM을 반환하고 실패하면 -1을 반환한다.
char* insert_sale_record(double total_amount, const char *payment_type) {

    /* EXEC SQL WHENEVER SQLERROR GOTO query_error; */ 

    /* EXEC SQL WHENEVER NOT FOUND GOTO query_error; */ 

    
    // SALE_NUM 생성용 호스트 변수 및 정적 반환 버퍼
    long next_sale_num;
    static char result_sale_num[16]; // SALE_NUM (VARCHAR2(15)) + 널문자

    // 호스트 변수 설정
    /* VARCHAR payment_type_hv[11]; */ 
struct { unsigned short len; unsigned char arr[11]; } payment_type_hv;

    strcpy((char*)payment_type_hv.arr, payment_type);
    payment_type_hv.len = strlen(payment_type);
    
    // EMP_ID는 '1'로 고정
    /* VARCHAR emp_id_hv[11]; */ 
struct { unsigned short len; unsigned char arr[11]; } emp_id_hv;

    strcpy((char*)emp_id_hv.arr, "1");
    emp_id_hv.len = 1; 

    // VARCHAR SALE_NUM 호스트 변수
    /* VARCHAR sale_num_hv[16]; */ 
struct { unsigned short len; unsigned char arr[16]; } sale_num_hv;


    // ------------------------------------------------------------
    // 1. DB 접속
    // ------------------------------------------------------------
    /* EXEC SQL CONNECT :db_user IDENTIFIED BY :db_pass USING :db_connect_string; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )10;
    sqlstm.offset = (unsigned int  )834;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)db_user;
    sqlstm.sqhstl[0] = (unsigned long )0;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)db_pass;
    sqlstm.sqhstl[1] = (unsigned long )0;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (unsigned char  *)db_connect_string;
    sqlstm.sqhstl[2] = (unsigned long )0;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         short *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned long )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlstm.sqlcmax = (unsigned int )100;
    sqlstm.sqlcmin = (unsigned int )2;
    sqlstm.sqlcincr = (unsigned int )1;
    sqlstm.sqlctimeout = (unsigned int )0;
    sqlstm.sqlcnowait = (unsigned int )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) goto query_error;
}



    // ------------------------------------------------------------
    // 2. SALE_NUM 시퀀스 값 생성
    // ------------------------------------------------------------
    /* EXEC SQL SELECT SYSTEM.SALE_NUM_SEQ.NEXTVAL INTO :next_sale_num FROM DUAL; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select SYSTEM.SALE_NUM_SEQ.nextval  into :b0  from DUAL ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )865;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.sqlpfmem = (unsigned int  )0;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&next_sale_num;
    sqlstm.sqhstl[0] = (unsigned long )sizeof(long);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode == 1403) goto query_error;
    if (sqlca.sqlcode < 0) goto query_error;
}


    
    // ------------------------------------------------------------
    // 3. SALE_NUM 문자열 포맷 및 INSERT
    // ------------------------------------------------------------
    
    // next_sale_num을 VARCHAR2(15) 문자열로 포맷하여 호스트 변수에 저장
    sprintf((char*)sale_num_hv.arr, "%015ld", next_sale_num);
    sale_num_hv.len = strlen((char*)sale_num_hv.arr);
    
    // 반환 버퍼에 최종 SALE_NUM 복사
    strcpy(result_sale_num, (char*)sale_num_hv.arr);


    /* EXEC SQL INSERT INTO SYSTEM.SALE (SALE_NUM, SALE_DATE, TOTAL_AMOUNT, PAYMENT_TYPE, EMP_ID)
    VALUES (:sale_num_hv, SYSDATE, :total_amount, :payment_type_hv, :emp_id_hv); */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "insert into SYSTEM.SALE (SALE_NUM,SALE_DATE,TOTAL_AMOUNT\
,PAYMENT_TYPE,EMP_ID) values (:b0,SYSDATE,:b1,:b2,:b3)";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )884;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&sale_num_hv;
    sqlstm.sqhstl[0] = (unsigned long )18;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)&total_amount;
    sqlstm.sqhstl[1] = (unsigned long )sizeof(double);
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (unsigned char  *)&payment_type_hv;
    sqlstm.sqhstl[2] = (unsigned long )13;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         short *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned long )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqhstv[3] = (unsigned char  *)&emp_id_hv;
    sqlstm.sqhstl[3] = (unsigned long )13;
    sqlstm.sqhsts[3] = (         int  )0;
    sqlstm.sqindv[3] = (         short *)0;
    sqlstm.sqinds[3] = (         int  )0;
    sqlstm.sqharm[3] = (unsigned long )0;
    sqlstm.sqadto[3] = (unsigned short )0;
    sqlstm.sqtdso[3] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode == 1403) goto query_error;
    if (sqlca.sqlcode < 0) goto query_error;
}



    /* EXEC SQL COMMIT WORK RELEASE; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )915;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) goto query_error;
}


    
    // 성공 시 문자열 SALE_NUM 반환
    return result_sale_num;

query_error:
    /* EXEC SQL ROLLBACK RELEASE; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )930;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) goto query_error;
}


    // 실패 시 문자열 "-1" 반환
    strcpy(result_sale_num, "-1");
    return result_sale_num;
}

// SALE_NUM, barcode, quantity, price 전달
// 시퀀스 적용 SALE_DETAIL_ID, 바코드를 앞3자를 제외하고 뒷 4자리만 prod_id에 저장
// insert into sale_detail values(SALE_DETAIL_ID, SALE_NUM=SALE_NUM, PROD_ID=prod_id, SALE_QTY=quantity, UNIT_PRICE=price, SUB_TOTAL=quantity*price)
// 삽입에 성공하면 1 실패하면 -1을 반환한다.
int insert_sale_detail_item(const char *sale_num, const char *barcode, int quantity, double price) {

    /* EXEC SQL WHENEVER SQLERROR GOTO query_error; */ 

    /* EXEC SQL WHENEVER NOT FOUND GOTO query_error; */ 
 

    // SALE_DETAIL_ID 생성용 호스트 변수
    long next_detail_id;
    
    // 호스트 변수 설정
    /* VARCHAR detail_id_hv[16]; */ 
struct { unsigned short len; unsigned char arr[16]; } detail_id_hv;
 // SALE_DETAIL_ID VARCHAR2(15)
    /* VARCHAR sale_num_hv[16]; */ 
struct { unsigned short len; unsigned char arr[16]; } sale_num_hv;
  // SALE_NUM VARCHAR2(15)
    /* VARCHAR prod_id_hv[5]; */ 
struct { unsigned short len; unsigned char arr[5]; } prod_id_hv;
    // PROD_ID VARCHAR2(4)
    double sub_total = (double)quantity * price;
    
    // 재고 확인용 변수 (UPDATE 후 재고 상태 확인)
    int remaining_qty = 0; 

    // ------------------------------------------------------------
    // 1. DB 접속
    // ------------------------------------------------------------
    /* EXEC SQL CONNECT :db_user IDENTIFIED BY :db_pass USING :db_connect_string; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )10;
    sqlstm.offset = (unsigned int  )945;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)db_user;
    sqlstm.sqhstl[0] = (unsigned long )0;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)db_pass;
    sqlstm.sqhstl[1] = (unsigned long )0;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (unsigned char  *)db_connect_string;
    sqlstm.sqhstl[2] = (unsigned long )0;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         short *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned long )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlstm.sqlcmax = (unsigned int )100;
    sqlstm.sqlcmin = (unsigned int )2;
    sqlstm.sqlcincr = (unsigned int )1;
    sqlstm.sqlctimeout = (unsigned int )0;
    sqlstm.sqlcnowait = (unsigned int )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) goto query_error;
}



    // ------------------------------------------------------------
    // 2. ID 생성 및 바코드 변환
    // ------------------------------------------------------------
    /* EXEC SQL SELECT SYSTEM.SALE_DETAIL_ID_SEQ.NEXTVAL INTO :next_detail_id FROM DUAL; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select SYSTEM.SALE_DETAIL_ID_SEQ.nextval  into :b0  from\
 DUAL ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )976;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.sqlpfmem = (unsigned int  )0;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&next_detail_id;
    sqlstm.sqhstl[0] = (unsigned long )sizeof(long);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode == 1403) goto query_error;
    if (sqlca.sqlcode < 0) goto query_error;
}


    
    sprintf((char*)detail_id_hv.arr, "%015ld", next_detail_id);
    detail_id_hv.len = strlen((char*)detail_id_hv.arr);

    strncpy((char*)prod_id_hv.arr, barcode + 3, 4); 
    prod_id_hv.arr[4] = '\0';
    prod_id_hv.len = 4;
    
    strncpy((char*)sale_num_hv.arr, sale_num, 15);
    sale_num_hv.arr[15] = '\0';
    sale_num_hv.len = strlen((char*)sale_num_hv.arr);

    // ------------------------------------------------------------
    // 3. SALE_DETAIL 테이블에 INSERT (판매 기록)
    // ------------------------------------------------------------
    /* EXEC SQL INSERT INTO SYSTEM.SALE_DETAIL (SALE_DETAIL_ID, SALE_NUM, PROD_ID, SALE_QTY, UNIT_PRICE, SUB_TOTAL)
    VALUES (:detail_id_hv, :sale_num_hv, :prod_id_hv, :quantity, :price, :sub_total); */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "insert into SYSTEM.SALE_DETAIL (SALE_DETAIL_ID,SALE_NUM,\
PROD_ID,SALE_QTY,UNIT_PRICE,SUB_TOTAL) values (:b0,:b1,:b2,:b3,:b4,:b5)";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )995;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&detail_id_hv;
    sqlstm.sqhstl[0] = (unsigned long )18;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)&sale_num_hv;
    sqlstm.sqhstl[1] = (unsigned long )18;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (unsigned char  *)&prod_id_hv;
    sqlstm.sqhstl[2] = (unsigned long )7;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         short *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned long )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqhstv[3] = (unsigned char  *)&quantity;
    sqlstm.sqhstl[3] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[3] = (         int  )0;
    sqlstm.sqindv[3] = (         short *)0;
    sqlstm.sqinds[3] = (         int  )0;
    sqlstm.sqharm[3] = (unsigned long )0;
    sqlstm.sqadto[3] = (unsigned short )0;
    sqlstm.sqtdso[3] = (unsigned short )0;
    sqlstm.sqhstv[4] = (unsigned char  *)&price;
    sqlstm.sqhstl[4] = (unsigned long )sizeof(double);
    sqlstm.sqhsts[4] = (         int  )0;
    sqlstm.sqindv[4] = (         short *)0;
    sqlstm.sqinds[4] = (         int  )0;
    sqlstm.sqharm[4] = (unsigned long )0;
    sqlstm.sqadto[4] = (unsigned short )0;
    sqlstm.sqtdso[4] = (unsigned short )0;
    sqlstm.sqhstv[5] = (unsigned char  *)&sub_total;
    sqlstm.sqhstl[5] = (unsigned long )sizeof(double);
    sqlstm.sqhsts[5] = (         int  )0;
    sqlstm.sqindv[5] = (         short *)0;
    sqlstm.sqinds[5] = (         int  )0;
    sqlstm.sqharm[5] = (unsigned long )0;
    sqlstm.sqadto[5] = (unsigned short )0;
    sqlstm.sqtdso[5] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode == 1403) goto query_error;
    if (sqlca.sqlcode < 0) goto query_error;
}


    
    // ------------------------------------------------------------
    // 4. INVENTORY 재고 감소
    // ------------------------------------------------------------
    /* EXEC SQL UPDATE SYSTEM.INVENTORY
             SET CURRENT_QTY = CURRENT_QTY - :quantity 
             WHERE PROD_ID = :prod_id_hv
             RETURNING CURRENT_QTY INTO :remaining_qty; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "update SYSTEM.INVENTORY  set CURRENT_QTY=(CURRENT_QTY-:b\
0) where PROD_ID=:b1 returning CURRENT_QTY into :b2 ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )1034;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )1;
    sqlstm.sqhstv[0] = (unsigned char  *)&quantity;
    sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)&prod_id_hv;
    sqlstm.sqhstl[1] = (unsigned long )7;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (unsigned char  *)&remaining_qty;
    sqlstm.sqhstl[2] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         short *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned long )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode == 1403) goto query_error;
    if (sqlca.sqlcode < 0) goto query_error;
}

 // ✨ 업데이트 후 남은 재고를 즉시 가져옴
             
    // ------------------------------------------------------------
    // 5. 재고가 0이 되면 해당 행 삭제 (DELETE) ✨
    // ------------------------------------------------------------
    if (remaining_qty == 0) {
        /* EXEC SQL DELETE FROM SYSTEM.INVENTORY
                 WHERE PROD_ID = :prod_id_hv; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 7;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "delete  from SYSTEM.INVENTORY  where PROD_ID=:b0";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )1061;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)&prod_id_hv;
        sqlstm.sqhstl[0] = (unsigned long )7;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode == 1403) goto query_error;
        if (sqlca.sqlcode < 0) goto query_error;
}


        
        wscrl(console_win, 1);
        if (has_colors()) {wattron(console_win, COLOR_PAIR(3) | A_BOLD); } 
        mvwaddwstr(console_win, CONSOLE_HEIGHT - 2, 1, L" [LOG] [상품 판매] 상품 재고가 0이 되어 재고가 삭제되었습니다.");
        if (has_colors()) {wattroff(console_win, COLOR_PAIR(3) | A_BOLD); }
        wnoutrefresh(console_win);
    }

    /* EXEC SQL COMMIT WORK RELEASE; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )1080;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) goto query_error;
}

 

    return 1; // 성공 반환

query_error:
    /* EXEC SQL ROLLBACK RELEASE; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )1095;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) goto query_error;
}

 
    return -1; // 실패 반환
}
// 1