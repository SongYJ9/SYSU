/*
	gcc -march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding -fno-PIE -masm=intel -c 6.c -o 6c.o
	gcc -march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding -fno-PIE -masm=intel -c io.c -o io.o
	nasm -felf 6.asm -o 6asm.o
	ld -m elf_i386 -N --oformat binary -Ttext 0xa100 6asm.o 6c.o io.o -o 6.com
	
*/
extern void pchar(char);
extern char gchar();
extern void pstr(char*);
extern void gstr(char*);
extern void pint(int);
extern int gint();

void cmain() {
	char msg[] = "Please input a char: \n\n>> ";
	char* ptr = msg;
	pstr(ptr);
	char c = gchar();
	pchar(c);
	char msg2[] = "\n\nThe input char is: ";
	ptr = msg2;
	pstr(ptr);
	pchar(c);
	char msg3[] = "\n\nPlease input a string: \n\n>> ";
	ptr = msg3;
	pstr(ptr);
	char s[100];
	gstr(s);
	char msg4[] = "\nThe input string is: ";
	ptr = msg4;
	pstr(ptr);
	ptr = s;
	pstr(ptr);
	char msg5[] = "\n\nPlease input an int: \n\n>> ";
	ptr = msg5;
	pstr(ptr);
	int n = gint();
	char msg6[] = "\n\nThe input int is: ";
	ptr = msg6;
	pstr(ptr);
	pint(n);
	char msg7[] = "\n\n          Enter any to return";
	ptr = msg7;
	pstr(ptr);
	return;
}
