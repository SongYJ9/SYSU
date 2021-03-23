#include <bits/stdc++.h>
#include <process.h>
#include <ws2tcpip.h> // 编译选项添加 -lWs2_32
#pragma comment(lib,"ws2_32.lib")

void sen(SOCKET sock, char* msg){
	printf(">> %s",msg);
	send(sock,msg,strlen(msg),0);
}

void rec(SOCKET sock, char* buf){
	int re = recv(sock,buf,10000000,0);
	buf[re] = '\0';
	printf(buf);
}

SOCKET dataConn(char* msg) {
	SOCKET datasock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	int ip1,ip2,ip3,ip4,port1,port2;
	char *str = strrchr(msg,'(');
	char dataip[100];
	
	// 提取数据连接的ip和端口号 
	sscanf(str,"(%d,%d,%d,%d,%d,%d)",&ip1,&ip2,&ip3,&ip4,&port1,&port2);
	sprintf(dataip,"%d.%d.%d.%d",ip1,ip2,ip3,ip4);
	int dataport = port1*256+port2;
	sockaddr_in datasin; 
	datasin.sin_family = AF_INET;							 
	datasin.sin_addr.s_addr = inet_addr(dataip);				 
	datasin.sin_port = htons(dataport);
	connect(datasock,(sockaddr*)&datasin, sizeof(datasin));
	return datasock;
}

int saveFile(SOCKET sock, char* fileName) {
	int filesize = 0,len = 0;
	static char filebuf[10000001];
	FILE *destfile = fopen(fileName,"wb");
	while (len = recv(sock,filebuf,10000000,0)){
		filesize += len;
		fwrite(filebuf,1,len,destfile);
	}
	fclose(destfile);
	return filesize;
}

int main(int argc,char **argv) {
	if (argc != 4) return 0;
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 0), &wsadata);
	struct addrinfo *host;
	getaddrinfo(argv[1], "21", NULL, &host);
	static char buf[10000000];
	
	// 连接服务器 
	SOCKET sock = socket(host->ai_family, host->ai_socktype, host->ai_protocol);
	if (connect(sock, host->ai_addr, host->ai_addrlen) == SOCKET_ERROR) {
		printf("Connect unsuccessfully.\n");
		return 0;
	}
	
	rec(sock,buf);
	
	// user net
	strcpy(buf,"user net\r\n");
	sen(sock,buf);
	rec(sock,buf);
	
	// pass 123456
	strcpy(buf,"pass 123456\r\n");
	sen(sock,buf);
	rec(sock,buf);
	
	// pasv
	strcpy(buf,"pasv\r\n");
	sen(sock,buf);
	rec(sock,buf);
	SOCKET datasock = dataConn(buf);
	
	// retr + 文件名 
	sprintf(buf,"retr %s\r\n",argv[2]);
	sen(sock,buf);
	rec(sock,buf);
	int filesize = saveFile(datasock,argv[3]);
	
	// quit
	strcpy(buf,"quit\r\n");
	sen(sock,buf);
	rec(sock,buf);
	
	closesocket(datasock);
	closesocket(sock);                            
	WSACleanup();
	return 0;
}
