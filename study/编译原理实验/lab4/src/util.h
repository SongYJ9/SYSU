#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFLEN 256
#define RESERVED_NUM 12

// �ʷ����� 

int lex = 0, row = 0, column = 0; 
FILE *input;                                                      // �ļ�ָ��
static char Buf[BUFLEN];
char tokenString[BUFLEN + 1];

typedef enum {                                                    // token����
	IF, ELSE, WRITE, READ, RETURN, BEGIN, END, MAIN, INT, REAL,	WHILE, FOR,  // �ؼ���
	SEMI, COMMA, LEFTPAREN, RIGHTPAREN,                           // �ָ��� ; , ( )
	ADD, SUB, MUL, DIV, ASSIGN, EQUAL, UNEQUAL, GREATER, LESS, MOD, XOR,     // ����� + - * / := == != > < % ^
	ID, NUM, STR,                                                 // ID NUM STR
	ERROR, ENDFILE                                                // other
}TokenType;

typedef enum {                                                    // DFA��״̬
	STATUS_START,                                                 // ��ʼ 
	STATUS_ASSIGN,                                                // ��ֵ 
	STATUS_EQUAL,                                                 // ��� 
	STATUS_UNEQUAL,                                               // ���� 
	STATUS_COMMENT,                                               // ע�� 
	STATUS_NUMBER,                                                // ���� 
	STATUS_REAL,                                                  // С�� 
	STATUS_STR,                                                   // �ַ��� 
	STATUS_ID,                                                    // ������/������ 
	STATUS_DONE                                                   // ���� 
}lexStatus;

static struct {                                                   // �ַ���תΪ��Ӧ��״̬ 
	char* str; TokenType token;
} reservedWords[RESERVED_NUM] = { 
	{"IF", IF}, {"ELSE", ELSE}, {"READ", READ}, {"WRITE", WRITE}, {"BEGIN", BEGIN}, {"WHILE", WHILE},
	{"END", END}, {"MAIN", MAIN}, {"RETURN", RETURN}, {"INT", INT}, {"REAL", REAL}, {"FOR", FOR} };

// �﷨���� 

static TokenType token;                                           // ���浱ǰ�� token
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
	struct TreeNode* child[10];                                   // �ӽڵ� 
	struct TreeNode* next;                                        // ָ����������һ���ڵ� 
	NodeKind nodekind;                                            // �ڵ�����
	struct Kind kind;
	struct Attr attr;
};

void menu(void) {
	printf("---------------------- WELCOME TO COMPILER -----------------------\n");
	printf("                   1. Lexical analysis test1\n");
	printf("                   2. Lexical analysis test2\n");
	printf("                   3. Syntax analysis test1\n");
	printf("                   4. Syntax analysis test2\n");
	printf("                   5. Semantic analysis test1\n");
	printf("                   6. Semantic analysis test2\n");
	printf("                   0. Exit\n");
	printf("------------------------------------------------------------------\n");
	printf("[INPUT] Please enter 0-6 ^_^ \n");
}

#endif
