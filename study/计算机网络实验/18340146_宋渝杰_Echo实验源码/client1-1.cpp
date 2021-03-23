#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <cstring>
#include <string>
#include <time.h>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main() {

	// 加载Winsock库
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	WSAStartup(sockVersion, &data);
 
	// 构造流式SOCKET
	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 配置要连接的地址和端口
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(50500);
	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	// 如果连接失败，提示信息并结束
	if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR) {
		printf("Error: %d.\n", GetLastError());
		// 关闭连接 
		closesocket(sclient);
		return 0;
	}

	// 输入要发送的信息 
	string indata;
	cin >> indata;

	// string转const char*
	const char* sendData;
	sendData = indata.c_str();

	// 发送信息
	send(sclient, sendData, strlen(sendData), 0);

	// 接收信息
	char recData[255];
	int ret = recv(sclient, recData, 255, 0);
	/* 解释：
		send()用来将数据由指定的socket传给对方主机
		recv()用来接收对方主机传来的消息
		int send(int s, const void * msg, int len, unsigned int flags)
		int recv(int s, const void * msg, int len, unsigned int flags)
		s为已建立好连接的socket，msg指向信息内容（指向char数组头部），len则为数据长度，参数flags一般设0
		成功则返回实际传送出去的字符数，失败返回-1
	*/

	// 如果接收成功，输出信息
	if (ret > 0) {
		recData[ret] = 0x00; // 信息结束标识符
		printf("\n收到的消息：\n%s\n",recData);
	}

	// 关闭连接
	closesocket(sclient);

	// 释放Winsock库
	WSACleanup();
	return 0;
}
