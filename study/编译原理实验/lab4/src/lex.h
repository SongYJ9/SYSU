#ifndef LEX_H 
#define LEX_H

#include "util.h"

// 词法分析器：得到token序列

// 主函数 
TokenType getToken();  

// 辅助函数 
static char getChar();
static void undo();
static TokenType reservedCheck(char*);
static void lexError();
void printToken(TokenType, char*);

// 函数实现
TokenType getToken() {
	int tokenStringIndex = 0;                                 // 记录字符位置
	TokenType currentToken;                                   // 记录当前分析得到的 token
	lexStatus currentStatus = STATUS_START;                   // 记录当前状态，初始为开始状态 
	int save = 0;                                             // 记录当前字符是否需要保存下来
	
	while (currentStatus != STATUS_DONE) {
		char c = getChar();                                   // 获得下一个字符
		switch (currentStatus) {                              // 状态转移
			case STATUS_START:                                // 开始状态 
				if (isdigit(c)) {                             // 如果是数字，当前状态转换为整数 
					save = 1;
					currentStatus = STATUS_NUMBER;
				}
				else if (isalpha(c)) {                        // 如果是字符，当前状态转换为 ID 
					save = 1;
					currentStatus = STATUS_ID;
				}
				else if (c == '"') {                          // 如果是引号 "，当前状态转换为字符串（文件名字符串） 
					save = 1; 
					currentStatus = STATUS_STR;
				} 
				else if (c == ':')                            // 如果是冒号 :，当前状态转换为赋值 
					currentStatus = STATUS_ASSIGN;
				else if (c == '=')                            // 如果是等号 =，当前状态转换为相等 
					currentStatus = STATUS_EQUAL;
				else if (c == '!')                            // 如果是感叹号 !，当前状态转换为不等 
					currentStatus = STATUS_UNEQUAL;
				else if (c == ' ' || c == '\t' || c == '\n'); // 忽略空格、制表符、换行符
				else if (c == '/') {
					if (getChar() == '*') {                   // 如果是注释符 /**，当前状态转换为注释
						if (getChar() == '*') 
							currentStatus = STATUS_COMMENT;
						else {
							currentStatus = STATUS_DONE;
							currentToken = ERROR;
						}
					}
					else {                                    // 识别为除号 
						undo();
						currentStatus = STATUS_DONE;
						currentToken = DIV;
					} 
				}
				else if (c == EOF) {
					currentStatus = STATUS_DONE;
					currentToken = ENDFILE;
				}
				else {                                        // 如果是符号开头 
					currentStatus = STATUS_DONE;
					switch (c) {                              // 判断为对应的符号 
						case EOF: currentToken = ENDFILE; break;
						case '+': currentToken = ADD; break;
						case '-': currentToken = SUB; break;
						case '*': currentToken = MUL; break;
						case '/': currentToken = DIV; break;
						case ',': currentToken = COMMA; break;
						case ';': currentToken = SEMI; break;
						case '(': currentToken = LEFTPAREN; break;
						case ')': currentToken = RIGHTPAREN; break;
						case '>': currentToken = GREATER; break;
						case '<': currentToken = LESS; break;
						case '%': currentToken = MOD; break;
						case '^': currentToken = XOR; break;
						default: currentToken = ERROR; break;
					}
				}
				break;
			case STATUS_ASSIGN:                               // 赋值状态 
				currentStatus = STATUS_DONE;
				if (c == '=') currentToken = ASSIGN;          // 判断为赋值 
				else {
					undo();
					currentToken = ERROR;
				}
				break;
			case STATUS_EQUAL:                                // 相等状态 
				currentStatus = STATUS_DONE;
				if (c == '=') currentToken = EQUAL;           // 判断为相等 
				else {
					undo();
					currentToken = ERROR;
				}
				break;
			case STATUS_UNEQUAL:                              // 不等状态 
				currentStatus = STATUS_DONE;
				if (c == '=') currentToken = UNEQUAL;         // 判断为不等 
				else {
					undo();
					currentToken = ERROR;
				}
				break;
			case STATUS_COMMENT:                              // 注释状态
				if (c == '*') { 
					if (getChar() == '*') {                   // 如果是注释符 **/，即注释结束，当前状态转换为开始 
						if (getChar() == '/') 
							currentStatus = STATUS_START;
						else undo();
					}
					else undo();
				}
				break;
			case STATUS_ID:
				if (!isalpha(c) && !isdigit(c)) {             // ID读取完毕
					if (c != EOF) undo();
					save = 0;
					currentStatus = STATUS_DONE;
					currentToken = ID;                        // 判断为ID 
				}
				break;
			case STATUS_NUMBER:                               // 整数状态 
				if (!isdigit(c)) {
					if (c == '.') currentStatus = STATUS_REAL;
					else {
						undo();
						save = 0;
						currentStatus = STATUS_DONE; 
						if (isalpha(c))                       // 数字后面直接为字母，ERROR 
							currentToken = ERROR;
						else currentToken = NUM;              // 判断为数字 
					}
				}
				break;
			case STATUS_REAL:                                 // 小数状态 
				if (!isdigit(c)) {
					undo();
					save = 0;
					currentStatus = STATUS_DONE;
					if (c == '.' || isalpha(c))               // 小数后面直接为小数点或字母，ERROR 
						currentToken = ERROR;
					else currentToken = NUM;                  // 判断为数字 
				}
				break;
			case STATUS_STR:                                  // 字符串状态 
				if (c == '"') {
					currentStatus = STATUS_DONE;
					currentToken = STR;                       // 判断为字符串 
				}
				break;
			case STATUS_DONE: break;
			default:                                          // ERROR 
				currentStatus = STATUS_DONE;
				currentToken = ERROR;
				break;
		}
		if (save) tokenString[tokenStringIndex++] = c;
		if (currentStatus == STATUS_DONE) {
			if (currentToken == ERROR) lexError();            // ERROR 就报错 
			tokenString[tokenStringIndex] = '\0';
			if (currentToken == ID) currentToken = reservedCheck(tokenString); // 判断是不是关键字 
		}
	}
	if (lex && currentToken != ENDFILE) printToken(currentToken, tokenString); // 输出Token序列 
	return currentToken;
}

void printToken(TokenType token, char* str) {
	switch (token) {
		case IF:                                              // 关键词 
		case ELSE: 
		case WRITE: 
		case READ: 
		case RETURN: 
		case BEGIN: 
		case END:
		case MAIN: 
		case INT:
		case REAL:
		case WHILE:
		case FOR: printf("( KEYWORD, %s )\n", str); break;
		
		case SEMI: printf("( SEP, ; )\n"); break;             // 分隔符 
		case COMMA: printf("( SEP, , )\n"); break;
		case LEFTPAREN: printf("( SEP, ( )\n"); break;
		case RIGHTPAREN: printf("( SEP, ) )\n"); break;
		
		case ADD: printf("( OP, + )\n"); break;               // 运算符 
		case SUB: printf("( OP, - )\n"); break;
		case MUL: printf("( OP, * )\n"); break;
		case DIV: printf("( OP, / )\n"); break;
		case ASSIGN: printf("( OP, := )\n"); break;
		case EQUAL: printf("( OP, == )\n"); break;
		case UNEQUAL: printf("( OP, != )\n"); break;
		case GREATER: printf("( OP, > )\n"); break;
		case LESS: printf("( OP, < )\n"); break;
		case MOD: printf("( OP, %% )\n"); break;
		case XOR: printf("( OP, ^ )\n"); break;
		
		case ID: printf("( ID, %s )\n", str); break;          // ID、NUM、STR 
		case NUM: printf("( NUM, %s )\n", str); break;
		case STR: printf("( STR, %s )\n", str); break;
		
		case ENDFILE: printf("EOF\n"); break;                 // ERROR
		default: printf("Unknown token: %d\n", token);
	}
}

static char getChar() {                                       // 返回下一个读取的字符 
	if (column >= strlen(Buf)) {
		if (fgets(Buf, BUFLEN-1, input)) {                    // 一次读入一行
			row++;
			column = 0;
		}
		else return EOF;
	}
	return Buf[column++];
}

static void undo() {                                          // 回退一个字符位置 
	column--;
}

static TokenType reservedCheck(char* str) {                   // 判断是否是保留字 
	for (int i=0; i<RESERVED_NUM; i++) {
		if (!strcmp(str, reservedWords[i].str))
			return reservedWords[i].token;                    // 返回保留字对应的状态 
	}
	return ID;                                                // 否则判断为 ID 
}

static void lexError() {                                      // 输出词法分析错误信息 
	printf("\n[LEXERROR] line %d, column %d is wrong. Please check it >_<\n", row, column);
	system("pause");
	exit(1);
}

#endif
