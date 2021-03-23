#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <cstring>
#include <string>
#include <time.h>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main() {

	// ����Winsock��
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	WSAStartup(sockVersion, &data);
 
	// ������ʽSOCKET
	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

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

	// ����Ҫ���͵���Ϣ 
	string indata;
	cin >> indata;

	// stringתconst char*
	const char* sendData;
	sendData = indata.c_str();

	// ������Ϣ
	send(sclient, sendData, strlen(sendData), 0);

	// ������Ϣ
	char recData[255];
	int ret = recv(sclient, recData, 255, 0);
	/* ���ͣ�
		send()������������ָ����socket�����Է�����
		recv()�������նԷ�������������Ϣ
		int send(int s, const void * msg, int len, unsigned int flags)
		int recv(int s, const void * msg, int len, unsigned int flags)
		sΪ�ѽ��������ӵ�socket��msgָ����Ϣ���ݣ�ָ��char����ͷ������len��Ϊ���ݳ��ȣ�����flagsһ����0
		�ɹ��򷵻�ʵ�ʴ��ͳ�ȥ���ַ�����ʧ�ܷ���-1
	*/

	// ������ճɹ��������Ϣ
	if (ret > 0) {
		recData[ret] = 0x00; // ��Ϣ������ʶ��
		printf("\n�յ�����Ϣ��\n%s\n",recData);
	}

	// �ر�����
	closesocket(sclient);

	// �ͷ�Winsock��
	WSACleanup();
	return 0;
}
