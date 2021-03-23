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

void pint(int n) {
	char str[10];
	int i = 0;
	if (n == 0) {
		pchar('0');
		return;
	}
	while (n) {
		str[i++] = n%10+48;
		n /= 10;
	}
	for (; i>0; i--)
		pchar(str[i-1]);
}

int gint() {
	int n = 0;
	char c;
	while (1) {
		c = gchar();
		if (c == '\r' || c == '\n')
			break;
		while (c > '9' || c < '0')
			c = gchar();
		pchar(c);
		n = n*10+c-48;
	}
	return n;
}
