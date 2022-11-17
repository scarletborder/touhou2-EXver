#pragma once
/*
char2tchar.h
����char���ͺ�TCHAR���ͻ���ת��
*/

//char* TCHAR2char(const TCHAR* STR);//TCHAR*�ַ���ת��Ϊchar*�ַ���

//TCHAR* char2TCAHR(const char* str);//char*�ַ���ת��ΪTCHAR*�ַ���




static char* TCHAR2char(const TCHAR* STR)
{

	//�����ַ����ĳ���

	int size = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, FALSE);

	//����һ�����ֽڵ��ַ�������

	char* str = new char[sizeof(char) * size];

	//��STRת��str

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