#ifndef CODE_DATE
#define CODE_DATE
#include "data.h"

// LLVMcode *codehd; /* 命令列の先頭のアドレスを保持するポインタ */
// LLVMcode *codetl; /* 命令列の末尾のアドレスを保持するポインタ */

// /* 関数定義の線形リストの先頭の要素のアドレスを保持するポインタ */
// Fundecl *declhd;
// /* 関数定義の線形リストの末尾の要素のアドレスを保持するポインタ */
// Fundecl *decltl;


/* 変数もしくは定数の型 */
typedef struct
{
    Scope type;      /* 変数（のレジスタ）か整数の区別 */
    char vname[256]; /* 変数の場合の変数名 */
    int val;         /* 整数の場合はその値，変数の場合は割り当てたレジスタ番号 */
} Factor;

/* LLVM命令名の定義 */
typedef enum
{
    // Common,   /* common */
    Alloca,   /* alloca */
    Store,    /* store  */
    Load,     /* load   */
    BrUncond, /* br     */
    BrCond,   /* brc    */
    Label,    /* label  */
    Add,      /* add    */
    Sub,      /* sub    */
    Mult,     /* mult   */
    Div,      /* div    */
    Icmp,     /* icmp   */
    Ret       /* ret    */
} LLVMcommand;

/* 比較演算子の種類 */
typedef enum
{
    EQUAL, /* eq （==）*/
    NE,    /* ne （!=）*/
    SGT,   /* sgt （>，符号付き） */
    SGE,   /* sge （>=，符号付き）*/
    SLT,   /* slt （<，符号付き） */
    SLE    /* sle （<=，符号付き）*/
} Cmptype;

typedef struct llvmcode
{
    LLVMcommand command; /* 命令名 */
    union {              /* 命令の引数 */
        struct
        { /* common */
            Factor arg1;
            Factor retval;
        } common;
        struct
        { /* alloca */
            Factor retval;
        } alloca;
        struct
        { /* store  */
            Factor arg1;
            Factor arg2;
        } store;
        struct
        { /* load   */
            Factor arg1;
            Factor retval;
        } load;
        struct
        { /* br     */
            int arg1;
        } bruncond;
        struct
        { /* brc    */
            Factor arg1;
            int arg2;
            int arg3;
        } brcond;
        struct
        { /* label  */
            int l;
        } label;
        struct
        { /* add    */
            Factor arg1;
            Factor arg2;
            Factor retval;
        } add;
        struct
        { /* sub    */
            Factor arg1;
            Factor arg2;
            Factor retval;
        } sub;
        struct
        { /* mult   */
            Factor arg1;
            Factor arg2;
            Factor retval;
        } mult;
        struct
        { /* div    */
            Factor arg1;
            Factor arg2;
            Factor retval;
        } div;
        struct
        { /* icmp   */
            Cmptype type;
            Factor arg1;
            Factor arg2;
            Factor retval;
        } icmp;
        struct
        { /* ret    */
            Factor arg1;
        } ret;
    } args;
    /* 次の命令へのポインタ */
    struct llvmcode *next;
} LLVMcode;

/* 変数もしくは定数のためのスタック */
typedef struct
{
    Factor element[100]; /* スタック（最大要素数は100まで） */
    unsigned int top;    /* スタックのトップの位置         */
} Factorstack;

Factorstack fstack; /* 整数もしくはレジスタ番号を保持するスタック */

/* LLVMの関数定義 */
typedef struct fundecl
{
    char fname[256];      /* 関数名                      */
    unsigned arity;       /* 引数個数                    */
    Factor args[10];      /* 引数名                      */
    LLVMcode *codes;      /* 命令列の線形リストへのポインタ */
    struct fundecl *next; /* 次の関数定義へのポインタ      */
} Fundecl;

void init_fstack();
Factor factorpop();
void factorpush(Factor x);
void generateCode(LLVMcommand command);
void displayFactor(Factor factor);
void displayLlvmcodes(LLVMcode *code);
void displayLlvmfundecl(Fundecl *decl);
void insertDecl(char *fname, unsigned arity, Factor *args);
Factor generateFactor(char *name);
void displayGlobalVar();
void insertCode(LLVMcode *tmp);

#endif