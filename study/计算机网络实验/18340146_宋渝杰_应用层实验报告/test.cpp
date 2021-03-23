#include <stdio.h>
#include <string.h>
#include <process.h>
#include <ws2tcpip.h> // 编译选项添加 -lWs2_32
#pragma comment(lib,"ws2_32.lib")
#define BUFLEN 10000000 

int endInput = 0;
int n;
SOCKET sock;

unsigned __stdcall recvMessage(void* n) {
	
	static char buf[BUFLEN];
	
	// 循环接收信息 
	while (endInput == 0) {
		int c = recv(sock, buf, BUFLEN, 0);
		if (c > 0) {
			buf[c] = 0; 
			printf("%s\n",buf);
		}
		else if (!c) {
			printf("Receive connect closed.\n");
			endInput = 1;
		}
		else if (c == SOCKET_ERROR) {
			printf("Receive Error: %d\n",GetLastError());
			endInput = 1;
		}
	}
	
	// 结束线程 
	return 0;
}

int main(int argc, char **argv) {
	
	if (argc < 3) {
		printf("Please input the IPAddress and PortNumber!\n");
		return 0;
	}
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 0), &wsadata);
	struct addrinfo *host;
	getaddrinfo(argv[1], argv[2], NULL, &host);
	static char buf[BUFLEN];
	
	// 连接服务器 
	sock = socket(host->ai_family, host->ai_socktype, host->ai_protocol);
	if (connect(sock, host->ai_addr, host->ai_addrlen) == SOCKET_ERROR) {
		printf("Connect unsuccessfully.\n");
		return 0;
	}
	
	// 创建接收信息线程 
	HANDLE h = (HANDLE)_beginthreadex(NULL, 0, &recvMessage, (void*)&n, 0, NULL);
	
	// 循环输入信息 
	while (endInput == 0 && gets(buf)) {
		
		int len = strlen(buf);
		buf[len] = '\r'; 
		buf[++len] = '\n';
		buf[++len] = 0;
		
		// 发送数据 
		int c = send(sock, buf, len, 0);
		if (c == 0) {
			printf("Send connect closed.\n");
			endInput = 1;
		}
		else if (c == SOCKET_ERROR) {
			printf("Send Error: %d\n",GetLastError());
			endInput = 1;
		}	
	}
	
	shutdown(sock,SD_SEND); 
	CloseHandle(h);
	closesocket(sock);
	freeaddrinfo(host);
	WSACleanup();
	return 0;	
}
