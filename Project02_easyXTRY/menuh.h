#pragma once
/********************************************************/
//���ڶ���ȫ���õ��ĺ�

#define SIZEX 960
#define SIZEY 720

#define CMD_UP 0x00000001
#define CMD_DOWN 0x00000002
#define CMD_LEFT 0x00000004
#define CMD_RIGHT 0x00000008
#define CMD_CONFIRM 0x00000010
#define CMD_CANCEL 0x00000020
#define CMD_ESC 0x00000040
#define CMD_SPECIAL 0x00000080
#define CMD_LREAP 0x00000160
#define CMD_RREAP 0x00000320

#define maxYUZHA 16 
#define maxbullet 512
#define XSIZE 960
#define YSIZE 720
#define RADIUS 30

//��ǰ�汾���ؿ�
#define maxstage 5

//�������ɿ�Ƭ�ı�Ե
#define xlef 20
#define xrig 940
#define ytop 52
#define ybot 452

//ÿ����λ��֮���x/y���
#define xsp 40
#define ysp 50

//��˵�����������Ƿ�����boss
//����x,y:�붨λ������ʾ�ĸ��ӻ�����ٸ�
//���磬boss��λ�����ڣ�2��3��,���boss�����չ���˸��ӣ�4,3������ô������(0,0)||(1,0)||(2,0)
//���������Ӧ�ó����������� if(isorbcrashboss(0,0) ||... ||... ||...)
#define isorbcrashboss(xboss,yboss) \
iscrash(40, 50, boss.x + (xboss) * 40, boss.y + (yboss) * 50,ORB.x,ORB.y,RADIUS) == 1

//��˵�������ڳ�ʼ��һ����Ļʱʹ�ã�����Ϊ�ҵ���һ��isliveΪ0����ʹ�õĵ�Ļ�ṹ��
//���ƣ����ڼ����ĵ�Ļ��ű����� bulletid
#define jexbullet \
			while (enemybullet[bulletid].islive != 0)\
			{\
				bulletid++;\
				if(bulletid >= maxbullet)			\
				{   bulletid = 0   ;        }							\
			}

#define PI 3.141592654

#include"midplay.h"
#include<stdio.h>	
#include<graphics.h>
#include<conio.h>
#include<queue>
#include"char2tchar.h"
#include <time.h>
#include<string.h>
#include<stringapiset.h>
#include"declarestruct.h"

#include<windows.h>
//#include"game_elements.h"
//#include"transimg.h"
#pragma comment(lib, "Winmm.lib")
//#include"MyTimer.h"


using namespace std;

//��Ϸ��ͷ��չʾ
void starbk();




//GLOBAL:
//ȫ�ֻ��õ��ļ���ָ��
int GETCMD();
int isDUkey_s(char key);//�ж���ϼ��Ƿ���ɣ��Լ�������ʱ�����
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor);//����͸��ͼ��
int limitmenujudge(int optnum, int c_opt, int optmove);//ȫ�ֻ��õ���ѡ����Խ���ж�



//MAINMENU:
//���˵����
int cmdmainmenu();
void drawmainmenu(int topt);
void drawmainmenufalme();

//���������
void rainbow();
void cmdmusicroommenu();
void drawmusicroommenu(int topt);

//�鿴Result���޸�Result
void seeresult();
void saveresult(int cscore);




void stage1();


//GAME:
//ѡ�����λ������
void drawselectflame_reimu();
int cmdselect_reimu();
void drawselect_reimu(int topt);

//��Ϸ�����е�GLOBAL
int gamemain(int);
void drawgameflame();
void cmdreimu();
void init_fastyuzha();

//escmenu
void escmenuflame();

void init_yuzha();


void aftercrash(double jjx, double jjy, double width, double height, double jp);
int iscrash(int width, int height, int jx, int jy, double ,double ,double );
void ishurtboss();

//�ؿ�����
int initstage(int num);
void aimreimubullet(double x, double y, int id, double aimx, double aimy);
void initbullet(int id, int x, int y, double speed, int aimx, int aimy,int,int);

//�ؿ��Դ���Ļ�趨
void stage2to();
void stage3sp();


void bossskill(short int stage);
void bossattack(short int stage);
/**************  reward   *********/
void rewardhurtcard(int iscontinuecard,int);
void punishtimemode(int stage);
void isrewardheart();
void rewardpoint(int iscontinuepoint, int stage);
void initreward(int type, int x, int y);
void moverewarditem();
void isreceivereward();
void harvestallreward();


//chat
void chat1();

void drawitemswhenstatic();
void drawitemswhenmove();			
void printscore(int stage);

void moveallbullet();
void ishurtcard();
void ishurtreimu();

void respawn();
