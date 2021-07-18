#ifndef SYMBOLTABLE_H 
#define SYMBOLTABLE_H 

#include "syntax.h"

void printSpecifiedSpaces(int n) {                                   // 输出空格
	for (int i=0; i<n; i++) printf("   ");
}

void printSymbolTable(struct TreeNode* root) {                       // 输出符号表 
	deep++;
	while (root != NULL) {
		if (root->nodekind == MethodK) {
			switch (root->kind.method) {
				case MainK:
		            printSpaces();
					printf("Main Method Symbol: %s\n", root->attr.name);
                    break;
				case NormalK:
		            printSpaces();
					printf("Method Symbol: %s\n", root->attr.name); 
                    break;
			}
		}
		else if (root->nodekind == TypeK) {
			switch (root->kind.type) {
				case IntTypeK: 
		            printSpecifiedSpaces(deep-1);
					printf("Param INT Symbol: %s\n", root->attr.name);
                    break;
				case RealTypeK:
		            printSpecifiedSpaces(deep-1);
					printf("Param REAL Symbol: %s\n", root->attr.name);
                    break;
			}
		}
		else if (root->nodekind == StatementK) {
			switch (root->kind.statement) {
				case IntDeclareK:
		            printSpaces();
					printf("Declare INT Symbol: %s\n", root->attr.name);
                    break;
				case RealDeclareK:
		            printSpaces();
					printf("Declare REAL Symbol: %s\n", root->attr.name);
                    break;
			}
		}
		for (int i = 0; i < 10; i++) printSymbolTable(root->child[i]);
		root = root->next;
	}
	deep--;
}

char symbolVector[100][100], funcVector[100][100];
int symLen = 0, funcLen = 0;
int judge = 1, c = 0;

void checkSymbol(struct TreeNode* root) {                            // 检查变量名和函数名问题 
	deep++;
	while (root != NULL) {
		if (root->nodekind == MethodK) {
			switch (root->kind.method) {
				case MainK:
				case NormalK:
                    c = 1;
                    for (int i = 1; i <= symLen; i++)
                        if (strcmp(symbolVector[i], root->attr.name) == 0) c = 0;
                    if (c == 0) judge = -1; // ID repeat declare error
                    strcpy(funcVector[++funcLen], root->attr.name);
					break;
			}
		}
		else if (root->nodekind == TypeK) {
			switch (root->kind.type) {
				case IntTypeK: 
				case RealTypeK:
                    c = 1;
                    for (int i = 1; i <= symLen; i++)
                        if (strcmp(symbolVector[i], root->attr.name) == 0) c = 0;
                    if (c == 0) judge = -1; // ID repeat declare error
                    strcpy(symbolVector[++symLen], root->attr.name);
					break;
			}
		}
		else if (root->nodekind == StatementK) {
			switch (root->kind.statement) {
				case IntDeclareK:
				case RealDeclareK:
                    c = 1;
                    for (int i = 1; i <= symLen; i++)
                        if (strcmp(symbolVector[i], root->attr.name) == 0) c = 0;
                    if (c == 0) judge = -1; // ID repeat declare error
                    strcpy(symbolVector[++symLen], root->attr.name);
					break;
				case AssignK:
                    c = 0;
                    for (int i = 1; i <= symLen; i++)
                        if (strcmp(symbolVector[i], root->attr.name) == 0) c = 1;
                    if (c == 0) judge = -2; // ID call error
                    break;
			}
		}
		else if (root->nodekind == ExpressionK) {
			switch (root->kind.expression) {
				case IdK:
                    c = 0;
                    for (int i = 1; i <= symLen; i++)
                        if (strcmp(symbolVector[i], root->attr.name) == 0) c = 1;
                    if (c == 0) judge = -2; // ID call error
                    break;
				case MethodCallK:
                    c = 0;
                    for (int i = 1; i <= funcLen; i++)
                        if (strcmp(funcVector[i], root->attr.name) == 0) c = 1;
                    if (c == 0) judge = -3; // func call error
                    break;
			}
		}
		for (int i = 0; i < 10; i++) checkSymbol(root->child[i]);
		root = root->next;
        if (deep == 1) symLen = 0;
	}
	deep--;
}

char symbolTypeVector[100][100];
int symbolType[100], symTypeLen = 0;

int getType(struct TreeNode* root) {                                // 获取type
    if (root->kind.statement == AssignK) {
        for (int i = 1; i <= symTypeLen; i++) {
            if (strcmp(symbolTypeVector[i], root->attr.name) == 0) return symbolType[i];
        }
        return 0;
    }
    if (root->kind.expression == ConstK) return 0;
    else if (root->kind.expression == OpK) {
        if (getType(root->child[0]) && getType(root->child[1]) && 
            getType(root->child[0]) != getType(root->child[1])) return -1;
        else return getType(root->child[0]);
    }
    else {
        for (int i = 1; i <= symTypeLen; i++) {
            if (strcmp(symbolTypeVector[i], root->attr.name) == 0) return symbolType[i];
        }
        return 0;
    }
}

void checkType(struct TreeNode* root) {                                // 检查类型匹配问题 
    deep++;
	while (root != NULL) {
        if (root->nodekind == ExpressionK) {
			switch (root->kind.expression) {
				case OpK:
                    if (getType(root->child[0]) && getType(root->child[1]) && 
                        getType(root->child[0]) != getType(root->child[1])) judge = -1;
					break;
			}
		}
		else if (root->nodekind == TypeK) {
			switch (root->kind.type) {
				case IntTypeK:
                    strcpy(symbolTypeVector[++symTypeLen], root->attr.name);
                    symbolType[symTypeLen] = 1;
					break;
				case RealTypeK:
                    strcpy(symbolTypeVector[++symTypeLen], root->attr.name);
                    symbolType[symTypeLen] = 2;
					break;
			}
		}
		else if (root->nodekind == StatementK) {
			switch (root->kind.statement) {
				case AssignK:
                    if (root->child[0] != NULL) {
                        if (root->child[0]->kind.expression == IdK && getType(root) && getType(root->child[0]) && 
                                    getType(root) != getType(root->child[0])) judge = -1;
                    }
                    break;
				case IntDeclareK:
                    strcpy(symbolTypeVector[++symTypeLen], root->attr.name);
                    symbolType[symTypeLen] = 1;
					break;
				case RealDeclareK:
                    strcpy(symbolTypeVector[++symTypeLen], root->attr.name);
                    symbolType[symTypeLen] = 2;
					break;
			}
		}
		for (int i = 0; i < 10; i++) checkType(root->child[i]);
		root = root->next;
        if (deep == 1) symTypeLen = 0;
	}
	deep--;
}

int labelCnt = 0, tempCnt = 0;

char* cal(struct TreeNode* root) {                                 // 自底向上计算表达式
    char* t = (char*)malloc(50 * sizeof(char)), *t0, *t1;
    struct TreeNode* p;
    switch (root->kind.expression) {
        case OpK:
            t0 = cal(root->child[0]);
            t1 = cal(root->child[1]);
            switch (root->attr.token) {
                case ADD: 
                    printf("   t%d := %s + %s\n", ++tempCnt, t0, t1);
                    sprintf(t, "t%d", tempCnt);
                    return t;
                case SUB: 
                    printf("   t%d := %s - %s\n", ++tempCnt, t0, t1);
                    sprintf(t, "t%d", tempCnt);
                    return t;
                case MUL: 
                    printf("   t%d := %s * %s\n", ++tempCnt, t0, t1);
                    sprintf(t, "t%d", tempCnt);
                    return t;
                case DIV: 
                    printf("   t%d := %s / %s\n", ++tempCnt, t0, t1);
                    sprintf(t, "t%d", tempCnt);
                    return t;
                case MOD: 
                    printf("   t%d := %s %% %s\n", ++tempCnt, t0, t1);
                    sprintf(t, "t%d", tempCnt);
                    return t;
                case XOR: 
                    printf("   t%d := %s ^ %s\n", ++tempCnt, t0, t1);
                    sprintf(t, "t%d", tempCnt);
                    return t;
                case EQUAL: 
                    printf("   t%d := %s == %s\n", ++tempCnt, t0, t1);
                    sprintf(t, "t%d", tempCnt);
                    return t;
                case UNEQUAL: 
                    printf("   t%d := %s != %s\n", ++tempCnt, t0, t1);
                    sprintf(t, "t%d", tempCnt);
                    return t;
                case GREATER: 
                    printf("   t%d := %s > %s\n", ++tempCnt, t0, t1);
                    sprintf(t, "t%d", tempCnt);
                    return t;
                case LESS: 
                    printf("   t%d := %s < %s\n", ++tempCnt, t0, t1);
                    sprintf(t, "t%d", tempCnt);
                    return t;
            }
            break;
        case ConstK:
            sprintf(t, "%.2f", root->attr.val);
            return t;
        case IdK:
            sprintf(t, "%s", root->attr.name);
            return t;
        case MethodCallK:
            p = root->child[0]->child[0];
            while (p != NULL) {
                printf("   ARG %s\n", p->attr.name);
                p = p->next;
            }
            printf("   CALL %s TO t%d\n", root->attr.name, ++tempCnt);
            sprintf(t, "t%d", tempCnt);
            return t;
    }
}

void dispose(struct TreeNode* root) {                               // 处理表达式
    tempCnt = 0;
    if (root->child[0]->kind.expression == OpK) {
        char* t0 = cal(root->child[0]->child[0]);
        char* t1 = cal(root->child[0]->child[1]);
        switch (root->child[0]->attr.token) {
            case ADD: printf("   %s := %s + %s\n", root->attr.name, t0, t1); break;
            case SUB: printf("   %s := %s - %s\n", root->attr.name, t0, t1); break;
            case MUL: printf("   %s := %s * %s\n", root->attr.name, t0, t1); break;
            case DIV: printf("   %s := %s / %s\n", root->attr.name, t0, t1); break;
            case MOD: printf("   %s := %s %% %s\n", root->attr.name, t0, t1); break;
            case XOR: printf("   %s := %s ^ %s\n", root->attr.name, t0, t1); break;
        }
    }
    else {
        char* temp = cal(root->child[0]);
        printf("   %s := %s\n", root->attr.name, temp);
    }
}

void dispose2(struct TreeNode* root) {                            // 处理判断式
    tempCnt = 0;
    if (root->kind.expression == OpK) {
        char* t0 = cal(root->child[0]);
        char* t1 = cal(root->child[1]);
        switch (root->attr.token) {
            case EQUAL: printf("   t1 := %s == %s\n", t0, t1); break;
            case UNEQUAL: printf("   t1 := %s != %s\n", t0, t1); break;
            case GREATER: printf("   t1 := %s > %s\n", t0, t1); break;
            case LESS: printf("   t1 := %s < %s\n", t0, t1); break;
        }
    }
    else {
        char* temp = cal(root->child[0]);
        printf("   t1 := %s\n", temp);
    }
}

void printMiddleCode(struct TreeNode* root) {                       // 输出中间代码
	while (root != NULL) {
		if (root->nodekind == MethodK) {
			switch (root->kind.method) {
				case MainK:
					printf("MAIN METHOD %s\nBEGIN\n", root->attr.name);
                    for (int i = 0; i < 10; i++) printMiddleCode(root->child[i]);
                    printf("END\n\n");
                    break;
				case NormalK:
					printf("METHOD %s\nBEGIN\n", root->attr.name);
                    for (int i = 0; i < 10; i++) printMiddleCode(root->child[i]);
                    printf("END\n\n");
                    break;
			}
		}
		else if (root->nodekind == TypeK) {
			switch (root->kind.type) {
				case ReturnTypeK:
					printf("   RETURN TYPE %s\n", root->attr.name); break;
				case IntTypeK: 
					printf("INT %s ", root->attr.name); break;
				case RealTypeK:
					printf("REAL %s ", root->attr.name); break;
			}
		}
		else if (root->nodekind == ParamK) {
			switch (root->kind.param) {
				case FormalK:
				case ActualK:
					printf("   PARAM ");
                    for (int i = 0; i < 10; i++) printMiddleCode(root->child[i]);
                    printf("\n");
                    break;
			}
		}
		else if (root->nodekind == StatementK) {
            struct TreeNode* rootCopy = root;
			switch (root->kind.statement) {
				case IfK:
                    rootCopy = root->child[0];
                    dispose2(rootCopy);
					printf("   IFZ t1 GOTO L%d\n", ++labelCnt);
                    for (int i = 1; i < 10; i++) printMiddleCode(root->child[i]);
                    printf("LABEL L%d\n", labelCnt);
                    break;
				case ReturnK:
					printf("   RETURN %s\n", root->child[0]->attr.name);
                    break;
				case AssignK:
                    dispose(rootCopy);
                    break;
				case ReadK:
					printf("   READ %s to %s\n", root->attr.name, root->child[0]->attr.name);
                    break;
				case WriteK:
					printf("   WRITE %s from %s\n", root->attr.name, root->child[0]->attr.name);
                    break;
				case WhileK:
					printf("LABEL L%d\n", ++labelCnt); 
                    rootCopy = root->child[0];
                    dispose2(rootCopy);
					printf("   IFZ t1 GOTO LABEL L%d\n", ++labelCnt);
                    for (int i = 1; i < 10; i++) printMiddleCode(root->child[i]);
					printf("   GOTO LABEL L%d\n", labelCnt-1);
					printf("LABEL L%d\n", labelCnt); 
                    break;
				case ForK:
                    rootCopy = root->child[0];
                    dispose(rootCopy);
					printf("LABEL L%d\n", ++labelCnt); 
                    rootCopy = root->child[1];
                    dispose2(rootCopy);
					printf("   IFZ t1 GOTO LABEL L%d\n", ++labelCnt); 
                    for (int i = 3; i < 10; i++) printMiddleCode(root->child[i]);
                    rootCopy = root->child[2];
                    dispose(rootCopy);
                    printf("   GOTO LABEL L%d\n", labelCnt-1);
					printf("LABEL L%d\n", labelCnt); 
					break;
				case IntDeclareK:
					printf("   INT %s\n", root->attr.name); break;
				case RealDeclareK:
					printf("   REAL %s\n", root->attr.name); break;
			}
		}
		root = root->next;
	}
}

void check(struct TreeNode* root) {                         // 总测试
    printf("\n-------------------------- Symbol Table --------------------------\n");
    struct TreeNode* rootcopy = root;
	printSymbolTable(rootcopy);
    printf("\n----------------------- Semantic analysis ------------------------\n");
    rootcopy = root;
    checkSymbol(rootcopy);
    if (judge == 1) {
        rootcopy = root;
        checkType(rootcopy);    
        if (judge == 1) {
            printf("No error ^_^\n");
            printf("\n-------------------------- Middle Code ---------------------------\n");
            rootcopy = root;
            printMiddleCode(rootcopy);
        }
        else printf("Type Error >_<\n");
    }
    else if (judge == -1) printf("ID repeat declare Error >_<\n");
    else if (judge == -2) printf("ID call Error >_<\n");
    else printf("Func call Error >_<\n");
}

#endif