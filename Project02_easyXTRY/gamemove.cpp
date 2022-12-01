#include"menuh.h"
/************************************/
//分离于gamecmd，2022年11月17日
//用途：总处理游戏中所有物体的移动，特殊物体发生交互的监测和处理
//作者：scarletborder
/************************************/

//引用游戏正文中用到的元素
#if 1
//计时各种时间间隔

//当前时间
extern DWORD currentticktime;

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

//计数器和是否器

//是否与墙发生碰撞
extern short int iscontinuecrashwall;
extern short int iscrashverwall;

extern int bombhurt;//炸弹伤害

extern int reimumove;//灵梦是否移动，以及朝向

extern int iscontinuecard;//持续连击卡片个数
extern int maxiscontinuecard;//本关游戏中，最大连击数


extern short int stage;//当前关卡

//结构体


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


/*****************判断阴阳玉是否与某个矩形物体相撞************************
阴阳玉总大小49*49，半径为RADIUS
输入：矩形的宽，矩形的高, 矩形定位点x, 矩形定位点y;圆心坐标，圆的半径
输出：整数1=YES,0=NO*/
int iscrash(int width, int height, int jx, int jy, double cirx, double ciry, double r)
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
		uy = uy;
	}
	else if (ux >= 0 && uy < 0)
	{
		ux = ux;
		uy = 0;
	}
	// 第3步：长度平方与半径平方比较
	if (((ux) * (ux)+(uy) * (uy)) <= r * r + 2)
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
//四周360判定
void aftercrash(double jjx, double jjy, double width, double height, double jp)
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
//底部180判定
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
		if (iscrash(20, 28, YUZHA[i].x, YUZHA[i].y, ORB.x, ORB.y, RADIUS) == 1)
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
	if (ORB.x - RADIUS + ORB.speed * cos(ORB.degree) < 2 || ORB.x + RADIUS + ORB.speed * cos(ORB.degree) > XSIZE - 2)
	{

		ORB.speed *= 0.8;
		crashlevel();

	}
	//竖直
	else if (ORB.y - RADIUS + ORB.speed * sin(ORB.degree) < 52 || ORB.y + RADIUS + ORB.speed * sin(ORB.degree) > YSIZE - 2)
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
		if (wall[i].islive == 1)
		{
			if (iscontinuecrashwall == 0 && wall[i].levver == 0 && (ORB.y + ORB.speed * sin(ORB.degree) + RADIUS <= wall[i].y2 + 2 && ORB.y + ORB.speed * sin(ORB.degree) - RADIUS >= wall[i].y1 - 2) && (wall[i].x1 >= ORB.x + ORB.speed * cos(ORB.degree) - RADIUS - 2 && wall[i].x1 <= ORB.x + ORB.speed * cos(ORB.degree) + RADIUS + 2))
			{
				crashlevel();
				ORB.speed *= 1.3;
				iscontinuecrashwall = 1;
			}
			else if (iscontinuecrashwall == 0 && wall[i].levver == 0 && (ORB.x + ORB.speed * cos(ORB.degree) + RADIUS <= wall[i].x2 + 2 && ORB.x + ORB.speed * cos(ORB.degree) - RADIUS >= wall[i].x1 - 2) && (wall[i].y1 >= ORB.y + ORB.speed * sin(ORB.degree) - RADIUS - 2 && wall[i].y1 <= ORB.y + ORB.speed * sin(ORB.degree) + RADIUS + 2))
			{
				if (ORB.speed < 4)
				{
					ORB.speed = 0;
				}
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
	if (ORB.y + ORB.speed * sin(ORB.degree) < YSIZE - RADIUS - 8 && iscrashverwall == 0 && iscontinuecrashwall == 0)
	{
		if (ORB.speed < 3)
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
	if (ORB.islive & 1)
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
			if (enemybullet[bulletid].x <= 0 || enemybullet[bulletid].x > XSIZE || enemybullet[bulletid].y > YSIZE)
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
	if (iscrash(32, 42, reimu.x + 5, reimu.y + 14, ORB.x, ORB.y, RADIUS) == 1)
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
				if (iscrash(40, 50, card[i].x, card[i].y, ORB.x, ORB.y, RADIUS) == 1)
				{
					card[i].havebeencrashed = 1;
					card[i].hp--;
					iscontinuecard++;
					rewardhurtcard(iscontinuecard, stage);
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
							initbullet(bulletid++, card[i].x + 20, card[i].y + 25, 10, reimu.x + 21, reimu.y + 50, 3, 0);//type
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


