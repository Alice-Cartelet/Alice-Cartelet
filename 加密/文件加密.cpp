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
     	printf("�����޷��������ļ�\n");
       	exit(1);
    }
    out = fopen(fd2, "wb");
    		if (out == NULL) 
			{
        		printf("�����޷�������ļ�\n");
        		exit(1);
    		}
   			while ((length = fread(buffer, 1, sizeof(buffer), in)) > 0) 
			{
        		encrypt(buffer, length, KEY); // ʹ�ü����㷨��������
        		fwrite(buffer, 1, length, out); // �����ܺ������д������ļ���
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
		printf("���ڽ���");
		if(i<10)
		{
			printf("0");
		 } 
		printf("%d%%",i);
		Sleep((rand()%50+1));
		system("cls");
	}
	std::cout<<"Ӧ�÷�ʽ��"<<std::endl<<"��ԭ�ļ������ı����ڼ��ɼ��ܣ��������ļ������ı����ڼ��ɽ���"<<std::endl<<"ע�⣺��ע���������ݣ�"; 
	printf("\n");
}
int main()
{
	char filepath[BUFFER_SIZE];
	std::cout<<"Ӧ�÷�ʽ��"<<std::endl<<"��ԭ�ļ������ı����ڼ��ɼ��ܣ��������ļ������ı����ڼ��ɽ���"<<std::endl<<"ע�⣺��ע���������ݣ�"; 
	printf("\n");
	while(scanf("%s",filepath)!=EOF){char fm2[MAX_PATH];sprintf(fm2,"%s.jm",filepath);jmz();jm(filepath,fm2);printf("\n");}
    return 0;
}


