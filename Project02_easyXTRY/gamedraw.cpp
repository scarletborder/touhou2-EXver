#include"menuh.h"
#include"MyTimer.h"
/********************************/
//2022��11��17�շ�����gamecmd
//��;���ܻ�����Ϸ�е�����ͼ��
// ÿ30msһ֡����(15+15)
//ps:MyTimer.h����ͬʱ�������ļ�ͬʱʹ��
/********************************/

//�ⲿ����gameelements�ı���
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

//�����Ƿ��ƶ����Լ�����
extern int reimumove;
extern short int stage;

extern int iscontinuecard ;//����������Ƭ����
extern int maxiscontinuecard ;

extern int ctimeflow ;
extern char hiscore[15];

extern DWORD oldtickshoottime;
extern DWORD currentticktime;//��ǰʱ��

extern short int hasplaycharge ;

extern unsigned short int punishmode ;
extern int punishtime ;

//���ڶ�����Ϸ�������õ���Ԫ��
#if 1
//��Ļ
//�е��ṹ
extern struct bullets enemybullet[maxbullet];


//����е��ṹ
extern struct lasers enemylaser[128];


//�з�
extern struct enemycards card[207];
extern struct TOWER tower[32];
extern struct BOSS boss;
extern struct WALL wall[8];

//��Ϸ�и��ֽ����ṹ
extern struct rewards reward[32];


//���λ��͵������Լ��ڳ��ϵ�λ��
extern struct player_status reimu;


//��Ϸ�Ϸ��ļƷְ�
extern struct game_score cscore;


//�����ṹ
//�ܴ�С20*28
extern struct REIMUBULLET YUZHA[maxYUZHA];


//����������ṹ
//�ܴ�С49*49���뾶ΪRADIUS
extern struct yinyang_orb ORB;
#endif

MyTimer tt;
#endif

/****************************************************/
//���Ƴ������з���������
//����������в�Ҫflush
void drawallbullets()
{

	//��������
	for (int i = 0; i <= maxYUZHA - 1; i++)
	{
		if (YUZHA[i].islive & 1)
		{
			transparentimage(NULL, YUZHA[i].x, YUZHA[i].y, &yuzha, 0X4afc3f);
		}
	}


	//����������
	if (ORB.islive & 1)
	{
		//�������������ϣ���ɫ
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

	//���Ƶе�
	for (short int i = 0; i < maxbullet; i++)
	{
		if (enemybullet[i].islive == 1)
		{
			fillcircle(enemybullet[i].x, enemybullet[i].y, enemybullet[i].radius);
		}
	}

	//����reward
	for (short int i = 0; i < 32; i++)
	{
		if (reward[i].islive == 1)
		{
			switch (reward[i].type)
			{
			case 1://��
				putimage(reward[i].x, reward[i].y, &rewardpointimg);
				break;
			case 2://bomb
				putimage(reward[i].x, reward[i].y, &rewardbombimg);
				break;
				//1up
			}

		}
	}


	//����ǽ��
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


	//��ͨ�ز���Ҫ����Ƭ����¥
	if (stage % 5 != 0)
	{
		//���Ƶз���Ƭ
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

		//���Ƶз���¥
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


	//boss�ؿ�����boss
	if (stage % 5 == 0)
	{
		transparentimage(NULL, boss.x, boss.y, &bossimg, 0X4afc3f);
	}


	//�ڻ����Ϸ���������,��л�����������
	//setlinecolor(BLACK);
	setlinecolor(RED);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
	line(0, 49, XSIZE, 49);
	settextstyle(45, 0, _T("Consolas"));
	settextcolor(RED);
	char debugnum[64] = { 0 };
	if (punishmode == 1)
	{
		sprintf(debugnum, "��%c%d B%d !��ʱ cs=%ld/%s %d��/%d", reimu.type + 64, cscore.heartnum, cscore.bombnum, cscore.c_score, hiscore, iscontinuecard, maxiscontinuecard);
	}
	else
	{
		sprintf(debugnum, "��%c%d B%d T=%d(%d) cs=%ld/%s %d��/%d", reimu.type + 64, cscore.heartnum, cscore.bombnum, ctimeflow, punishtime, cscore.c_score, hiscore, iscontinuecard, maxiscontinuecard);
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


//���������ƶ�ʱ��������
//�ȴ�hydicator���ƻ���ͼƬ������滻
void drawitemswhenmove()
{

	//������ͨ�ƶ�
	if (reimumove & CMD_LEFT || reimumove & CMD_RIGHT)
	{
		int eachstep = reimu.speed / 6;//����ÿһ���Ĳ�����С����6������
		for (int stepi = 1; stepi <= 6; stepi++)
		{
			if (stepi <= 2)//ǰ����
			{
				cleardevice();
				if (reimumove & CMD_LEFT)//���������ƶ�
				{
					reimu.x -= eachstep;
					transparentimage(NULL, reimu.x, reimu.y, &reimuleft1, 0X4afc3f);
				}
				else if (reimumove & CMD_RIGHT)//���������ƶ�
				{
					reimu.x += eachstep;
					transparentimage(NULL, reimu.x, reimu.y, &reimuright1, 0X4afc3f);
				}

			}
			if (stepi >= 5)//������
			{
				cleardevice();
				if (reimumove & CMD_LEFT)//���������ƶ�
				{
					reimu.x -= eachstep;
					transparentimage(NULL, reimu.x, reimu.y, &reimuleft3, 0X4afc3f);
				}
				else if (reimumove & CMD_RIGHT)//���������ƶ�
				{
					reimu.x += eachstep;
					transparentimage(NULL, reimu.x, reimu.y, &reimuright3, 0X4afc3f);
				}

			}
			else//�м�����
			{
				cleardevice();
				if (reimumove & CMD_LEFT)//���������ƶ�
				{
					reimu.x -= eachstep;
					transparentimage(NULL, reimu.x, reimu.y, &reimuleft2, 0X4afc3f);
				}
				else if (reimumove & CMD_RIGHT)//���������ƶ�
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


	//���ƻ����ƶ�
	else if (reimumove == CMD_RREAP)
	{
		double eachstep = 1.5 * reimu.speed / 6;//����ÿһ���Ĳ�����С����6������
		for (int stepi = 1; stepi <= 6; stepi++)
		{
			if (stepi <= 2)//ǰ����
			{
				cleardevice();

				reimu.x += eachstep;
				transparentimage(NULL, reimu.x, reimu.y, &reimuright1, 0X4afc3f);


			}
			if (stepi >= 5)//������
			{
				cleardevice();

				reimu.x += eachstep;
				transparentimage(NULL, reimu.x, reimu.y, &reimuright3, 0X4afc3f);


			}
			else//�м�����
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
		double eachstep = 1.5 * reimu.speed / 6;//����ÿһ���Ĳ�����С����6������
		for (int stepi = 1; stepi <= 6; stepi++)
		{
			if (stepi <= 2)//ǰ����
			{
				cleardevice();

				reimu.x -= eachstep;
				transparentimage(NULL, reimu.x, reimu.y, &reimuleft1, 0X4afc3f);


			}
			if (stepi >= 5)//������
			{
				cleardevice();

				reimu.x -= eachstep;
				transparentimage(NULL, reimu.x, reimu.y, &reimuleft3, 0X4afc3f);


			}
			else//�м�����
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


//�������ξ�ֹʱ��������
void drawitemswhenstatic()
{
	cleardevice();

	drawallbullets();

	//���ƾ�̬����
	transparentimage(NULL, reimu.x, reimu.y, &pixelreimu, 0X4afc3f);

	FlushBatchDraw();
	tt.Sleep(30);
}


//����ÿһ����Ϸ�������ͳ��
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
	sprintf(rewarddetail, "ʱ��ӷ�:%d,�ؿ��̶���:%d", (160 * (punishtime - ctimeflow) > 0 ? 160 * (punishtime - ctimeflow) : 0), (stage - 1) * 320);

	outtextxy(120, 320, char2TCAHR(rewarddetail));

	sprintf(rewarddetail, "ʣ����Դ�ӷ�:%d,����������ӷ�:%d", cscore.heartnum * 800 + cscore.bombnum * 300, (maxiscontinuecard * 80 >= 6400 ? 6400 : maxiscontinuecard * 80));
	outtextxy(120, 380, char2TCAHR(rewarddetail));
	FlushBatchDraw();
	tt.Sleep(3000);
	_getch();
}