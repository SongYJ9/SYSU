#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include "conio.h"
#pragma comment(lib,"ws2_32.lib")

int main() {

	// 加载Winsock库
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	WSAStartup(sockVersion, &wsaData);

	// 构造流式SOCKET
	SOCKET serSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// 绑定IP和端口
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(50500);
	serAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	// 开始绑定
	bind(serSocket, (sockaddr*)&serAddr, sizeof(serAddr));

	// 启动服务器
	sockaddr_in remoteAddr;
	int nAddrLen = sizeof(remoteAddr);
	printf("服务器已启动！\n\n");

	// 循环接收数据 
	while (!_kbhit()) { // 如果检测到按键，则接收一次数据后退出循环

		char* pts;
		time_t now;

		// 接收数据
		char recvData[255];
		int ret = recvfrom(serSocket, recvData, 255, 0, (sockaddr*)&remoteAddr, &nAddrLen);
		unsigned int tem;

		// 如果接收成功，输出信息
		if (ret > 0) {
			recvData[ret] = 0x00;
			(void)time(&now); // 取得系统时间
			pts = ctime(&now); // 把时间转换为字符串
			tem = remoteAddr.sin_addr.s_addr;
			printf("收到信息：%s\n收到时间：%s客户端IP地址: %d.%d.%d.%d\n客户端端口号: %d\n\n",
				recvData, pts, (tem << 24) >> 24, (tem << 16) >> 24, (tem << 8) >> 24, tem >> 24, remoteAddr.sin_port);
		}

		// 发送信息
		char sendData[200];
		sprintf(sendData, "信息：%s\n时间：%s客户端IP地址: %d.%d.%d.%d\n客户端端口号: %d\n\n",
			recvData, pts, (tem << 24) >> 24, (tem << 16) >> 24, (tem << 8) >> 24, tem >> 24, remoteAddr.sin_port);
		sendto(serSocket, sendData, strlen(sendData), 0, (sockaddr*)&remoteAddr, nAddrLen);
	}

	// 关闭接收
	closesocket(serSocket);

	// 释放Winsock库
	WSACleanup();
	return 0;
}
