#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h> 
#include <iostream>
#define BUFFER_SIZE 1024
#define KEY 0xC7 
void encrypt(unsigned char* data, int length, unsigned char key)
{
    for (int i = 0; i < length; i++) {
        data[i] ^= key;
        key = (key << 1) | (key >> 7);
    }
}
void decrypt(unsigned char* data, int length, unsigned char key)
{
    for (int i = 0; i < length; i++) {
        data[i] ^= key;
        key = (key << 1) | (key >> 7);
    }
}
void jm(char *fd,char *fd2)
{
    FILE* in, * out;
    unsigned char buffer[1024];
   	size_t length;
    in = fopen(fd, "rb");
    if (in == NULL)
	{
     	printf("错误：无法打开输入文件\n");
       	exit(1);
    }
    out = fopen(fd2, "wb");
    		if (out == NULL) 
			{
        		printf("错误：无法打开输出文件\n");
        		exit(1);
    		}
   			while ((length = fread(buffer, 1, sizeof(buffer), in)) > 0) 
			{
        		encrypt(buffer, length, KEY); // 使用加密算法加密数据
        		fwrite(buffer, 1, length, out); // 将加密后的内容写入输出文件中
    		}
    		fclose(in);
    		fclose(out);
    return;
}
void jmz()
{
	time_t t;
	time(&t);
	srand((unsigned int)time(0));
	for(int i=1;i<=100;i++)
	{
		printf("正在进行");
		if(i<10)
		{
			printf("0");
		 } 
		printf("%d%%",i);
		Sleep((rand()%50+1));
		system("cls");
	}
	std::cout<<"应用方式："<<std::endl<<"将原文件拖入文本框内即可加密，将加密文件拖入文本框内即可解密"<<std::endl<<"注意：请注意自留备份！"; 
	printf("\n");
}
int main()
{
	char filepath[BUFFER_SIZE];
	std::cout<<"应用方式："<<std::endl<<"将原文件拖入文本框内即可加密，将加密文件拖入文本框内即可解密"<<std::endl<<"注意：请注意自留备份！"; 
	printf("\n");
	while(scanf("%s",filepath)!=EOF){char fm2[MAX_PATH];sprintf(fm2,"%s.jm",filepath);jmz();jm(filepath,fm2);printf("\n");}
    return 0;
}


