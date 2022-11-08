#pragma once
#include <iostream>
#define hstring_no_char -1
//#define NULL 
class hstring {
private:
	unsigned short	recordStringMemorysize;//该变量记录长度以此减少内存重新分配
	unsigned short unsignedStringLength;
	char* stringContent;
	unsigned short getStringLength(const char* string) const;
	void copyStringLength(char* target, const char* source);

public:
	char* returnStrContent() { return stringContent; }
	//void* mymemcpy(void* dest, const void* src, size_t n);这个该有的是memcpy的手动实现函数声明
	~hstring();
	hstring();
	hstring(const char* string);//利用字符串构造
	hstring(const hstring& string);//利用类构造
	hstring& operator=(const hstring& string);//实现将一个类的实例等于另一个类的实例
	//hstring& operator=(const int& string);这两段是赋值运算符的作业，待完成
	//hstring& operator=(const long long& string);
	//hstring& operator=(const float string);
	//bool resetMemcory(unsigned short);//重置缓冲区大小
	//unsigned short getMemcory();//获取当前缓冲区大小
	//unsigned short getstringlength();//获取字符串长度
	//const char& operator[](const char*key)const;//返回指定位置后的内容
	hstring& operator<<(const hstring& string);
	hstring& operator+(const hstring& string);//通过左移运算为内容增加字符串
	hstring& operator+(unsigned value);//将字符串转换为数字
	const char& operator[](const unsigned short index )const;//不支持中文
	//wchar_t operator[](const unsigned short index)const;//
	hstring operator()(const unsigned short startCutPoint, const unsigned short length);
	operator int();//将正负数字转换成字符串
};
std::ostream& operator<<(std::ostream& _cout, hstring& _string);
std::ostream& operator<<(std::ostream& _cout, hstring&& _string);
std::istream& operator>>(std::istream& _cin, hstring& _string);