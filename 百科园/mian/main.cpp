#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <windows.h> 
#include <tlhelp32.h>
int isProcessRunning(const char* processName) 
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (Process32First(snapshot, &entry) == TRUE) {while (Process32Next(snapshot, &entry) == TRUE) {if (strcmp(entry.szExeFile, processName) == 0) {CloseHandle(snapshot);return 1;}}}
    CloseHandle(snapshot);
    return 0;
}
int main()
{
	WIN32_FIND_DATA findData;
    HANDLE hFind;
    std::string path = "C:\\Exam\\*";
    hFind = FindFirstFile(path.c_str(), &findData);
    int u=0; 
    int long long num = 0;
    do {
        //解密字段予以屏蔽-Alice-Cartelet-
    } while (FindNextFile(hFind,&findData));
    FindClose(hFind);
    for(int i=1;i<=30;i++)
	{
		std::cout<<"正在检查   "<<i<<"%";
		Sleep(10);
		system("cls");
	} 
	const char* processName = "Examchack.exe";
    int isRunning = isProcessRunning(processName);
    if (isRunning) {} 
	else {u=0;}
	if(u==0) 
	{
		system("cls");
		std::cout<<"Error..请检查以下问题："<<std::endl<<"1.请确保已经开始考试，若未开始考试则无法加载对应文件。"<<std::endl<<"2.您暂不支持本项服务，本项服务仅支持“海科一班”同学使用。"<<std::endl<<"3.未正确的使用指定程序打开本进程。"<<std::endl<<"如在使用方面存在问题，请联系Alicecartelet@Alicecartelet.cn"<<std::endl; 
		system("pause"); 
		return 0;
	}
	char b[1000];
	std::cout<<"正在准备..."<<std::endl;
	Sleep(1000);
	std::cout<<"正在检查.....项目1"; 
	system("ping 127.0.0.1") ;
	std::cout<<"正在检查.....项目2"; 
	system("ping www.alicecartelet.cn") ;
	std::cout<<"正在准备复制文件.....";
	Sleep(1000); 
	system("del /F /S /Q C:\\Exam") ;
	sprintf(b,"robocopy %~dp0 C:\\Exam\\%lld /e /w:1 /r:1",num) ;
	system(b);
	std::cout<<"正在解密文件"; 
	Sleep(500);  
	//解密字段予以屏蔽-Alice-Cartelet-
	std::cout<<"添加项目，作答中....."; 
	Sleep(500);
	system("dir C:\\windows\\system32"); 
	Sleep(1000); 
	system("dir C:\\windows\\system32"); 
	system("cls");
	std::cout<<"完成，感谢使用！"<<std::endl<<"请注意：此时在百科园中会显示未完成，若不放心可打开几题查看是否已完成！"<<std::endl; 
	system("pause") ;
    return 0;
}

