/*
	gcc -march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding -fno-PIE -masm=intel -c 3-1c.c -o 3-1c.o
	nasm -felf 3-1asm.asm -o 3-1asm.o
	ld -m elf_i386 -N --oformat binary -Ttext 0x7e00 3-1asm.o 3-1c.o -o 1.bin
*/

void pchar(char c) {
	static int X = 0, Y = 0;
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

void gstr(char *s) {
	for (;; ++s) {
		pchar(*s = gchar());
		if (*s == '\r' || *s == '\n')
			break;
	}
	*s = '\0';
}

void pstr(char *s) {
	for (; *s; ++s)
		pchar(*s);
}

extern char find[]; 

void main() {
	pchar('>');
	pchar('>');
	pchar(' ');
	char msg[] = "The string is 'abbcccddddeeeeesyj',\n enter a letter to find its number: \n";
	char msg2[] = "The number of ";
	char msg3[] = " is ";
	pstr(msg);
	char c = gchar();
	int num = 0;
	for (int i=0; i<18; ++i) {
		if (c == find[i]) num++;
	}
	pstr(msg2);
	pchar(c);
	c = (char)(num+48);
	pstr(msg3);
	pchar(c);
	pchar('\n');
	pchar('\n');
	return main();
}
