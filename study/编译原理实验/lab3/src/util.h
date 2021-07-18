#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFLEN 256
#define RESERVED_NUM 12

// 词法分析 

int lex = 0, row = 0, column = 0; 
FILE *input;                                                      // 文件指针
static char Buf[BUFLEN];
char tokenString[BUFLEN + 1];

typedef enum {                                                    // token类型
	IF, ELSE, WRITE, READ, RETURN, BEGIN, END, MAIN, INT, REAL,	WHILE, FOR,  // 关键字
	SEMI, COMMA, LEFTPAREN, RIGHTPAREN,                           // 分隔符 ; , ( )
	ADD, SUB, MUL, DIV, ASSIGN, EQUAL, UNEQUAL, GREATER, LESS, MOD, XOR,     // 运算符 + - * / := == != > < % ^
	ID, NUM, STR,                                                 // ID NUM STR
	ERROR, ENDFILE                                                // other
}TokenType;

typedef enum {                                                    // DFA的状态
	STATUS_START,                                                 // 开始 
	STATUS_ASSIGN,                                                // 赋值 
	STATUS_EQUAL,                                                 // 相等 
	STATUS_UNEQUAL,                                               // 不等 
	STATUS_COMMENT,                                               // 注释 
	STATUS_NUMBER,                                                // 整数 
	STATUS_REAL,                                                  // 小数 
	STATUS_STR,                                                   // 字符串 
	STATUS_ID,                                                    // 函数名/变量名 
	STATUS_DONE                                                   // 结束 
}lexStatus;

static struct {                                                   // 字符串转为对应的状态 
	char* str; TokenType token;
} reservedWords[RESERVED_NUM] = { 
	{"IF", IF}, {"ELSE", ELSE}, {"READ", READ}, {"WRITE", WRITE}, {"BEGIN", BEGIN}, {"WHILE", WHILE},
	{"END", END}, {"MAIN", MAIN}, {"RETURN", RETURN}, {"INT", INT}, {"REAL", REAL}, {"FOR", FOR} };

// 语法分析 

static TokenType token;                                           // 储存当前的 token
static int deep = 0;

typedef enum { MethodK, TypeK, ParamK, StatementK, ExpressionK } NodeKind;
typedef enum { MainK, NormalK } MethodKind;
typedef enum { FormalK, ActualK } ParamKind;
typedef enum { ReturnTypeK, IntTypeK, RealTypeK } TypeKind;
typedef enum { IfK, ReturnK, AssignK, ReadK, WriteK, IntDeclareK, RealDeclareK, WhileK, ForK } StatementKind;
typedef enum { OpK, ConstK, IdK, MethodCallK} ExpressionKind;

struct Kind { 
	MethodKind method;
	ParamKind param;
	TypeKind type;
	StatementKind statement;
	ExpressionKind expression;
}; 

struct Attr {
	TokenType token;
	float val;
	char* name;
};

struct TreeNode {
	struct TreeNode* child[10];                                   // 子节点 
	struct TreeNode* next;                                        // 指向序列中下一个节点 
	NodeKind nodekind;                                            // 节点类型
	struct Kind kind;
	struct Attr attr;
};

void menu(void) {
	printf("---------------------- WELCOME TO COMPILER -----------------------\n");
	printf("                   1. Lexical analysis test1\n");
	printf("                   2. Lexical analysis test2\n");
	printf("                   3. Syntax analysis test1\n");
	printf("                   4. Syntax analysis test2\n");
	printf("                   0. Exit\n");
	printf("------------------------------------------------------------------\n");
	printf("[INPUT] Please enter 0-4 ^_^ \n");
}

#endif
