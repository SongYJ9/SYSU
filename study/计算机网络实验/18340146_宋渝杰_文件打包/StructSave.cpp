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
	char*	pts;		  			  /* pointer to time string */
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
	
	Person personSave;
	FILE* pFile = fopen("c:\\temp\\aaa.stru", "wb"); // �����ļ�λ�� 
	if (pFile == NULL) {
		printf("can't open the file!\n");
		exit(0); 
	}

	/* ����Ա����¼ */
	printf("\nusername: ");
	scanf("%s", inputBuf);    // �����û���
	while (strcmp(inputBuf, "exit") != 0) {
		(void)time(&now);     // ȡ��ϵͳʱ��
		pts = ctime(&now);    // ��ʱ��ת��Ϊ�ַ���
		strcpy(personSave.username, inputBuf);
		printf("level: ");
		scanf("%d", &inputNumber);                   // �����û�����
		personSave.level = inputNumber;
		printf("email: ");
		scanf("%s", inputBuf);
		strcpy(personSave.email, inputBuf);          // ��������ʼ�
		personSave.sendtime = (DWORD)now;            // ���÷���ʱ��
		personSave.regtime = now;                    // ����ע��ʱ��
		if (fwrite(&personSave, sizeof(Person), 1, pFile) != 1) {  // д���ļ� 
			printf("file write error!\n"); 
		}
		printf("\nusername: ");
		scanf("%s", inputBuf);    // �����û���
	}
	fclose(pFile);
	printf("���������\n");
}
