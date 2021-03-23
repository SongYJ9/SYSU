#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <io.h>

static char fileread[10000000]; // 保存读取的文件内容 
static char Name[100][300];     // 判断是否重名 
int count[100];					// 重名次数 
int x=0;						// 文件个数（重名只算一次） 

int main() {
	struct FileStruct {
    	char fileName[300];
    	int fileSize;
	};
	int i=1,j;
	char input[300],input2[300]; // 目标文件名、打包文件名 
	for (j=0; j<100; j++) count[j] = 1; // 初始化 
	
	printf("输入目标文件名：");
	scanf("%s",input);
	FILE* pFile = fopen(input, "wb");
	
	FileStruct fileSave;
	printf("输入要打包的#%d文件：",i);
	scanf("%s",input2);
	while (strcmp(input2, "exit") != 0) {
		strcpy(fileSave.fileName,strrchr(input2,'\\')); // 文件名去除目录（但保留斜杠 \ ） 
		
		FILE* file = fopen(input2, "rb");
		fileSave.fileSize = filelength(fileno(file)); // 读取文件大小 
		if (fread(fileread, fileSave.fileSize, 1, file) != 1) { // 读取文件内容 
			printf("file read error!\n");
		}
		fclose(file);
		
		for (j=0; j<x; j++) {
			if (strcmp(input2,Name[j]) == 0) { // 判断重名 
				count[j]++;
				char p[300];
				strcpy(p,strrchr(input2,'.'));
				sprintf(strrchr(input2,'.'),"(%d)%s",count[j],p); // 加入（2）标识 
				goto th; 
			} 
		}
		strcpy(Name[x],input2); // 没有重名情况 
		x++;
		
		th:
		strcpy(fileSave.fileName,strrchr(input2,'\\')); // 更新文件名
		if (fwrite(&fileSave, sizeof(FileStruct), 1, pFile) != 1) { // 写文件 struct 
			printf("file write error!\n");
		}
		if (fwrite(fileread, fileSave.fileSize, 1, pFile) != 1) { // 写文件内容 
			printf("file write error!\n"); 
		}
		i++;
		printf("输入要打包的#%d文件：",i);
		scanf("%s",input2);
	}
	fclose(pFile);
	printf("打包完毕！\n");
}
