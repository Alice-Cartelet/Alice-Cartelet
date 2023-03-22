#include<stdio.h>
#include<iostream>
#include<time.h>
using namespace std;
#include<windows.h>
int main()
{
	MessageBox(NULL,"首次启动，需进行配置操作。","提示",MB_TASKMODAL|MB_ICONINFORMATION); 
			system("cls");
			int i=0;
			while(i<=100)
			{
				cout<<"我们正在准备 "<<i<<"%";
				system("cls");
				i++;
			}
			cout<<endl<<"正在创建记录文档...";
			Sleep(1000);
			freopen("D:\\intjz.ini","w",stdout);
			for(int io=0;io<=212;io++)
			{
				char wue;
				wue=rand()%100;
				cout<<wue;				
			}
			system("attrib D:\\intjz.ini +h +r +s");
			freopen("D:\\记账.ini","w",stdout);			
			time_t t;
			time(&t);
			cout<<"0  Time stamp："<<t; 
			Sleep(1000);
			MessageBox(NULL,"完成！请重启程序！记录文件位于D盘目录下，名称：记账.ini","提示",MB_TASKMODAL|MB_ICONINFORMATION); 
			return 0; 
}
