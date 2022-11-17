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


//���ɿ�Ƭ��¥��ĻӲ�����
//��Ҫ�޸�!!!
#if 1

/************ÿһ����Ϸǰ��ʼ����Ƭ***************/
//����:��Ƭ��id�����һ����ƬidΪ0���ڶ���Ϊ1�����207��
//		x,y����Ƭ�����Ϸ���λ��
//		hp ����Ƭ�ĳ�ʼѪ��
//�������ȫ�֣����ṹ���������Ƭ��islive����Ϊ1����������Ϊû�б�������һֱ�Ӵ�,x,y,hp����Ϊ����ֵ
void initcard(int id, int x, int y, int hp)
{
	card[id].hp = hp;
	card[id].x = x;
	card[id].y = y;
	card[id].havebeencrashed = 0;
}
//�򵥰汾���ɿ�Ƭ��x��yΪ��׼�������(1~23/1~8)
void easyinitcard(int id, int x, int y, int hp)
{
	initcard(id, xlef + (x - 1) * xsp, ytop + (y - 1) * ysp, hp);
}


/****************ÿһ����Ϸǰ��ʼ����¥**********************/
//���룺��¥��id����һ��Ϊ0���ڶ���Ϊ1�����32��
//		x,y����¥���Ϸ���λ��
//�������ȫ�֣����ṹ��idָ�����¥islive����Ϊ1������x,yΪ��λ��������¥
void inittower(int id, int x, int y)
{
	tower[id].islive = 1;
	tower[id].x = x;
	tower[id].y = y;
}
//�򵥰汾������¥��x��yΪ��׼�������(1~23 / 1~8)
void easyinittower(int id, int x, int y)
{
	inittower(id, xlef + (x - 1) * xsp, ytop + (y - 1) * ysp);
}



/***************��ʼ���з���Ļ**********************/
//���룺�е�id��һ����ѭ������������������λ�õ����꣬�ٶ�
//		��������꣨�����Ի�����reimu.x+21,reimu.y+50��
//		radius:��Ļ�İ뾶��С
//		isunbreak:�Ƿ񲻿ɱ�������/��������(1=���ɱ�������0=�ɱ�������bomb������Ӱ��
// �������ȫ�֣����ṹ����(x,y)Ϊ���ģ�����һ����Ļ����speed���ٶ���(aimx,aimy)�ƶ�
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



/****************�е�����ʱ��׼ĳ��λ��*********************/
//���룺����Ҫ���ɵе���λ���������ģ��е�id;ĳ��λ�õ���������
//�������ȫ�֣��е��Ƕ�
void aimreimubullet(double x, double y, int id, double aimx, double aimy)
{

	//��ֱ�������
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


//ÿ��ǰ��ʼ��ǽ��
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



/*************************�ؿ����ⵯĻ���****************************************/


/**********************�ͷ�ģʽ�ĵ�Ļ*****************************/
//���ã����ݲ�ͬ�ؿ������óͷ�ģʽ�ĵ�Ļ
//�ͷ�ģʽ����ʱ����gamecmd������
//�����ҪҪ������һ����Ļ��������һ��������jexbullet �����÷ֺţ���
void punishtimemode(int stage)
{
	int bulletid = 0;
	switch (stage)//���ݹؿ������ͷ�����
	{
	case 1:case 2:case 3:case 4: 
		
				jexbullet
				//���ɶ���е�ע�⣬Ҫ��bulleti + n	
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



/**************************��ʱ���䵯Ļ*********************************/

//�ڶ�����¥��Ļ
void stage2to()
//����ͬʱ������ƫ���ƫ�ҷ��䵯Ļ
{
	for(short int toweri = 0;toweri < 32;toweri++)
	{
		if (tower[toweri].islive == 0)
		{
			return;
		}
		short int bulletid = 0;
		jexbullet
				initbullet(bulletid++, tower[toweri].x + 20, tower[toweri].y + 25, 10, reimu.x + 61, reimu.y + 50, 5, 0);//��¥,����ƫ��
				jexbullet
				initbullet(bulletid++, tower[toweri].x + 20, tower[toweri].y + 25, 10, reimu.x -19, reimu.y + 50, 5, 0);//��¥,����ƫ��
				jexbullet
	}
}


void stage3sp()
{
	short int bulletid = 0;
	jexbullet

			//���ɶ���е�ע�⣬Ҫ��bulleti + n	
			initbullet(bulletid++, 20,  50, 10,  reimu.x+21, reimu.y+50, 3, 0);//���
			jexbullet			
			initbullet(bulletid++, 20, 20, 5, reimu.x+21, reimu.y+50, 9, 0);//���
			jexbullet
			initbullet(bulletid++, XSIZE - 20, 50, 10, reimu.x+21, reimu.y+50, 3, 0);//���
			jexbullet			
			initbullet(bulletid++, XSIZE - 20, 20, 5, reimu.x+21, reimu.y+50, 9, 0);//���
			jexbullet
			initbullet(bulletid++, 0,360, 5, reimu.x + 21, reimu.y + 50, 25, 0);//���
			jexbullet
			initbullet(bulletid++, XSIZE, 360, 5, reimu.x + 21, reimu.y + 50, 25, 0);//���
			return;
}








/*******************�ؿ���ʼ��********************************/
//��Ϊ�����ʼ����Ƭ��
//��ţ�x����,y���꣬Ѫ��
//������ѭ������������һ���еĿ�Ƭ���ǵ���ϰ����һ�κ���y = kx + b
//��¥����������٣�������Ūi++�ˣ������0��ʼ
void stage1()//debug�ؿ�
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
/**************��ʼ���ؿ�main****************************/
int initstage(int num)
{
	mciSendString(_T("close nextstage"), NULL, 0, NULL);
	mciSendString(_T("open m\\nextstage.mp3 alias nextstage"), NULL, 0, NULL);
	mciSendString(_T("play nextstage"), NULL, 0, NULL);
	Sleep(250);
	//���õ�Ļ����Ƭ��ţ���¥״̬,boss,ǽ
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


	//���ݹؿ����룬����ʼ���ض��ؿ�
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


/********���ɵе�ʾ��**********/
#if 0
for (int bulletid = 0; bulletid < maxbullet; bulletid++)
{
	if (enemybullet[bulletid].islive == 0)
	{
		//���ɶ���е�ע�⣬Ҫ��bulleti + n	
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