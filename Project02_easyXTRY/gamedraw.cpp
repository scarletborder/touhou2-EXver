#include"menuh.h"
#include"MyTimer.h"
/********************************/
//2022年11月17日分离于gamecmd
//用途：总绘制游戏中的所有图画
// 每30ms一帧画面(15+15)
//ps:MyTimer.h不能同时在两个文件同时使用
/********************************/

//外部引用gameelements的变量
#if 1
extern IMAGE pixelreimu;
extern IMAGE reimuleft1;
extern IMAGE reimuleft2;
extern IMAGE reimuleft3;
extern IMAGE reimuright1;
extern IMAGE reimuright2;
extern IMAGE reimuright3;
extern IMAGE yuzha;
extern IMAGE statictower;
extern IMAGE bossimg;
extern IMAGE rewardpointimg;
extern IMAGE rewardbombimg;

//灵梦是否移动，以及朝向
extern int reimumove;
extern short int stage;

extern int iscontinuecard ;//持续连击卡片个数
extern int maxiscontinuecard ;

extern int ctimeflow ;
extern char hiscore[15];

extern DWORD oldtickshoottime;
extern DWORD currentticktime;//当前时间

extern short int hasplaycharge ;

extern unsigned short int punishmode ;
extern int punishtime ;

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
#endif

/****************************************************/
//绘制场上所有非灵梦物体
//在这个函数中不要flush
void drawallbullets()
{

	//绘制御札
	for (int i = 0; i <= maxYUZHA - 1; i++)
	{
		if (YUZHA[i].islive & 1)
		{
			transparentimage(NULL, YUZHA[i].x, YUZHA[i].y, &yuzha, 0X4afc3f);
		}
	}


	//绘制阴阳玉
	if (ORB.islive & 1)
	{
		//御札连射充能完毕，变色
		if (currentticktime - oldtickshoottime >= 5000)
		{
			if (hasplaycharge == 0)
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
			fillcircle(enemybullet[i].x, enemybullet[i].y, enemybullet[i].radius);
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
				//1up
			}

		}
	}


	//绘制墙壁
	setlinecolor(YELLOW);
	setlinestyle(PS_SOLID, 5);
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
	if (stage % 5 != 0)
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


	//boss关卡绘制boss
	if (stage % 5 == 0)
	{
		transparentimage(NULL, boss.x, boss.y, &bossimg, 0X4afc3f);
	}


	//在画面上方绘制数据,如残机数，分数等
	//setlinecolor(BLACK);
	setlinecolor(RED);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
	line(0, 49, XSIZE, 49);
	settextstyle(45, 0, _T("Consolas"));
	settextcolor(RED);
	char debugnum[64] = { 0 };
	if (punishmode == 1)
	{
		sprintf(debugnum, "梦%c%d B%d !超时 cs=%ld/%s %d连/%d", reimu.type + 64, cscore.heartnum, cscore.bombnum, cscore.c_score, hiscore, iscontinuecard, maxiscontinuecard);
	}
	else
	{
		sprintf(debugnum, "梦%c%d B%d T=%d(%d) cs=%ld/%s %d连/%d", reimu.type + 64, cscore.heartnum, cscore.bombnum, ctimeflow, punishtime, cscore.c_score, hiscore, iscontinuecard, maxiscontinuecard);
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
//等待hydicator绘制滑铲图片后进行替换
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
	else if (reimumove == CMD_RREAP)
	{
		double eachstep = 1.5 * reimu.speed / 6;//灵梦每一步的步伐大小，共6步画完
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