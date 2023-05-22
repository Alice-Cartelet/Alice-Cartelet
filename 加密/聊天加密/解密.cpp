#include <iostream>
#include <string>
#include <bitset> 
using namespace std;
string decrypt(const string& ciphertext, const string& key) {
    string plaintext;
    for (size_t i = 0; i < ciphertext.length(); i += 8) {
        string binary_byte = ciphertext.substr(i, 8);
        char decrypted_char = static_cast<char>(bitset<8>(binary_byte).to_ulong());
        char original_char = decrypted_char ^ key[i / 8 % key.length()];
        plaintext += original_char;}
    return plaintext;
    
}
int main() {
    string ciphertext;
    string cl="cls";
    string key;
    cout<< "------------------------����---------------------"<<endl; 
    cout <<"��������Կ��";
    getline(cin, key);
	for(int i=1;i<=2;)
	{
		cout<<"������ܺ�����ģ�";
   		getline(cin, ciphertext);
		string decrypted_text = decrypt(ciphertext, key);
    	cout << "���ܺ�����ģ�" << decrypted_text << endl;
	} 
    return 0;
}

