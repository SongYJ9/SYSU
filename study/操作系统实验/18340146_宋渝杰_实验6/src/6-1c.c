/*
	gcc -march=i386 -m16 -mpreferred-stack-boundary=2 -ffreestanding -fno-PIE -masm=intel -c 6-1c.c -o 6-1c.o
	nasm -felf 6-1asm.asm -o 6-1asm.o
	ld -m elf_i386 -N --oformat binary -Ttext 0x7e00 6-1asm.o 6-1c.o -o 6-1.bin
	nasm 6-1os.asm -o 6-1os.bin
	
	nasm 1.asm -o 1.com
	nasm 2.asm -o 2.com
	nasm 3.asm -o 3.com
	nasm 4.asm -o 4.com
	 
	rm -f syjos.img
	/sbin/mkfs.msdos -C syjos.img 1440
	dd if=1.com of=syjos.img seek=18 conv=notrunc
	dd if=2.com of=syjos.img seek=19 conv=notrunc
	dd if=3.com of=syjos.img seek=20 conv=notrunc
	dd if=4.com of=syjos.img seek=21 conv=notrunc
	dd if=5.com of=syjos.img seek=22 conv=notrunc
	dd if=6.com of=syjos.img seek=23 conv=notrunc
	dd if=6-1.bin of=syjos.img seek=1 conv=notrunc
	dd if=6-1os.bin of=syjos.img conv=notrunc	
	
*/

int X = 0, Y = 0, num = 4;
int queue[] = {0,0,0,0};
int count=0,num1=0,num2=0,num3=0,num4=0;
int judge=0,xc=2,yc=8;
int in=0,muti=0;

struct PCB {
	int ip, cs, flags, es, ds, ss, ax, bx, cx, dx, di, bp, sp, si, pid, statu;
	char exename[10];
	char address[10];
} q[10], *qi = q, *qe = q+1;

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

void draw() {
	if (1) {
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
}

void toupper(char* s) {
    int i = 0;
    while (s[i]) {
        if (s[i] >= 'a' && s[i] <= 'z')  
        	s[i] = s[i]-32;
        i++;
    }
}

void tolower(char* s) {
    int i = 0;
    while (s[i]) {
        if (s[i] >= 'A' && s[i] <= 'Z')  
        	s[i] = s[i]+32;
        i++;
    }
}

void reverse(char* s, int len) {
	int l=0,r=len-1;
	char temp;
	for (; l<r; l++, r--) {
		temp = *(s+l);
		*(s+l) = *(s+r);
		*(s+r) = temp;
	}
}

int atoi(char *s) {
    int ans = 0,i;
    for (i=0; s[i]!='\0'; ++i)
        ans = ans*10+s[i]-48; 
    return ans; 
}

void itoa(int num, char* str) {
	int i = 0;
	if (num == 0)
		str[i++] = '0';
	while (num) {
		str[i++] = num%10+48;
		num /= 10;
	}
	str[i] = '\0';
	reverse(str, i);
}

int atoi_2(char *s) {
    int ans = 0,i;
    for (i=0; s[i]!='\0'; ++i)
        ans = ans*2+s[i]-48; 
    return ans; 
}

void itoa_2(int num, char* str) {
	int i = 0;
	if (num == 0)
		str[i++] = '0';
	while (num) {
		str[i++] = num%2+48;
		num /= 2;
	}
	str[i] = '\0';
	reverse(str, i);
}

void schedule() {
	if (++qi == q+5) qi = q;
	while (qi->statu == 0)
		if (++qi == q+5) qi = q;
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
	qi = q;
	qi->statu = 1;
	static char msg1[] = "Welcome to syj's os! Enter a instruction (or Enter 'help' for help): \n";
	static char msg2[] = "Enter a number (1-6) to open an exe: \n";
	static char msg3[] = "Enter 4 number (1-4) to open 4 exes: \n";
	static char err[] = "Error: Instruction does not exist!\n";
	const char help[] = "help", exe[] = "exe", exes[] = "exes", exit[] = "exit", ls[] = "ls", clear[] = "cls", run[] = "runs";
	static char helpstr[] =
		"You can input these instructions.\n"
		"\n"
		"help         -- Print instructions\n"
		"exe          -- Open an exe\n"
		"exes         -- Open many exes\n"
		"runs         -- run all basic exes at the same time\n"
		"ls           -- Show four exes' information\n"
		"cls          -- Clear the screen\n"
		"exit         -- Exit OS\n";
	static char exestr[] =
		"exe1         -- LeftUp     512 bytes\n"
		"exe2         -- RightUp    512 bytes\n"
		"exe3         -- LeftDown   512 bytes\n"
		"exe4         -- RightDown  512 bytes\n"
		"exe5         -- RightDown  401 bytes\n"
		"exe6         -- RightDown  1724 bytes\n";
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
		while (c > '6' || c < '1') c = gchar();
		pchar(c);
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
	else if (cstr(str, run) == 0) {
		for (int i=0; i<4; i++) {
			(qe+i)->flags = 512;
			(qe+i)->ip = 0xa300+i*0x200;
			(qe+i)->sp = 0xfba0;
			(qe+i)->bp = 0xfba0;
			(qe+i)->si = 0x000e008a;
			(qe+i)->di = 0xffac;
			(qe+i)->ss = 0x0000;
			(qe+i)->es = 0xb800;
			(qe+i)->ds = 0x0000;
			(qe+i)->cs = 0x0000;
			(qe+i)->ax = 0x0005;
			(qe+i)->bx = 0x1f40;
			(qe+i)->cx = 0x0000;
			(qe+i)->dx = 0x0000;
			(qe+i)->pid = i+1;
			(qe+i)->statu = 1;
			LoadnEx(i+1);
		}
		muti = 1;
		while (muti) {}
	}
	else {
		ptr = err;
		pstr(ptr);
	}
	return main();
}
