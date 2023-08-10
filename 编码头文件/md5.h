#ifndef INDEX_H
#define INDEX_H
#include <iostream>
#include <string>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <sstream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cctype>
using namespace std;
//url±àÂë²¿·Ö 

string urlencode(const string &input) 
{
    ostringstream escaped;
    escaped.fill('0');
    escaped<<hex;
    for (size_t i=0;i<input.length();++i) 
	{
        char c=input[i];
        if(isalnum(c)||c=='-'||c=='_'||c=='.'||c=='~')
		{
            escaped<<c;
        } 
		else 
		{
            escaped<<uppercase;
            escaped<<'%'<<setw(2)<<int(static_cast<unsigned char>(c));
            escaped<<nouppercase;
        }
    }
    return escaped.str();
}


//base64decode


string base64decode(const string &input) 
{
    const string base64_chars="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char base64_lookup[256]={0};
    for(size_t i=0;i<base64_chars.length();++i) 
	{
        base64_lookup[base64_chars[i]]=static_cast<char>(i);
    }
    string output;
    int val=0,bits=-8;
    for (size_t i=0;i<input.length();++i)
	{
        char c=input[i];
        if (base64_lookup[c]==0) 
		{
            continue;
        }
        val=(val<<6)+base64_lookup[c];
        bits+=6;
        if(bits>=0) 
		{
            output.push_back(static_cast<char>((val>>bits)&0xFF));
            bits-=8;
        }
    }
    return output;
}

//base64encode
string base64encode(const string &input)
{
    const string base64_chars="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    ostringstream encoded_stream;
    unsigned char three_bytes[3];
    int i=0;
    for (string::const_iterator it=input.begin();it!=input.end();++it) 
	{
    	char c=*it;
        three_bytes[i++]=c;
        if (i == 3)
		{
            encoded_stream<<base64_chars[(three_bytes[0]&0xFC)>>2];
            encoded_stream<<base64_chars[((three_bytes[0]&0x03)<<4)+((three_bytes[1]&0xF0)>>4)];
            encoded_stream<<base64_chars[((three_bytes[1]&0x0F)<<2)+((three_bytes[2]&0xC0)>>6)];
            encoded_stream<<base64_chars[three_bytes[2]&0x3F];
            i = 0;
        }
    }
    if (i > 0) 
	{
        encoded_stream<<base64_chars[(three_bytes[0]&0xFC)>>2];
        if (i == 1) 
		{
            encoded_stream<<base64_chars[(three_bytes[0]&0x03)<<4];
            encoded_stream<<"==";
        } 
		else 
		{
            encoded_stream<<base64_chars[((three_bytes[0]&0x03)<<4)+((three_bytes[1]&0xF0)>>4)];
            encoded_stream<<base64_chars[(three_bytes[1]&0x0F)<<2];
            encoded_stream<<"=";
        }
    }
    return encoded_stream.str();
}


//md5¼ÓÃÜ 

const uint32_t T[64]={0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,0xa679438e,0x49b40821,0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,0xd62f105d,0x2441453,0xd8a1e681,0xe7d3fbc8,0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,0x289b7ec6,0xeaa127fa,0xd4ef3085,0x4881d05,0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391};
const unsigned int SHIFT[4][4]{{7,12,17,22},{5,9,14,20},{4,11,16,23},{6,10,15,21}};
const uint8_t PADDING[]={0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
inline uint32_t hs4(uint32_t x, unsigned int num)
{
	num&=31;
	return (x<<num)|(x>>(-num&31));
}

inline uint32_t hs2(int a, uint32_t b, uint32_t c, uint32_t d)
{
	switch(a)
	{
		case 3:
			return c^(b|~d);
		case 2:
			return b^c^d;
		case 1:
			return (b&d)|(c&~d);
		case 0:
			return (b&c)|(~b&d);
	}
	return 0;
}
inline unsigned int hs3(int a, int i)
{
	switch (a)
	{
		case 0:
			return i;
		case 1:
			return (1+5*i)%16;
		case 2:
			return (5+3*i)%16;
		case 3:
			return (7*i)%16;
	}
	return 0;
}
void hs1(int a, uint32_t b[4], const uint32_t c[16])
{
	for (int i=0;i<16;i++)
	{
		b[0]+=hs2(a,b[1],b[2],b[3]);
		b[0]+=c[hs3(a,i)];
		b[0]+=T[a*16 + i];
		b[0]=hs4(b[0],SHIFT[a][i%4]);
		b[0]+=b[1];
		uint32_t bCache=b[3];
		b[3]=b[2];
		b[2]=b[1];
		b[1]=b[0];
		b[0]=bCache;
	}
	return;
}
void Hash_MD5(uint32_t chain_vector[4],const uint32_t message_block[16])
{
	uint32_t buffer[4];
	memcpy(buffer,chain_vector,128/CHAR_BIT);
	for (int i=0;i<4;i++)
	{
		hs1(i,buffer,message_block);
	}
	for (int i=0;i<4;i++)
	{
		chain_vector[i]+=buffer[i];
	}
}
__uint128_t MD5(string _message)
{
	uint64_t messageLength=_message.length();
	uint64_t messageBitCount=messageLength*CHAR_BIT;
	int blockCount=(messageBitCount+64-1)/512+1;
	uint8_t message[64*blockCount];
	memcpy(message,_message.c_str(),messageLength);
	for (int i=messageLength,j=0;i<(64*blockCount-8);i++)
	{
		message[i]=PADDING[j++];
	}
	memcpy(message+(64*blockCount-8),&messageBitCount,64/CHAR_BIT);
	uint32_t *messageBuffer=new uint32_t[16];
	uint32_t res[4]={0x67452301,0xEFCDAB89,0x98BADCFE,0x10325476};
	for (int i=0;i<blockCount;i++)
	{
		memcpy(messageBuffer,message+64*i,64);
		Hash_MD5(res,messageBuffer);
	}
	__uint128_t md5=0;
	for (int i=0;i<4;i++)
	{
		md5+=(__uint128_t)res[i]<<(i*32);
	}
	delete[] messageBuffer;
	return md5;
}
string ss1;
char a[2];
string MD5_P(__uint128_t in)
{
	string ss; 
	unsigned char *ptr = (unsigned char *)&in;
	for (int i = 0; i < 16; i++)
	{
		sprintf(a,"%02x",ptr[i]);
		ss.append(a);
	}
	ss1=ss;
	return ss1;
}
string md5(string str)
{
	__uint128_t md5 = MD5(str);
	string sss;
	sss=MD5_P(md5);
	return sss;
}
#endif
