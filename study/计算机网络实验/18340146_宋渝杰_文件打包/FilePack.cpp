#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <io.h>

static char fileread[10000000]; // �����ȡ���ļ����� 
static char Name[100][300];     // �ж��Ƿ����� 
int count[100];					// �������� 
int x=0;						// �ļ�����������ֻ��һ�Σ� 

int main() {
	struct FileStruct {
    	char fileName[300];
    	int fileSize;
	};
	int i=1,j;
	char input[300],input2[300]; // Ŀ���ļ���������ļ��� 
	for (j=0; j<100; j++) count[j] = 1; // ��ʼ�� 
	
	printf("����Ŀ���ļ�����");
	scanf("%s",input);
	FILE* pFile = fopen(input, "wb");
	
	FileStruct fileSave;
	printf("����Ҫ�����#%d�ļ���",i);
	scanf("%s",input2);
	while (strcmp(input2, "exit") != 0) {
		strcpy(fileSave.fileName,strrchr(input2,'\\')); // �ļ���ȥ��Ŀ¼��������б�� \ �� 
		
		FILE* file = fopen(input2, "rb");
		fileSave.fileSize = filelength(fileno(file)); // ��ȡ�ļ���С 
		if (fread(fileread, fileSave.fileSize, 1, file) != 1) { // ��ȡ�ļ����� 
			printf("file read error!\n");
		}
		fclose(file);
		
		for (j=0; j<x; j++) {
			if (strcmp(input2,Name[j]) == 0) { // �ж����� 
				count[j]++;
				char p[300];
				strcpy(p,strrchr(input2,'.'));
				sprintf(strrchr(input2,'.'),"(%d)%s",count[j],p); // ���루2����ʶ 
				goto th; 
			} 
		}
		strcpy(Name[x],input2); // û��������� 
		x++;
		
		th:
		strcpy(fileSave.fileName,strrchr(input2,'\\')); // �����ļ���
		if (fwrite(&fileSave, sizeof(FileStruct), 1, pFile) != 1) { // д�ļ� struct 
			printf("file write error!\n");
		}
		if (fwrite(fileread, fileSave.fileSize, 1, pFile) != 1) { // д�ļ����� 
			printf("file write error!\n"); 
		}
		i++;
		printf("����Ҫ�����#%d�ļ���",i);
		scanf("%s",input2);
	}
	fclose(pFile);
	printf("�����ϣ�\n");
}
