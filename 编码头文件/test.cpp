#include<iostream>
#include"md5.h"
using namespace std;
int main(void)
{
	cout<<"----------------- TEST -----------------\n";
	string str;
	while (1)
	{
		cout<<"原: ";
		getline(cin,str);
		string str2=base64encode(str);
		string str3=urlencode(str); 
		cout<<"md5结果: "<<md5(str)<<"\nbase64加码结果："<<str2<<"解码结果："<<base64decode(str2 )<<"\nurl编码为"<<str3;
		cout<<"\n-----------------------\n";
		
	}

	return 0;
}
