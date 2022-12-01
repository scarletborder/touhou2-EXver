#pragma once
/********************************************************/
//用于定义全局用到的宏

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

//当前版本最多关卡
#define maxstage 5

//画面生成卡片的边缘
#define xlef 20
#define xrig 940
#define ytop 52
#define ybot 452

//每个定位点之间的x/y间隔
#define xsp 40
#define ysp 50

//宏说明：阴阳玉是否碰到boss
//输入x,y:离定位点所表示的格子还差多少格
//例如，boss定位点现在（2，3）,如果boss体积延展到了格子（4,3），那么可以用(0,0)||(1,0)||(2,0)
//输出：根据应用场景，用例是 if(isorbcrashboss(0,0) ||... ||... ||...)
#define isorbcrashboss(xboss,yboss) \
iscrash(40, 50, boss.x + (xboss) * 40, boss.y + (yboss) * 50,ORB.x,ORB.y,RADIUS) == 1

//宏说明，用于初始化一个弹幕时使用，功能为找到下一个islive为0可以使用的弹幕结构体
//限制，用于计数的弹幕序号必须是 bulletid
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

//游戏开头的展示
void starbk();




//GLOBAL:
//全局会用到的键盘指令
int GETCMD();
int isDUkey_s(char key);//判断组合键是否完成，以及由消抖时间代替
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor);//绘制透明图像
int limitmenujudge(int optnum, int c_opt, int optmove);//全局会用到的选择栏越界判断



//MAINMENU:
//主菜单相关
int cmdmainmenu();
void drawmainmenu(int topt);
void drawmainmenufalme();

//音乐室相关
void rainbow();
void cmdmusicroommenu();
void drawmusicroommenu(int topt);

//查看Result和修改Result
void seeresult();
void saveresult(int cscore);




void stage1();


//GAME:
//选择灵梦机型相关
void drawselectflame_reimu();
int cmdselect_reimu();
void drawselect_reimu(int topt);

//游戏主体中的GLOBAL
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

//关卡设置
int initstage(int num);
void aimreimubullet(double x, double y, int id, double aimx, double aimy);
void initbullet(int id, int x, int y, double speed, int aimx, int aimy,int,int);

//关卡自带弹幕设定
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
