#include<iostream>
#include"md5.h"
using namespace std;
int main(void)
{
	cout<<"----------------- TEST -----------------\n";
	string str;
	while (1)
	{
		cout<<"ԭ: ";
		getline(cin,str);
		string str2=base64encode(str);
		string str3=urlencode(str); 
		cout<<"md5���: "<<md5(str)<<"\nbase64��������"<<str2<<"��������"<<base64decode(str2 )<<"\nurl����Ϊ"<<str3;
		cout<<"\n-----------------------\n";
		
	}

	return 0;
}
