/* 
	chat实验 (5) 客户端程序 
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
		
		// 接收信息
		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		
		// 如果接收成功，输出信息
		if (ret > 0) {
			recData[ret] = 0x00; // 信息结束标识符
			printf("%s\n\n",recData);
		}
	}
	return 0;
}

int main() {

	// 加载Winsock库
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	WSAStartup(sockVersion, &data);
 
	// 构造流式SOCKET
	sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 配置要连接的地址和端口
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(50500);
	serAddr.sin_addr.S_un.S_addr = inet_addr("103.26.79.35");

	// 如果连接失败，提示信息并结束
	if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR) {
		printf("Error: %d.\n", GetLastError());
		// 关闭连接 
		closesocket(sclient);
		return 0;
	}
	
	th = (HANDLE)_beginthreadex(NULL, 0, &receive, (void *)&n, 0, NULL); 
	
	while (1) {
		
		// 输入要发送的信息 
		string indata;
		getline(cin,indata);
		
		// string转const char*
		const char* sendData;
		sendData = indata.c_str();

		// 发送信息
		send(sclient, sendData, strlen(sendData), 0);
		
		// 如果关闭客户端，则中断线程 
		if (indata == "exit") {
			CloseHandle(th);
			break;
		}
	}
	
	WaitForSingleObject(th, INFINITE); 

	// 关闭连接
	closesocket(sclient);

	// 释放Winsock库
	// WSACleanup();
	cout << "按任意键结束：";
	getchar();
	getchar();
	return 0;
}
