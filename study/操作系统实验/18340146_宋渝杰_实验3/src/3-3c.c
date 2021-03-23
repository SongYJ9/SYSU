/*
	gcc -march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding -fno-PIE -masm=intel -c 3-3c.c -o 3-3c.o
	nasm -felf 3-3asm.asm -o 3-3asm.o
	ld -m elf_i386 -N --oformat binary -Ttext 0x7e00 3-3asm.o 3-3c.o -o 3-3.bin
*/

int X = 0, Y = 0;

void pchar(char c) {
	if (c != '\r' && c != '\n') {
		asm volatile(
			"push es\n"
			"mov es, ax\n"
			"mov es:[bx],cx\n"
			"pop es\n"
			:
			: "a"(0xB800), "b"((X*80+Y)*2), "c"((0x07<<8)+c)
			:);
		if (++Y >= 80) {
			if (++X >= 25)
				X = 0;
			Y = 0;
		}
		asm volatile(
			"int 0x10\n"
			:
			: "a"(0x0200), "b"(0), "d"((X<<8)|Y));
		return;
	}
	do
		pchar(' ');
	while (Y);
}

char gchar() {
	char ch;
	asm volatile("int 0x16\n"
				 : "=a"(ch)
				 : "a"(0x1000));
	return ch;
}

void pstr(char *s) {
	for (; *s; ++s)
		pchar(*s);
}

void gstr(char *s) {
	for (;; ++s) {
		pchar(*s = gchar());
		if (*s == '\r' || *s == '\n')
			break;
	}
	*s = '\0';
}

extern void LoadnEx(int );

void main() {
	X = 0;
	Y = 0;
	static char msg1[] = "Welcome to syj's os! Enter a number (1-4) to open a program: ";
	char *ptr = msg1;
	pstr(ptr);
	pchar('\n');
	pchar('>');
	pchar('>');
	pchar(' ');
	char c = gchar();
	while (c > '4' || c < '1') c = gchar();
	LoadnEx((int)(c-48));
	return main();
}
