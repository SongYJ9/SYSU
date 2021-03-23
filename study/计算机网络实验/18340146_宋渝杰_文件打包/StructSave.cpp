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
		char username[USER_NAME_LEN]; //  用户名
		int level;                    //  级别
		char email[EMAIL_LEN];        //  email地址
		DWORD sendtime;               //  发送时间
		time_t regtime;               //  注册时间
	};
	
	Person personSave;
	FILE* pFile = fopen("c:\\temp\\aaa.stru", "wb"); // 保存文件位置 
	if (pFile == NULL) {
		printf("can't open the file!\n");
		exit(0); 
	}

	/* 输入员工记录 */
	printf("\nusername: ");
	scanf("%s", inputBuf);    // 输入用户名
	while (strcmp(inputBuf, "exit") != 0) {
		(void)time(&now);     // 取得系统时间
		pts = ctime(&now);    // 把时间转换为字符串
		strcpy(personSave.username, inputBuf);
		printf("level: ");
		scanf("%d", &inputNumber);                   // 输入用户级别
		personSave.level = inputNumber;
		printf("email: ");
		scanf("%s", inputBuf);
		strcpy(personSave.email, inputBuf);          // 输入电子邮件
		personSave.sendtime = (DWORD)now;            // 设置发送时间
		personSave.regtime = now;                    // 设置注册时间
		if (fwrite(&personSave, sizeof(Person), 1, pFile) != 1) {  // 写入文件 
			printf("file write error!\n"); 
		}
		printf("\nusername: ");
		scanf("%s", inputBuf);    // 输入用户名
	}
	fclose(pFile);
	printf("输入结束！\n");
}
