#include"menuh.h"
extern struct enemycards card[207];
extern struct bullets enemybullet[maxbullet];
extern struct TOWER tower[32];
extern struct BOSS boss;

extern struct player_status reimu;
extern DWORD currentticktime;
extern IMAGE bossimg;
extern WALL wall[8];
extern struct rewards reward[32];


//生成卡片塔楼弹幕硬件相关
//不要修改!!!
#if 1

/************每一局游戏前初始化卡片***************/
//输入:卡片的id，如第一个卡片id为0，第二个为1，最多207个
//		x,y，卡片的左上方定位点
//		hp 即卡片的初始血量
//输出：（全局）（结构）将这个卡片的islive设置为1，重新设置为没有被阴阳玉一直接触,x,y,hp设置为输入值
void initcard(int id, int x, int y, int hp)
{
	card[id].hp = hp;
	card[id].x = x;
	card[id].y = y;
	card[id].havebeencrashed = 0;
}
//简单版本生成卡片，x、y为标准格子序号(1~23/1~8)
void easyinitcard(int id, int x, int y, int hp)
{
	initcard(id, xlef + (x - 1) * xsp, ytop + (y - 1) * ysp, hp);
}


/****************每一局游戏前初始化塔楼**********************/
//输入：塔楼的id，第一个为0，第二个为1，最多32个
//		x,y，塔楼左上方定位点
//输出：（全局）（结构）id指向的塔楼islive设置为1，并以x,y为定位点生成塔楼
void inittower(int id, int x, int y)
{
	tower[id].islive = 1;
	tower[id].x = x;
	tower[id].y = y;
}
//简单版本生成塔楼，x、y为标准格子序号(1~23 / 1~8)
void easyinittower(int id, int x, int y)
{
	inittower(id, xlef + (x - 1) * xsp, ytop + (y - 1) * ysp);
}



/***************初始化敌方弹幕**********************/
//输入：敌弹id（一般是循环计数变量），生成位置的坐标，速度
//		朝向的坐标（例如自机狙是reimu.x+21,reimu.y+50）
//		radius:弹幕的半径大小
//		isunbreak:是否不可被阴阳玉/御札消除(1=不可被消除，0=可被消除）bomb消弹不影响
// 输出：（全局）（结构）以(x,y)为中心，生成一个弹幕，以speed的速度向(aimx,aimy)移动
void initbullet(int id, int x, int y, double speed,int aimx,int aimy, int radius,int isunbreak)
{
	enemybullet[id].islive = 1;
	aimreimubullet(x, y, id, aimx, aimy);
	enemybullet[id].speed = speed;
	enemybullet[id].x = x;
	enemybullet[id].y = y;
	enemybullet[id].radius = radius;
	enemybullet[id].isunbreak = isunbreak;
	enemybullet[id].oldunbreaktime = GetTickCount();
}



/****************敌弹生成时瞄准某个位置*********************/
//输入：所需要生成敌弹的位置坐标中心，敌弹id;某个位置的坐标中心
//输出：（全局）敌弹角度
void aimreimubullet(double x, double y, int id, double aimx, double aimy)
{

	//垂直特殊情况
	if (x == aimx)
	{
		enemybullet[id].degree = PI / 2;
	}
	else
	{
		enemybullet[id].degree = atan((y - aimy) / (x - aimx));
		while (enemybullet[id].degree < 0)
		{
			enemybullet[id].degree += PI;
		}
	}


}


//每关前初始化墙壁
void initwall(int id,int x1, int y1, int x2, int y2)
{
	wall[id].islive = 1;
	wall[id].x1 = x1;
	wall[id].x2 = x2;
	wall[id].y1 = y1;
	wall[id].y2 = y2;
	if(x1 == x2)
	{
		wall[id].levver = 1;
	}
	else
	{
		wall[id].levver = 0;
	}
}

void easyinitwall(int id, int qx1, int qy1, int qx2, int qy2)
{
	initwall(id, xlef + (qx1 - 1) * xsp, ytop + (qy1 - 1) * ysp, xlef + (qx2- 1) * xsp, ytop + (qy2 - 1) * ysp);
}
#endif



/*************************关卡特殊弹幕相关****************************************/


/**********************惩罚模式的弹幕*****************************/
//作用：根据不同关卡，放置惩罚模式的弹幕
//惩罚模式触发时间在gamecmd里设置
//如果需要要生成下一个弹幕，请先在一行内输入jexbullet ，不用分号！！
void punishtimemode(int stage)
{
	int bulletid = 0;
	switch (stage)//根据关卡决定惩罚种类
	{
	case 1:case 2:case 3:case 4: 
		
				jexbullet
				//生成多个敌弹注意，要用bulleti + n	
				initbullet(bulletid, 10, 20, 15, reimu.x + 21, reimu.y + 50, 9, 0);//type
				jexbullet
				initbullet(bulletid, 10, 20, 10, reimu.x + 21, reimu.y + 50, 9, 0);//type	
				jexbullet
				initbullet(bulletid, XSIZE - 10, 20, 15, reimu.x + 21, reimu.y + 50, 9, 0);//type
				jexbullet
				initbullet(bulletid, XSIZE - 10, 20, 10, reimu.x + 21, reimu.y + 50, 9, 0);//type	
				break;

		break;
	case 5:
		jexbullet
			initbullet(bulletid++, boss.x + xsp, boss.y + 4 * ysp, 8, boss.x + xsp, YSIZE, 5, 0);
		jexbullet
			initbullet(bulletid++, boss.x + xsp, boss.y + 3 * ysp, 8, boss.x + xsp, YSIZE, 5, 0);
		jexbullet
			initbullet(bulletid++, boss.x + 100, boss.y + 4 * ysp, 10, boss.x + xsp, YSIZE, 20, 0);
		jexbullet
			initbullet(bulletid++, boss.x + 4 * xsp, boss.y + 4 * ysp, 8, boss.x + xsp, YSIZE, 5, 0);
		jexbullet
			initbullet(bulletid++, boss.x + 4 * xsp, boss.y + 3 * ysp, 8, boss.x + xsp, YSIZE, 5, 0);
		jexbullet
			initbullet(bulletid++, boss.x + xsp, boss.y + 4 * ysp, 12, boss.x + xsp, YSIZE, 5, 0);
		jexbullet
			initbullet(bulletid++, boss.x + xsp, boss.y + 3 * ysp, 12, boss.x + xsp, YSIZE, 5, 0);
		jexbullet
			initbullet(bulletid++, boss.x + 100, boss.y + 4 * ysp, 10, boss.x + xsp, YSIZE, 20, 0);
		jexbullet
			initbullet(bulletid++, boss.x + 4 * xsp, boss.y + 4 * ysp, 12, boss.x + xsp, YSIZE, 5, 0);
		jexbullet
			initbullet(bulletid++, boss.x + 4 * xsp, boss.y + 3 * ysp, 12, boss.x + xsp, YSIZE, 5, 0);
	default:
		break;
	}
}



/**************************定时发射弹幕*********************************/

//第二关塔楼弹幕
void stage2to()
//两塔同时向灵梦偏左和偏右发射弹幕
{
	for(short int toweri = 0;toweri < 32;toweri++)
	{
		if (tower[toweri].islive == 0)
		{
			return;
		}
		short int bulletid = 0;
		jexbullet
				initbullet(bulletid++, tower[toweri].x + 20, tower[toweri].y + 25, 10, reimu.x + 61, reimu.y + 50, 5, 0);//塔楼,灵梦偏击
				jexbullet
				initbullet(bulletid++, tower[toweri].x + 20, tower[toweri].y + 25, 10, reimu.x -19, reimu.y + 50, 5, 0);//塔楼,灵梦偏击
				jexbullet
	}
}


void stage3sp()
{
	short int bulletid = 0;
	jexbullet

			//生成多个敌弹注意，要用bulleti + n	
			initbullet(bulletid++, 20,  50, 10,  reimu.x+21, reimu.y+50, 3, 0);//虚空
			jexbullet			
			initbullet(bulletid++, 20, 20, 5, reimu.x+21, reimu.y+50, 9, 0);//虚空
			jexbullet
			initbullet(bulletid++, XSIZE - 20, 50, 10, reimu.x+21, reimu.y+50, 3, 0);//虚空
			jexbullet			
			initbullet(bulletid++, XSIZE - 20, 20, 5, reimu.x+21, reimu.y+50, 9, 0);//虚空
			jexbullet
			initbullet(bulletid++, 0,360, 5, reimu.x + 21, reimu.y + 50, 25, 0);//虚空
			jexbullet
			initbullet(bulletid++, XSIZE, 360, 5, reimu.x + 21, reimu.y + 50, 25, 0);//虚空
			return;
}








/*******************关卡初始化********************************/
//分为分配初始化卡片，
//序号，x坐标,y坐标，血量
//可以用循环来连续设置一整行的卡片，记得温习初中一次函数y = kx + b
//塔楼如果数量过少，我懒得弄i++了，从序号0开始
void stage1()//debug关卡
{
	int i = 0;
	for (int j = 7; j <= 17; j++)
	{
		easyinitcard(i++, j, 1, 1);
	}
	for (int j = 5; j <= 19; j++)
	{
		easyinitcard(i++, j, 3, 1);
	}
	easyinitcard(i++, 9, 2, 1);
	easyinitcard(i++, 15, 2, 1);
	for (int j = 4; j <= 7; j++)
	{
		easyinitcard(i++,9 , j, 1);
		easyinitcard(i++, 15, j, 1);
	}

}

void stage2()
{
	int i = 0;
	for (int j = 6; j <= 18; j++)
	{
		easyinitcard(i++, j, 5,3);
	}
	easyinitcard(i++, 12, 1, 2);
	easyinitcard(i++, 11, 2, 2);
	easyinitcard(i++, 13, 2, 2);
	easyinitcard(i++, 10, 3, 2);
	easyinitcard(i++, 14, 3, 2);
	easyinitcard(i++, 15, 4, 2);
	easyinitcard(i++, 9, 4, 2);

	easyinittower(0, 7, 2);
	easyinittower(1, 17, 2);
}

void stage3()
{
	int i = 0;
	for (int line = 5; line <= 19; line++)
	{
		easyinitcard(i++, line, 1, 3);
	}

	for (int line = 2; line <= 6; line++)
	{
		easyinitcard(i++, 5, line, 2);
		easyinitcard(i++, 6, line, 2);
		easyinitcard(i++, 18, line, 2);
		easyinitcard(i++, 19, line, 2);
	}

	easyinittower(0, 4, 2);
	easyinittower(1, 7, 2);
	easyinittower(2, 17, 2);
	easyinittower(3, 20, 2);
}

void stage4()
{
	int i = 0;
	for (int line = 9; line <= 15; line++)
	{
		easyinitcard(i++, line, 1, 3);
	}
	for (int line = 4; line <= 8; line++)
	{
		easyinitcard(i++,  line, 10 - line, 4);
	}
	for (int line = 16; line <= 20; line++)
	{
		easyinitcard(i++,  line,line - 14, 4);
	}
	easyinitcard(i++, 11, 2, 5);
	easyinitcard(i++, 12, 2, 5);
	easyinitcard(i++, 13, 2, 5);
	easyinitcard(i++, 11, 3, 5);
	easyinitcard(i++, 13, 3, 5);
	easyinitcard(i++, 11, 4, 5);
	easyinitcard(i++, 12, 4, 5);
	easyinitcard(i++, 13, 4, 5);
	easyinittower(0, 8, 1);
	easyinittower(1, 16, 1);
	easyinittower(2, 12, 3);

	easyinitwall(0, 8, 6, 17, 6);
}

void stage5()
{
	boss.hp = 16;
	boss.x = xlef + 9 * xsp;
	boss.y = ytop + 1 * ysp;
	chat1();
}

void stage6()
{



}
/**************初始化关卡main****************************/
int initstage(int num)
{
	mciSendString(_T("close nextstage"), NULL, 0, NULL);
	mciSendString(_T("open m\\nextstage.mp3 alias nextstage"), NULL, 0, NULL);
	mciSendString(_T("play nextstage"), NULL, 0, NULL);
	Sleep(250);
	//重置弹幕，卡片序号，塔楼状态,boss,墙
	for (int bulleti = 0; bulleti < maxbullet; bulleti++)
	{
		enemybullet[bulleti].islive = 0;
	}

	for (int cardi = 0; cardi < 207; cardi++)
	{
		card[cardi].hp = 0;
	}

	for (int toweri = 0; toweri < 32; toweri++)
	{
		tower[toweri].islive = 0;
	}

	boss.degree = 0;
	boss.havebeencrashed = 0;
	boss.speed = 0;

	for (short int i = 0; i < 8; i++)
	{
		wall[i].islive = 0;
	}

	for (short int i = 0; i < 32; i++)
	{
		reward[i].islive = 0;
	}

	Sleep(50);


	//根据关卡输入，来初始化特定关卡
	switch (num) 
	{
	case 1:
		endbgm;
		startbgm(m\\(2).MID);
		stage1();
		break;
	case 2:
		stage2();
		break;
	case 3:
		stage3();
		break;
	case 4:		
		stage4();
		break;
	case 5:
		endbgm;
		startbgm(m\\(7).MID);
		loadimage(&bossimg, _T("resource\\tankgril.png"), 200, 250, false);
		stage5();
		break;









	}

	if (num == maxstage)
	{
		return 1;
	}

	Sleep(200);
}


/********生成敌弹示例**********/
#if 0
for (int bulletid = 0; bulletid < maxbullet; bulletid++)
{
	if (enemybullet[bulletid].islive == 0)
	{
		//生成多个敌弹注意，要用bulleti + n	
		initbullet(bulletid++, 20, 50, 10, reimu.x + 21, reimu.y + 50, 3, 0);//type
		jexbullet
			initbullet(bulletid++, 20, 40, 5, reimu.x + 21, reimu.y + 50, 9, 0);//type
	
		break;
		}
	else
	{
		continue;
	}
	}
#endif