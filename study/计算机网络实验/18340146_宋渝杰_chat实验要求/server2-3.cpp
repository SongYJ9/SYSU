/* 
	chat实验 (3) 服务器程序 
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
	
	// 与第 num 个客户端建立连接，并保存信息 
	int num = *((int *)n);
	char s1[] = "Enter!";
	char s2[] = "Leave!";
	char revData[255];
	unsigned int tem = remoteAdd[num].sin_addr.s_addr; // 保存ip
	
	// 标识该客户端为连接状态 
	judge[num] = 1;
	
	// 取得系统时间 
	char* pts;
	time_t now;
	(void)time(&now);
	pts = ctime(&now);
	
	// 服务器输出 Enter! 信息 
	char sendData[200];
	sprintf(sendData, "IP地址: %d.%d.%d.%d  端口号: %d\n时间：%s信息：%s",
		(tem << 24) >> 24, (tem << 16) >> 24, (tem << 8) >> 24, tem >> 24, remoteAdd[num].sin_port, pts, s1);
	cout << sendData << endl << endl;
	
	// 把信息发给所有客户端 
	for (int i=1; i<200; i++)
		if (judge[i])
			send(sClients[i], sendData, strlen(sendData), 0);
	
	// 循环接收信息 
	while (1) {
		
		int ret = recv(sClients[num], revData, 255, 0);
		
		// 如果接收成功，输出信息
		if (ret > 0) {
			
			// 信息结束标识符
			revData[ret] = 0x00;
			
			// 取得系统时间 
			(void)time(&now);
			pts = ctime(&now);
			
			// 服务器输出收到信息 
			string s(revData);
			if (s == "exit") {
				s = "Leave!";
				strcpy(revData,"Leave!");
			}
			printf("IP地址: %d.%d.%d.%d  端口号: %d\n时间：%s信息：%s\n\n",
				(tem << 24) >> 24, (tem << 16) >> 24, (tem << 8) >> 24, tem >> 24, remoteAdd[num].sin_port, pts, revData);
				
			// 发送信息 
			char sendData[200];
			sprintf(sendData, "IP地址: %d.%d.%d.%d  端口号: %d\n时间：%s信息：%s",
				(tem << 24) >> 24, (tem << 16) >> 24, (tem << 8) >> 24, tem >> 24, remoteAdd[num].sin_port, pts, revData);
			for (int i=1; i<200; i++)
				if (judge[i])
					send(sClients[i], sendData, strlen(sendData), 0);
					
			// 如果收到的是 Leave! 则中断连接 
			if (s == "Leave!") {
				judge[num] = 0;
				break;
			}
		}
	}
	
	// 中断连接，线程结束 
	closesocket(sClients[num]);
	return 0;
} 

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
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	int num = 0;
	printf("服务器已启动！\n\n");

	// 循环接收数据 
	while (++num) {
		sClients[num] = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
		remoteAdd[num] = remoteAddr;
		int x = num;
		h[num] = (HANDLE)_beginthreadex(NULL, 0, &newConnect, (void *)&x, 0, NULL); 
	}

	// 关闭接收 
	closesocket(slisten);

	// 释放Winsock库
	WSACleanup();
	return 0;
}
