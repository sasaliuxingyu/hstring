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
		//�����ص��ڴ�й¶����
		delete[] stringContent;//Ϊʲô��Ҫɾ���ڴ棿��ɾ���ᷢ��ʲô���ҵ�stringContent����Զ�������趨���ڴ�ռ�ᷢ��ʲô����ָ�룿����ָ�����ң�
		stringContent = new char[length];
		recordStringMemorysize = length;
	}
	memcpy(stringContent, source, length);
	//void* mymemcpy(void* dest, const void* src, size_t n);������е���memcpy���ֶ�ʵ�ֺ���ʹ��
	unsignedStringLength = length;//�ַ�����������
}
hstring::~hstring()
{
	if (stringContent != nullptr) delete[]stringContent;
}
hstring::hstring()
{
	recordStringMemorysize = 0x32;//���˴���Ϊ��̬�����ڴ�
	unsignedStringLength = 0;
	stringContent = new char[recordStringMemorysize];
}//���캯��ǰ�û�����
hstring::hstring(const char* string) :hstring()
{
	copyStringLength(stringContent, string);
	//stringContent = (char*)string;
}
hstring::hstring(const hstring& string) :hstring()
{
	copyStringLength(stringContent, string.stringContent);
}
hstring::hstring(const int* string) :hstring()
{
	//copyStringLength(stringContent, stringContent);212312312312313254654
}
hstring& hstring::operator=(const hstring& string)
{
	copyStringLength(stringContent, string.stringContent);
	return (*this);//return *this���ص��ǵ�ǰ����Ŀ�¡���߱�������������ΪA�� ���ǿ�¡�� ����������ΪA&�� ���Ǳ��� ����return this���ص�ǰ����ĵ�ַ��ָ��ǰ�����ָ�룩
}

hstring& hstring::operator=(const int& string)
{
	
	copyStringLength(stringContent, string);//2312132564648
	return (*this);
}

hstring& hstring::operator<<(const hstring& string)
{
	unsigned short length = getStringLength(string.stringContent);//��ȡ����ĳ���
	length = unsignedStringLength + length - 1;//�ӹ�ԭ���ַ���+�����ַ����ĳ���
	if (unsignedStringLength + length - 1 > recordStringMemorysize) {
		char* stringContentCopy = stringContent;//����ԭ�ַ�������
		stringContent = new char[length];//���ټӹ����ַ������ڴ�ռ�
		recordStringMemorysize = length;//���»������ڴ��С
		delete[] stringContentCopy;
	}//����ڴ��С���ڻ�����
	memcpy(stringContent+unsignedStringLength-1, string.stringContent, length-unsignedStringLength+1);//�ַ�����ʼ��λ��+���ȿ�ʼ�����ڴ棬�������½�Ϊ�����ַ����ĳ���
	//void* mymemcpy(void* dest, const void* src, size_t n);������е���memcpy���ֶ�ʵ�ֺ���ʹ��
	unsignedStringLength = length;//ԭ���ַ�����������Ϊ���ַ�������
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
	bool isPositiveNumber = value >= 0;//�Ƿ�Ϊ����
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
	unsignedStringLength = stringLength;//��������
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
	}//�ж����ݿ�ʼλ����ȷ���
	memcpy(newString, stringContent+startCutPoint, ActualOperationLength + 1);
	newString[ActualOperationLength] = 0;
		return hstring(newString);
}

hstring::operator int()
{
	int value = 0;
	int i = stringContent[0] == '-';//����и��ž�����
	while (stringContent[i] >= '0' && stringContent[i] <= '9') {
		value = value * 10 + stringContent[i++] - 48;
	}
	value = value * ((stringContent[0] != '-') * 2 - 1);//��ԭ����
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







//����Ķ������油
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
//memcpy ʹ��forѭ��ʵ�ֵĶ���
