#include <iostream>
#include <string>
#include <bitset> 
using namespace std;

string encrypt(const string& plaintext, const string& key) {
    string ciphertext;
    for (size_t i = 0; i < plaintext.length(); ++i) {char encrypted_char = plaintext[i] ^ key[i % key.length()];
	ciphertext += bitset<8>(encrypted_char).to_string();
	}
    return ciphertext;
}
int main() 
{
    string plaintext;
    string key;
    cout<< "------------------------����---------------------"<<endl; 
    cout << "��������Կ��";
    getline(cin, key);
    for(int i=1;i<=2;)
	{ 
    	cout << "������Ҫ���ܵ����ģ�";
    	getline(cin, plaintext);
    	string ciphertext = encrypt(plaintext, key);
    	cout << "���ܺ�����ģ�" << ciphertext << endl;
	}
    return 0;
}

