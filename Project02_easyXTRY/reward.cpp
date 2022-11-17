#include"menuh.h"
/**************奖励模块*********************/
//用于定义游戏正文中用到的元素
#if 1

//游戏中各种奖励结构
extern struct rewards reward[32];

extern struct player_status reimu;

//游戏上方的计分板
extern struct game_score cscore;

extern unsigned int iscontinuepoint;
extern short int stage;

#endif

/**********根据连打卡片数量来提供奖励分数***********/
void rewardhurtcard(int iscontinuecard,int stage)
{
//根据关卡不同决定基础分不同
	int tempscorepp = 10 * (1 + stage / 5) + 3 * (iscontinuecard - 1) * (iscontinuecard - 1);
	if (tempscorepp >= 3200)
	{
		tempscorepp = 3200;
	}
	cscore.c_score += tempscorepp;
}


/****************接到点道具加分项目*********************/

//初始化各种奖励道具
//在点道具离开屏幕后，islive = 0，同时清空iscontinuepoint
//道具通用像素大小是40*40
//输入：奖励的类型（1点，2b，3残）
//		xy->定位点坐标，为标准坐标与卡片的定位点重合
void initreward(int type,int x,int y)
{
	for (short int i = 0; i < 32; i++)
	{
		if (reward[i].islive == 0)
		{
			reward[i].islive = 1;
			reward[i].type = type;
			reward[i].x = x;
			reward[i].y = y;
			reward[i].downorup = 0;
			reward[i].isup = 0;
			break;
		}		
	}
}

//移动所有的奖励道具
void moverewarditem()
{
	for (short int i = 0; i < 32; i++)
	{
		if (reward[i].islive == 1)
		{
			if (reward[i].downorup == 0 && reward[i].isup == 0)//正在下坠，没有反弹过
			{
				if (reward[i].y + 6 >= YSIZE)//检测到即将出去，开始反弹
				{
					reward[i].downorup = 1;
					reward[i].y -= 6;
					reward[i].isup = 1;
					break;
				}
				else
				{
					reward[i].y += 6;
				}				
			}

			else if (reward[i].downorup == 1)//上弹状态
			{
				if (reward[i].y < 400)
				{
					reward[i].downorup = 0;
					break;
				}
				else
				{
					reward[i].y -= 10;
				}
			}

			else if(reward[i].downorup == 0 && reward[i].isup == 1)//下坠，不再反弹
			{
				if (reward[i].y > YSIZE + 4)
				{
					reward[i].islive = 0;
					reward[i].y = 2 * YSIZE;
					iscontinuepoint = 0;
					break;
				}
				else
				{
					reward[i].y += 6;
				}

			}
//end if
		}
		//receive
		if (reward[i].islive==1&&reward[i].y >= reimu.y - 10 && !(reward[i].x > reimu.x + 42 || reimu.x > reward[i].x + 40))
		{
			reward[i].islive = 0;//被接到
			reward[i].y = 2 * YSIZE;

			switch (reward[i].type)//根据接到东西的种类反馈
			{
			case 1://point
				iscontinuepoint++;
				rewardpoint(iscontinuepoint, stage);
				break;
			case 2:
				cscore.bombnum++;
				break;
			case 3:
				cscore.heartnum++;
				break;
			}
			break;
		}
//end for
	}
}



//判断是否接到点
//已经和moverewad合并
void isreceivereward()
{
	for (short int i = 0; i < 32; i++)
	{
		if (reward[i].islive == 1)
		{
			if(reward[i].y >= reimu.y && !(reward[i].x > reimu.x + 42 || reimu.x > reward[i].x + 40))
			{
				reward[i].islive = 0;//被接到

				switch (reward[i].type)//根据接到东西的种类反馈
				{
				case 1://point
					rewardpoint(iscontinuepoint, stage);
					break;
				case 2:
					cscore.bombnum++;
					break;
				case 3:
					cscore.heartnum++;
					break;
				}
				break;
			}
		}

	}

}


void rewardpoint(int iscontinuepoint,int stage)
{
	//iscontinuepoint++;
	//根据关卡不同决定基础分不同
	int tempscorepp = 100 * (1 + stage / 5) + 30 * (iscontinuepoint - 1) * (iscontinuepoint - 1);
	if (tempscorepp >= 64000)
	{
		tempscorepp = 64000;
	}
	cscore.c_score += tempscorepp;
}

void harvestallreward()
{
	for (short int i = 0; i < 32; i++)
	{
		if (reward[i].islive == 1)
		{
			reward[i].islive = 0;
			switch (reward[i].type)
			{
			case 1://point
				rewardpoint(iscontinuepoint, stage);
				break;
			case 2:
				cscore.bombnum++;
				break;
			case 3:
				cscore.heartnum++;
				break;
			}
		}
	}
}


/***********************************************************************************************************/



/**************************************************/
//每25w分奖励一个残机
static int rewarddegree = 1;
void isrewardheart()
{
	if (cscore.c_score >= 250000 * rewarddegree)
	{
		mciSendString(_T("close 1up"), NULL, 0, NULL);
		mciSendString(_T("open m\\1up.mp3 alias 1up"), NULL, 0, NULL);
		mciSendString(_T("play 1up"), NULL, 0, NULL);
		cscore.heartnum++;
		rewarddegree++;
	}

}
