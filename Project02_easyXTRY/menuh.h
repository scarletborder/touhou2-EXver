#pragma once
//���ڶ���ȫ���õ��ĺ���

#include"midplay.h"
#include<stdio.h>	
#include<graphics.h>
#include<conio.h>
#include<queue>
#include"char2tchar.h"
#include <time.h>
#include<graphics.h>
#include<string.h>
#include<stringapiset.h>
//#include"game_elements.h"
//#include"transimg.h"
#pragma comment(lib, "Winmm.lib")


#define CMD_UP 88
#define CMD_DOWN 22
#define CMD_LEFT 44
#define CMD_RIGHT 66
#define CMD_CONFIRM 55
#define CMD_CANCEL 99
#define CMD_ESC 77
#define CMD_SPECIAL 33

using namespace std;

//��Ϸ��ͷ��չʾ
void starbk();



//GLOBAL:
//ȫ�ֻ��õ��ļ���ָ��
int GETCMD();
int isDUkey_s(char key);

//ȫ�ֻ��õ���ѡ����Խ���ж�
int limitmenujudge(int optnum, int c_opt, int optmove);



//MAINMENU:
//���˵����
int cmdmainmenu(int*);
void drawmainmenu(int topt);
void drawmainmenufalme();

//���������
void rainbow();
void cmdmusicroommenu();
void drawmusicroommenu(int topt);

//�鿴Result���޸�Result
void seeresult();
void seeresult(int);



//GAME:
//ѡ�����λ������
void drawselectflame_reimu();
int cmdselect_reimu();
void drawselect_reimu(int topt);

//��Ϸ�����е�GLOBAL
int gamemain(int* endsignal,int);
void drawgameflame();
void moveinspect(IMAGE* pixelreimu, IMAGE* l1, IMAGE* l2, IMAGE* l3, IMAGE* r1, IMAGE* r2, IMAGE* r3);

