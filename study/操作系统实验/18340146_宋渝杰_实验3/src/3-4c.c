/*
	gcc -march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding -fno-PIE -masm=intel -c 3-4c.c -o 3-4c.o
	nasm -felf 3-4asm.asm -o 3-4asm.o
	ld -m elf_i386 -N --oformat binary -Ttext 0x7e00 3-4asm.o 3-4c.o -o 3-4.bin
	
	/sbin/mkfs.msdos -C syjos.img 1440
	dd if=1.com of=syjos.img seek=18 conv=notrunc
	dd if=2.com of=syjos.img seek=19 conv=notrunc
	dd if=3.com of=syjos.img seek=20 conv=notrunc
	dd if=4.com of=syjos.img seek=21 conv=notrunc
	dd if=3-4.bin of=syjos.img seek=1 conv=notrunc
	dd if=3-4os.bin of=syjos.img conv=notrunc	
	
*/

int X = 0, Y = 0, num = 4;
int queue[] = {0,0,0,0}; 

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

int cstr(const char *s1, const char *s2) {
	while (*s1 && (*s1 == *s2))
		++s1, ++s2;
	return (int)*s1 - (int)*s2;
}

extern void LoadnEx(int );
extern void cls();

void main() {
	if (num < 4) num++;
	if (num < 4 && queue[num] != 0) {
		int j = queue[num];
		queue[num] = 0;
		LoadnEx(j);
		return main();
	}
	pchar('\n');
	static char msg1[] = "Welcome to syj's os! Enter a instruction (or Enter 'help' for help): \n";
	static char msg2[] = "Enter a number (1-4) to open an exe: \n";
	static char msg3[] = "Enter 4 number (1-4) to open 4 exes: \n";
	static char err[] = "Error: Instruction does not exist!\n";
	const char help[] = "help", exe[] = "exe", exes[] = "exes", exit[] = "exit", ls[] = "ls", clear[] = "cls";
	static char helpstr[] =
		"You can input these instructions.\n"
		"\n"
		"help         -- Print instructions\n"
		"exe          -- Open an exe\n"
		"exes         -- Open many exes\n"
		"ls           -- Show four exes' information\n"
		"cls          -- Clear the screen\n"
		"exit         -- Exit OS\n";
	static char exestr[] =
		"exe1         -- LeftUp     512 bytes\n"
		"exe2         -- RightUp    512 bytes\n"
		"exe3         -- LeftDown   512 bytes\n"
		"exe4         -- RightDown  512 bytes\n";
	char *ptr = msg1;
	char str[1000];
	pstr(ptr);
	pchar('>');
	pchar('>');
	pchar(' ');
	gstr(str);
	if (cstr(str, help) == 0) {
		ptr = helpstr;
		pstr(ptr);
	}
	else if (cstr(str, clear) == 0) {
		cls();
		X = 0;
		Y = 0;
	}
	else if (cstr(str, exit) == 0) {
		return;
	}
	else if (cstr(str, ls) == 0) {
		ptr = exestr;
		pstr(ptr);	
	}
	else if (cstr(str, exe) == 0) {
		ptr = msg2;
		pstr(ptr);
		pchar('\n');
		pchar('>');
		pchar('>');
		pchar(' ');
		char c = gchar();
		while (c > '4' || c < '1') c = gchar();
		LoadnEx((int)(c-48));
	}
	else if (cstr(str, exes) == 0) {
		ptr = msg3;
		pstr(ptr);
		pchar('\n');	
		pchar('>');
		pchar('>');
		pchar(' ');
		for (int i=0; i<4; i++) {
			char c = gchar();
			while (c > '4' || c < '1') c = gchar();
			pchar(c);
			queue[i] = (int)(c-48);
		}
		num = -1;
	}
	else {
		ptr = err;
		pstr(ptr);
	}
	return main();
}
