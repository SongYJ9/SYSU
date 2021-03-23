#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <io.h>

static char fileread[10000000];

int main() {
	struct FileStruct {
    	char fileName[300];
    	int fileSize;
	};
	char input[300],input2[300],input3[300]; // 目标文件夹、解压文件名、解压后的文件 
	 
	printf("输入目标文件夹：");
	scanf("%s",input);
	printf("输入要解压的文件名：");
	scanf("%s",input2);
	
	FILE* pFile = fopen(input2, "rb");
	FileStruct fileSave;
	while (fread(&fileSave, sizeof(FileStruct), 1, pFile) == 1) {
		sprintf(input3,"%s%s",input,fileSave.fileName); // 解压后的文件 = 目标文件夹 + 打包的文件名（内含斜杠 \ ） 
		FILE* file = fopen(input3, "wb"); // 新建文件  
		fread(fileread, fileSave.fileSize, 1, pFile); // 读取包中文件内容 
		fwrite(fileread, fileSave.fileSize, 1, file); // 写入新建的文件 
		fclose(file);
	} 
	fclose(pFile);
	printf("解压结束！\n");
}
