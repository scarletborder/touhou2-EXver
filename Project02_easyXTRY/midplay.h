#pragma once
/*
midplay.h
���ڲ���mid���ֵ�ͷ����
by scb
*/

//��Ҫ<graphics.h>ͷ����
//���ص�ַ:
//https://easyx.cn/easyx
// ���� Windows Multimedia API

#include <graphics.h>

//ѭ����������
//�����song�淶�� xxx.mid
//debugģʽ�£������ļ��������Ŀ�ļ��У���test14/music.mid
//releaseģʽ�£���������ļ��ͱ���� exe ����һ��
#define startbgm(song) \
mciSendString(_T("open "#song" type MPEGVideo alias current_bgm"), NULL, 0, NULL);\
mciSendString(_T("play current_bgm repeat"), NULL, 0, NULL)

//������ǰ����
#define endbgm \
mciSendString(_T("stop current_bgm"), NULL, 0, NULL); \
mciSendString(_T("close current_bgm"), NULL, 0, NULL)