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
	char input[300],input2[300],input3[300]; // Ŀ���ļ��С���ѹ�ļ�������ѹ����ļ� 
	 
	printf("����Ŀ���ļ��У�");
	scanf("%s",input);
	printf("����Ҫ��ѹ���ļ�����");
	scanf("%s",input2);
	
	FILE* pFile = fopen(input2, "rb");
	FileStruct fileSave;
	while (fread(&fileSave, sizeof(FileStruct), 1, pFile) == 1) {
		sprintf(input3,"%s%s",input,fileSave.fileName); // ��ѹ����ļ� = Ŀ���ļ��� + ������ļ������ں�б�� \ �� 
		FILE* file = fopen(input3, "wb"); // �½��ļ�  
		fread(fileread, fileSave.fileSize, 1, pFile); // ��ȡ�����ļ����� 
		fwrite(fileread, fileSave.fileSize, 1, file); // д���½����ļ� 
		fclose(file);
	} 
	fclose(pFile);
	printf("��ѹ������\n");
}
