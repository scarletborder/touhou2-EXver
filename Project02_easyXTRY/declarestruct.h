#pragma once

//游戏中用到的结构体和说明
//结构体变量的初次定义在gamestruct中
/***************结构体定义***********************/


//敌方翻牌卡片
struct enemycards
{
	short int x;
	short int y;
	unsigned int hp;//生命值&是否在场
	unsigned int havebeencrashed :1;//判断卡片上是否一直有阴阳玉，防止一直打击

};


//敌方塔楼结构
struct TOWER
{
	short int x;
	short int y;
	unsigned int islive : 1;
};


//用于定义游戏正文中用到的元素
//弹幕
//敌弹结构
struct bullets
{
	unsigned int islive : 1;//是否在场
	double x;//x坐标
	double y;//y坐标
	double degree;//偏移角度
	double speed;//弹幕速度
	int radius;//弹幕半径
	int isunbreak;//是否不可消除
	DWORD oldunbreaktime;//生成时间，放生成时被立即消除
};


//激光敌弹结构
struct lasers
{
	unsigned int islive : 1;//是否在场
	double x;//x坐标
	double y;//y坐标
	double length;//激光长度
	double moverad;//偏移角度
	double speed;//激光速度
	int type;//激光类型
};

//游戏中各种奖励结构
struct rewards
{
	unsigned int islive :1;//是否在场
	unsigned int downorup :1;//下坠还是上弹状态，0为下，1为上
	unsigned int isup : 1;//是否已经上弹,1为已经有
	short int x;//x坐标
	short int y;//y坐标
	unsigned short int type;//奖励的类型,1=点,2=B,3=残
};

//灵梦机型的数据以及在场上的位置
struct player_status
{
	double x;////左上角定位点x
	double y;////左上角定位点y
	double speed;//灵梦的速度，不同机型速度不同
	unsigned short int type;//机型
	DWORD oldunbreaktime;//上一次被阴阳玉/弹幕击打的时间

};

//游戏上方的计分板
struct game_score
{
	unsigned int c_score;//当前分数
	unsigned int hi_score;//历史最高分
	short int heartnum;//残机个数
	short int bombnum;//炸弹个数
	short int stagenum;//当前关卡数
};

//御札结构
//总大小20*28
struct REIMUBULLET
{
	unsigned int islive :1;//判断这个御札是否在场，1在场，0不在
	short int x;//左上角定位点
	short int y;//左上角定位点

};

//定义阴阳玉结构
//总大小49*49，半径为RADIUS
struct yinyang_orb
{
	unsigned int islive : 1;//判断阴阳玉是否在场，1在场，0不在
	double x;//真实圆心
	double y;//真实圆心
	double degree;
	double speed;
};


//定义boss结构
//Boss发技能统一调用spbullet的计时
//发射位置是boss.x,boss.y+体型（switch stage）
struct BOSS
{
	double x;//
	double y;
	unsigned short int speed;
	double degree;
	short int hp;
	unsigned int havebeencrashed : 1;//判断boss上是否一直有阴阳玉，防止一直打击
};


//定义墙wall结构，类似画面边缘
//预计像素宽度为5，黄色
struct WALL
{
	//起始点
	unsigned short int x1;
	unsigned short int y1;

	//终止点
	unsigned short int x2;
	unsigned short int y2;

	unsigned int islive : 1;//是否在场
	unsigned int levver : 1;//是lev=0,ver=1
};

