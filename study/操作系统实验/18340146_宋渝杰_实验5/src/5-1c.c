/*
	gcc -march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding -fno-PIE -masm=intel -c 5-1c.c -o 5-1c.o
	nasm -felf 5-1asm.asm -o 5-1asm.o
	ld -m elf_i386 -N --oformat binary -Ttext 0x7e00 5-1asm.o 5-1c.o -o 5-1.bin
	nasm 5-1os.asm -o 5-1os.bin
	 
	rm -f syjos.img
	/sbin/mkfs.msdos -C syjos.img 1440
	dd if=1.com of=syjos.img seek=18 conv=notrunc
	dd if=2.com of=syjos.img seek=19 conv=notrunc
	dd if=3.com of=syjos.img seek=20 conv=notrunc
	dd if=4.com of=syjos.img seek=21 conv=notrunc
	dd if=5-1.bin of=syjos.img seek=1 conv=notrunc
	dd if=5-1os.bin of=syjos.img conv=notrunc	
	
*/

int X = 0, Y = 0, num = 4;
int queue[] = {0,0,0,0}; 
int count=0,num1=0,num2=0,num3=0,num4=0; 
int judge=0,xc=2,yc=8; 
extern void schar();
int in=0;

struct PCB {
	int ip, cs, es, ds, ss, di, si, bp, sp, ax, bx, cx, dx, flags, pid;
} q[5], *qi = q;

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

void pchar2(char c,int x,int y) {
	asm volatile(
		"push es\n"
		"mov es, ax\n"
		"mov es:[bx],cx\n"
		"pop es\n"
		:
		: "a"(0xB800), "b"((x*80+y)*2), "c"((0x07<<8)+c)
		:);
	return;
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

void draw() {
	if (judge == 0) {
		count++;
		if (count >= 18) {
			count = 0;
			num1++;
			if (num1 >= 10) {
				num1 = 0;
				num2++;
				if (num2 >= 6) {
					num2 = 0;
					num3++;
					if (num3 >= 10) {
						num3 = 0;
						num4++;
						if (num4 >= 6) num4 = 0;
					}
				}
			}
			pchar2((char)(num4+48),24,75);
			pchar2((char)(num3+48),24,76);
			pchar2(':',24,77);
			pchar2((char)(num2+48),24,78);
			pchar2((char)(num1+48),24,79);
		}	
	}
	else {
		schar();
		if (in == 1) {
			pchar2('O',xc,yc);
			pchar2('U',xc,yc+1);
			pchar2('C',xc,yc+2);
			pchar2('H',xc,yc+3);
			pchar2('!',xc,yc+4);
			pchar2('O',xc,yc+5);
			pchar2('U',xc,yc+6);
			pchar2('C',xc,yc+7);
			pchar2('H',xc,yc+8);
			pchar2('!',xc,yc+9);
			xc = (xc+2)%24;
			yc = (yc+18)%65;
			in = 0;
		}
	}
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
	judge = 0;
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
		judge = 1;
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
		judge = 1;
		num = -1;
	}
	else {
		ptr = err;
		pstr(ptr);
	}
	return main();
}
