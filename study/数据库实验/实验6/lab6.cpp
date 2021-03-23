#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <winsock.h>
#include "mysql.h"

MYSQL mysql;

void create_course_table() {
	if (mysql_query(&mysql, "create table course(cno varchar(4), cname varchar(10), cpno varchar(4), ccredit int);")) {
		printf("The course table already exists. Do you want to delete it? (y--yes,n--no):\n");
		char c = getch();
		while (c != 'y' && c != 'n') c = getch();
		if (c == 'y') {
			if (!mysql_query(&mysql, "drop table course")) printf("Delete successfully!\n");
			else printf("Delete ERROR!\n");
		}
		else return ;
		if (mysql_query(&mysql, "create table course(cno varchar(4), cname varchar(10), cpno varchar(4), ccredit int);") == 0)
			printf("Create table successfully!\n");
		else printf("Create ERROR!\n");
	}
	else printf("Create table successfully!\n");
}

void insert_rows_into_course_table() {
	char cno[10], cname[12], cpno[10], all[100];
	int ccredit;
	printf("Enter cno:\n");
	scanf("%s",cno);
	printf("Enter cname:\n");
	scanf("%s",cname);
	printf("Enter cpno:\n");
	scanf("%s",cpno);
	printf("Enter ccredit:\n");
	scanf("%d",&ccredit);
	sprintf(all, "insert into course values(\"%s\",\"%s\",\"%s\",%d);", cno, cname, cpno, ccredit);
	if (mysql_query(&mysql, all) == 0)
		printf("Insert successfully!\n");
	else printf("Insert ERROR!\n");
}

int main() {
	char c;
	mysql_init(&mysql); 
	if (mysql_real_connect(&mysql, "localhost", "root", "123456", "jxgl", 3306, NULL, 0) == NULL)
		printf("%s\n", mysql_error(&mysql));
	do {
		printf("Enter 1 to create table Course\nEnter 2 to insert data into table Course\nEnter q to exit\n>>> ");
		c = getch();
		while (c != '1' && c != '2' && c != 'q') c = getch();
		printf("%c\n",c);
		if (c == '1') create_course_table();
		else if (c == '2') insert_rows_into_course_table();
	} while (c != 'q');
	mysql_close(&mysql);
	return 0;
}
