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
    cout<< "------------------------加密---------------------"<<endl; 
    cout << "请输入密钥：";
    getline(cin, key);
    for(int i=1;i<=2;)
	{ 
    	cout << "请输入要加密的明文：";
    	getline(cin, plaintext);
    	string ciphertext = encrypt(plaintext, key);
    	cout << "加密后的密文：" << ciphertext << endl;
	}
    return 0;
}

