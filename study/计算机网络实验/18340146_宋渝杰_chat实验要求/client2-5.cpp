/* 
	chatʵ�� (5) �ͻ��˳��� 
*/ 

#include <bits/stdc++.h>
#include <winsock2.h>
#include <process.h>
#include "conio.h"
#pragma comment(lib,"ws2_32.lib")

using namespace std;

int n;
SOCKET sclient; 
HANDLE th;

unsigned __stdcall receive(void *n) {
	
	while (1) {
		
		// ������Ϣ
		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		
		// ������ճɹ��������Ϣ
		if (ret > 0) {
			recData[ret] = 0x00; // ��Ϣ������ʶ��
			printf("%s\n\n",recData);
		}
	}
	return 0;
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
	serAddr.sin_addr.S_un.S_addr = inet_addr("103.26.79.35");

	// �������ʧ�ܣ���ʾ��Ϣ������
	if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR) {
		printf("Error: %d.\n", GetLastError());
		// �ر����� 
		closesocket(sclient);
		return 0;
	}
	
	th = (HANDLE)_beginthreadex(NULL, 0, &receive, (void *)&n, 0, NULL); 
	
	while (1) {
		
		// ����Ҫ���͵���Ϣ 
		string indata;
		getline(cin,indata);
		
		// stringתconst char*
		const char* sendData;
		sendData = indata.c_str();

		// ������Ϣ
		send(sclient, sendData, strlen(sendData), 0);
		
		// ����رտͻ��ˣ����ж��߳� 
		if (indata == "exit") {
			CloseHandle(th);
			break;
		}
	}
	
	WaitForSingleObject(th, INFINITE); 

	// �ر�����
	closesocket(sclient);

	// �ͷ�Winsock��
	// WSACleanup();
	cout << "�������������";
	getchar();
	getchar();
	return 0;
}
