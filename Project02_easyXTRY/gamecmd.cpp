#include"menuh.h"
#include<iostream>
/*********************************************/
//gamecmd.cpp
// 最重要的源文件
//用处1：初始化灵梦，阴阳玉，重生灵梦
//用处2：根据接受到的键盘命令做出反馈
//用处4：控制游戏中的流程
//用处4：章末结算
/*********************************************/

//引用游戏正文中用到的元素
#if 1
//计时各种时间间隔，图像声明

extern DWORD currentticktime;//当前时间

//移动间隔
extern DWORD oldtickmovetime;

//御札发射间隔
extern DWORD oldtickshoottime;

//弹幕更新间隔
extern DWORD oldtickbullettime;

//滑铲间隔
extern DWORD oldtickreaptime;

//阴阳玉减速间隔
extern DWORD oldtickslowtime;

//游戏单局开始前计时，计算出进行过程中已用时间
extern DWORD timeflow;

//上一次发射关卡特殊弹幕时间，共8个
//0固定为惩罚弹幕，1-7为虚空/塔楼
extern DWORD oldspbullettime[8];

DWORD continuetime;

//wall
extern short int iscontinuecrashwall;
extern short int iscrashverwall;

extern int bombhurt;//炸弹伤害

//灵梦是否移动，以及朝向
extern int reimumove;

extern int iscontinuecard;//持续连击卡片个数
extern int maxiscontinuecard;

extern unsigned int iscontinuepoint;//持续接点个数

extern short int stage;

extern int ctimeflow;

extern unsigned short int punishmode;
extern int punishtime;


extern char hiscore[15];

extern short int hasplaycharge;

short int isendgame;

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



//通用图像文件
IMAGE pixelreimu;
IMAGE reimuleft1;
IMAGE reimuleft2;
IMAGE reimuleft3;
IMAGE reimuright1;
IMAGE reimuright2;
IMAGE reimuright3;
IMAGE yuzha;
IMAGE statictower;
IMAGE bossimg;
IMAGE rewardpointimg;
IMAGE rewardbombimg;

#endif




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

	Sleep(50);
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
	Sleep(50);
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


/******************获得键盘上操纵灵梦的命令*************************/
void cmdreimu()
{
	int optmove = GETCMD();
	int firstdo = 0;//优先占用：部分操作会使该值变为1，跳过之后的所有移动检测
	int isx = 0;

		/***********暂停游戏********************/
	if (optmove & CMD_ESC && currentticktime - continuetime >= 200)
	{
		DWORD pausetime = GetTickCount();
		escmenuflame();
		while (1)
		{
			Sleep(100);
			if ((GETCMD() & CMD_ESC || GETCMD() & CMD_CONFIRM) && GetTickCount() - pausetime >= 400)
			{
				break;
			}
			if (GETCMD() & CMD_SPECIAL && GetTickCount() - pausetime >= 400)
			{
				isendgame = 1;
				break;
			}
		}

		continuetime = GetTickCount();
		currentticktime += continuetime - pausetime;
		oldtickmovetime += continuetime - pausetime;
		oldtickshoottime += continuetime - pausetime;
		oldtickbullettime += continuetime - pausetime;
		oldtickreaptime += continuetime - pausetime;
		oldtickslowtime += continuetime - pausetime;
		timeflow += continuetime - pausetime;
		for(int iiii = 0;iiii < 8;iiii ++)
		{
			oldspbullettime[iiii] += continuetime - pausetime;
		}

	}

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





//游戏主体
int gamemain(int charcter_type)
{
	setbkcolor(BLUE);//背景色，后会每关不同
	cleardevice();
	//init
	reimu.type = charcter_type;
	initreimu();
	cscore.c_score = 0;
	isendgame = 0;

	Sleep(100);

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


	Sleep(1000);
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
		continuetime = GetTickCount();

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
				//是否续关...,续关记号...

				//否则
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
				Sleep(4000);
				_getch();
				return 0;
			}

			//中途退出
			if (isendgame == 1)
			{
				return 0;
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
				Sleep(30);
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

	//根据游戏线路
	//....
	//if 续关...
	return 1;
}





