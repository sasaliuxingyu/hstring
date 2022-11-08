#include "hstring.h"
#include<iostream>
//#define NULL=NULL
unsigned short hstring::getStringLength(const char* string) const
{
	unsigned short length{ 0 };
	for (; string[length++];);
	return length;
}

void hstring::copyStringLength(char* target, const char* source)
{
	unsigned short length{ getStringLength(source) };
	if (length > recordStringMemorysize) {
		//有严重的内存泄露问题
		delete[] stringContent;//为什么需要删除内存？
		stringContent = new char[length];
		recordStringMemorysize = length;
	}
	memcpy(stringContent, source, length);
	//void* mymemcpy(void* dest, const void* src, size_t n);这里该有的是memcpy的手动实现函数使用
	unsignedStringLength = length;//字符串长度重置
}
hstring::~hstring()
{
	if (stringContent != nullptr) delete[]stringContent;
}
hstring::hstring()
{
	recordStringMemorysize = 0x32;//将此处改为动态分配内存
	unsignedStringLength = 0;
	stringContent = new char[recordStringMemorysize];
}//构造函数前置缓冲区
hstring::hstring(const char* string) :hstring()
{
	copyStringLength(stringContent, string);
	//stringContent = (char*)string;
}
hstring::hstring(const hstring& string) :hstring()
{
	copyStringLength(stringContent, string.stringContent);
}
hstring& hstring::operator=(const hstring& string)
{
	copyStringLength(stringContent, string.stringContent);
	return (*this);//return *this返回的是当前对象的克隆或者本身（若返回类型为A， 则是克隆， 若返回类型为A&， 则是本身 ）。return this返回当前对象的地址（指向当前对象的指针）
}

hstring& hstring::operator<<(const hstring& string)
{
	unsigned short length = getStringLength(string.stringContent);
	length = unsignedStringLength + length - 1;
	if (unsignedStringLength + length - 1 > recordStringMemorysize) {
		char* stringContentCopy = stringContent;
		stringContent = new char[length];
		recordStringMemorysize = length;
		delete[] stringContentCopy;
	}
	memcpy(stringContent+unsignedStringLength-1, string.stringContent, length-unsignedStringLength+1);
	//void* mymemcpy(void* dest, const void* src, size_t n);这里该有的是memcpy的手动实现函数使用
	unsignedStringLength = length;//字符串长度重置
	return *this;
}



hstring& hstring::operator+(const hstring& string)
{
	return *this << string;
}

hstring& hstring::operator+(unsigned value)
{
	int length{ 0x1f };
	char string[0x20]{};
	unsigned short stringLength = unsignedStringLength + 0x20 - length - 1;
	bool isPositiveNumber = value >= 0;//是否为正数
	value = value * (isPositiveNumber * 2 - 1);
	do {
		string[--length] = value % 10 + 48;

	} while (value = value / 10);
	string[length = length - 1 * (1 - isPositiveNumber)] = '-' * (isPositiveNumber + 1) * (1 - isPositiveNumber) + string[length] * isPositiveNumber;
	if (stringLength > unsignedStringLength) {
		char* ptrStringX = stringContent;
		stringContent = new char[stringLength] {};
		unsignedStringLength = stringLength;
		memcpy(stringContent, ptrStringX, unsignedStringLength);
		delete[] ptrStringX;
	}
	memcpy(stringContent + unsignedStringLength - 1, string + length, 0x20 - length);
	unsignedStringLength = stringLength;//修正长度
	return *this;
}

const char& hstring::operator[](const unsigned short index)const
{
	if (index > unsignedStringLength) 
		return hstring_no_char;
	else 
		return stringContent[index];
}



hstring hstring::operator()(const unsigned short startCutPoint, const unsigned short length)
{
	unsigned int ActualOperationLength = (startCutPoint + length + 1) > unsignedStringLength ? (unsignedStringLength - startCutPoint) : length;
	char* newString=new char[ActualOperationLength+1];

	if (startCutPoint > unsignedStringLength-2) {
		return hstring("");
	}//判断内容开始位置正确与否
	memcpy(newString, stringContent+startCutPoint, ActualOperationLength + 1);
	newString[ActualOperationLength] = 0;
		return hstring(newString);
}

hstring::operator int()
{
	int value = 0;
	int i = stringContent[0] == '-';//如果有负号就跳过
	while (stringContent[i] >= '0' && stringContent[i] <= '9') {
		value = value * 10 + stringContent[i++] - 48;
	}
	value = value * ((stringContent[0] != '-') * 2 - 1);//还原负号
	return value;
}



std::ostream& operator<<(std::ostream& _cout, hstring& _string) {
	_cout << _string.returnStrContent();
	return _cout;
}

std::ostream& operator<<(std::ostream& _cout, hstring&& _string)
{
	_cout << _string.returnStrContent();
	return _cout;
}

std::istream& operator>>(std::istream& _cin, hstring& _string)
{
	char _sRead[0xff]{};
	_cin >> _sRead;
	_string = _sRead;
	return _cin;
}







//下面的东西后面补
//void* mymemcpy(void* dest, const void* src, size_t n)
//{
//	if (dest == NULL || src == NULL)
//		return NULL;
//	int* pDest = (int*)dest;
//	int* pSrc = (int*)src;
//	int iWordNum = n / 4;
//	int iSlice = n % 4;
//	while (iWordNum--)
//	{
//		*pDest++ = *pSrc++;
//	}
//	char* pcDest = (char*)pDest;
//	char* pcSrc = (char*)pSrc;
//
//	while (iSlice--)
//	{
//		*pcDest++ = *pcSrc++;
//	}
//
//	return dest;
//}
//memcpy 使用for循环实现的定义
