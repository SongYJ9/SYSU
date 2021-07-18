#include "lex.h"
#include "syntax.h"

int main() {
	menu();
	int choice;
	scanf("%d", &choice);
	while (choice < 0 || choice > 4) {
		printf("Wrong input >_< Try again: ");
		scanf("%d", &choice);
	}
	if (choice != 0) {
		if (choice == 1 || choice == 3) input = fopen("../txt/test1.tiny", "r");
		else input = fopen("../txt/test2.tiny", "r");
		if (input == NULL)  fprintf(stderr, "[ERROR] File not found >_<\n");
		if (choice == 1 || choice == 2) {
			lex = 1;
			while (getToken() != ENDFILE);
		} 
		else {
			struct TreeNode * syntaxTree = syntax();
			printTree(syntaxTree);
		} 
		fclose(input);
	}
	system("pause");
	return 0;
}

