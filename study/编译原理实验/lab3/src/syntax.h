#ifndef PARSE_H 
#define PARSE_H

#include "lex.h"

// �﷨�������������﷨������

// ������ 
struct TreeNode* syntax();

// �½��ڵ㺯��
struct TreeNode* NewMethodNode(MethodKind);
struct TreeNode* NewTypeNode(TypeKind);
struct TreeNode* NewParamNode(ParamKind);
struct TreeNode* newStatementNode(StatementKind);
struct TreeNode* newExpressionNode(ExpressionKind);

// ƥ�亯��
static struct TreeNode* MethodSequence();
static struct TreeNode* Method();
static struct TreeNode* ReturnType();
static struct TreeNode* TypeSequence();
static struct TreeNode* Params();
static struct TreeNode* Block();
static struct TreeNode* StatementSequence();
static struct TreeNode* Statement();
static struct TreeNode* IntVarStatement();
static struct TreeNode* RealVarStatement();
static struct TreeNode* AssignStatement();
static struct TreeNode* ReturnStatement();
static struct TreeNode* IfStatement();
static struct TreeNode* WriteStatement();
static struct TreeNode* ReadStatement();
static struct TreeNode* WhileStatement();
static struct TreeNode* ForStatement();
static struct TreeNode* Expression();
static struct TreeNode* AdditiveExpression();
static struct TreeNode* MultiplicativeExpression();
static struct TreeNode* PrimaryExpression();
static struct TreeNode* BoolExpression();
static struct TreeNode* ActualParams();

// �������� 
void printTree(struct TreeNode*);
char* copyString(char*);
void printSpaces();
static void syntaxError(char*);
static void match(TokenType);

// ����ʵ�֣������� 
struct TreeNode* syntax() {
	token = getToken();
	struct TreeNode* root = MethodSequence();                 // ���򼴺������� 
	if (token != ENDFILE) syntaxError("Code ends before file");
	return root;
}

// ����ʵ�֣��½��ڵ㺯�� 
struct TreeNode* NewMethodNode(MethodKind kind) {             // �����ڵ� 
	struct TreeNode* t = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	for (int i = 0; i < 10; i++) {
		t->child[i] = NULL;
		t->next = NULL;
		t->nodekind = MethodK;
		t->kind.method = kind;
	}
	return t;
}

struct TreeNode* NewTypeNode(TypeKind kind) {                 // ���ͽڵ� 
	struct TreeNode* t = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	for (int i = 0; i < 10; i++) {
		t->child[i] = NULL;
		t->next = NULL;
		t->nodekind = TypeK;
		t->kind.type = kind;
	}
	return t;
}

struct TreeNode* NewParamNode(ParamKind kind) {               // �����ڵ� 
	struct TreeNode* t = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	for (int i = 0; i < 10; i++) {
		t->child[i] = NULL;
		t->next = NULL;
		t->nodekind = ParamK;
		t->kind.param = kind;
	}
	return t;
}

struct TreeNode* newStatementNode(StatementKind kind) {       // �����ڵ� 
	struct TreeNode* t = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	for (int i = 0; i < 10; i++) {
		t->child[i] = NULL;
		t->next = NULL;
		t->nodekind = StatementK;
		t->kind.statement = kind;
	}
	return t;
}

struct TreeNode* newExpressionNode(ExpressionKind kind) {     // ���ʽ�ڵ� 
	struct TreeNode* t = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	for (int i = 0; i < 10; i++) {
		t->child[i] = NULL;
		t->next = NULL;
		t->nodekind = ExpressionK;
		t->kind.expression = kind;
	}
	return t;
}

// ����ʵ�֣�ƥ�亯�� 
static struct TreeNode* MethodSequence() {                    // �����ڵ�����
	struct TreeNode* t = Method();
	struct TreeNode* p = t;
	while (token != ENDFILE) {
		struct TreeNode* q = Method();
		p->next = q;
		p = q;
	}
	return t;
}

static struct TreeNode* Method() {                            // �����ڵ�
	struct TreeNode* t;
	struct TreeNode* p = ReturnType();
	if (token == MAIN) {
		t = NewMethodNode(MainK);
		match(MAIN);
	}
	else t = NewMethodNode(NormalK);
	t->child[0] = p;                                          // �����ڵ��һ���ӽڵ�Ϊ������������ 
	t->attr.name = copyString(tokenString);                   // ������
	match(ID); match(LEFTPAREN);
	if (token == RIGHTPAREN) {
		t->child[1] = NULL;                                   // �����ڵ�ڶ����ӽڵ�Ϊ������ʽ���� 
		match(RIGHTPAREN);
		t->child[2] = Block();                                // �����ڵ�������ӽڵ�Ϊ��������� 
	}
	else {
		t->child[1] = Params();
		match(RIGHTPAREN);
		t->child[2] = Block();
	}
	return t;	
}

static struct TreeNode* ReturnType() {                        // �������ͽڵ� 
	struct TreeNode* t = NewTypeNode(ReturnTypeK);
	if (token != INT && token != REAL) syntaxError("Invalid return type");
	t->attr.name = copyString(tokenString);
	match(token);
	return t;
}

static struct TreeNode* Params() {                            // ��ʽ�����ڵ�
	struct TreeNode* t = NewParamNode(FormalK);
	t->child[0] = TypeSequence();                             // ��ʽ�����ڵ���ӽڵ�Ϊ�������ͽڵ����� 
	return t;
}

static struct TreeNode* TypeSequence() {                      // �������ͽڵ�����
	struct TreeNode* t;
	switch (token) {
		case INT:
			t = NewTypeNode(IntTypeK); match(INT); break;     // INT ���ͽڵ� 
		case REAL:
			t = NewTypeNode(RealTypeK); match(REAL); break;   // REAL ���ͽڵ� 
		default:
			syntaxError("Invalid parameter type"); break;
	}
	t->attr.name = copyString(tokenString);
	match(ID);
	struct TreeNode* p = t;
	while (token == COMMA) {                                  // ƥ�䵽���ţ������滹�в��� 
		match(COMMA);
		struct TreeNode* q = TypeSequence();
		p->next = q;
		p = q;
	}
	return t;
}

static struct TreeNode* StatementSequence() {                 // �����ڵ�����
	struct TreeNode* t = Statement();
	struct TreeNode* p = t;
	while (token != ENDFILE && token != END) {
		struct TreeNode* q = Statement();
		p->next = q;
		p = q;
	}
	return t;
}

static struct TreeNode* Statement() {                         // �����ڵ� 
	struct TreeNode* t;
	switch (token) {                                          // ��������
		case BEGIN: t = Block(); break;
		case INT: t = IntVarStatement(); break;
		case REAL: t = RealVarStatement(); break;
		case ID: t = AssignStatement(); match(SEMI); break;
		case RETURN: t = ReturnStatement(); break;
		case IF: t = IfStatement(); break;
		case WRITE: t = WriteStatement(); break;
		case READ: t = ReadStatement(); break;
		case WHILE: t = WhileStatement(); break;
		case FOR: t = ForStatement(); break;
		default: syntaxError("Unexpected token"); break;
	}
	return t;
}

static struct TreeNode* Block() {                             // �����ڵ� 
	match(BEGIN);
	struct TreeNode* t = StatementSequence();                 // �����ڵ���ӽڵ�Ϊ�����ڵ����� 
	match(END);
	return t;
}

static struct TreeNode* IntVarStatement() {                   // INT �����ڵ� 
	struct TreeNode* t = newStatementNode(IntDeclareK);
	match(INT);                                               // INT ID ; 
	t->attr.name = copyString(tokenString);
	match(ID);
	if (token == ASSIGN) {
		match(ASSIGN);
		match(NUM);
	}
	match(SEMI);
	return t;
}

static struct TreeNode* RealVarStatement() {                  // REAL �����ڵ� 
	struct TreeNode* t = newStatementNode(RealDeclareK);
	match(REAL);                                              // REAL ID ; 
	t->attr.name = copyString(tokenString);
	match(ID);
	if (token == ASSIGN) {
		match(ASSIGN);
		match(NUM);
	}
	match(SEMI);
	return t;
}

static struct TreeNode* AssignStatement() {                   // ��ֵ�ڵ� 
	struct TreeNode* t = newStatementNode(AssignK);
	if (token == ID) t->attr.name = copyString(tokenString);
	match(ID);                                                // ID := ���ʽ ;
	match(ASSIGN);
	t->child[0] = Expression();
	return t;
}

static struct TreeNode* ReturnStatement() {                   // RETURN �ڵ� 
	struct TreeNode* t = newStatementNode(ReturnK);
	match(RETURN);                                            // RETURN ���ʽ ; 
	t->child[0] = Expression();
	match(SEMI);
	return t;
}

static struct TreeNode* IfStatement() {                       // IF �ڵ� 
	struct TreeNode* t = newStatementNode(IfK);
	match(IF);                                                // IF ( �ж�ʽ ) ���� ( else ���� )
	match(LEFTPAREN);
	t->child[0] = BoolExpression();
	match(RIGHTPAREN);
	t->child[1] = Statement();
	if (token == ELSE) {
		match(ELSE);
		t->child[2] = Statement();
	}
	return t;
}

static struct TreeNode* WriteStatement() {                    // WRITE �ڵ� 
	struct TreeNode* t = newStatementNode(WriteK);
	match(WRITE);                                             // WRITE ( ���ʽ , STR ) ; 
	match(LEFTPAREN);
	t->child[0] = Expression();
	match(COMMA);
	if (token != STR) syntaxError("Invalid write path");
	t->attr.name = copyString(tokenString);
	match(STR);
	match(RIGHTPAREN);
	match(SEMI);
	return t;
}

static struct TreeNode* ReadStatement() {                     // READ �ڵ� 
	struct TreeNode* t = newStatementNode(ReadK);
	match(READ);                                              // READ ( ���ʽ , STR ) ; 
	match(LEFTPAREN);
	if (token == ID) t->child[0] = PrimaryExpression();
	match(COMMA);
	if (token != STR) syntaxError("Invalid read path");
	t->attr.name = copyString(tokenString);
	match(STR);
	match(RIGHTPAREN);
	match(SEMI);
	return t;
}

static struct TreeNode* WhileStatement() {                    // WHILE �ڵ� 
	struct TreeNode* t = newStatementNode(WhileK);
	match(WHILE);                                             // WHILE ( �ж�ʽ ) ���� else ����
	match(LEFTPAREN);
	t->child[0] = BoolExpression();
	match(RIGHTPAREN);
	t->child[1] = Statement();
	return t;
}

static struct TreeNode* ForStatement() {                      // FOR �ڵ� 
	struct TreeNode* t = newStatementNode(ForK);
	match(FOR);                                               // FOR ( ��ֵ ; �ж�ʽ ; ��ֵ ) ����
	match(LEFTPAREN);
	t->child[0] = AssignStatement();
	match(SEMI);
	t->child[1] = BoolExpression();
	match(SEMI);
	t->child[2] = AssignStatement();
	match(RIGHTPAREN);
	t->child[3] = Statement();
	return t;
}

static struct TreeNode* Expression() {                        // ���ʽ�ڵ�
	struct TreeNode* t = AdditiveExpression();
	while (token == XOR) {
		struct TreeNode *p = newExpressionNode(OpK);
		p->child[0] = t;
		p->attr.token = token;
		t = p;
		match(token);
		t->child[1] = AdditiveExpression();
	}
	return t;
}

static struct TreeNode* AdditiveExpression() {                // ���ʽ��ֻ�� +,-���ڵ�
	struct TreeNode* t = MultiplicativeExpression();
	while (token == ADD || token == SUB) {
		struct TreeNode *p = newExpressionNode(OpK);
		p->child[0] = t;
		p->attr.token = token;
		t = p;
		match(token);
		t->child[1] = MultiplicativeExpression();
	}
	return t;
}

static struct TreeNode* MultiplicativeExpression() {          // ���ʽ��ֻ�� *,/,%���ڵ�
	struct TreeNode* t = PrimaryExpression();
	while (token == MUL || token == DIV || token == MOD) {
		struct TreeNode *p = newExpressionNode(OpK);
		p->child[0] = t;
		p->attr.token = token;
		t = p;
		match(token);
		t->child[1] = PrimaryExpression();
	}
	return t;
}

static struct TreeNode* PrimaryExpression() {                 // �������ڵ� 
	char* temp;
	struct TreeNode* t;
	switch (token) {                                          // ����ƥ����ֵ��������������ס�ı��ʽ���������ķ���ֵ�� 
		case NUM:                                             // ��ֵ 
			t = newExpressionNode(ConstK);
			t->attr.val = atof(tokenString);
			match(NUM);
			break;
		case ID:
			temp = copyString(tokenString);
			match(ID);
			if (token == LEFTPAREN) {                         // �������ķ���ֵ�� 
				t = newExpressionNode(MethodCallK);
				t->attr.name = copyString(temp);
				match(LEFTPAREN);
				t->child[0] = ActualParams();
				match(RIGHTPAREN);
			}
			else {                                            // ���� 
				t = newExpressionNode(IdK);
				t->attr.name = copyString(temp);
			}
			break;
		case LEFTPAREN:                                       // ������ס�ı��ʽ 
			match(LEFTPAREN);
			t = Expression();
			match(RIGHTPAREN);
			break;
		default:
			syntaxError("Unexpected token");
			break;
	}
	return t;
}

static struct TreeNode * BoolExpression() {                   // �ж�ʽ�ڵ� 
	struct TreeNode* t = Expression();
	if (token == EQUAL || token == UNEQUAL || token == GREATER || token == LESS) {  // ���ʽ == (or != or > or <) ���ʽ 
		struct TreeNode * p = newExpressionNode(OpK);
		p->child[0] = t;
		p->attr.token = token;
		t = p;
		match(token);
		t->child[1] = Expression();
	}
	else syntaxError("Unexpected token");
	return t;
}

static struct TreeNode * ActualParams() {                     // ʵ�ʲ����б�ڵ� 
	struct TreeNode* t = NewParamNode(ActualK);
	struct TreeNode* e = Expression();
	t->child[0] = e;
	struct TreeNode* p = e;
	while (token == COMMA) {
		match(COMMA);
		struct TreeNode* q = Expression();
		p->next = q;
		p = q; 
	}
	return t;
}

void printTree(struct TreeNode* root) {                       // ����﷨�� 
	deep++;
	while (root != NULL) {
		printSpaces();
		if (root->nodekind == MethodK) {
			switch (root->kind.method) {
				case MainK:
					printf("Main Method: %s\n", root->attr.name); break;
				case NormalK:
					printf("Method: %s\n", root->attr.name); break;
				default:  
					break;
			}
		}
		else if (root->nodekind == TypeK) {
			switch (root->kind.type) {
				case ReturnTypeK:
					printf("Return Type: %s\n", root->attr.name); break;
				case IntTypeK: 
					printf("INT: %s\n", root->attr.name); break;
				case RealTypeK:
					printf("REAL: %s\n", root->attr.name); break;
				default:
					printf("Unknown TypeNode kind\n"); break;
			}
		}
		else if (root->nodekind == ParamK) {
			switch (root->kind.param) {
				case FormalK:
				case ActualK:
					printf("PARAM:\n"); break;
				default:
					printf("Unknown ParamNode kind\n"); break;
			}
		}
		else if (root->nodekind == StatementK) {
			switch (root->kind.statement) {
				case IfK:
					printf("IF\n"); break;
				case ReturnK:
					printf("RETURN\n"); break;
				case AssignK:
					printf("ASSIGN: %s\n", root->attr.name); break;
				case ReadK:
					printf("READ %s to:\n", root->attr.name); break;
				case WriteK:
					printf("WRITE %s from:\n", root->attr.name); break;
				case WhileK:
					printf("WHILE\n"); break;
				case ForK:
					printf("FOR\n"); break;
				case IntDeclareK:
					printf("DECLARE: INT %s\n", root->attr.name); break;
				case RealDeclareK:
					printf("DECLARE: REAL %s\n", root->attr.name); break;
				default:
					printf("Unknown StatementNode kind\n"); break;
			}
		}
		else if (root->nodekind == ExpressionK) {
			switch (root->kind.expression) {
				case OpK:
					printf("OPERATOR: "); 
					switch (root->attr.token) {
						case ADD: printf("+\n"); break;
						case SUB: printf("-\n"); break;
						case MUL: printf("*\n"); break;
						case DIV: printf("/\n"); break;
						case MOD: printf("%%\n"); break;
						case XOR: printf("^\n"); break;
						case EQUAL: printf("==\n"); break;
						case UNEQUAL: printf("!=\n"); break;
						case GREATER: printf(">\n"); break;
						case LESS: printf("<\n"); break;
					}
					break;
				case ConstK:
					printf("CONST: %f\n", root->attr.val); break;
				case IdK:
					printf("ID: %s\n", root->attr.name); break;
				case MethodCallK:
					printf("FUNC: %s\n", root->attr.name); break;
				default:
					printf("Unknown ExpressionNode kind\n"); break;
			}
		}
		else printf("Unknown node kind\n");
		for (int i = 0; i < 10; i++) printTree(root->child[i]);
		root = root->next;
	}
	deep--;
}

char* copyString(char* str) {
	char* res = (char*)malloc(strlen(str)+1);
	strcpy(res, str);
	return res;
}

void printSpaces() {
	for (int i=0; i<deep; i++) printf("   ");
}

static void syntaxError(char* errMessage) {
	printf("\n[SYNTAXERROR] line %d, column %d is wrong: %s. Please check it >_<\n", row, column, errMessage);
	system("pause");
	exit(1);
}

static void match(TokenType expected) {
	if (token == expected) token = getToken();
	else syntaxError("Unexpected token");
}

#endif 
