#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <time.h>
#pragma comment(lib,"ws2_32.lib")

int main() {

	// 加载Winsock库
	WORD socketVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	WSAStartup(socketVersion, &wsaData);

	// 构造流式SOCKET
	SOCKET sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// 配置要连接的地址和端口 
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(50500);
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int len = sizeof(sin);

	// 输入要发送的信息 
	char sendData[200];
	scanf("%s", sendData);

	// 发送信息
	int sen = sendto(sclient, sendData, strlen(sendData), 0, (sockaddr*)&sin, len);
	if (sen == SOCKET_ERROR) {
		printf("发送失败，错误号：%d\n", WSAGetLastError());
	}

	// 接收信息
	char recvData[255];
	int ret = recvfrom(sclient, recvData, 255, 0, (sockaddr*)&sin, &len);

	// 如果接收成功，输出信息
	if (ret > 0) {
		recvData[ret] = 0x00; // 信息结束标识符
		printf("\n收到的消息：\n%s\n", recvData);
	}
	else {
		printf("接收失败，错误号：%d\n", WSAGetLastError());
	}

	// 关闭连接
	closesocket(sclient);

	// 释放Winsock库
	WSACleanup();
	return 0;
}
