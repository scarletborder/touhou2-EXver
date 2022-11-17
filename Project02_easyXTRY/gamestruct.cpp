#include"menuh.h"


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
