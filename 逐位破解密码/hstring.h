#pragma once
#include <iostream>
#define hstring_no_char -1
//#define NULL 
class hstring {
private:
	unsigned short	recordStringMemorysize;//�ñ�����¼�����Դ˼����ڴ����·���
	unsigned short unsignedStringLength;
	char* stringContent;
	unsigned short getStringLength(const char* string) const;
	void copyStringLength(char* target, const char* source);

public:
	char* returnStrContent() { return stringContent; }
	//void* mymemcpy(void* dest, const void* src, size_t n);������е���memcpy���ֶ�ʵ�ֺ�������
	~hstring();
	hstring();
	hstring(const char* string);//�����ַ�������
	hstring(const hstring& string);//�����๹��
	hstring& operator=(const hstring& string);//ʵ�ֽ�һ�����ʵ��������һ�����ʵ��
	//hstring& operator=(const int& string);�������Ǹ�ֵ���������ҵ�������
	//hstring& operator=(const long long& string);
	//hstring& operator=(const float string);
	//bool resetMemcory(unsigned short);//���û�������С
	//unsigned short getMemcory();//��ȡ��ǰ��������С
	//unsigned short getstringlength();//��ȡ�ַ�������
	//const char& operator[](const char*key)const;//����ָ��λ�ú������
	hstring& operator<<(const hstring& string);
	hstring& operator+(const hstring& string);//ͨ����������Ϊ���������ַ���
	hstring& operator+(unsigned value);//���ַ���ת��Ϊ����
	const char& operator[](const unsigned short index )const;//��֧������
	//wchar_t operator[](const unsigned short index)const;//
	hstring operator()(const unsigned short startCutPoint, const unsigned short length);
	operator int();//����������ת�����ַ���
};
std::ostream& operator<<(std::ostream& _cout, hstring& _string);
std::ostream& operator<<(std::ostream& _cout, hstring&& _string);
std::istream& operator>>(std::istream& _cin, hstring& _string);