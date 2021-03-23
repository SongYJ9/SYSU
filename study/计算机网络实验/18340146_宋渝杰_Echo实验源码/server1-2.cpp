#include <stdio.h>
#include <winsock2.h>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include "conio.h"
#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main() {

	// 加载Winsock库
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	WSAStartup(sockVersion, &data);

	// 构造流式SOCKET
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 绑定IP和端口
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons((u_short)atoi("50500"));

	// 开始绑定
	bind(slisten, (LPSOCKADDR)&sin, sizeof(sin));

	// 开始监听
	listen(slisten, 5);

	// 启动服务器
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[255];
	printf("服务器已启动！\n\n");

	// 循环接收数据 
	while (!_kbhit()) { // 如果检测到按键，则接收一次数据后退出循环

		char* pts;
		time_t now;

		// 检测客户端接入(失败则显示信息并重新循环)
		sClient = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
		if (sClient == INVALID_SOCKET) {
			printf("Accept Error !");
			break;
		}

		// 接收数据
		int ret = recv(sClient, revData, 255, 0);
		unsigned int tem;

		// 如果接收成功，输出信息
		if (ret > 0) {
			revData[ret] = 0x00; // 信息结束标识符
			(void)time(&now); // 取得系统时间
			pts = ctime(&now); // 把时间转换为字符串
			tem = remoteAddr.sin_addr.s_addr;
			printf("收到信息：%s\n收到时间：%s客户端IP地址: %d.%d.%d.%d\n客户端端口号: %d\n\n",
				revData, pts, (tem << 24) >> 24, (tem << 16) >> 24, (tem << 8) >> 24, tem >> 24, remoteAddr.sin_port);
		}

		// 发送信息 
		char sendData[200];
		sprintf(sendData, "信息：%s\n时间：%s客户端IP地址: %d.%d.%d.%d\n客户端端口号: %d\n\n",
			revData, pts, (tem << 24) >> 24, (tem << 16) >> 24, (tem << 8) >> 24, tem >> 24, remoteAddr.sin_port);
		send(sClient, sendData, strlen(sendData), 0);

		// 关闭连接
		closesocket(sClient);
	}

	// 关闭接收 
	closesocket(slisten);

	// 释放Winsock库
	WSACleanup();
	return 0;
}
