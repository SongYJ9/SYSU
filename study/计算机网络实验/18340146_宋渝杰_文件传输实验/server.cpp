#include <bits/stdc++.h>
#include <winsock2.h>
#include <process.h>
#include "conio.h"
#pragma comment(lib,"ws2_32.lib")

char name[100][300]; 
HANDLE h;
SOCKET sClients;
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
		int re = recv(sClients,buf,2000000,0); // ��������
		buf[re]='\0';
		
		// ���� 
		if (!strcmp(buf,"0")) {
			re = recv(sClients,buf,2000000,0);
			buf[re]='\0'; 
			printf("\n�յ���Ϣ��%s\n>> ",buf);
		}
		
		// �����ļ� 
		else if (!strcmp(buf,"1")) {
			
			// �����ļ����ʹ�С 
			re = recv(sClients,buf,2000000,0);
			buf[re]='\0'; 
			
			// ���������ļ������� 
			if (!strcmp(buf,"none")) continue;
			
			// �½��ļ� 
			char *temp = strrchr(buf,' ');
			int filesize = atoi(temp+1);
			char filename[100];
			for (int i=0; i<100; i++) filename[i] = '\0'; 
			for (int i=0; buf[i]!=' '; i++) filename[i] = buf[i];
			strcpy(name[num++],filename);
			char *filename2 = getFileName(filename); // ������� 
			char dest[100];
			sprintf(dest,"%s\\%s",address,filename2);
			FILE *destfile = fopen(dest,"wb");
			
			// �����ļ�����
			int len = 0;
			while ((len = recv(sClients,buf,2000000,0)) >= 2000000)
				fwrite(buf,1,2000000,destfile);
			fwrite(buf,1,len,destfile);
			printf("\n�յ��ļ���%s\n>> ",filename2);
			fclose(destfile);
		}
		
		// �˳� 
		else if (!strcmp(buf,"2")) {
			printf("\n�ͻ����˳�...\n");
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
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// ��IP�Ͷ˿�
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons((u_short)atoi("50500"));

	// ��ʼ��
	bind(slisten, (LPSOCKADDR)&sin, sizeof(sin));

	// ��ʼ����
	listen(slisten, 5);

	// ����������
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	printf("��������������\n\n");
	
	sClients = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
	int x = 0;
	h = (HANDLE)_beginthreadex(NULL, 0, &newConnect, (void *)&x, 0, NULL); 
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
			send(sClients,pack1,strlen(pack1),0);
			gets(pack2);
			send(sClients,pack2,strlen(pack2),0);
		}
		
		// �����ļ� 
		else if (!strcmp(input,"file")) {
			char pack1[5];
			char pack2[200];
			char pack3[2000000];
			
			// �������� 
			strcpy(pack1,"1");
			send(sClients,pack1,strlen(pack1),0);
			
			// ��������and��С 
			scanf("%s",pack2);
			FILE *srcfile = fopen(pack2,"rb");
			if (srcfile == NULL) { // ��������� 
				printf("�ļ�������\n");
				fclose(srcfile);
				strcpy(pack2,"none");
				send(sClients,pack2,strlen(pack2),0);
				continue;
			}
			char filename[100];
			strcpy(filename,strrchr(pack2,'\\')+1);
			int filesize = getFileSize(srcfile);
			char char_size[10];
			itoa(filesize,char_size,10);
			sprintf(pack2,"%s %s",filename,char_size);
			send(sClients,pack2,strlen(pack2),0);
			
			// ��������
			int len=0;
			while ((len = fread(pack3,1,2000000,srcfile)) >= 2000000)
				send(sClients,pack3,strlen(pack3),0);
			send(sClients,pack3,len,0); 
			
			// �ر��ļ� 
			fclose(srcfile);
		}
		
		// �˳� 
		else if (!strcmp(input,"exit")) {
			char pack1[10];
			strcpy(pack1,"2");
			int s = send(sClients,pack1,strlen(pack1),0);
			break; 
		}
		else {
			printf("ָ����ڣ����������룡\n");
		}
	}
	WaitForSingleObject(h,1);
	CloseHandle(h);
	closesocket(sClients);
	closesocket(slisten);                             
	WSACleanup();  
	system("pause");
	return 0; 
}
	
	
