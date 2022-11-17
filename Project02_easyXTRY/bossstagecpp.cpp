#include"menuh.h"
extern struct bullets enemybullet[maxbullet];
extern struct BOSS boss;
extern struct player_status reimu;
extern DWORD currentticktime;
extern short int stage;
extern struct game_score cscore;
extern struct yinyang_orb ORB;

//boss���м��
#define jtime(waittick) \
if (currentticktime - skilltick >= (waittick))

/*********************BOSS����*******************************/
void bossattack(short int stagea)
{
	short int bulletid = 0;
	switch (stagea)
	{
	case 5:
		jexbullet
			initbullet(bulletid++, boss.x + 100, boss.y + 175, 3, reimu.x + 21, reimu.y + 50, 20, 0);
		jexbullet
			initbullet(bulletid++, boss.x + 60, boss.y + 175, 8, reimu.x + 21, reimu.y + 50, 10, 0);
		jexbullet
			initbullet(bulletid++, boss.x + 140, boss.y + 175, 8, reimu.x + 21, reimu.y + 50, 10, 0);
		jexbullet
			initbullet(bulletid++, 20, 50, 10, reimu.x + 21, reimu.y + 50, 3, 0);//���
		jexbullet
			initbullet(bulletid++, XSIZE - 20, 50, 10, reimu.x + 21, reimu.y + 50, 3, 0);//���
		jexbullet
			initbullet(bulletid++, 20, 60, 10, reimu.x + 21, reimu.y + 50, 3, 0);//���
		jexbullet
			initbullet(bulletid++, XSIZE - 20, 60, 10, reimu.x + 21, reimu.y + 50, 3, 0);//���
		jexbullet
			initbullet(bulletid++, 20, 70, 10, reimu.x + 21, reimu.y + 50, 3, 0);//���
		jexbullet
			initbullet(bulletid++, XSIZE - 20, 70, 10, reimu.x + 21, reimu.y + 50, 3, 0);//���
		jexbullet
			initbullet(bulletid++, 20, 80, 10, reimu.x + 21, reimu.y + 50, 3, 0);//���
		jexbullet
			initbullet(bulletid++, XSIZE - 20, 80, 10, reimu.x + 21, reimu.y + 50, 3, 0);//���


		break;
	}


}

//�������Ƿ��boss
void ishurtboss()
{
	short int iscrashboss = 0;
	//�߼��������crash�ģ���ôisΪ1��havebeen��ֵΪ1�����ж��Ƿ��ǳ���������->��Ѫ������->�޲���
	//��crash����ôisΪ0����ʱhavebeen = 0

	//���ݹؿ��������ܵ��������ж������С���ж��Ƿ�����(��boss)
	switch (stage)
	{
	case 5:
		if (isorbcrashboss(0, 0) || isorbcrashboss(1, 0) || isorbcrashboss(2, 0) || isorbcrashboss(3, 0) || isorbcrashboss(4, 0) ||
			isorbcrashboss(0, 1) || isorbcrashboss(1, 1) || isorbcrashboss(2, 1) || isorbcrashboss(3, 1) || isorbcrashboss(4, 1) ||
			isorbcrashboss(0, 2) || isorbcrashboss(1, 2) || isorbcrashboss(2, 2) || isorbcrashboss(3, 2) || isorbcrashboss(4, 2) ||
			isorbcrashboss(1, 3) || isorbcrashboss(2, 3) || isorbcrashboss(3, 3) ||
			isorbcrashboss(2, 4)
			)
		{
			iscrashboss = 1;
		}
		break;
	}

	//�����crash��״̬
	if (iscrashboss == 1)
	{
		if (boss.havebeencrashed == 0)//�Ƿ��ǳ�������
		{
			//ͨ�ã���Ѫ����ŭ
			boss.hp--;
			cscore.c_score += 1000 * stage / 5;
			bossattack(stage);
			boss.havebeencrashed = 1;
			return;
		}
		else
		{
			return;
		}
	}
	else
	{
		boss.havebeencrashed = 0;
		return;
	}
}



/****************************************************************/
//���ܣ�
//���뵱ǰ�ؿ�
//ʵ���÷�����ʽ�������ɾ�̬����ʵ�֣�ÿ��������ʱ���Ὣ��ǰ����ʽ++��
//��5���1ʽ����10,11,12,13
void bossskill(short int stage)
{
	//��ÿ�����¸�ֵskillnum���ȡһ�ε�ǰʱ��
	static DWORD skilltick;

	//��ǰ���е�״̬��0Ϊû�п�ʼ���У����Կ�ʼ���У�������ֵ�����������У��ȴ���һ��
	static unsigned short int skillnum = 0;

	//���ݹؿ���ͬ���жϿ��Խ�����Щ����
	switch (stage)
	{
	case 5:
		//��δ���У�����һ��
		if (skillnum == 0)
		{
			skillnum = 10;//��·1
			skilltick = GetTickCount();
			break;
		}

		/*********************��·1*******************************/
		//t=0->8,׼��״̬
		else if (skillnum == 10)
		{
			if (currentticktime - skilltick >= 4000)
			{
				skillnum = 11;
				skilltick = GetTickCount();
				boss.speed = 2;
				boss.degree = PI;
			}
			break;
		}

		//t=8->10,����״̬�У������һ�ε�Ļ
		else if (skillnum == 11)
		{
			if (currentticktime - skilltick >= 1000)
			{
				short int bulletid = 0;
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
				skillnum = 12;
				skilltick = GetTickCount();
			}
			break;
		}

		//t= 10->12,����״̬�У�����ڶ��ε�Ļ
		else if (skillnum == 12)
		{
			jtime(1000)
			{
				short int bulletid = 0;
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
				skillnum = 13;
				skilltick = GetTickCount();
			}
			break;
		}

		//t=12->13,ֹͣ���ƶ�����ʼ����
		else if (skillnum == 13)
		{
			jtime(1000)
			{
				boss.degree = 0;
				skilltick = GetTickCount();
				skillnum = 14;
			}
			break;
		}

		//t=13->15,����״̬�����һ�ε�Ļ
		else if (skillnum == 14)
		{
			jtime(1000)
			{
				short int bulletid = 0;
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
				skillnum = 15;
				skilltick = GetTickCount();
			}
			break;
		}

		//t=15->17,����ڶ��ε�Ļ
		else if (skillnum == 15)
		{
			jtime(1000)
			{
				short int bulletid = 0;
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
				skillnum = 16;
				skilltick = GetTickCount();
			}
			break;
		}

		//t=17->18,ֹͣ״̬��
		else if (skillnum == 16)
		{
			jtime(1000)
			{
				boss.speed = 0;
				skillnum = 20;
				skilltick = GetTickCount();
			}
			break;
		}
		/*************************************************************************************************/


		/***********************��·��**************************/
		//t=0->8,�Ⱦ�ֹ������һ�ι̶�����֮��ÿ�����뷢��һ�ι̶���
		else if (skillnum == 20)
		{
			jtime(4000)
			{
				short int bulletid = 0;
				initreward(1, boss.x + 100, boss.y);
				for (short int stage5sp2i = 0; stage5sp2i < 5; stage5sp2i++)
				{
					jexbullet
						initbullet(bulletid, boss.x + 100, boss.y + stage5sp2i * ysp, 10, boss.x + xsp, YSIZE, 5, 0);
					enemybullet[bulletid].degree = PI / 6;
					jexbullet
						initbullet(bulletid, boss.x + 100, boss.y + stage5sp2i * ysp, 10, boss.x + xsp, YSIZE, 5, 0);
					enemybullet[bulletid].degree = PI / 3;
					jexbullet
						initbullet(bulletid, boss.x + 100, boss.y + stage5sp2i * ysp, 10, boss.x + xsp, YSIZE, 5, 0);
					enemybullet[bulletid].degree = PI / 6 + PI / 2;
					jexbullet
						initbullet(bulletid, boss.x + 100, boss.y + stage5sp2i * ysp, 10, boss.x + xsp, YSIZE, 5, 0);
					enemybullet[bulletid].degree = PI / 3 + PI / 2;
					jexbullet
						initbullet(bulletid, boss.x + 100, boss.y + stage5sp2i * ysp, 10, boss.x + xsp, YSIZE, 5, 0);
					enemybullet[bulletid].degree = PI / 2;
				}


				
				skillnum = 21;
				skilltick = GetTickCount();
			}
			break;
		}

		else if (skillnum == 21)
		{
			jtime(4000)
			{
				short int bulletid = 0;
				for (short int stage5sp2i = 0; stage5sp2i < 5; stage5sp2i++)
				{
					jexbullet
						initbullet(bulletid, boss.x + 100, boss.y + stage5sp2i * ysp, 10, boss.x + xsp, YSIZE, 5, 0);
					enemybullet[bulletid].degree = PI / 6;
					jexbullet
						initbullet(bulletid, boss.x + 100, boss.y + stage5sp2i * ysp, 10, boss.x + xsp, YSIZE, 5, 0);
					enemybullet[bulletid].degree = PI / 3;
					jexbullet
						initbullet(bulletid, boss.x + 100, boss.y + stage5sp2i * ysp, 10, boss.x + xsp, YSIZE, 5, 0);
					enemybullet[bulletid].degree = PI / 6 + PI / 2;
					jexbullet
						initbullet(bulletid, boss.x + 100, boss.y + stage5sp2i * ysp, 10, boss.x + xsp, YSIZE, 5, 0);
					enemybullet[bulletid].degree = PI / 3 + PI / 2;
					jexbullet
						initbullet(bulletid, boss.x + 100, boss.y + stage5sp2i * ysp, 10, boss.x + xsp, YSIZE, 5, 0);
					enemybullet[bulletid].degree = PI / 2;
				}
				skillnum = 22;
				skilltick = GetTickCount();
			}
			break;
		}

		else if (skillnum == 22)
		{
			jtime(4000)
			{
				short int bulletid = 0;
				for (short int stage5sp2i = 0; stage5sp2i < 5; stage5sp2i++)
				{
					jexbullet
						initbullet(bulletid, boss.x + 100, boss.y + stage5sp2i * ysp, 10, boss.x + xsp, YSIZE, 5, 0);
					enemybullet[bulletid].degree = PI / 6;
					jexbullet
						initbullet(bulletid, boss.x + 100, boss.y + stage5sp2i * ysp, 10, boss.x + xsp, YSIZE, 5, 0);
					enemybullet[bulletid].degree = PI / 3;
					jexbullet
						initbullet(bulletid, boss.x + 100, boss.y + stage5sp2i * ysp, 10, boss.x + xsp, YSIZE, 5, 0);
					enemybullet[bulletid].degree = PI / 6 + PI / 2;
					jexbullet
						initbullet(bulletid, boss.x + 100, boss.y + stage5sp2i * ysp, 10, boss.x + xsp, YSIZE, 5, 0);
					enemybullet[bulletid].degree = PI / 3 + PI / 2;
					jexbullet
						initbullet(bulletid, boss.x + 100, boss.y + stage5sp2i * ysp, 10, boss.x + xsp, YSIZE, 5, 0);
					enemybullet[bulletid].degree = PI / 2;
				}
				skillnum = 30;
			}
			break;
		}

		/*********************��·3*******************************/
		//t=0->8,׼��״̬
		else if (skillnum == 30)
		{
			if (currentticktime - skilltick >= 4000)
			{
				skillnum = 11;
				skilltick = GetTickCount();
				boss.speed = 2;
				boss.degree = PI;
			}
			break;
		}

		//t=8->10,����״̬�У������һ�ε�Ļ
		else if (skillnum == 31)
		{
			if (currentticktime - skilltick >= 1000)
			{
				short int bulletid = 0;
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
				skillnum = 32;
				skilltick = GetTickCount();
			}
			break;
		}

		//t= 10->12,����״̬�У�����ڶ��ε�Ļ
		else if (skillnum == 32)
		{
			jtime(1000)
			{
				short int bulletid = 0;
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
				skillnum = 33;
				skilltick = GetTickCount();
			}
			break;
		}

		//t=12->13,ֹͣ���ƶ�����ʼ����
		else if (skillnum == 33)
		{
			jtime(1000)
			{
				boss.degree = 0;
				skilltick = GetTickCount();
				skillnum = 34;
			}
			break;
		}

		//t=13->15,����״̬�����һ�ε�Ļ
		else if (skillnum == 34)
		{
			jtime(1000)
			{
				short int bulletid = 0;
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
				skillnum = 35;
				skilltick = GetTickCount();
			}
			break;
		}

		//t=15->17,����ڶ��ε�Ļ
		else if (skillnum == 35)
		{
			jtime(1000)
			{
				short int bulletid = 0;
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
				skillnum = 36;
				skilltick = GetTickCount();
			}
			break;
		}

		//t=17->18,ֹͣ״̬��
		else if (skillnum == 36)
		{
			jtime(1000)
			{
				boss.speed = 0;
				skillnum = 20;
				skilltick = GetTickCount();
			}
			break;
		}
		/*************************************************************************************************/
			break;
	}

}