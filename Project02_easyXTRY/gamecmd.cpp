#include"menuh.h"
#include<iostream>
#include"MyTimer.h"


//��ʱ����ʱ������ͼ������
#if 1
DWORD currentticktime;//��ǰʱ��

//�ƶ����
static DWORD oldtickmovetime;

//����������
static DWORD oldtickshoottime;

//��Ļ���¼��
static DWORD oldtickbullettime;

//�������
static DWORD oldtickreaptime;

//��������ټ��
static DWORD oldtickslowtime;

//��Ϸ���ֿ�ʼǰ��ʱ����������й���������ʱ��
static DWORD timeflow;

//��һ�η���ؿ����ⵯĻʱ�䣬��8��
//0�̶�Ϊ�ͷ���Ļ��1-7Ϊ���/��¥
static DWORD oldspbullettime[8];

//wall
short int iscontinuecrashwall;
short int iscrashverwall;

static int bombhurt = 1;//ը���˺�

//�����Ƿ��ƶ����Լ�����
static int reimumove = 0;

short int iscontinuecard = 0;//����������Ƭ����
short int maxiscontinuecard = 0;

extern unsigned int iscontinuepoint;//�����ӵ����

short int stage = 1;

static int ctimeflow = 0;

unsigned short int punishmode = 0;
int punishtime = 0;


char hiscore[15];



//ͨ��ͼ���ļ�
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

	tt.Sleep(50);
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
	tt.Sleep(50);
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





//������ζ����������������ƶ�·��������
//֮��Ҫ�����µİ���ӳ�亯�����Լ����������������


short int hasplaycharge = 0;


/******************��ü����ϲ������ε�����*************************/
void cmdreimu()
{
	int optmove = GETCMD();
	int firstdo = 0;//����ռ�ã����ֲ�����ʹ��ֵ��Ϊ1������֮��������ƶ����
	int isx = 0;

		/***********��ͣ��Ϸ********************/
	

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

void escmenuflame();



/*****************�ж��������Ƿ���ĳ������������ײ************************
�������ܴ�С49*49���뾶ΪRADIUS
���룺���εĿ����εĸ�, ���ζ�λ��x, ���ζ�λ��y;Բ�����꣬Բ�İ뾶
���������1=YES,0=NO*/
int iscrash(int width, int height, int jx, int jy,double cirx, double ciry,double r)
{
	if (cirx - r >= XSIZE || cirx + r <= 0 || ciry - r >= YSIZE || ciry + r <= 0)
	{
		return 0;
	}

	//������Բ��


	double cx = static_cast<double>(jx) + width / 2;
	double cy = static_cast<double>(jy) + height / 2;
	double hx = width / static_cast<double>(2);
	double hy = height / static_cast<double>(2);
	
	// ��1����ת������1����
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
	// ��2������Բ�������ε���̾���ʸ��
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
	// ��3��������ƽ����뾶ƽ���Ƚ�
	if (((ux) * (ux) + (uy) * (uy)) <= r * r + 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/***************��������ĳ������������ײ������ƶ�״̬******************/
//���룺��ȫ�֣��������ٶȣ��Ƕȣ���λ�����ꣻ���ֲ��������������Ķ�λ�����꣬��ȣ�����;���������һ������
// ������������25�����߶���35
//���: (ȫ��)����������ٶȣ��Ƕ�
void aftercrash(double jjx, double jjy, double width,double height,double jp)
{
	//������Բ��
	double cx = ORB.x ;
	double cy = ORB.y ;

	//��������
	double jx = jjx + width / 2;
	double jy = jjy + height / 2;

	//�нǵ����Ǻ���
	//����
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


		int isfu = 1;//�Ƿ�Ϊ����������-1������1

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
	//���ζ�������Ķ���
	double jpx = -(jp * cos_a);
	double jpy = jp * sin_a;

	//������ԭ�����ֽ�
	double orbcos = cos(ORB.degree);
	double cpx = ORB.speed * orbcos;
	double cpy = ORB.speed * sin(ORB.degree);

	//�����µ��ٶȺͽǶ�
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
	//������Բ��
	double cx = ORB.x;
	double cy = ORB.y;

	//��������
	double jx = jjx + width / 2;
	double jy = jjy + height / 2;

	//�нǵ����Ǻ���
	//����
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


		int isfu = 1;//�Ƿ�Ϊ����������-1������1

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
	//���ζ�������Ķ���
	double jpx = -(jp * cos_a);
	double jpy = jp * sin_a;

	//������ԭ�����ֽ�
	double orbcos = cos(ORB.degree);
	double cpx = ORB.speed * orbcos;
	double cpy = ORB.speed * sin(ORB.degree);

	//�����µ��ٶȺͽǶ�
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




/*******************��������������������˶�״̬�ı�******************/
//����ǽ�ڣ���״��
#if 1
//ˮƽײ�� ���and�ұ�=
void crashvertical()
{
	ORB.degree = 2 * PI - ORB.degree;
}
//��ֱײ�� �ϱ�and�±�
void crashlevel()
{
	ORB.degree = 3 * PI - ORB.degree;
}

#endif



void moveorb()
{
	//����Ƿ������򵽶���ɽǶȺ��ٶȸı�
	for (short int i = 0; i <= maxYUZHA - 1; i++)
	{
		if (YUZHA[i].islive == 0)
		{
			continue;
		}
		if (iscrash(20, 28, YUZHA[i].x, YUZHA[i].y,ORB.x,ORB.y,RADIUS) == 1)
		{
			YUZHA[i].islive = 0;//ԭ�ȵ�����ʧ��
			//���ˣ����и��¼��ټ�ʱ��
			oldtickslowtime = GetTickCount();
			//��һ����ײ����();
			botcrash(YUZHA[i].x, YUZHA[i].y, 20, 28, 30);

			break;
		}
	}

	//����Ƿ񱻻�������ɽǶȺ��ٶȸı�

	
	//������������Ե�Ƿ�Ӵ�ǽ�ڶ���ɽǶȺ��ٶȸı�
	//ˮƽ
	if (ORB.x - RADIUS + ORB.speed * cos(ORB.degree) < 2 || ORB.x + RADIUS + ORB.speed * cos(ORB.degree) > XSIZE - 2 )
	{

			ORB.speed *= 0.8;
			crashlevel();

	}
	//��ֱ
	else if (ORB.y  - RADIUS + ORB.speed * sin(ORB.degree) < 52 || ORB.y + RADIUS + ORB.speed * sin(ORB.degree) > YSIZE - 2)
	{
		if (ORB.y + RADIUS + ORB.speed * sin(ORB.degree) > YSIZE - 2)
		{
			iscontinuecard = 0;
		}
			ORB.speed *= 0.8;
			crashvertical();

	}
	//ˮƽǽ��
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

	//����������һ�����µķ��ٶ�
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
	//��ʱ�����Ŷ�����ٶ�˥��if(>0)
#if 1
	if (currentticktime - oldtickslowtime >= 5000)
	{
		ORB.speed *= 0.98;
	}
#endif

	//����ٶ�����
	if (ORB.speed > 40)
	{
		ORB.speed = 40;
	}
}



//�ܿ����е�Ļ���ƶ�
void moveallbullet()
{

	//�����ƶ�
	for (int i = 0; i <= maxYUZHA - 1; i++)
	{
		if (YUZHA[i].islive & 1)
		{
			YUZHA[i].y -= 30;

			//��������
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

	
		//�������뿪����������
		if (YUZHA[i].y <= 42)
		{
			YUZHA[i].islive = 0;
		}
	}



	//�������ƶ�
	if(ORB.islive & 1)
	{
		moveorb();
		ORB.x += ORB.speed * cos(ORB.degree);
		ORB.y += ORB.speed * sin(ORB.degree);
	}

	//boss�ƶ�
	if (boss.hp >= 1)
	{
		boss.x += boss.speed * cos(boss.degree);
		boss.y += boss.speed * sin(boss.degree);
	}

	//�е��ƶ�
	for (int bulletid = 0; bulletid < maxbullet; bulletid++)
	{
		if (enemybullet[bulletid].islive & 1)
		{
			enemybullet[bulletid].x += enemybullet[bulletid].speed * cos(enemybullet[bulletid].degree);
			enemybullet[bulletid].y += enemybullet[bulletid].speed * sin(enemybullet[bulletid].degree);
			
			//�е��Ƴ���Ļ
			if (enemybullet[bulletid].x <= 0 || enemybullet[bulletid].x > XSIZE || enemybullet[bulletid].y  > YSIZE)
			{
				enemybullet[bulletid].islive = 0;
			}

			if ((currentticktime - enemybullet[bulletid].oldunbreaktime > 200) && ((enemybullet[bulletid].x - ORB.x) * (enemybullet[bulletid].x - ORB.x) + (enemybullet[bulletid].y - ORB.y) * (enemybullet[bulletid].y - ORB.y) <= (RADIUS + enemybullet[bulletid].radius) * (RADIUS + enemybullet[bulletid].radius)) && enemybullet[bulletid].isunbreak == 0)
			{
				enemybullet[bulletid].islive = 0;
			}

			//���е��Ƿ������
			//�����ж�����뾶��
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


	//reward�ƶ�
	moverewarditem();
}





//����������Ƿ�Ӵ����Σ�ʹ������
#if 1
void ishurtreimu()
{
	if (iscrash(32, 42, reimu.x + 5, reimu.y + 14,ORB.x,ORB.y,RADIUS) == 1)
	{
		if (currentticktime - reimu.oldunbreaktime >= 2500)//���Ҳ����޵�ʱ����
		{
			reimu.oldunbreaktime = GetTickCount();
			respawn();
		}
	}
}
#endif

//�ж��Ƿ��˺����˵з���Ƭ
void ishurtcard()
{
	for (int i = 0; i < 207; i++)
	{
		//�жϸÿ�Ƭ�Ƿ��ڳ�
		if (card[i].hp >= 1)
		{
			if (card[i].havebeencrashed == 0)//�������ڿ�Ƭ״̬���ú����½Ӵ���Ƭ
			{
				//�����Ƭ�������������Ӵ������һ��Ѫ
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

					//���䵯Ļ/�е��������޸ĵ�Ļ����
					//void makebullet(���ݹؿ�)
					short int bulletid = 0;

							switch (stage)
							{
								//���ɶ���е�ע�⣬Ҫ��bulleti + n
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
							

							//��Ƭ�������꣬�Ƴ�
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
			if (iscrash(40, 50, card[i].x, card[i].y, ORB.x, ORB.y, RADIUS) != 1)//������Ӹÿ�Ƭ���ƿ����ָ��ȴ��Ӵ�״̬
			{

				card[i].havebeencrashed = 0;
			}
		}	
	}
}



//���Ƴ������з����Ρ�boss����
//��Ҫflush
void drawallbullets()
{
	
	//��������
	for (int i = 0; i <= maxYUZHA -1; i++)
	{
		if (YUZHA[i].islive & 1)
		{
			transparentimage(NULL, YUZHA[i].x, YUZHA[i].y, &yuzha, 0X4afc3f);
		}
	}


	//����������
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

	//���Ƶе�
	for (short int i = 0; i < maxbullet; i++)
	{
		if (enemybullet[i].islive == 1)
		{
			fillcircle(enemybullet[i].x,enemybullet[i].y, enemybullet[i].radius);
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
			}

		}
	}

	//����ǽ��
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

	//��ͨ�ز���Ҫ����Ƭ����¥
	if(stage % 5 != 0)
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

	//����boss
	if (stage % 5 == 0)
	{
		transparentimage(NULL, boss.x, boss.y, &bossimg, 0X4afc3f);
	}
	
	//����debug����
	//setlinecolor(BLACK);
	setlinecolor(RED);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
	line(0, 49, XSIZE, 49);
	settextstyle(45, 0, _T("Consolas"));
	settextcolor(RED);
	char debugnum[64] = { 0 };
	if (punishmode == 1)
	{
		sprintf(debugnum, "��%c%d B%d !��ʱ cs=%ld/%s %d��/%d",reimu.type + 64, cscore.heartnum, cscore.bombnum,  cscore.c_score,hiscore, iscontinuecard,maxiscontinuecard);
	}
	else
	{
		sprintf(debugnum, "��%c%d B%d T=%d(%d) cs=%ld/%s %d��/%d", reimu.type + 64,cscore.heartnum, cscore.bombnum, ctimeflow,punishtime, cscore.c_score,hiscore, iscontinuecard,maxiscontinuecard);
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
	else if (reimumove== CMD_RREAP )
	{
		double eachstep = 1.5  *reimu.speed / 6;//����ÿһ���Ĳ�����С����6������
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


//��Ϸ����
int gamemain(int* signalp,int endsignal)
{
	setbkcolor(BLUE);//����ɫ�����ÿ�ز�ͬ
	cleardevice();
	//init
	reimu.type = endsignal;
	initreimu();
	cscore.c_score = 0;

	tt.Sleep(100);

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


	tt.Sleep(1000);
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
				tt.Sleep(4000);
				_getch();
				return 1;
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
				tt.Sleep(30);
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
	return 0;
}

//����Ϸ�������Ϸ���״̬��ֵ������л�����������
void drawgameflame();


