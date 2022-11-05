#pragma once
//用于定义全局用到的函数


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

#include<windows.h>
//#include"game_elements.h"
//#include"transimg.h"
#pragma comment(lib, "Winmm.lib")
//#include"MyTimer.h"

#define CMD_UP 0x00000001
#define CMD_DOWN 0x00000002
#define CMD_LEFT 0x00000004
#define CMD_RIGHT 0x00000008
#define CMD_CONFIRM 0x00000010
#define CMD_CANCEL 0x00000020
#define CMD_ESC 0x00000040
#define CMD_SPECIAL 0x00000080

using namespace std;

//游戏开头的展示
void starbk();




//GLOBAL:
//全局会用到的键盘指令
int GETCMD();
int isDUkey_s(char key);

//全局会用到的选择栏越界判断
int limitmenujudge(int optnum, int c_opt, int optmove);



//MAINMENU:
//主菜单相关
int cmdmainmenu(int*);
void drawmainmenu(int topt);
void drawmainmenufalme();

//音乐室相关
void rainbow();
void cmdmusicroommenu();
void drawmusicroommenu(int topt);

//查看Result和修改Result
void seeresult();
void seeresult(int);



//GAME:
//选择灵梦机型相关
void drawselectflame_reimu();
int cmdselect_reimu();
void drawselect_reimu(int topt);

//游戏主体中的GLOBAL
int gamemain(int* endsignal,int);
void drawgameflame();
void moveinspect(IMAGE* pixelreimu, IMAGE* l1, IMAGE* l2, IMAGE* l3, IMAGE* r1, IMAGE* r2, IMAGE* r3,int *xk,int*xn);

