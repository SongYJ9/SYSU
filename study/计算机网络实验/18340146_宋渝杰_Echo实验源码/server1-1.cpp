#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <cstring>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "conio.h"
#pragma comment(lib,"ws2_32.lib")

using namespace std;

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
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[255];
	printf("��������������\n\n");

	// ѭ���������� 
	while (!_kbhit()) { // �����⵽�����������һ�����ݺ��˳�ѭ��

		char* pts;
		time_t now;

		// ���ͻ��˽���(ʧ������ʾ��Ϣ������ѭ��)
		sClient = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
		if (sClient == INVALID_SOCKET) {
			printf("Accept Error !");
			break;
		}
		// ��������
		int ret = recv(sClient, revData, 255, 0);

		// ������ճɹ��������Ϣ
		if (ret > 0) {
			revData[ret] = 0x00; // ��Ϣ������ʶ��
			(void)time(&now); // ȡ��ϵͳʱ��
			pts = ctime(&now); // ��ʱ��ת��Ϊ�ַ���
			printf("�յ���Ϣ��%s\n�յ�ʱ�䣺%s\n",revData,pts);
		}

		// ������Ϣ 
		string s1(pts), s2(revData);
		s1 = s1 + s2;
		const char* sendData;
		sendData = s1.c_str();
		send(sClient, sendData, strlen(sendData), 0);

		// �ر�����
		closesocket(sClient);
	}

	// �رս��� 
	closesocket(slisten);

	// �ͷ�Winsock��
	WSACleanup();
	return 0;
}
