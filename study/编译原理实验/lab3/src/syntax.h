#ifndef PARSE_H 
#define PARSE_H

#include "lex.h"

// 语法分析器：构建语法分析树

// 主函数 
struct TreeNode* syntax();

// 新建节点函数
struct TreeNode* NewMethodNode(MethodKind);
struct TreeNode* NewTypeNode(TypeKind);
struct TreeNode* NewParamNode(ParamKind);
struct TreeNode* newStatementNode(StatementKind);
struct TreeNode* newExpressionNode(ExpressionKind);

// 匹配函数
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

// 辅助函数 
void printTree(struct TreeNode*);
char* copyString(char*);
void printSpaces();
static void syntaxError(char*);
static void match(TokenType);

// 函数实现：主函数 
struct TreeNode* syntax() {
	token = getToken();
	struct TreeNode* root = MethodSequence();                 // 程序即函数序列 
	if (token != ENDFILE) syntaxError("Code ends before file");
	return root;
}

// 函数实现：新建节点函数 
struct TreeNode* NewMethodNode(MethodKind kind) {             // 函数节点 
	struct TreeNode* t = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	for (int i = 0; i < 10; i++) {
		t->child[i] = NULL;
		t->next = NULL;
		t->nodekind = MethodK;
		t->kind.method = kind;
	}
	return t;
}

struct TreeNode* NewTypeNode(TypeKind kind) {                 // 类型节点 
	struct TreeNode* t = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	for (int i = 0; i < 10; i++) {
		t->child[i] = NULL;
		t->next = NULL;
		t->nodekind = TypeK;
		t->kind.type = kind;
	}
	return t;
}

struct TreeNode* NewParamNode(ParamKind kind) {               // 参数节点 
	struct TreeNode* t = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	for (int i = 0; i < 10; i++) {
		t->child[i] = NULL;
		t->next = NULL;
		t->nodekind = ParamK;
		t->kind.param = kind;
	}
	return t;
}

struct TreeNode* newStatementNode(StatementKind kind) {       // 声明节点 
	struct TreeNode* t = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	for (int i = 0; i < 10; i++) {
		t->child[i] = NULL;
		t->next = NULL;
		t->nodekind = StatementK;
		t->kind.statement = kind;
	}
	return t;
}

struct TreeNode* newExpressionNode(ExpressionKind kind) {     // 表达式节点 
	struct TreeNode* t = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	for (int i = 0; i < 10; i++) {
		t->child[i] = NULL;
		t->next = NULL;
		t->nodekind = ExpressionK;
		t->kind.expression = kind;
	}
	return t;
}

// 函数实现：匹配函数 
static struct TreeNode* MethodSequence() {                    // 函数节点序列
	struct TreeNode* t = Method();
	struct TreeNode* p = t;
	while (token != ENDFILE) {
		struct TreeNode* q = Method();
		p->next = q;
		p = q;
	}
	return t;
}

static struct TreeNode* Method() {                            // 函数节点
	struct TreeNode* t;
	struct TreeNode* p = ReturnType();
	if (token == MAIN) {
		t = NewMethodNode(MainK);
		match(MAIN);
	}
	else t = NewMethodNode(NormalK);
	t->child[0] = p;                                          // 函数节点第一个子节点为函数返回类型 
	t->attr.name = copyString(tokenString);                   // 函数名
	match(ID); match(LEFTPAREN);
	if (token == RIGHTPAREN) {
		t->child[1] = NULL;                                   // 函数节点第二个子节点为函数形式参数 
		match(RIGHTPAREN);
		t->child[2] = Block();                                // 函数节点第三个子节点为函数代码块 
	}
	else {
		t->child[1] = Params();
		match(RIGHTPAREN);
		t->child[2] = Block();
	}
	return t;	
}

static struct TreeNode* ReturnType() {                        // 返回类型节点 
	struct TreeNode* t = NewTypeNode(ReturnTypeK);
	if (token != INT && token != REAL) syntaxError("Invalid return type");
	t->attr.name = copyString(tokenString);
	match(token);
	return t;
}

static struct TreeNode* Params() {                            // 形式参数节点
	struct TreeNode* t = NewParamNode(FormalK);
	t->child[0] = TypeSequence();                             // 形式参数节点的子节点为参数类型节点序列 
	return t;
}

static struct TreeNode* TypeSequence() {                      // 参数类型节点序列
	struct TreeNode* t;
	switch (token) {
		case INT:
			t = NewTypeNode(IntTypeK); match(INT); break;     // INT 类型节点 
		case REAL:
			t = NewTypeNode(RealTypeK); match(REAL); break;   // REAL 类型节点 
		default:
			syntaxError("Invalid parameter type"); break;
	}
	t->attr.name = copyString(tokenString);
	match(ID);
	struct TreeNode* p = t;
	while (token == COMMA) {                                  // 匹配到逗号，即后面还有参数 
		match(COMMA);
		struct TreeNode* q = TypeSequence();
		p->next = q;
		p = q;
	}
	return t;
}

static struct TreeNode* StatementSequence() {                 // 声明节点序列
	struct TreeNode* t = Statement();
	struct TreeNode* p = t;
	while (token != ENDFILE && token != END) {
		struct TreeNode* q = Statement();
		p->next = q;
		p = q;
	}
	return t;
}

static struct TreeNode* Statement() {                         // 声明节点 
	struct TreeNode* t;
	switch (token) {                                          // 各种声明
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

static struct TreeNode* Block() {                             // 代码块节点 
	match(BEGIN);
	struct TreeNode* t = StatementSequence();                 // 代码块节点的子节点为声明节点序列 
	match(END);
	return t;
}

static struct TreeNode* IntVarStatement() {                   // INT 变量节点 
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

static struct TreeNode* RealVarStatement() {                  // REAL 变量节点 
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

static struct TreeNode* AssignStatement() {                   // 赋值节点 
	struct TreeNode* t = newStatementNode(AssignK);
	if (token == ID) t->attr.name = copyString(tokenString);
	match(ID);                                                // ID := 表达式 ;
	match(ASSIGN);
	t->child[0] = Expression();
	return t;
}

static struct TreeNode* ReturnStatement() {                   // RETURN 节点 
	struct TreeNode* t = newStatementNode(ReturnK);
	match(RETURN);                                            // RETURN 表达式 ; 
	t->child[0] = Expression();
	match(SEMI);
	return t;
}

static struct TreeNode* IfStatement() {                       // IF 节点 
	struct TreeNode* t = newStatementNode(IfK);
	match(IF);                                                // IF ( 判断式 ) 声明 ( else 声明 )
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

static struct TreeNode* WriteStatement() {                    // WRITE 节点 
	struct TreeNode* t = newStatementNode(WriteK);
	match(WRITE);                                             // WRITE ( 表达式 , STR ) ; 
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

static struct TreeNode* ReadStatement() {                     // READ 节点 
	struct TreeNode* t = newStatementNode(ReadK);
	match(READ);                                              // READ ( 表达式 , STR ) ; 
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

static struct TreeNode* WhileStatement() {                    // WHILE 节点 
	struct TreeNode* t = newStatementNode(WhileK);
	match(WHILE);                                             // WHILE ( 判断式 ) 声明 else 声明
	match(LEFTPAREN);
	t->child[0] = BoolExpression();
	match(RIGHTPAREN);
	t->child[1] = Statement();
	return t;
}

static struct TreeNode* ForStatement() {                      // FOR 节点 
	struct TreeNode* t = newStatementNode(ForK);
	match(FOR);                                               // FOR ( 赋值 ; 判断式 ; 赋值 ) 声明
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

static struct TreeNode* Expression() {                        // 表达式节点
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

static struct TreeNode* AdditiveExpression() {                // 表达式（只含 +,-）节点
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

static struct TreeNode* MultiplicativeExpression() {          // 表达式（只含 *,/,%）节点
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

static struct TreeNode* PrimaryExpression() {                 // 运算数节点 
	char* temp;
	struct TreeNode* t;
	switch (token) {                                          // 可以匹配数值、变量、括号括住的表达式、函数（的返回值） 
		case NUM:                                             // 数值 
			t = newExpressionNode(ConstK);
			t->attr.val = atof(tokenString);
			match(NUM);
			break;
		case ID:
			temp = copyString(tokenString);
			match(ID);
			if (token == LEFTPAREN) {                         // 函数（的返回值） 
				t = newExpressionNode(MethodCallK);
				t->attr.name = copyString(temp);
				match(LEFTPAREN);
				t->child[0] = ActualParams();
				match(RIGHTPAREN);
			}
			else {                                            // 变量 
				t = newExpressionNode(IdK);
				t->attr.name = copyString(temp);
			}
			break;
		case LEFTPAREN:                                       // 括号括住的表达式 
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

static struct TreeNode * BoolExpression() {                   // 判断式节点 
	struct TreeNode* t = Expression();
	if (token == EQUAL || token == UNEQUAL || token == GREATER || token == LESS) {  // 表达式 == (or != or > or <) 表达式 
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

static struct TreeNode * ActualParams() {                     // 实际参数列表节点 
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

void printTree(struct TreeNode* root) {                       // 输出语法树 
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
