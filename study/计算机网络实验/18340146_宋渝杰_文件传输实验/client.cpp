#include <bits/stdc++.h>
#include <winsock2.h>
#include <process.h>
#include "conio.h"
#pragma comment(lib,"ws2_32.lib")

char name[100][300];
HANDLE h;
SOCKET sclient;
char address[100],buf[2000002];
int num;

char* getFileName(char a[]) { // ������� 
	int count=1;
	for (int i=0; i<num-1; i++)
		if (strcmp(name[i],a) == 0)
			count++;
	strcpy(name[num-1],a);
	if (count==1) return a;	
	else {
		char p[100],q[100];
		strcpy(p,strrchr(a,'.'));
		sprintf(strrchr(a,'.'),"(%d)%s",count,p);
		return a;
	}
} 

int getFileSize(FILE *file_handle) { // ��ȡ�ļ���С 
	int current_read_position = ftell(file_handle);
	fseek(file_handle,0,SEEK_END);
	int file_size = ftell(file_handle);
	fseek(file_handle,current_read_position,SEEK_SET);
	return file_size;
}

unsigned __stdcall newConnect(void *n) {
	while (1) {
		int re = recv(sclient,buf,2000000,0); //��������
		buf[re]='\0'; 
	
		// ���� 
		if (!strcmp(buf,"0")) {
			re = recv(sclient,buf,2000000,0);
			buf[re]='\0'; 
			printf("\n�յ���Ϣ��%s\n>> ",buf);
		}
		
		// �����ļ� 
		else if (!strcmp(buf,"1")) {
				
			// �����ļ����ʹ�С 
			re = recv(sclient,buf,2000000,0);
			buf[re]='\0'; 
			
			// ���������ļ������� 
			if (!strcmp(buf,"none")) continue;
			
			// �½��ļ� 
			char *temp = strrchr(buf,' ');
			int filesize = atoi(temp+1);
			char filename[100];
			for (int i=0;i<100;i++)	filename[i] = '\0'; 
			for (int i=0; buf[i]!=' '; i++) filename[i] = buf[i];
			strcpy(name[num++],filename);
			char *filename2 = getFileName(filename); // ������� 
			char dest[100];
			sprintf(dest,"%s\\%s",address,filename2);
			FILE *destfile = fopen(dest,"wb");
			
			// �����ļ�����
			int len = 0;
			while ((len = recv(sclient,buf,2000000,0)) >= 2000000)
				fwrite(buf,1,2000000,destfile);
			fwrite(buf,1,len,destfile);
			printf("\n�յ��ļ���%s\n>> ",filename2);
			fclose(destfile);
		}
		
		// �˳� 
		else if (!strcmp(buf,"2")) {
			printf("\n�������˳�...\n");
			return 0;
		}
	}
}

int main() {

	// ����Winsock��
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	WSAStartup(sockVersion, &data);
 
	// ������ʽSOCKET
	sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// ����Ҫ���ӵĵ�ַ�Ͷ˿�
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(50500);
	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); 

	// �������ʧ�ܣ���ʾ��Ϣ������
	if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR) {
		printf("Error: %d.\n", GetLastError());
		// �ر����� 
		closesocket(sclient);
		return 0;
	}
	int x = 0;
	h = (HANDLE)_beginthreadex(NULL, 0, &newConnect, (void *)&x, 0, NULL); 
	printf("---���ӷ������ɹ�---\n\n");
	
	while (1) {
		printf(">> ");
		char input[100];
		scanf("%s",input);
		
		// �����ַ 
		if (!strcmp(input,"rdir")) {
			scanf("%s",address);
			printf("�ļ������ַ�޸�Ϊ��%s\n",address);
		}
		
		// ���� 
		else if (!strcmp(input,"chat")) {
			char pack1[5];
			char pack2[2000];
			strcpy(pack1,"0");
			send(sclient,pack1,strlen(pack1),0);
			gets(pack2);
			send(sclient,pack2,strlen(pack2),0);
		}
		
		// �����ļ� 
		else if (!strcmp(input,"file")) {
			char pack1[5];
			char pack2[200];
			char pack3[2000000];
			
			// �������� 
			strcpy(pack1,"1");
			send(sclient,pack1,strlen(pack1),0);
			
			// ��������and��С 
			scanf("%s",pack2);
			FILE *srcfile = fopen(pack2,"rb");
			if (srcfile == NULL) { // ��������� 
				printf("�ļ�������\n");
				fclose(srcfile);
				strcpy(pack2,"none");
				send(sclient,pack2,strlen(pack2),0);
				continue;
			}
			char filename[100];
			strcpy(filename,strrchr(pack2,'\\')+1);
			int filesize = getFileSize(srcfile);
			char char_size[10];
			itoa(filesize,char_size,10);
			sprintf(pack2,"%s %s",filename,char_size);
			send(sclient,pack2,strlen(pack2),0);
			
			// ��������
			int len=0;
			while ((len = fread(pack3,1,2000000,srcfile)) >= 2000000) {
				send(sclient,pack3,strlen(pack3),0);
			}
			send(sclient,pack3,len,0); 
			
			// �ر��ļ� 
			fclose(srcfile);
		}
		
		// �˳� 
		else if (!strcmp(input,"exit")) {
			char pack1[10];
			strcpy(pack1,"2");
			int s = send(sclient,pack1,strlen(pack1),0);
			break; 
		}
		else {
			printf("ָ����ڣ����������룡\n");
		}
	}
	WaitForSingleObject(h,1);
	CloseHandle(h);
	closesocket(sclient);                          
	WSACleanup();   
	system("pause");
	return 0; 
}
	
	
