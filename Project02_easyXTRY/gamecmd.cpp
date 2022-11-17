#include"menuh.h"
#include<iostream>
#include"MyTimer.h"


//计时各种时间间隔，图像声明
#if 1
DWORD currentticktime;//当前时间

//移动间隔
static DWORD oldtickmovetime;

//御札发射间隔
static DWORD oldtickshoottime;

//弹幕更新间隔
static DWORD oldtickbullettime;

//滑铲间隔
static DWORD oldtickreaptime;

//阴阳玉减速间隔
static DWORD oldtickslowtime;

//游戏单局开始前计时，计算出进行过程中已用时间
static DWORD timeflow;

//上一次发射关卡特殊弹幕时间，共8个
//0固定为惩罚弹幕，1-7为虚空/塔楼
static DWORD oldspbullettime[8];

//wall
short int iscontinuecrashwall;
short int iscrashverwall;

static int bombhurt = 1;//炸弹伤害

//灵梦是否移动，以及朝向
static int reimumove = 0;

short int iscontinuecard = 0;//持续连击卡片个数
short int maxiscontinuecard = 0;

extern unsigned int iscontinuepoint;//持续接点个数

short int stage = 1;

static int ctimeflow = 0;

unsigned short int punishmode = 0;
int punishtime = 0;


char hiscore[15];



//通用图像文件
static IMAGE pixelreimu;
static IMAGE reimuleft1;
static IMAGE reimuleft2;
static IMAGE reimuleft3;
static IMAGE reimuright1;
static IMAGE reimuright2;
static IMAGE reimuright3;
static IMAGE yuzha;
static IMAGE statictower;
IMAGE bossimg;
IMAGE rewardpointimg;
IMAGE rewardbombimg;

#endif

//用于定义游戏正文中用到的元素
#if 1
//弹幕
//敌弹结构
extern struct bullets enemybullet[maxbullet];


//激光敌弹结构
extern struct lasers enemylaser[128];


//敌方
extern struct enemycards card[207];
extern struct TOWER tower[32];
extern struct BOSS boss;
extern struct WALL wall[8];

//游戏中各种奖励结构
extern struct rewards reward[32];


//灵梦机型的数据以及在场上的位置
extern struct player_status reimu;


//游戏上方的计分板
extern struct game_score cscore;


//御札结构
//总大小20*28
extern struct REIMUBULLET YUZHA[maxYUZHA];


//定义阴阳玉结构
//总大小49*49，半径为RADIUS
extern struct yinyang_orb ORB;
#endif

MyTimer tt;

//重生
//后期在做重生时要考虑场上弹幕全消
void respawn()
{

	//残机-1
	cscore.heartnum --;

	//根据机体不同，重生时获得不同数量的资源
	switch (reimu.type)
	{
	case 1:
		cscore.bombnum = 3;
		break;
	case 2:
		cscore.bombnum = 3;
		break;
	case 3:
		if (cscore.bombnum >= 1)
		{
			cscore.bombnum = 4;
		}
		else
		{
			cscore.bombnum = 3;
		}
		break;
	case 4:
		cscore.bombnum++;
		cscore.heartnum++;
	}

	//播放被弹音效
	mciSendString(_T("close respawn"), NULL, 0, NULL);
	mciSendString(_T("open m\\playerdie.mp3 alias respawn"), NULL, 0, NULL);
	mciSendString(_T("play respawn"), NULL, 0, NULL);

	tt.Sleep(50);
	for (int bulleti = 0; bulleti < maxbullet; bulleti++)
	{
		enemybullet[bulleti].islive = 0;
	}
	
	//重新定位灵梦

	
}


//第一局游戏前初始化灵梦数值
void initreimu()
{
	//初始化灵梦
	switch (reimu.type)
	{
	case 1:
		cscore.heartnum = 3;
		cscore.bombnum = 3;
		reimu.speed = 16;
		bombhurt = 38;
		break;
	case 2:
		cscore.heartnum = 2;
		cscore.bombnum = 3;
		reimu.speed = 18;
		bombhurt = 52;
		break;
	case 3:
		cscore.heartnum = 4;
		cscore.bombnum = 3;
		reimu.speed = 12;
		bombhurt = 24;
		break;
	case 4:
		cscore.heartnum = 9;
		cscore.bombnum = 99;
		reimu.speed = 14;
		bombhurt = 99;
	}
	tt.Sleep(50);
	reimu.x = SIZEX /2;
	reimu.y = SIZEY - 58;
}


//每一局游戏前初始化阴阳玉
void initorb()
{
	ORB.islive = 1;
	ORB.speed = 0;
	ORB.degree = 0;
	ORB.x = XSIZE - 60;
	ORB.y = YSIZE/2;

}





//侦测灵梦动作，并绘制灵梦移动路径，动画
//之后要适配新的按键映射函数，以及御札，滑铲，灵击


short int hasplaycharge = 0;


/******************获得键盘上操纵灵梦的命令*************************/
void cmdreimu()
{
	int optmove = GETCMD();
	int firstdo = 0;//优先占用：部分操作会使该值变为1，跳过之后的所有移动检测
	int isx = 0;

		/***********暂停游戏********************/
	

		/******普通移动********/

		if (optmove & CMD_LEFT && firstdo == 0)//普通左移
		{
			//首先是否可以移动，免得穿墙
			//接着进行移动操作，改变一次坐标并穿插着进行移动时的图片动画
			if (reimu.x - reimu.speed <= 1)
			{
				reimumove = 0;
				return;
			}

			else
			{
				reimumove = CMD_LEFT;
				oldtickmovetime = GetTickCount();
			}
			
		}

		if (optmove & CMD_RIGHT && firstdo == 0)//普通右移
		{
			if (reimu.x + reimu.speed >= SIZEX - 43)
			{
				reimumove = 0;
				return;
			}

			else
			{
				reimumove = CMD_RIGHT;
				oldtickmovetime = GetTickCount();
			}
			
		}
	
		/******************滑铲移动***********/
#if 1
		if (optmove & CMD_CANCEL )//按下x键
		{
			if(currentticktime - oldtickmovetime <= 40)//确定是在移动过程中，按下x键
			{
				firstdo = 1;
			}
			else
			{
				if (currentticktime - oldtickreaptime < 300 && currentticktime - oldtickreaptime > 40)
				{
					//前脚翻
					if (iscrash(52, 15, reimu.x - 5, reimu.y - 5, ORB.x, ORB.y, RADIUS) == 1 || iscrash(32, 15, reimu.x + 5, reimu.y - 20, ORB.x, ORB.y, RADIUS))
					{
						reimu.oldunbreaktime = GetTickCount() - 2200;
						aftercrash(reimu.x, reimu.y, 42, 60, 50);
						oldtickslowtime = GetTickCount();
					}
					oldtickreaptime = GetTickCount();
				}
				else if(currentticktime - oldtickreaptime >= 300)
				{
					//挥舞御币，打击

					if (iscrash(52, 15, reimu.x - 5, reimu.y - 5, ORB.x, ORB.y, RADIUS) == 1|| iscrash(32, 15, reimu.x + 5, reimu.y - 20, ORB.x, ORB.y, RADIUS))
					{
						reimu.oldunbreaktime = GetTickCount() - 2200;
						aftercrash(reimu.x, reimu.y, 42, 60, 40);
						oldtickslowtime = GetTickCount();
					}
					oldtickreaptime = GetTickCount();

				}

			}
		}

		if (optmove & CMD_LEFT && firstdo == 1)//滑铲左移
		{
			//首先是否可以移动，免得穿墙
			//接着进行移动操作，改变一次坐标并穿插着进行移动时的图片动画
			if (reimu.x - 1.5*reimu.speed <= 1)
			{
				reimumove = 0;
				return;
			}

			else
			{
				reimumove = CMD_LREAP;
				if (iscrash(20, 51, reimu.x - 20, reimu.y + 5 , ORB.x, ORB.y, RADIUS) == 1)
				{
					aftercrash(reimu.x, reimu.y + 30, 42, 60, 35);
					reimu.oldunbreaktime = GetTickCount() - 2000;
					oldtickslowtime = GetTickCount();
				}
				oldtickmovetime = GetTickCount();
				oldtickreaptime = GetTickCount();
			}

		}

		if (optmove & CMD_RIGHT && firstdo == 1)//
		{
			if (reimu.x + 1.5* reimu.speed >= SIZEX - 43)
			{
				reimumove = 0;
				return;
			}

			else
			{
				reimumove = CMD_RREAP;
				if (iscrash(20, 51, reimu.x + 42, reimu.y + 5, ORB.x, ORB.y, RADIUS) == 1)
				{
					aftercrash(reimu.x, reimu.y + 30, 42, 60, 35);
					reimu.oldunbreaktime = GetTickCount() - 2000;
					oldtickslowtime = GetTickCount();
				}
				oldtickmovetime = GetTickCount();
				oldtickreaptime = GetTickCount();
			}

		}

#endif


	if (optmove & CMD_CONFIRM && firstdo ==0)//在静止或者普通移动中可以发射单发御札
	{
		if (currentticktime - oldtickshoottime >= 5000 && currentticktime - oldtickmovetime >= 0 && currentticktime - oldtickmovetime <= 300 && currentticktime - oldtickreaptime >= 0 && currentticktime - oldtickreaptime <= 300)
		{
			init_fastyuzha();
			hasplaycharge = 0;
			oldtickshoottime = GetTickCount() + 2000;
		}
		if (currentticktime - oldtickshoottime >= 250)
		{
			init_yuzha();
			oldtickshoottime = GetTickCount();
		}

	}

	if (optmove & CMD_SPECIAL && cscore.bombnum >= 1 && currentticktime - reimu.oldunbreaktime >= 1000)
	{
		cscore.bombnum--;
		reimu.oldunbreaktime = GetTickCount() - 500;
		int hurt = bombhurt;//bomb伤害，根据机型调节
		mciSendString(_T("close bomb"), NULL, 0, NULL);
		mciSendString(_T("open m\\bomb.mp3 alias bomb"), NULL, 0, NULL);
		mciSendString(_T("play bomb"), NULL, 0, NULL);

		for (short int cardii = 0; cardii < 207; cardii++)
		{
			if (hurt <= 0)
			{
				break;
			}
			while(card[cardii].hp >= 1)
			{
				if (hurt <= 0)
				{
					break;
				}
				card[cardii].hp--;
				//卡片生命掉完，移除
				if (card[cardii].hp == 0)
				{
					if (cardii == 0 && stage == 4)
					{
						initreward(2, card[cardii].x, card[cardii].y);
					}
					else if (rand() % 8 == 0)
					{
						initreward(1, card[cardii].x, card[cardii].y);
					}

				}
				iscontinuecard++;
				rewardhurtcard(iscontinuecard, stage);

				if(iscontinuecard > maxiscontinuecard)
				{
					maxiscontinuecard = iscontinuecard;
				}
				hurt--;
			}

		}
		for (short int bulleti = 0; bulleti < maxbullet; bulleti++)
		{
			enemybullet[bulleti].islive = 0;
		}
		optmove = CMD_DOWN;
		harvestallreward();

	}

}


/**************发射御札****************/
//每次z键初始化发射一个御札
static int yuzhanum = -1;
void init_yuzha()
{
	//每次放御札时，都会切换到上一个释放的下一个序号的御札
	yuzhanum++;
	if (yuzhanum == maxYUZHA)
	{
		yuzhanum = 0;
	}

	YUZHA[yuzhanum].islive = 1;//调整这个序号的御札状态
	YUZHA[yuzhanum].x = reimu.x + 9;
	YUZHA[yuzhanum].y = reimu.y + 30;

}
void init_fastyuzha()
{
	//每次放御札时，都会切换到上一个释放的下一个序号的御札
	yuzhanum++;
	if (yuzhanum == maxYUZHA)
	{
		yuzhanum = 0;
	}
	YUZHA[yuzhanum].islive = 1;//调整这个序号的御札状态
	YUZHA[yuzhanum].x = reimu.x + 9;//1
	YUZHA[yuzhanum].y = reimu.y ;
	yuzhanum++;
	if (yuzhanum == maxYUZHA)
	{
		yuzhanum = 0;
	}
	YUZHA[yuzhanum].islive = 1;//调整这个序号的御札状态
	YUZHA[yuzhanum].x = reimu.x + 29;//5
	YUZHA[yuzhanum].y = reimu.y + 50;
	yuzhanum++;
	if (yuzhanum == maxYUZHA)
	{
		yuzhanum = 0;
	}
	YUZHA[yuzhanum].islive = 1;//调整这个序号的御札状态
	YUZHA[yuzhanum].x = reimu.x - 11;//1
	YUZHA[yuzhanum].y = reimu.y + 90;
	yuzhanum++;
	if (yuzhanum == maxYUZHA)
	{
		yuzhanum = 0;
	}
	YUZHA[yuzhanum].islive = 1;//调整这个序号的御札状态
	YUZHA[yuzhanum].x = reimu.x + 19;//4
	YUZHA[yuzhanum].y = reimu.y + 140;
	yuzhanum++;
	if (yuzhanum == maxYUZHA)
	{
		yuzhanum = 0;
	}
	YUZHA[yuzhanum].islive = 1;//调整这个序号的御札状态
	YUZHA[yuzhanum].x = reimu.x - 1;//2
	YUZHA[yuzhanum].y = reimu.y + 190;
	yuzhanum++;
	if (yuzhanum == maxYUZHA)
	{
		yuzhanum = 0;
	}
	YUZHA[yuzhanum].islive = 1;//调整这个序号的御札状态
	YUZHA[yuzhanum].x = reimu.x + 9;//3
	YUZHA[yuzhanum].y = reimu.y + 230;
}

void escmenuflame();



/*****************判断阴阳玉是否与某个矩形物体相撞************************
阴阳玉总大小49*49，半径为RADIUS
输入：矩形的宽，矩形的高, 矩形定位点x, 矩形定位点y;圆心坐标，圆的半径
输出：整数1=YES,0=NO*/
int iscrash(int width, int height, int jx, int jy,double cirx, double ciry,double r)
{
	if (cirx - r >= XSIZE || cirx + r <= 0 || ciry - r >= YSIZE || ciry + r <= 0)
	{
		return 0;
	}

	//阴阳玉圆心


	double cx = static_cast<double>(jx) + width / 2;
	double cy = static_cast<double>(jy) + height / 2;
	double hx = width / static_cast<double>(2);
	double hy = height / static_cast<double>(2);
	
	// 第1步：转换至第1象限
	double vx = cirx - cx;
	double vy = ciry - cy;
	if (vx < 0)
	{
		vx *= -1;
	}
	if (vy < 0)
	{
		vy *= -1;
	}
	// 第2步：求圆心至矩形的最短距离矢量
	double ux = vx - hx;
	double uy = vy - hy;
	if (ux < 0 && uy < 0)
	{
		return 1;
	}
	else if (ux < 0 && uy >= 0)
	{
		ux = 0;
		uy = uy ;
	}
	else if (ux >= 0 && uy < 0)
	{
		ux = ux;
		uy = 0 ;
	}
	// 第3步：长度平方与半径平方比较
	if (((ux) * (ux) + (uy) * (uy)) <= r * r + 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/***************阴阳玉与某个矩形物体相撞后的新移动状态******************/
//输入：（全局）阴阳玉速度，角度，定位点坐标；（局部）这个矩形物体的定位点坐标，宽度，长度;按照情况给一个动量
// 比如御札动量25，飞踢动量35
//输出: (全局)阴阳玉的新速度，角度
void aftercrash(double jjx, double jjy, double width,double height,double jp)
{
	//阴阳玉圆心
	double cx = ORB.x ;
	double cy = ORB.y ;

	//矩形重心
	double jx = jjx + width / 2;
	double jy = jjy + height / 2;

	//夹角的三角函数
	//象限
	int xiangxian = 0;
	if (jx - cx >= 0 && jy - cy >= 0)
		xiangxian = 1;
	else if (jx - cx < 0 && jy - cy > 0)
		xiangxian = 2;
	else if (jx - cx < 0 && jy - cy < 0)
		xiangxian = 3;
	else
		xiangxian = 4;

	double sin_a;
	double cos_a;

	if (jx != cx)
	{
		double tan_a = (jy - cy) / (jx - cx);


		int isfu = 1;//是否为负数，负数-1，正数1

		if (xiangxian == 2 || xiangxian == 3)
			isfu = (-1);
		cos_a = isfu * sqrt(abs(1 / (1 + tan_a * tan_a)));

		isfu = 1;
		if (xiangxian == 3 || xiangxian == 4)
			isfu = (-1);
		sin_a = isfu * sqrt(abs(1 - 1 / (1 + tan_a * tan_a)));
	}
	else
	{
		if (jy >= cy)
		{
			sin_a = 1;
		}
		else
		{
			sin_a = -1;
		}
		cos_a = 0;
	}
	//矩形对阴阳玉的动量
	double jpx = -(jp * cos_a);
	double jpy = jp * sin_a;

	//阴阳玉原动量分解
	double orbcos = cos(ORB.degree);
	double cpx = ORB.speed * orbcos;
	double cpy = ORB.speed * sin(ORB.degree);

	//计算新的速度和角度
	ORB.speed = sqrt(abs((cpx + jpx) * (cpx + jpx) + (cpy + jpy) * (cpy + jpy)));
	if (cpy + jpy == 0 && cpx + jpx == 0)
	{
		ORB.degree = PI / 2;
		return;
	}
	
	double newabsdegree;
	if(cpx + jpx != 0)
	{
		newabsdegree = abs(atan((cpy + jpy) / (cpx + jpx)));


		if (jpx + cpx >= 0 && jpy + cpy >= 0)//1
			ORB.degree = 2 * PI - newabsdegree;//4
		else if (jpx + cpx < 0 && jpy + cpy > 0)//2
			ORB.degree = PI + newabsdegree;//3
		else if (jpx + cpx < 0 && jpy + cpy < 0)//3
			ORB.degree = PI - newabsdegree;//2	
		else//4
			ORB.degree = newabsdegree;//1
	}
	else
	{
		if (cpy + jpy >= 0)
		{
			ORB.degree = PI / 2;
		}
		else
		{
			ORB.degree = 3 * PI / 2;
		}
	}

	return;
}

void botcrash(double jjx, double jjy, double width, double height, double jp)
{
	//阴阳玉圆心
	double cx = ORB.x;
	double cy = ORB.y;

	//矩形重心
	double jx = jjx + width / 2;
	double jy = jjy + height / 2;

	//夹角的三角函数
	//象限
	int xiangxian = 0;
	if (jx - cx >= 0 && jy - cy >= 0)
		xiangxian = 1;
	else if (jx - cx < 0 && jy - cy > 0)
		xiangxian = 2;
	else if (jx - cx < 0 && jy - cy < 0)
		xiangxian = 2;
	else
		xiangxian = 1;

	double sin_a;
	double cos_a;

	if (jx != cx)
	{
		double tan_a = (jy - cy) / (jx - cx);


		int isfu = 1;//是否为负数，负数-1，正数1

		if (xiangxian == 2 || xiangxian == 3)
			isfu = (-1);
		cos_a = isfu * sqrt(abs(1 / (1 + tan_a * tan_a)));

		isfu = 1;
		if (xiangxian == 3 || xiangxian == 4)
			isfu = (-1);
		sin_a = isfu * sqrt(abs(1 - 1 / (1 + tan_a * tan_a)));
	}
	else
	{
		if (jy >= cy)
		{
			sin_a = 1;
		}
		else
		{
			sin_a = -1;
		}
		cos_a = 0;
	}
	//矩形对阴阳玉的动量
	double jpx = -(jp * cos_a);
	double jpy = jp * sin_a;

	//阴阳玉原动量分解
	double orbcos = cos(ORB.degree);
	double cpx = ORB.speed * orbcos;
	double cpy = ORB.speed * sin(ORB.degree);

	//计算新的速度和角度
	ORB.speed = sqrt(abs((cpx + jpx) * (cpx + jpx) + (cpy + jpy) * (cpy + jpy)));
	if (cpy + jpy == 0 && cpx + jpx == 0)
	{
		ORB.degree = PI / 2;
		return;
	}

	double newabsdegree;
	if (cpx + jpx != 0)
	{
		newabsdegree = abs(atan((cpy + jpy) / (cpx + jpx)));


		if (jpx + cpx >= 0 && jpy + cpy >= 0)//1
			ORB.degree = 2 * PI - newabsdegree;//4
		else if (jpx + cpx < 0 && jpy + cpy > 0)//2
			ORB.degree = PI + newabsdegree;//3
		else if (jpx + cpx < 0 && jpy + cpy < 0)//3
			ORB.degree = PI - newabsdegree;//2	
		else//4
			ORB.degree = newabsdegree;//1
	}
	else
	{
		if (cpy + jpy >= 0)
		{
			ORB.degree = PI / 2;
		}
		else
		{
			ORB.degree = 3 * PI / 2;
		}
	}

	return;
}




/*******************因特殊情况导致阴阳玉运动状态改变******************/
//碰到墙壁（线状）
#if 1
//水平撞击 左壁and右壁=
void crashvertical()
{
	ORB.degree = 2 * PI - ORB.degree;
}
//竖直撞击 上壁and下壁
void crashlevel()
{
	ORB.degree = 3 * PI - ORB.degree;
}

#endif



void moveorb()
{
	//侦测是否被御札打到而造成角度和速度改变
	for (short int i = 0; i <= maxYUZHA - 1; i++)
	{
		if (YUZHA[i].islive == 0)
		{
			continue;
		}
		if (iscrash(20, 28, YUZHA[i].x, YUZHA[i].y,ORB.x,ORB.y,RADIUS) == 1)
		{
			YUZHA[i].islive = 0;//原先的御札失活
			//打到了，进行更新减速计时器
			oldtickslowtime = GetTickCount();
			//进一个碰撞操作();
			botcrash(YUZHA[i].x, YUZHA[i].y, 20, 28, 30);

			break;
		}
	}

	//侦测是否被滑铲而造成角度和速度改变

	
	//侦测阴阳玉左边缘是否接触墙壁而造成角度和速度改变
	//水平
	if (ORB.x - RADIUS + ORB.speed * cos(ORB.degree) < 2 || ORB.x + RADIUS + ORB.speed * cos(ORB.degree) > XSIZE - 2 )
	{

			ORB.speed *= 0.8;
			crashlevel();

	}
	//竖直
	else if (ORB.y  - RADIUS + ORB.speed * sin(ORB.degree) < 52 || ORB.y + RADIUS + ORB.speed * sin(ORB.degree) > YSIZE - 2)
	{
		if (ORB.y + RADIUS + ORB.speed * sin(ORB.degree) > YSIZE - 2)
		{
			iscontinuecard = 0;
		}
			ORB.speed *= 0.8;
			crashvertical();

	}
	//水平墙壁
	for (short int i = 0; i < 8; i++)
	{
		if(wall[i].islive == 1)
		{
			if (iscontinuecrashwall == 0&&wall[i].levver == 0 && (ORB.y + ORB.speed * sin(ORB.degree) + RADIUS  <= wall[i].y2 + 2 && ORB.y + ORB.speed * sin(ORB.degree) - RADIUS  >= wall[i].y1 - 2) && (wall[i].x1 >= ORB.x + ORB.speed * cos(ORB.degree) -RADIUS -2 && wall[i].x1 <= ORB.x + ORB.speed * cos(ORB.degree) + RADIUS + 2))
			{
				crashlevel();
				ORB.speed *= 1.3;
				iscontinuecrashwall = 1;
			}
			else if (iscontinuecrashwall == 0 &&wall[i].levver == 0 && (ORB.x + ORB.speed * cos(ORB.degree) + RADIUS <= wall[i].x2 + 2 && ORB.x + ORB.speed * cos(ORB.degree) - RADIUS >= wall[i].x1 - 2) && (wall[i].y1 >= ORB.y + ORB.speed * sin(ORB.degree) - RADIUS - 2 && wall[i].y1 <= ORB.y + ORB.speed * sin(ORB.degree) + RADIUS + 2))
			{
				crashvertical();
				ORB.speed *= 1.3;
				iscontinuecrashwall = 1;
				iscrashverwall = 1;
			}
			else
			{
				iscontinuecrashwall = 0;
				iscrashverwall = 0;
			}
		}
		else 
		{
			break;
		}
	}



	int tempdegree = abs(ORB.degree);
	while (tempdegree > 2 * PI)
	{
		tempdegree -= 2 * PI;
	}

	//因重力而有一个向下的分速度
#if 1
	if (ORB.y + ORB.speed * sin(ORB.degree) < YSIZE - RADIUS - 8 && iscrashverwall == 0)
	{		
		if(ORB.speed < 3)
		{
			ORB.y += 8;
		}
		if (ORB.speed >= 3 && ORB.speed <= 6)
		{
			ORB.y += 5;
		}
	}
#endif
	//因时间流逝而造成速度衰减if(>0)
#if 1
	if (currentticktime - oldtickslowtime >= 5000)
	{
		ORB.speed *= 0.98;
	}
#endif

	//最大速度限制
	if (ORB.speed > 40)
	{
		ORB.speed = 40;
	}
}



//总控所有弹幕的移动
void moveallbullet()
{

	//御札移动
	for (int i = 0; i <= maxYUZHA - 1; i++)
	{
		if (YUZHA[i].islive & 1)
		{
			YUZHA[i].y -= 30;

			//御札消弹
			for (int ji = 0; ji < maxbullet; ji++)
			{
				if (enemybullet[ji].islive == 1);//type
				{
		
					
					if (enemybullet[ji].isunbreak == 0 && iscrash(20, 28, YUZHA[i].x, YUZHA[i].y, enemybullet[ji].x, enemybullet[ji].y, enemybullet[ji].radius) == 1)
					{
						enemybullet[ji].islive = 0;
						YUZHA[i].islive = 0;
					}
					

				}
			}
		}

	
		//当御札离开画面后，清除他
		if (YUZHA[i].y <= 42)
		{
			YUZHA[i].islive = 0;
		}
	}



	//阴阳玉移动
	if(ORB.islive & 1)
	{
		moveorb();
		ORB.x += ORB.speed * cos(ORB.degree);
		ORB.y += ORB.speed * sin(ORB.degree);
	}

	//boss移动
	if (boss.hp >= 1)
	{
		boss.x += boss.speed * cos(boss.degree);
		boss.y += boss.speed * sin(boss.degree);
	}

	//敌弹移动
	for (int bulletid = 0; bulletid < maxbullet; bulletid++)
	{
		if (enemybullet[bulletid].islive & 1)
		{
			enemybullet[bulletid].x += enemybullet[bulletid].speed * cos(enemybullet[bulletid].degree);
			enemybullet[bulletid].y += enemybullet[bulletid].speed * sin(enemybullet[bulletid].degree);
			
			//敌弹移除屏幕
			if (enemybullet[bulletid].x <= 0 || enemybullet[bulletid].x > XSIZE || enemybullet[bulletid].y  > YSIZE)
			{
				enemybullet[bulletid].islive = 0;
			}

			if ((currentticktime - enemybullet[bulletid].oldunbreaktime > 200) && ((enemybullet[bulletid].x - ORB.x) * (enemybullet[bulletid].x - ORB.x) + (enemybullet[bulletid].y - ORB.y) * (enemybullet[bulletid].y - ORB.y) <= (RADIUS + enemybullet[bulletid].radius) * (RADIUS + enemybullet[bulletid].radius)) && enemybullet[bulletid].isunbreak == 0)
			{
				enemybullet[bulletid].islive = 0;
			}

			//侦测敌弹是否打到灵梦
			//人物判定点与半径框
			if (iscrash(32, 42, reimu.x + 5, reimu.y + 14, enemybullet[bulletid].x, enemybullet[bulletid].y, enemybullet[bulletid].radius) == 1)
			{
				if (currentticktime - reimu.oldunbreaktime >= 2500)
				{
					enemybullet[bulletid].islive = 0;
					enemybullet[bulletid].y = YSIZE + 100;
					reimu.oldunbreaktime = GetTickCount();
					respawn();

				}
			}
		}
		else
		{
			enemybullet[bulletid].y = YSIZE + 100;
		}
	}


	//reward移动
	moverewarditem();
}





//侦测阴阳玉是否接触灵梦，使其重生
#if 1
void ishurtreimu()
{
	if (iscrash(32, 42, reimu.x + 5, reimu.y + 14,ORB.x,ORB.y,RADIUS) == 1)
	{
		if (currentticktime - reimu.oldunbreaktime >= 2500)//并且不在无敌时间内
		{
			reimu.oldunbreaktime = GetTickCount();
			respawn();
		}
	}
}
#endif

//判断是否伤害到了敌方卡片
void ishurtcard()
{
	for (int i = 0; i < 207; i++)
	{
		//判断该卡片是否在场
		if (card[i].hp >= 1)
		{
			if (card[i].havebeencrashed == 0)//阴阳玉在卡片状态重置后重新接触卡片
			{
				//如果卡片和阴阳玉近距离接触，则掉一点血
				if (iscrash(40, 50, card[i].x, card[i].y,ORB.x,ORB.y,RADIUS) == 1)
				{
					card[i].havebeencrashed = 1;
					card[i].hp--;
					iscontinuecard++;
					rewardhurtcard(iscontinuecard,stage);
					if (iscontinuecard > maxiscontinuecard)
					{
						maxiscontinuecard = iscontinuecard;
					}					

					//发射弹幕/敌弹，后期修改弹幕类型
					//void makebullet(根据关卡)
					short int bulletid = 0;

							switch (stage)
							{
								//生成多个敌弹注意，要用bulleti + n
							case 1:case 2: 
								jexbullet
								initbullet(bulletid++, card[i].x + 20, card[i].y + 25, 10, reimu.x + 21, reimu.y + 50, 3,0);//type
								break;
							case 3:case 4:
								jexbullet
								initbullet(bulletid++, card[i].x + 20, card[i].y + 25, 10, reimu.x + 21, reimu.y + 50, 3, 0);//type
								jexbullet
								initbullet(bulletid++, card[i].x + 20, card[i].y + 25, 5, reimu.x + 21, reimu.y + 50, 9, 0);//type
								break;
							case 6:case 7:case 8: case 9:
								break;
							}
							

							//卡片生命掉完，移除
							if (card[i].hp == 0)
							{
								if (i == 0 && stage == 4)
								{
									initreward(2, card[i].x, card[i].y);
								}

								else if (rand() % 8 == 0)
								{
									initreward(1, card[i].x, card[i].y);
								}

							}
				}
			
			}
			if (iscrash(40, 50, card[i].x, card[i].y, ORB.x, ORB.y, RADIUS) != 1)//阴阳玉从该卡片上移开，恢复等待接触状态
			{

				card[i].havebeencrashed = 0;
			}
		}	
	}
}



//绘制场上所有非灵梦、boss物体
//不要flush
void drawallbullets()
{
	
	//绘制御札
	for (int i = 0; i <= maxYUZHA -1; i++)
	{
		if (YUZHA[i].islive & 1)
		{
			transparentimage(NULL, YUZHA[i].x, YUZHA[i].y, &yuzha, 0X4afc3f);
		}
	}


	//绘制阴阳玉
	if (ORB.islive & 1)
	{
		if (currentticktime - oldtickshoottime >= 5000)
		{
			if(hasplaycharge == 0)
			{
				mciSendString(_T("stop ccc"), NULL, 0, NULL);
				mciSendString(_T("close ccc"), NULL, 0, NULL);
				mciSendString(_T("open m\\hascharged.mp3 alias ccc"), NULL, 0, NULL);
				mciSendString(_T("play ccc"), NULL, 0, NULL);
				hasplaycharge = 1;
			}
			setfillcolor(YELLOW);
		}
		else
		{
			hasplaycharge = 0;
			setfillcolor(WHITE);
		}
		fillcircle(ORB.x, ORB.y, RADIUS);
	}

	setfillcolor(BLACK);

	//绘制敌弹
	for (short int i = 0; i < maxbullet; i++)
	{
		if (enemybullet[i].islive == 1)
		{
			fillcircle(enemybullet[i].x,enemybullet[i].y, enemybullet[i].radius);
		}
	}

	//绘制reward
	for (short int i = 0; i < 32; i++)
	{
		if (reward[i].islive == 1)
		{
			switch (reward[i].type)
			{
			case 1://点
				putimage(reward[i].x, reward[i].y, &rewardpointimg);
				break;
			case 2://bomb
				putimage(reward[i].x, reward[i].y, &rewardbombimg);
				break;
			}

		}
	}

	//绘制墙壁
	setlinecolor(YELLOW);
	setlinestyle(PS_SOLID,5);
	for (short int i = 0; i < 8; i++)
	{
		if (wall[i].islive == 1)
		{
			line(wall[i].x1, wall[i].y1, wall[i].x2, wall[i].y2);
		}
	}
	setlinecolor(BLACK);
	setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);

	//普通关才需要画卡片和塔楼
	if(stage % 5 != 0)
	{
		//绘制敌方卡片

		for (short int i = 0; i < 207; i++)
		{
			if (card[i].hp >= 4)
			{
				setfillcolor(GREEN);
				fillrectangle(card[i].x, card[i].y, card[i].x + 40, card[i].y + 50);
			}
			else if (card[i].hp == 3)
			{
				setfillcolor(YELLOW);
				fillrectangle(card[i].x, card[i].y, card[i].x + 40, card[i].y + 50);
			}
			else if (card[i].hp == 2)
			{
				setfillcolor(RGB(0xfd, 0x96, 0x2c));
				fillrectangle(card[i].x, card[i].y, card[i].x + 40, card[i].y + 50);
			}
			else if (card[i].hp == 1)
			{
				setfillcolor(RED);
				fillrectangle(card[i].x, card[i].y, card[i].x + 40, card[i].y + 50);
			}

		}
		//绘制敌方塔楼
		for (short int toweri = 0; toweri < 64; toweri++)
		{
			if (tower[toweri].islive == 1)
			{
				transparentimage(NULL, tower[toweri].x, tower[toweri].y, &statictower, 0X4afc3f);
			}
			else
			{
				break;
			}
		}
	}

	//绘制boss
	if (stage % 5 == 0)
	{
		transparentimage(NULL, boss.x, boss.y, &bossimg, 0X4afc3f);
	}
	
	//绘制debug数据
	//setlinecolor(BLACK);
	setlinecolor(RED);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
	line(0, 49, XSIZE, 49);
	settextstyle(45, 0, _T("Consolas"));
	settextcolor(RED);
	char debugnum[64] = { 0 };
	if (punishmode == 1)
	{
		sprintf(debugnum, "梦%c%d B%d !超时 cs=%ld/%s %d连/%d",reimu.type + 64, cscore.heartnum, cscore.bombnum,  cscore.c_score,hiscore, iscontinuecard,maxiscontinuecard);
	}
	else
	{
		sprintf(debugnum, "梦%c%d B%d T=%d(%d) cs=%ld/%s %d连/%d", reimu.type + 64,cscore.heartnum, cscore.bombnum, ctimeflow,punishtime, cscore.c_score,hiscore, iscontinuecard,maxiscontinuecard);
	}
	
	if (stage % 5 == 0)
	{
		char bossdatadisplay[8] = { 0 };
		sprintf(bossdatadisplay, "BOSS %d", boss.hp);
		outtextxy(5, 50, char2TCAHR(bossdatadisplay));
	}
	TCHAR* debugdisplay = char2TCAHR(debugnum);

	outtextxy(5, 0, debugdisplay);
	


}


//绘制灵梦移动时所有物体
void drawitemswhenmove()
{

	//绘制普通移动
	if (reimumove & CMD_LEFT || reimumove & CMD_RIGHT)
	{
		int eachstep = reimu.speed / 6;//灵梦每一步的步伐大小，共6步画完
		for (int stepi = 1; stepi <= 6; stepi++)
		{
			if (stepi <= 2)//前两步
			{
				cleardevice();
				if (reimumove & CMD_LEFT)//灵梦向左移动
				{
					reimu.x -= eachstep;
					transparentimage(NULL, reimu.x, reimu.y, &reimuleft1, 0X4afc3f);
				}
				else if (reimumove & CMD_RIGHT)//灵梦向右移动
				{
					reimu.x += eachstep;
					transparentimage(NULL, reimu.x, reimu.y, &reimuright1, 0X4afc3f);
				}

			}
			if (stepi >= 5)//后两步
			{
				cleardevice();
				if (reimumove & CMD_LEFT)//灵梦向左移动
				{
					reimu.x -= eachstep;
					transparentimage(NULL, reimu.x, reimu.y, &reimuleft3, 0X4afc3f);
				}
				else if (reimumove & CMD_RIGHT)//灵梦向右移动
				{
					reimu.x += eachstep;
					transparentimage(NULL, reimu.x, reimu.y, &reimuright3, 0X4afc3f);
				}

			}
			else//中间两步
			{
				cleardevice();
				if (reimumove & CMD_LEFT)//灵梦向左移动
				{
					reimu.x -= eachstep;
					transparentimage(NULL, reimu.x, reimu.y, &reimuleft2, 0X4afc3f);
				}
				else if (reimumove & CMD_RIGHT)//灵梦向右移动
				{
					reimu.x += eachstep;
					transparentimage(NULL, reimu.x, reimu.y, &reimuright2, 0X4afc3f);
				}

			}
			drawallbullets();
			FlushBatchDraw();
			tt.Sleep(5);
		}
	}


	//绘制滑铲移动
	else if (reimumove== CMD_RREAP )
	{
		double eachstep = 1.5  *reimu.speed / 6;//灵梦每一步的步伐大小，共6步画完
		for (int stepi = 1; stepi <= 6; stepi++)
		{
			if (stepi <= 2)//前两步
			{
				cleardevice();
				
					reimu.x += eachstep;
					transparentimage(NULL, reimu.x, reimu.y, &reimuright1, 0X4afc3f);
				

			}
			if (stepi >= 5)//后两步
			{
				cleardevice();
				
					reimu.x += eachstep;
					transparentimage(NULL, reimu.x, reimu.y, &reimuright3, 0X4afc3f);
				

			}
			else//中间两步
			{
				cleardevice();
				
					reimu.x += eachstep;
					transparentimage(NULL, reimu.x, reimu.y, &reimuright2, 0X4afc3f);
				

			}
			drawallbullets();
			FlushBatchDraw();
			tt.Sleep(5);
		}
	
	}
	else if (reimumove & CMD_LREAP)
	{
		double eachstep = 1.5 * reimu.speed / 6;//灵梦每一步的步伐大小，共6步画完
		for (int stepi = 1; stepi <= 6; stepi++)
		{
			if (stepi <= 2)//前两步
			{
				cleardevice();
				
					reimu.x -= eachstep;
					transparentimage(NULL, reimu.x, reimu.y, &reimuleft1, 0X4afc3f);
				

			}
			if (stepi >= 5)//后两步
			{
				cleardevice();
				
					reimu.x -= eachstep;
					transparentimage(NULL, reimu.x, reimu.y, &reimuleft3, 0X4afc3f);
				

			}
			else//中间两步
			{
				cleardevice();
				
					reimu.x -= eachstep;
					transparentimage(NULL, reimu.x, reimu.y, &reimuleft2, 0X4afc3f);
				

			}
			drawallbullets();
			FlushBatchDraw();
			tt.Sleep(5);
		}

	}
}


//绘制灵梦静止时所有物体
void drawitemswhenstatic()
{
	cleardevice();

	drawallbullets();

	//绘制静态灵梦
	transparentimage(NULL, reimu.x, reimu.y, &pixelreimu, 0X4afc3f);

	FlushBatchDraw();
	tt.Sleep(30);
}


//绘制每一关游戏结束后的统计
void printscore(int stage)
{
	cleardevice();
	char scorenum[22] = { 0 };
	char rewarddetail[64] = { 0 };
	
	sprintf(scorenum, " STAGE %d CLEAR!!", stage);
	

	TCHAR* stagedisplay = char2TCAHR(scorenum);

	settextstyle(60, 0, _T("Consolas"));
	outtextxy(260, 240, stagedisplay);

	settextstyle(45, 0, _T("Consolas"));
	sprintf(rewarddetail, "时间加分:%d,关卡固定分:%d", (160 * (punishtime - ctimeflow) > 0 ? 160 * (punishtime - ctimeflow) : 0), (stage - 1) * 320);
	
	outtextxy(120, 320, char2TCAHR(rewarddetail));

	sprintf(rewarddetail, "剩余资源加分:%d,最大连击数加分:%d", cscore.heartnum * 800 + cscore.bombnum * 300, (maxiscontinuecard * 80 >= 6400 ? 6400 : maxiscontinuecard * 80));
	outtextxy(120, 380, char2TCAHR(rewarddetail));
	FlushBatchDraw();
	tt.Sleep(3000);
	_getch();
}


//游戏主体
int gamemain(int* signalp,int endsignal)
{
	setbkcolor(BLUE);//背景色，后会每关不同
	cleardevice();
	//init
	reimu.type = endsignal;
	initreimu();
	cscore.c_score = 0;

	tt.Sleep(100);

	//加载灵梦图片
	
	loadimage(&pixelreimu, _T("resource\\pixelreimu.png"), 42, 56,false);
	loadimage(&reimuleft1, _T("resource\\reimul1.png"), 42, 56, false);
	loadimage(&reimuleft2, _T("resource\\reimul2.png"), 42, 56, false);	
	loadimage(&reimuleft3, _T("resource\\reimul3.png"), 42, 56, false);	
	loadimage(&reimuright1, _T("resource\\reimur1.png"), 42, 56, false);
	loadimage(&reimuright2, _T("resource\\reimur2.png"), 42, 56, false);	
	loadimage(&reimuright3, _T("resource\\reimur3.png"), 42, 56, false);
	loadimage(&yuzha, _T("resource\\yuzha.png"), 20, 28, false);
	loadimage(&statictower, _T("resource\\tower.png"), 40, 50, false);
	loadimage(&rewardpointimg, _T("resource\\rewardpoint.png"), 40, 40, false);
	loadimage(&rewardbombimg, _T("resource\\rewardbomb.png"), 40, 40, false);


	tt.Sleep(1000);
	BeginBatchDraw();

	FILE* score_num = fopen("result\\score.txt", "r");;
	fgets(hiscore, 14, (FILE*)score_num);
	
	reimumove = 0;
	int allclear = 0;
	
	stage = 1;

	//直到allclear正常结束
	while(allclear != 1)
	{
		//每局游戏前初始化内容
		initorb();
		iscontinuecard = 0;
		maxiscontinuecard = 0;

		oldtickmovetime = GetTickCount();
		oldtickshoottime = GetTickCount();
		oldtickbullettime = GetTickCount();
		oldtickslowtime = GetTickCount();
		reimu.oldunbreaktime = GetTickCount();
		timeflow = GetTickCount();

		iscontinuecrashwall = 0;
		iscrashverwall = 0;

		hasplaycharge = 0;

		for (int sptimei = 0; sptimei < 8; sptimei++)
		{
			oldspbullettime[sptimei] = GetTickCount();
		}

		allclear = initstage(stage);
		punishmode = 0;//是否惩罚模式
		punishtime = 0;//进入惩罚模式的时间
		switch (stage)//根据关卡判断时间是否满足进入惩罚模式
		{
		case 1:
			punishtime = 30;
			break;
		case 2:case 3:
			punishtime = 45;
			break;
		case 4:
			punishtime = 60;
			break;
		case 5:
			punishtime = 90;
			break;
		}

		while (1)
		{


			/************************满身疮痍后计分板****************************/
			if (cscore.heartnum <= 0)//死亡
			{
				setfillcolor(BLACK);
				cleardevice();
				settextcolor(WHITE);
				settextstyle(80, 0, _T("Consolas"));
				outtextxy(100, 250, _T("满身疮痍!!"));
				char cscorestr[15] = { 0 };
				sprintf(cscorestr, "%d", cscore.c_score);	
				outtextxy(50, 350, _T("你的分数为"));
				outtextxy(50, 450, char2TCAHR(cscorestr));
				FlushBatchDraw();
				tt.Sleep(4000);
				_getch();
				return 1;
			}

#if 1
			/*****************88888888*********时间相关设置**********88*********************/
			//计时器计录当前时间从而和上次某些操作相比较，判断是否有继续进行某些特殊操作的必要条件
			currentticktime = GetTickCount();
			ctimeflow = (currentticktime - timeflow) / 1000;//本局游戏已经经过的时间



			if (ctimeflow >= punishtime)//时间满足进入惩罚模式
			{
				punishmode = 1;
			}

			if(punishmode == 1)
			{
				if(currentticktime - oldspbullettime[0] >= 5000)
				{
					oldspbullettime[0] = GetTickCount();
					punishtimemode(stage);
				}
			}
			/*********************************************************************************/
#endif

					



			moveallbullet();

			
		//判断卡片或boss是否受到攻击，并进行反馈
			if(stage % 5 != 0)
			{
				ishurtcard();
			}
			else if (stage % 5 == 0)
			{
				ishurtboss();
			}


			/***********************关卡自带特殊弹幕设定*****************************************/
			//需要不同关卡不同的触发时间
			//虚空发射弹幕
			switch (stage)
			{
			case 1:case 2:
				break;
			case 3:case 4:
				if (currentticktime - oldspbullettime[1] > 5000)
				{
					oldspbullettime[1] = GetTickCount();
					stage3sp();
				}
				break;
			}
#if 1
			//塔楼发射弹幕
			switch (stage)
			{
			case 1: case 2:case 3:case 4:
				if (currentticktime - oldspbullettime[2] > 3500)
				{
					oldspbullettime[2] = GetTickCount();
					stage2to();
				}
				break;
			}

			//boss关使用boss技能，转到bossstage.cpp
			if (stage % 5 == 0)
			{
				bossskill(stage);
			}
#endif
			/******************************************************************************/

			cmdreimu();

			ishurtreimu();

			isrewardheart();
			
			//判断方向键是否松开按下
			if ((currentticktime)-oldtickmovetime >= 40)
			{
				reimumove = 0;
			}

			//judgeall

			if (reimumove == 0)
			{
				drawitemswhenstatic();
#if 0
				//drawitemswhenstatic有某段时间不可用，故直接代替，如果再不行尝试考虑宏
				cleardevice();
				drawallbullets();
				transparentimage(NULL, reimu.x, reimu.y, &pixelreimu, 0X4afc3f);
				FlushBatchDraw();
				tt.Sleep(30);
#endif
			}
			else
			{
				drawitemswhenmove();
			}




			//判断是否按下esc菜单

			//画灵梦移动后的图像


			//控制滑铲频率

			//弃置的古代光栅
			/*putimage(reimu.x, reimu.y, &pixelreimu, SRCAND);
			putimage(reimu.x, reimu.y, &pixelreimu, SRCPAINT);*/


			/**************本关游戏结束判定********************/
			//判断是否打完全部方块
			int sum = 0;
			for (int cardii = 0; cardii < 207; cardii++)
			{
				sum += card[cardii].hp;
			}
			//卡片全打完或者boss消灭
			if ((sum <= 0 && (stage % 5) != 0)|| (boss.hp <= 0 && stage % 5 == 0))
			{
#if 0
				switch (stage)//根据关卡和时间进行奖励
				{
				case 1:case 2:case 3:case 4: case 5:
					if (ctimeflow < punishtime)
					{
						//
					}
					break;
				}
#endif
				cscore.c_score += (160 * (punishtime - ctimeflow) > 0? 160 * (punishtime - ctimeflow):0);//时间加分
				cscore.c_score += (stage - 1) * 320;//关卡固定分数
				cscore.c_score += cscore.heartnum * 800 + cscore.bombnum * 300;//残机和bomb奖励
				cscore.c_score += (maxiscontinuecard * 80 >= 6400 ? 6400 : maxiscontinuecard * 80);


				printscore(stage);
				stage++;
				break;
			}
			

			/******************************************************/
		}
	}

	_getch();
	

	//游戏总结算
	saveresult(cscore.c_score);
	return 0;
}

//画游戏过程中上方的状态数值栏，如残机数，分数等
void drawgameflame();


