/*
	gcc -march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding -fno-PIE -masm=intel -c 7.c -o 7c.o
	gcc -march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding -fno-PIE -masm=intel -c io.c -o io.o
	nasm -felf 7.asm -o 7asm.o
	ld -m elf_i386 -N --oformat binary -Ttext 0xb500 7asm.o 7c.o io.o -o 7.com
	
*/
extern void pchar(char);
extern char gchar();
extern void pstr(char*);
extern void gstr(char*);
extern void pint(int);
extern int gint();

void fork() {
	asm volatile(
		"mov ax, 0\n"
		"int 0x23\n");
}

void wait() {
	asm volatile(
		"mov ah, 1\n"
		"int 0x23\n");
}

void exit() {
	asm volatile(
		"mov ah, 2\n"
		"int 0x23\n");
}

int letterNum = 0;
int figureNum = 0;

void cmain() {
	char msg1[] = "Testing fork and multithreading ^_^\n\n";
	char* ptr = msg1;
	pstr(ptr);
	fork();
	int pid;
	asm volatile(
		"add ax,0\n"
		: "=a"(pid) // pid = ax 
		:);
	if (pid == 0) {
		char msg2[] = "The string is 129djwqhdsajd128dw9i39ie93i8494urjoiew98kdkd.\n\n";
		ptr = msg2;
		pstr(ptr);
		wait();
		char msg3[] = "Letter number is: ";
		ptr = msg3;
		pstr(ptr);
		pint(letterNum);
		char msg4[] = "\n\nFigure number is: ";
		ptr = msg4;
		pstr(ptr);
		pint(figureNum);
		char msg9[] = "\n\nProcess finish. Enter any to return.";
		ptr = msg9;
		pstr(ptr);
	}
	else if (pid == 1) {
		char msg5[] = "Thread 1 run...\n\n";
		ptr = msg5;
		pstr(ptr);
		char msg[] = "129djwqhdsajd128dw9i39ie93i8494urjoiew98kdkd";
		for (int i=0; msg[i]; i++)
			if (msg[i] >= 'a' && msg[i] <= 'z') letterNum++;
		char msg6[] = "Thread 1 finish...\n\n";
		ptr = msg6;
		pstr(ptr);
		exit();
	}
	else if (pid == 2) {
		char msg7[] = "Thread 2 run...\n\n";
		ptr = msg7;
		pstr(ptr);
		char msg[] = "129djwqhdsajd128dw9i39ie93i8494urjoiew98kdkd";
		for (int i=0; msg[i]; i++)
			if (msg[i] >= '0' && msg[i] <= '9') figureNum++;
		char msg8[] = "Thread 2 finish...\n\n";
		ptr = msg8;
		pstr(ptr);
		exit();
	}
	return;
}
