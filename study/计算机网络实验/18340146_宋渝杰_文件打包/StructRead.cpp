#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUF_LEN 100
#define USER_NAME_LEN 20
#define EMAIL_LEN 80
#define TIME_BUF_LEN 30

typedef unsigned long DWORD;

int main() {
	char *pts,*pts2;		   		  /* pointer to time string	*/
	time_t	now;			          /* current time */
	char inputBuf[100];
	int inputNumber;

	struct Person {
		char username[USER_NAME_LEN]; //  �û���
		int level;                    //  ����
		char email[EMAIL_LEN];        //  email��ַ
		DWORD sendtime;               //  ����ʱ��
		time_t regtime;               //  ע��ʱ��
	};
	
	Person personRead;
	FILE* pFile = fopen("c:\\temp\\aaa.stru", "rb"); // ��ȡ�ļ� 
	if (pFile == NULL) {
		printf("can't open the file!\n");
		exit(0); 
	}

	/* ���Ա����¼ */
	while (fread(&personRead, sizeof(Person), 1, pFile) == 1) {
		time_t t1 = (time_t)personRead.sendtime;
		pts = ctime(&t1);   				// ��ʱ��ת��Ϊ�ַ���
		pts2 = ctime(&personRead.regtime);  // ��ʱ��ת��Ϊ�ַ���
		printf("������%s ����%d �����ʼ���%s ����ʱ�䣺%s ע��ʱ�䣺%s\n",
			personRead.username,personRead.level,personRead.email,pts,pts2);
	}
	fclose(pFile);
}
