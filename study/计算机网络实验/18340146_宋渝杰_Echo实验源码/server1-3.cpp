#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include "conio.h"
#pragma comment(lib,"ws2_32.lib")

int main() {

	// ����Winsock��
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	WSAStartup(sockVersion, &wsaData);

	// ������ʽSOCKET
	SOCKET serSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// ��IP�Ͷ˿�
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(50500);
	serAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	// ��ʼ��
	bind(serSocket, (sockaddr*)&serAddr, sizeof(serAddr));

	// ����������
	sockaddr_in remoteAddr;
	int nAddrLen = sizeof(remoteAddr);
	printf("��������������\n\n");

	// ѭ���������� 
	while (!_kbhit()) { // �����⵽�����������һ�����ݺ��˳�ѭ��

		char* pts;
		time_t now;

		// ��������
		char recvData[255];
		int ret = recvfrom(serSocket, recvData, 255, 0, (sockaddr*)&remoteAddr, &nAddrLen);
		unsigned int tem;

		// ������ճɹ��������Ϣ
		if (ret > 0) {
			recvData[ret] = 0x00;
			(void)time(&now); // ȡ��ϵͳʱ��
			pts = ctime(&now); // ��ʱ��ת��Ϊ�ַ���
			tem = remoteAddr.sin_addr.s_addr;
			printf("�յ���Ϣ��%s\n�յ�ʱ�䣺%s�ͻ���IP��ַ: %d.%d.%d.%d\n�ͻ��˶˿ں�: %d\n\n",
				recvData, pts, (tem << 24) >> 24, (tem << 16) >> 24, (tem << 8) >> 24, tem >> 24, remoteAddr.sin_port);
		}

		// ������Ϣ
		char sendData[200];
		sprintf(sendData, "��Ϣ��%s\nʱ�䣺%s�ͻ���IP��ַ: %d.%d.%d.%d\n�ͻ��˶˿ں�: %d\n\n",
			recvData, pts, (tem << 24) >> 24, (tem << 16) >> 24, (tem << 8) >> 24, tem >> 24, remoteAddr.sin_port);
		sendto(serSocket, sendData, strlen(sendData), 0, (sockaddr*)&remoteAddr, nAddrLen);
	}

	// �رս���
	closesocket(serSocket);

	// �ͷ�Winsock��
	WSACleanup();
	return 0;
}
