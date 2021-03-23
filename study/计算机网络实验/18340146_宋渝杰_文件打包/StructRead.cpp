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
		char username[USER_NAME_LEN]; //  用户名
		int level;                    //  级别
		char email[EMAIL_LEN];        //  email地址
		DWORD sendtime;               //  发送时间
		time_t regtime;               //  注册时间
	};
	
	Person personRead;
	FILE* pFile = fopen("c:\\temp\\aaa.stru", "rb"); // 读取文件 
	if (pFile == NULL) {
		printf("can't open the file!\n");
		exit(0); 
	}

	/* 输出员工记录 */
	while (fread(&personRead, sizeof(Person), 1, pFile) == 1) {
		time_t t1 = (time_t)personRead.sendtime;
		pts = ctime(&t1);   				// 把时间转换为字符串
		pts2 = ctime(&personRead.regtime);  // 把时间转换为字符串
		printf("姓名：%s 级别：%d 电子邮件：%s 发送时间：%s 注册时间：%s\n",
			personRead.username,personRead.level,personRead.email,pts,pts2);
	}
	fclose(pFile);
}
