#include <stdio.h>
#include <winsock2.h>
#include <cstring>
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
		unsigned int tem;

		// ������ճɹ��������Ϣ
		if (ret > 0) {
			revData[ret] = 0x00; // ��Ϣ������ʶ��
			(void)time(&now); // ȡ��ϵͳʱ��
			pts = ctime(&now); // ��ʱ��ת��Ϊ�ַ���
			tem = remoteAddr.sin_addr.s_addr;
			printf("�յ���Ϣ��%s\n�յ�ʱ�䣺%s�ͻ���IP��ַ: %d.%d.%d.%d\n�ͻ��˶˿ں�: %d\n\n",
				revData, pts, (tem << 24) >> 24, (tem << 16) >> 24, (tem << 8) >> 24, tem >> 24, remoteAddr.sin_port);
		}

		// ������Ϣ 
		char sendData[200];
		sprintf(sendData, "��Ϣ��%s\nʱ�䣺%s�ͻ���IP��ַ: %d.%d.%d.%d\n�ͻ��˶˿ں�: %d\n\n",
			revData, pts, (tem << 24) >> 24, (tem << 16) >> 24, (tem << 8) >> 24, tem >> 24, remoteAddr.sin_port);
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
