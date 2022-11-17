#pragma once
/*
char2tchar.h
用于char类型和TCHAR类型互相转换
*/

//char* TCHAR2char(const TCHAR* STR);//TCHAR*字符串转化为char*字符串

//TCHAR* char2TCAHR(const char* str);//char*字符串转化为TCHAR*字符串




static char* TCHAR2char(const TCHAR* STR)
{

	//返回字符串的长度

	int size = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, FALSE);

	//申请一个多字节的字符串变量

	char* str = new char[sizeof(char) * size];

	//将STR转成str

	WideCharToMultiByte(CP_ACP, 0, STR, -1, str, size, NULL, FALSE);

	return str;

}


static TCHAR* char2TCAHR(const char* str)
{

	int size = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);

	TCHAR* retStr = new TCHAR[size * sizeof(TCHAR)];

	MultiByteToWideChar(CP_ACP, 0, str, -1, retStr, size);

	return retStr;

}