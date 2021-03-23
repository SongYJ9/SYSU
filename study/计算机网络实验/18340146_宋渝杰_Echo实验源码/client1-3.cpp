#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <time.h>
#pragma comment(lib,"ws2_32.lib")

int main() {

	// ����Winsock��
	WORD socketVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	WSAStartup(socketVersion, &wsaData);

	// ������ʽSOCKET
	SOCKET sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// ����Ҫ���ӵĵ�ַ�Ͷ˿� 
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(50500);
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int len = sizeof(sin);

	// ����Ҫ���͵���Ϣ 
	char sendData[200];
	scanf("%s", sendData);

	// ������Ϣ
	int sen = sendto(sclient, sendData, strlen(sendData), 0, (sockaddr*)&sin, len);
	if (sen == SOCKET_ERROR) {
		printf("����ʧ�ܣ�����ţ�%d\n", WSAGetLastError());
	}

	// ������Ϣ
	char recvData[255];
	int ret = recvfrom(sclient, recvData, 255, 0, (sockaddr*)&sin, &len);

	// ������ճɹ��������Ϣ
	if (ret > 0) {
		recvData[ret] = 0x00; // ��Ϣ������ʶ��
		printf("\n�յ�����Ϣ��\n%s\n", recvData);
	}
	else {
		printf("����ʧ�ܣ�����ţ�%d\n", WSAGetLastError());
	}

	// �ر�����
	closesocket(sclient);

	// �ͷ�Winsock��
	WSACleanup();
	return 0;
}
