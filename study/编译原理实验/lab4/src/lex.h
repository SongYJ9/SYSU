#ifndef LEX_H 
#define LEX_H

#include "util.h"

// �ʷ����������õ�token����

// ������ 
TokenType getToken();  

// �������� 
static char getChar();
static void undo();
static TokenType reservedCheck(char*);
static void lexError();
void printToken(TokenType, char*);

// ����ʵ��
TokenType getToken() {
	int tokenStringIndex = 0;                                 // ��¼�ַ�λ��
	TokenType currentToken;                                   // ��¼��ǰ�����õ��� token
	lexStatus currentStatus = STATUS_START;                   // ��¼��ǰ״̬����ʼΪ��ʼ״̬ 
	int save = 0;                                             // ��¼��ǰ�ַ��Ƿ���Ҫ��������
	
	while (currentStatus != STATUS_DONE) {
		char c = getChar();                                   // �����һ���ַ�
		switch (currentStatus) {                              // ״̬ת��
			case STATUS_START:                                // ��ʼ״̬ 
				if (isdigit(c)) {                             // ��������֣���ǰ״̬ת��Ϊ���� 
					save = 1;
					currentStatus = STATUS_NUMBER;
				}
				else if (isalpha(c)) {                        // ������ַ�����ǰ״̬ת��Ϊ ID 
					save = 1;
					currentStatus = STATUS_ID;
				}
				else if (c == '"') {                          // ��������� "����ǰ״̬ת��Ϊ�ַ������ļ����ַ����� 
					save = 1; 
					currentStatus = STATUS_STR;
				} 
				else if (c == ':')                            // �����ð�� :����ǰ״̬ת��Ϊ��ֵ 
					currentStatus = STATUS_ASSIGN;
				else if (c == '=')                            // ����ǵȺ� =����ǰ״̬ת��Ϊ��� 
					currentStatus = STATUS_EQUAL;
				else if (c == '!')                            // ����Ǹ�̾�� !����ǰ״̬ת��Ϊ���� 
					currentStatus = STATUS_UNEQUAL;
				else if (c == ' ' || c == '\t' || c == '\n'); // ���Կո��Ʊ�������з�
				else if (c == '/') {
					if (getChar() == '*') {                   // �����ע�ͷ� /**����ǰ״̬ת��Ϊע��
						if (getChar() == '*') 
							currentStatus = STATUS_COMMENT;
						else {
							currentStatus = STATUS_DONE;
							currentToken = ERROR;
						}
					}
					else {                                    // ʶ��Ϊ���� 
						undo();
						currentStatus = STATUS_DONE;
						currentToken = DIV;
					} 
				}
				else if (c == EOF) {
					currentStatus = STATUS_DONE;
					currentToken = ENDFILE;
				}
				else {                                        // ����Ƿ��ſ�ͷ 
					currentStatus = STATUS_DONE;
					switch (c) {                              // �ж�Ϊ��Ӧ�ķ��� 
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
			case STATUS_ASSIGN:                               // ��ֵ״̬ 
				currentStatus = STATUS_DONE;
				if (c == '=') currentToken = ASSIGN;          // �ж�Ϊ��ֵ 
				else {
					undo();
					currentToken = ERROR;
				}
				break;
			case STATUS_EQUAL:                                // ���״̬ 
				currentStatus = STATUS_DONE;
				if (c == '=') currentToken = EQUAL;           // �ж�Ϊ��� 
				else {
					undo();
					currentToken = ERROR;
				}
				break;
			case STATUS_UNEQUAL:                              // ����״̬ 
				currentStatus = STATUS_DONE;
				if (c == '=') currentToken = UNEQUAL;         // �ж�Ϊ���� 
				else {
					undo();
					currentToken = ERROR;
				}
				break;
			case STATUS_COMMENT:                              // ע��״̬
				if (c == '*') { 
					if (getChar() == '*') {                   // �����ע�ͷ� **/����ע�ͽ�������ǰ״̬ת��Ϊ��ʼ 
						if (getChar() == '/') 
							currentStatus = STATUS_START;
						else undo();
					}
					else undo();
				}
				break;
			case STATUS_ID:
				if (!isalpha(c) && !isdigit(c)) {             // ID��ȡ���
					if (c != EOF) undo();
					save = 0;
					currentStatus = STATUS_DONE;
					currentToken = ID;                        // �ж�ΪID 
				}
				break;
			case STATUS_NUMBER:                               // ����״̬ 
				if (!isdigit(c)) {
					if (c == '.') currentStatus = STATUS_REAL;
					else {
						undo();
						save = 0;
						currentStatus = STATUS_DONE; 
						if (isalpha(c))                       // ���ֺ���ֱ��Ϊ��ĸ��ERROR 
							currentToken = ERROR;
						else currentToken = NUM;              // �ж�Ϊ���� 
					}
				}
				break;
			case STATUS_REAL:                                 // С��״̬ 
				if (!isdigit(c)) {
					undo();
					save = 0;
					currentStatus = STATUS_DONE;
					if (c == '.' || isalpha(c))               // С������ֱ��ΪС�������ĸ��ERROR 
						currentToken = ERROR;
					else currentToken = NUM;                  // �ж�Ϊ���� 
				}
				break;
			case STATUS_STR:                                  // �ַ���״̬ 
				if (c == '"') {
					currentStatus = STATUS_DONE;
					currentToken = STR;                       // �ж�Ϊ�ַ��� 
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
			if (currentToken == ERROR) lexError();            // ERROR �ͱ��� 
			tokenString[tokenStringIndex] = '\0';
			if (currentToken == ID) currentToken = reservedCheck(tokenString); // �ж��ǲ��ǹؼ��� 
		}
	}
	if (lex && currentToken != ENDFILE) printToken(currentToken, tokenString); // ���Token���� 
	return currentToken;
}

void printToken(TokenType token, char* str) {
	switch (token) {
		case IF:                                              // �ؼ��� 
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
		
		case SEMI: printf("( SEP, ; )\n"); break;             // �ָ��� 
		case COMMA: printf("( SEP, , )\n"); break;
		case LEFTPAREN: printf("( SEP, ( )\n"); break;
		case RIGHTPAREN: printf("( SEP, ) )\n"); break;
		
		case ADD: printf("( OP, + )\n"); break;               // ����� 
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
		
		case ID: printf("( ID, %s )\n", str); break;          // ID��NUM��STR 
		case NUM: printf("( NUM, %s )\n", str); break;
		case STR: printf("( STR, %s )\n", str); break;
		
		case ENDFILE: printf("EOF\n"); break;                 // ERROR
		default: printf("Unknown token: %d\n", token);
	}
}

static char getChar() {                                       // ������һ����ȡ���ַ� 
	if (column >= strlen(Buf)) {
		if (fgets(Buf, BUFLEN-1, input)) {                    // һ�ζ���һ��
			row++;
			column = 0;
		}
		else return EOF;
	}
	return Buf[column++];
}

static void undo() {                                          // ����һ���ַ�λ�� 
	column--;
}

static TokenType reservedCheck(char* str) {                   // �ж��Ƿ��Ǳ����� 
	for (int i=0; i<RESERVED_NUM; i++) {
		if (!strcmp(str, reservedWords[i].str))
			return reservedWords[i].token;                    // ���ر����ֶ�Ӧ��״̬ 
	}
	return ID;                                                // �����ж�Ϊ ID 
}

static void lexError() {                                      // ����ʷ�����������Ϣ 
	printf("\n[LEXERROR] line %d, column %d is wrong. Please check it >_<\n", row, column);
	system("pause");
	exit(1);
}

#endif
