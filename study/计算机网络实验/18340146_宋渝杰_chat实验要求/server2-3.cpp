/* 
	chatʵ�� (3) ���������� 
*/ 

#include <bits/stdc++.h>
#include <winsock2.h>
#include <process.h>
#include "conio.h"
#pragma comment(lib,"ws2_32.lib")

using namespace std;

HANDLE h[200];
SOCKET sClients[200];
int judge[200];
sockaddr_in remoteAdd[200];

unsigned __stdcall newConnect(void *n) {
	
	// ��� num ���ͻ��˽������ӣ���������Ϣ 
	int num = *((int *)n);
	char s1[] = "Enter!";
	char s2[] = "Leave!";
	char revData[255];
	unsigned int tem = remoteAdd[num].sin_addr.s_addr; // ����ip
	
	// ��ʶ�ÿͻ���Ϊ����״̬ 
	judge[num] = 1;
	
	// ȡ��ϵͳʱ�� 
	char* pts;
	time_t now;
	(void)time(&now);
	pts = ctime(&now);
	
	// ��������� Enter! ��Ϣ 
	char sendData[200];
	sprintf(sendData, "IP��ַ: %d.%d.%d.%d  �˿ں�: %d\nʱ�䣺%s��Ϣ��%s",
		(tem << 24) >> 24, (tem << 16) >> 24, (tem << 8) >> 24, tem >> 24, remoteAdd[num].sin_port, pts, s1);
	cout << sendData << endl << endl;
	
	// ����Ϣ�������пͻ��� 
	for (int i=1; i<200; i++)
		if (judge[i])
			send(sClients[i], sendData, strlen(sendData), 0);
	
	// ѭ��������Ϣ 
	while (1) {
		
		int ret = recv(sClients[num], revData, 255, 0);
		
		// ������ճɹ��������Ϣ
		if (ret > 0) {
			
			// ��Ϣ������ʶ��
			revData[ret] = 0x00;
			
			// ȡ��ϵͳʱ�� 
			(void)time(&now);
			pts = ctime(&now);
			
			// ����������յ���Ϣ 
			string s(revData);
			if (s == "exit") {
				s = "Leave!";
				strcpy(revData,"Leave!");
			}
			printf("IP��ַ: %d.%d.%d.%d  �˿ں�: %d\nʱ�䣺%s��Ϣ��%s\n\n",
				(tem << 24) >> 24, (tem << 16) >> 24, (tem << 8) >> 24, tem >> 24, remoteAdd[num].sin_port, pts, revData);
				
			// ������Ϣ 
			char sendData[200];
			sprintf(sendData, "IP��ַ: %d.%d.%d.%d  �˿ں�: %d\nʱ�䣺%s��Ϣ��%s",
				(tem << 24) >> 24, (tem << 16) >> 24, (tem << 8) >> 24, tem >> 24, remoteAdd[num].sin_port, pts, revData);
			for (int i=1; i<200; i++)
				if (judge[i])
					send(sClients[i], sendData, strlen(sendData), 0);
					
			// ����յ����� Leave! ���ж����� 
			if (s == "Leave!") {
				judge[num] = 0;
				break;
			}
		}
	}
	
	// �ж����ӣ��߳̽��� 
	closesocket(sClients[num]);
	return 0;
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
	int num = 0;
	printf("��������������\n\n");

	// ѭ���������� 
	while (++num) {
		sClients[num] = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
		remoteAdd[num] = remoteAddr;
		int x = num;
		h[num] = (HANDLE)_beginthreadex(NULL, 0, &newConnect, (void *)&x, 0, NULL); 
	}

	// �رս��� 
	closesocket(slisten);

	// �ͷ�Winsock��
	WSACleanup();
	return 0;
}
