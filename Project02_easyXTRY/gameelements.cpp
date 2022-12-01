#include"menuh.h"
/**************************************/
//分离于gamecmd.cpp
//首次定义游戏中用到的元素
//从而被其他文件引用外部变量
/**************************************/


//弹幕
//敌弹结构
struct bullets enemybullet[maxbullet] = { 0 };

//激光敌弹结构
struct lasers enemylaser[128] = { 0 };

//御札结构
//总大小20*28
struct REIMUBULLET YUZHA[maxYUZHA] = { 0 };


//定义阴阳玉结构
//总大小49*49，半径为RADIUS
struct yinyang_orb ORB = { 0 };


//敌人
//敌方翻牌卡片
struct enemycards card[207] = { 0 };
//boss
struct BOSS boss = { 0 };
//塔楼
struct TOWER tower[32] = { 0 };
//墙壁
struct WALL wall[8] = { 0 };


//游戏中各种奖励结构
struct rewards reward[32] = { 0 };


//灵梦机型的数据以及在场上的位置
struct player_status reimu = { 310,445,10,0 };


//游戏上方的计分板
struct game_score cscore = { 0,0,0,0,1 };

unsigned int iscontinuepoint = 0;


//灵梦是否移动，以及朝向
int reimumove = 0; 
short int stage = 1; 
int maxiscontinuecard = 0;

int ctimeflow = 0; 
char hiscore[15];

DWORD currentticktime;//当前时间

short int hasplaycharge = 0;

unsigned short int punishmode = 0;
int punishtime = 0;

int iscontinuecard = 0;//持续连击卡片个数

//移动间隔
DWORD oldtickmovetime;

//御札发射间隔
DWORD oldtickshoottime;

//弹幕更新间隔
DWORD oldtickbullettime;

//滑铲间隔
DWORD oldtickreaptime;

//阴阳玉减速间隔
DWORD oldtickslowtime;

//游戏单局开始前计时，计算出进行过程中已用时间
DWORD timeflow;

//上一次发射关卡特殊弹幕时间，共8个
//0固定为惩罚弹幕，1-7为虚空/塔楼
DWORD oldspbullettime[8];

//wall
short int iscontinuecrashwall;
short int iscrashverwall;

int bombhurt = 1;//炸弹伤害

