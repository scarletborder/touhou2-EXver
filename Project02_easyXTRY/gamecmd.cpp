#include"menuh.h"
#include<iostream>
/*********************************************/
//gamecmd.cpp
// ����Ҫ��Դ�ļ�
//�ô�1����ʼ�����Σ���������������
//�ô�2�����ݽ��ܵ��ļ���������������
//�ô�4��������Ϸ�е�����
//�ô�4����ĩ����
/*********************************************/

//������Ϸ�������õ���Ԫ��
#if 1
//��ʱ����ʱ������ͼ������

extern DWORD currentticktime;//��ǰʱ��

//�ƶ����
extern DWORD oldtickmovetime;

//����������
extern DWORD oldtickshoottime;

//��Ļ���¼��
extern DWORD oldtickbullettime;

//�������
extern DWORD oldtickreaptime;

//��������ټ��
extern DWORD oldtickslowtime;

//��Ϸ���ֿ�ʼǰ��ʱ����������й���������ʱ��
extern DWORD timeflow;

//��һ�η���ؿ����ⵯĻʱ�䣬��8��
//0�̶�Ϊ�ͷ���Ļ��1-7Ϊ���/��¥
extern DWORD oldspbullettime[8];

DWORD continuetime;

//wall
extern short int iscontinuecrashwall;
extern short int iscrashverwall;

extern int bombhurt;//ը���˺�

//�����Ƿ��ƶ����Լ�����
extern int reimumove;

extern int iscontinuecard;//����������Ƭ����
extern int maxiscontinuecard;

extern unsigned int iscontinuepoint;//�����ӵ����

extern short int stage;

extern int ctimeflow;

extern unsigned short int punishmode;
extern int punishtime;


extern char hiscore[15];

extern short int hasplaycharge;

short int isendgame;

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



//ͨ��ͼ���ļ�
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




//����
//������������ʱҪ���ǳ��ϵ�Ļȫ��
void respawn()
{

	//�л�-1
	cscore.heartnum --;

	//���ݻ��岻ͬ������ʱ��ò�ͬ��������Դ
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

	//���ű�����Ч
	mciSendString(_T("close respawn"), NULL, 0, NULL);
	mciSendString(_T("open m\\playerdie.mp3 alias respawn"), NULL, 0, NULL);
	mciSendString(_T("play respawn"), NULL, 0, NULL);

	Sleep(50);
	for (int bulleti = 0; bulleti < maxbullet; bulleti++)
	{
		enemybullet[bulleti].islive = 0;
	}
	
	//���¶�λ����

	
}


//��һ����Ϸǰ��ʼ��������ֵ
void initreimu()
{
	//��ʼ������
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


//ÿһ����Ϸǰ��ʼ��������
void initorb()
{
	ORB.islive = 1;
	ORB.speed = 0;
	ORB.degree = 0;
	ORB.x = XSIZE - 60;
	ORB.y = YSIZE/2;

}


/******************��ü����ϲ������ε�����*************************/
void cmdreimu()
{
	int optmove = GETCMD();
	int firstdo = 0;//����ռ�ã����ֲ�����ʹ��ֵ��Ϊ1������֮��������ƶ����
	int isx = 0;

		/***********��ͣ��Ϸ********************/
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

		/******��ͨ�ƶ�********/

		if (optmove & CMD_LEFT && firstdo == 0)//��ͨ����
		{
			//�����Ƿ�����ƶ�����ô�ǽ
			//���Ž����ƶ��������ı�һ�����겢�����Ž����ƶ�ʱ��ͼƬ����
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

		if (optmove & CMD_RIGHT && firstdo == 0)//��ͨ����
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
	
		/******************�����ƶ�***********/
#if 1
		if (optmove & CMD_CANCEL )//����x��
		{
			if(currentticktime - oldtickmovetime <= 40)//ȷ�������ƶ������У�����x��
			{
				firstdo = 1;
			}
			else
			{
				if (currentticktime - oldtickreaptime < 300 && currentticktime - oldtickreaptime > 40)
				{
					//ǰ�ŷ�
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
					//�������ң����

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

		if (optmove & CMD_LEFT && firstdo == 1)//��������
		{
			//�����Ƿ�����ƶ�����ô�ǽ
			//���Ž����ƶ��������ı�һ�����겢�����Ž����ƶ�ʱ��ͼƬ����
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


	if (optmove & CMD_CONFIRM && firstdo ==0)//�ھ�ֹ������ͨ�ƶ��п��Է��䵥������
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
		int hurt = bombhurt;//bomb�˺������ݻ��͵���
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
				//��Ƭ�������꣬�Ƴ�
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


/**************��������****************/
//ÿ��z����ʼ������һ������
static int yuzhanum = -1;
void init_yuzha()
{
	//ÿ�η�����ʱ�������л�����һ���ͷŵ���һ����ŵ�����
	yuzhanum++;
	if (yuzhanum == maxYUZHA)
	{
		yuzhanum = 0;
	}

	YUZHA[yuzhanum].islive = 1;//���������ŵ�����״̬
	YUZHA[yuzhanum].x = reimu.x + 9;
	YUZHA[yuzhanum].y = reimu.y + 30;

}
void init_fastyuzha()
{
	//ÿ�η�����ʱ�������л�����һ���ͷŵ���һ����ŵ�����
	yuzhanum++;
	if (yuzhanum == maxYUZHA)
	{
		yuzhanum = 0;
	}
	YUZHA[yuzhanum].islive = 1;//���������ŵ�����״̬
	YUZHA[yuzhanum].x = reimu.x + 9;//1
	YUZHA[yuzhanum].y = reimu.y ;
	yuzhanum++;
	if (yuzhanum == maxYUZHA)
	{
		yuzhanum = 0;
	}
	YUZHA[yuzhanum].islive = 1;//���������ŵ�����״̬
	YUZHA[yuzhanum].x = reimu.x + 29;//5
	YUZHA[yuzhanum].y = reimu.y + 50;
	yuzhanum++;
	if (yuzhanum == maxYUZHA)
	{
		yuzhanum = 0;
	}
	YUZHA[yuzhanum].islive = 1;//���������ŵ�����״̬
	YUZHA[yuzhanum].x = reimu.x - 11;//1
	YUZHA[yuzhanum].y = reimu.y + 90;
	yuzhanum++;
	if (yuzhanum == maxYUZHA)
	{
		yuzhanum = 0;
	}
	YUZHA[yuzhanum].islive = 1;//���������ŵ�����״̬
	YUZHA[yuzhanum].x = reimu.x + 19;//4
	YUZHA[yuzhanum].y = reimu.y + 140;
	yuzhanum++;
	if (yuzhanum == maxYUZHA)
	{
		yuzhanum = 0;
	}
	YUZHA[yuzhanum].islive = 1;//���������ŵ�����״̬
	YUZHA[yuzhanum].x = reimu.x - 1;//2
	YUZHA[yuzhanum].y = reimu.y + 190;
	yuzhanum++;
	if (yuzhanum == maxYUZHA)
	{
		yuzhanum = 0;
	}
	YUZHA[yuzhanum].islive = 1;//���������ŵ�����״̬
	YUZHA[yuzhanum].x = reimu.x + 9;//3
	YUZHA[yuzhanum].y = reimu.y + 230;
}





//��Ϸ����
int gamemain(int charcter_type)
{
	setbkcolor(BLUE);//����ɫ�����ÿ�ز�ͬ
	cleardevice();
	//init
	reimu.type = charcter_type;
	initreimu();
	cscore.c_score = 0;
	isendgame = 0;

	Sleep(100);

	//��������ͼƬ
	
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

	//ֱ��allclear��������
	while(allclear != 1)
	{
		//ÿ����Ϸǰ��ʼ������
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
		punishmode = 0;//�Ƿ�ͷ�ģʽ
		punishtime = 0;//����ͷ�ģʽ��ʱ��
		switch (stage)//���ݹؿ��ж�ʱ���Ƿ��������ͷ�ģʽ
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


			/************************�������Ʒְ�****************************/
			if (cscore.heartnum <= 0)//����
			{
				//�Ƿ�����...,���ؼǺ�...

				//����
				setfillcolor(BLACK);
				cleardevice();
				settextcolor(WHITE);
				settextstyle(80, 0, _T("Consolas"));
				outtextxy(100, 250, _T("������!!"));
				char cscorestr[15] = { 0 };
				sprintf(cscorestr, "%d", cscore.c_score);	
				outtextxy(50, 350, _T("��ķ���Ϊ"));
				outtextxy(50, 450, char2TCAHR(cscorestr));
				FlushBatchDraw();
				Sleep(4000);
				_getch();
				return 0;
			}

			//��;�˳�
			if (isendgame == 1)
			{
				return 0;
			}

#if 1
			/*****************88888888*********ʱ���������**********88*********************/
			//��ʱ����¼��ǰʱ��Ӷ����ϴ�ĳЩ������Ƚϣ��ж��Ƿ��м�������ĳЩ��������ı�Ҫ����
			currentticktime = GetTickCount();
			ctimeflow = (currentticktime - timeflow) / 1000;//������Ϸ�Ѿ�������ʱ��



			if (ctimeflow >= punishtime)//ʱ���������ͷ�ģʽ
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

			
		//�жϿ�Ƭ��boss�Ƿ��ܵ������������з���
			if(stage % 5 != 0)
			{
				ishurtcard();
			}
			else if (stage % 5 == 0)
			{
				ishurtboss();
			}


			/***********************�ؿ��Դ����ⵯĻ�趨*****************************************/
			//��Ҫ��ͬ�ؿ���ͬ�Ĵ���ʱ��
			//��շ��䵯Ļ
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
			//��¥���䵯Ļ
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

			//boss��ʹ��boss���ܣ�ת��bossstage.cpp
			if (stage % 5 == 0)
			{
				bossskill(stage);
			}
#endif
			/******************************************************************************/

			cmdreimu();

			ishurtreimu();

			isrewardheart();
			
			//�жϷ�����Ƿ��ɿ�����
			if ((currentticktime)-oldtickmovetime >= 40)
			{
				reimumove = 0;
			}

			//judgeall

			if (reimumove == 0)
			{
				drawitemswhenstatic();
#if 0
				//drawitemswhenstatic��ĳ��ʱ�䲻���ã���ֱ�Ӵ��棬����ٲ��г��Կ��Ǻ�
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




			//�ж��Ƿ���esc�˵�

			//�������ƶ����ͼ��


			//���ƻ���Ƶ��

			//���õĹŴ���դ
			/*putimage(reimu.x, reimu.y, &pixelreimu, SRCAND);
			putimage(reimu.x, reimu.y, &pixelreimu, SRCPAINT);*/


			/**************������Ϸ�����ж�********************/
			//�ж��Ƿ����ȫ������
			int sum = 0;
			for (int cardii = 0; cardii < 207; cardii++)
			{
				sum += card[cardii].hp;
			}
			//��Ƭȫ�������boss����
			if ((sum <= 0 && (stage % 5) != 0)|| (boss.hp <= 0 && stage % 5 == 0))
			{
#if 0
				switch (stage)//���ݹؿ���ʱ����н���
				{
				case 1:case 2:case 3:case 4: case 5:
					if (ctimeflow < punishtime)
					{
						//
					}
					break;
				}
#endif
				cscore.c_score += (160 * (punishtime - ctimeflow) > 0? 160 * (punishtime - ctimeflow):0);//ʱ��ӷ�
				cscore.c_score += (stage - 1) * 320;//�ؿ��̶�����
				cscore.c_score += cscore.heartnum * 800 + cscore.bombnum * 300;//�л���bomb����
				cscore.c_score += (maxiscontinuecard * 80 >= 6400 ? 6400 : maxiscontinuecard * 80);


				printscore(stage);
				stage++;
				break;
			}
			

			/******************************************************/
		}
	}

	_getch();
	

	//��Ϸ�ܽ���
	saveresult(cscore.c_score);

	//������Ϸ��·
	//....
	//if ����...
	return 1;
}





