#include<iostream>
#include<time.h>
#include<windows.h>
#include<fstream>
#include<string>
using namespace std;
int main()
{
	system("cls");
	freopen("D:\\记账.ini","r",stdin);
	int awm=0;
	for(int io=0;io<=212;io++)
	{
		int ue;
		cin>>ue;
		ue=ue+rand()%10092; 
	}
	cin>>awm;
	awm=awm/361;
	for(int i=1;i<=awm+1;i++)
	{
		int uw=0;
		cin>>uw;
	}
	int jsj=0; 
	cin>>jsj;
	jsj=jsj/352;
	int y[jsj+1],d[jsj+1],m[jsj+1],je[jsj+1];
	int zj=0;
	for(int i=1;i<=jsj;i++)
	{
		cin>>y[i]>>m[i]>>d[i]>>je[i];
		m[i]=m[i]/7612;
				y[i]=y[i]/824;
				d[i]=d[i]/162;
				je[i]=je[i]/129;
			}
			for(int i=1;i<=jsj;i++)
			{
				zj=zj+je[i];
			}
			int yuii=0;
			for(int i=1;i<=5;i++)
			{
				yuii++;
				if(yuii==1)
				{
					cout<<"读取中.";
				}
				if(yuii==2)
				{
					cout<<"读取中..";
				} 
				if(yuii==3)
				{
					cout<<"读取中...";
				}
				if(yuii==4)
				{
					cout<<"读取中....";
				}
				if(yuii==5)
				{
					cout<<"读取中.....";
					yuii=0;
				}
				Sleep(200);
				system("cls");
			}
			for(int i=1;i<=jsj;i++)
			{
				cout<<"第";
				Sleep(10); 
				if(i<10)
				{
					cout<<" ";
				}
				Sleep(10); 
				if(i<100)
				{
					cout<<" ";
				}
				Sleep(10); 
				cout<<i;
				Sleep(10);
				cout<<"笔:";
				Sleep(10);
				cout<<y[i];
				Sleep(10);
				cout<<"年";
				if(m[i]<10)
				{
					cout<<"0";
				}
				Sleep(10);
				cout<<m[i];
				Sleep(10);
				cout<<"月";
				if(d[i]<10)
				{
					cout<<"0";
				}
				Sleep(10);
				cout<<d[i];
				Sleep(10);
				cout<<"日";
				Sleep(10);
				cout<<"       消";
				Sleep(10);
				cout<<"费";
				if(je[i]<10)
				{
					cout<<" ";
				}
				Sleep(10);
				if(je[i]<100)
				{
					cout<<" ";
				}
				Sleep(10);
				cout<<je[i];
				Sleep(10);
				cout<<"元"<<endl;
				Sleep(10);	
			} 
			cout<<"共";
			Sleep(50);
			cout<<"计";
			Sleep(50);
			cout<<"支";
			Sleep(50);
			cout<<"出";
			Sleep(50);
			cout<<"了";
			Sleep(50);
			cout<<jsj;
			Sleep(50);
			cout<<"笔";
	Sleep(50);
	cout<<"，";
	Sleep(50);
	cout<<"消";
	Sleep(50);
	cout<<"费";
	Sleep(50);
	cout<<zj;
	Sleep(50);
	cout<<"元"<<endl;
	freopen("CON", "r", stdin);
	system("pause"); 
} 
