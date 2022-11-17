#include"menuh.h"
/**************����ģ��*********************/
//���ڶ�����Ϸ�������õ���Ԫ��
#if 1

//��Ϸ�и��ֽ����ṹ
extern struct rewards reward[32];

extern struct player_status reimu;

//��Ϸ�Ϸ��ļƷְ�
extern struct game_score cscore;

extern unsigned int iscontinuepoint;
extern short int stage;

#endif

/**********��������Ƭ�������ṩ��������***********/
void rewardhurtcard(int iscontinuecard,int stage)
{
//���ݹؿ���ͬ���������ֲ�ͬ
	int tempscorepp = 10 * (1 + stage / 5) + 3 * (iscontinuecard - 1) * (iscontinuecard - 1);
	if (tempscorepp >= 3200)
	{
		tempscorepp = 3200;
	}
	cscore.c_score += tempscorepp;
}


/****************�ӵ�����߼ӷ���Ŀ*********************/

//��ʼ�����ֽ�������
//�ڵ�����뿪��Ļ��islive = 0��ͬʱ���iscontinuepoint
//����ͨ�����ش�С��40*40
//���룺���������ͣ�1�㣬2b��3�У�
//		xy->��λ�����꣬Ϊ��׼�����뿨Ƭ�Ķ�λ���غ�
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

//�ƶ����еĽ�������
void moverewarditem()
{
	for (short int i = 0; i < 32; i++)
	{
		if (reward[i].islive == 1)
		{
			if (reward[i].downorup == 0 && reward[i].isup == 0)//������׹��û�з�����
			{
				if (reward[i].y + 6 >= YSIZE)//��⵽������ȥ����ʼ����
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

			else if (reward[i].downorup == 1)//�ϵ�״̬
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

			else if(reward[i].downorup == 0 && reward[i].isup == 1)//��׹�����ٷ���
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
			reward[i].islive = 0;//���ӵ�
			reward[i].y = 2 * YSIZE;

			switch (reward[i].type)//���ݽӵ����������෴��
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



//�ж��Ƿ�ӵ���
//�Ѿ���moverewad�ϲ�
void isreceivereward()
{
	for (short int i = 0; i < 32; i++)
	{
		if (reward[i].islive == 1)
		{
			if(reward[i].y >= reimu.y && !(reward[i].x > reimu.x + 42 || reimu.x > reward[i].x + 40))
			{
				reward[i].islive = 0;//���ӵ�

				switch (reward[i].type)//���ݽӵ����������෴��
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
	//���ݹؿ���ͬ���������ֲ�ͬ
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
//ÿ25w�ֽ���һ���л�
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
