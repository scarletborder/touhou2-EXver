#include"menuh.h"
#define XSIZE 640
#define YSIZE 480

/******************************************************/
#pragma comment( lib, "MSIMG32.LIB")
//// ͸����ͼ����
//// ������
////		dstimg: Ŀ�� IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
////		x, y:	Ŀ����ͼλ��
////		srcimg: Դ IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
////		transparentcolor: ͸��ɫ��srcimg �ĸ���ɫ�����Ḵ�Ƶ� dstimg �ϣ��Ӷ�ʵ��͸����ͼ
//// 
////     ͸��ɫ��BGR��ʽ��ʹ��ʱRGB������ 
//// 
////	transparentimage(NULL, 120, 0, &src, 0x3ffc4a);
//void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
//{
//	HDC dstDC = GetImageHDC(dstimg);
//	HDC srcDC = GetImageHDC(srcimg);
//	int w = srcimg->getwidth();
//	int h = srcimg->getheight();
//
//	// ʹ�� Windows GDI ����ʵ��͸��λͼ
//	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
//}

// ͸����ͼ����
// ������
//		dstimg: Ŀ�� IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
//		x, y:	Ŀ����ͼλ��
//		srcimg: Դ IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
//		transparentcolor: ͸��ɫ��srcimg �ĸ���ɫ�����Ḵ�Ƶ� dstimg �ϣ��Ӷ�ʵ��͸����ͼ
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer(dstimg);
	DWORD* src = GetImageBuffer(srcimg);
	int src_width = srcimg->getwidth();
	int src_height = srcimg->getheight();
	int dst_width = (dstimg == NULL ? getwidth() : dstimg->getwidth());
	int dst_height = (dstimg == NULL ? getheight() : dstimg->getheight());

	// ������ͼ��ʵ�ʳ���
	int iwidth = (x + src_width > dst_width) ? dst_width - x : src_width;
	int iheight = (y + src_height > dst_height) ? dst_height - y : src_height;

	// ������ͼ��ʼλ��
	dst += dst_width * y + x;

	// ����͸��ɫ����ʾ�������е����ݽṹΪ 0xaarrggbb
	transparentcolor = 0xff000000 | BGR(transparentcolor);

	// ʵ��͸����ͼ
	for (int iy = 0; iy < iheight; iy++)
	{
		for (int ix = 0; ix < iwidth; ix++)
		{
			if (src[ix] != transparentcolor)
				dst[ix] = src[ix];
		}
		dst += dst_width;
		src += src_width;
	}
}

/******************************************************/
// �������ƣ���ȷ��΢�����ʱ�ࣨ���ڶ�ý�嶨ʱ����
// �����д��yangw80 <yw80@qq.com>
// ����޸ģ�2011-5-4
//
#pragma once
#include <windows.h>

class MyTimer
{
private:
	LARGE_INTEGER m_clk;

	// ����ʱ����Ϣ
	LONGLONG m_oldclk;


	// ���濪ʼʱ�Ӻͽ���ʱ��
	int m_freq;




	// ʱ��Ƶ��(ʱ��ʱ�任����)��ʱ���

public:
	MyTimer();
	void Sleep(int ms);
	void Reset();
};

// ���캯��
MyTimer::MyTimer()
{
	QueryPerformanceFrequency(&m_clk);
	m_freq = (int)m_clk.QuadPart / 1000;

	// ��ü�������ʱ��Ƶ��
	m_oldclk = 0;
}

// ��ʱ
void MyTimer::Sleep(int ms)
{
	unsigned int c = ms * m_freq;

	if (m_oldclk == 0)
	{

		// ��ʼ��ʱ

		QueryPerformanceCounter(&m_clk);

		m_oldclk = m_clk.QuadPart;



		// ��ÿ�ʼʱ��
	}

	m_oldclk += c;

	QueryPerformanceCounter(&m_clk);

	if (m_clk.QuadPart > m_oldclk)

		m_oldclk = m_clk.QuadPart;
	else

		do

		{


			::Sleep(1);


			QueryPerformanceCounter(&m_clk);
			// �����ֹʱ��

		}

	while (m_clk.QuadPart < m_oldclk);
}

// ������ʱ��
void MyTimer::Reset()
{
	m_oldclk = 0;
}
/****************************************************/



//���ڶ�����Ϸ�������õ���Ԫ��

typedef struct bullets
{
	int x;//x����
	int y;//y����
	double moverad;//ƫ�ƽǶ�
	double speed;//��Ļ�ٶ�
	int type;//��Ļ����
}BULLET;

typedef struct lasers
{
	int x;//x����
	int y;//y����
	int length;//���ⳤ��
	double moverad;//ƫ�ƽǶ�
	double speed;//�����ٶ�
	int type;//��������
}LASER;

typedef struct rewards
{
	int x;//x����
	int y;//y����
	int type;//����������,11=��,22=B,33=��
}REWARD;

static struct player_status
{
	int x;//x����
	int y;//y���꣬�̶�
	double speed;//���ε��ٶȣ���ͬ�����ٶȲ�ͬ
	//int isunbreak;//�Ƿ��޵У�����������b
	int type;//����
}reimu = { 310,445,10,0 };

static struct game_score
{
	int c_score;//��ǰ����
	int hi_score;//��ʷ��߷�
	int heartnum;//�л�����
	int bombnum;//ը������
	int stagenum;//��ǰ�ؿ���
}cscore = { 0,0,0,0,1 };



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
			cscore.bombnum = 3;
		}
		else
		{
			cscore.bombnum = 2;
		}
	}

	//���ű�����Ч
	mciSendString(_T("open m\\playerdie.mp3 alias respawn"), NULL, 0, NULL);
	mciSendString(_T("play respawn"), NULL, 0, NULL);
	Sleep(50);
	
	//���¶�λ����
	reimu.x = 310;
	reimu.y = 445;
}

//��ʼ��������ֵ
void initreimu()
{

	switch (reimu.type)
	{
	case 1:
		cscore.heartnum = 3;
		cscore.bombnum = 3;
		reimu.speed = 18;
		break;
	case 2:
		cscore.heartnum = 2;
		cscore.bombnum = 3;
		reimu.speed = 12;
		break;
	case 3:
		cscore.heartnum = 4;
		cscore.bombnum = 2;
		reimu.speed = 12;

	}
	Sleep(50);
	reimu.x = 310;
	reimu.y = 445;
}

//������ζ����������������ƶ�·��������
//֮��Ҫ�����µİ���ӳ�亯�����Լ����������������
static DWORD oldtickmovetime;
static DWORD newtickmovetime;
void moveinspect(IMAGE* pixelreimu,IMAGE*l1,IMAGE*l2,IMAGE*l3,IMAGE*r1,IMAGE*r2,IMAGE*r3,int* xk,int* xn)
{
	MyTimer tmove;

	int optmove = GETCMD();
	int firstdo = 0;//����ռ�ã����ֲ�����ʹ��ֵ��Ϊ1������֮��������ƶ����
	int isx = 0;



	newtickmovetime = GetTickCount();

	//int ismove = 0;//�Ƿ������ƶ�����0Ϊ�ޣ�1Ϊ��2Ϊ��

	//�ж����εĸ��ֲ���
	//������Ϊ��ĸ (+ ��)
	//���ȼ���
	// C = ���ը��
	//�ƶ�+X = ����  ��β����+Z = ��������
	//�ƶ� = ��ͨ�ƶ�    &&  Z = ��������

	/******���õ��ƶ����*******/
	//if (optmove == CMD_LEFT)//�����жϲ���ĸ���Ƿ����ƶ�
	//{
	//	ismove = 1;//����
	//}
	//if (optmove == CMD_RIGHT)//�����жϲ���ĸ���Ƿ����ƶ�
	//{
	//	ismove = 2;//����
	//}
	if(_kbhit())
	{

#if 0
		if (optmove == CMD_CANCEL)
		{
			if (*xn == 0)
			{
				isx = 1;
				*xn = 1;
			}
			*xn++;
			if (*xk % 10 == 0 && *xn > 10)
			{
				isx = 1;
			}
			else xn = 0;

	}
#endif
#if 0
		//��ʱû��
			/************����*************/
			//�Ƿ����ƶ�ͬʱ������x�����Ӷ���������
		if ((isx == 1))// && (optmove == CMD_LEFT))
		{
			firstdo = 1;
			double speedx = 1.5 * reimu.x;//���������α���
			if (reimu.x - speedx <= 1)
			{
				return;
			}
			else
			{
				int movetimes = speedx / 2;

				for (int i = 1; i <= movetimes; i++)
				{
					cleardevice();
					if (i % 3 == 1)
					{
						transparentimage(NULL, reimu.x, reimu.y, l1, 0X4afc3f);
					}
					else if (i % 3 == 2)
					{
						transparentimage(NULL, reimu.x, reimu.y, l2, 0X4afc3f);
					}
					else
					{
						transparentimage(NULL, reimu.x, reimu.y, l3, 0X4afc3f);
					}
					reimu.x -= 2;

					FlushBatchDraw();
					Sleep(5);

				}
				cleardevice();
				transparentimage(NULL, reimu.x, reimu.y, pixelreimu, 0X4afc3f);
			}
		}

#endif
#if 0
		if ((isx == 1) && (optmove == CMD_RIGHT))
		{
			firstdo = 1;
			double speedx = 1.5 * reimu.x;//���������α���
			if (reimu.x + speedx >= 618)
			{
				return;
			}
			else
			{
				int movetimes = speedx / 2;

				for (int i = 1; i <= movetimes; i++)
				{
					cleardevice();
					if (i % 3 == 1)
					{
						transparentimage(NULL, reimu.x, reimu.y, r1, 0X4afc3f);
					}
					else if (i % 3 == 2)
					{
						transparentimage(NULL, reimu.x, reimu.y, r2, 0X4afc3f);
					}
					else
					{
						transparentimage(NULL, reimu.x, reimu.y, r3, 0X4afc3f);
					}
					reimu.x += 2;

					FlushBatchDraw();
					Sleep(5);

				}
				cleardevice();
				transparentimage(NULL, reimu.x, reimu.y, pixelreimu, 0X4afc3f);
			}
}
#endif





		/******��ͨ�ƶ�********/

		if (optmove == CMD_LEFT && firstdo == 0)//��ͨ����
		{
			//�����Ƿ�����ƶ�����ô�ǽ
			//���Ž����ƶ��������ı�һ�����겢�����Ž����ƶ�ʱ��ͼƬ����
			if (reimu.x - reimu.speed <= 1)
			{
				transparentimage(NULL, reimu.x, reimu.y, pixelreimu, 0X4afc3f);
				FlushBatchDraw();
				return;
			}

			else
			{

				int movetimes = reimu.speed;

				for (int i = 1; i <= movetimes; i++)
				{
					cleardevice();
					if (i < (movetimes / 3))
					{
						transparentimage(NULL, reimu.x, reimu.y, l1, 0X4afc3f);
						FlushBatchDraw();
					}
					else if (i > ((movetimes / 3)) * 2)
					{
						transparentimage(NULL, reimu.x, reimu.y, l2, 0X4afc3f);
						FlushBatchDraw();
					}
					else
					{
						transparentimage(NULL, reimu.x, reimu.y, l3, 0X4afc3f);
						FlushBatchDraw();
					}
					reimu.x -= 1;

					FlushBatchDraw();
					tmove.Sleep(5);
					
				}
				cleardevice();
				oldtickmovetime = GetTickCount();

			}
			
		}

		if (optmove == CMD_RIGHT && firstdo == 0)//��ͨ����
		{
			if (reimu.x + reimu.speed >= 618)
			{
				transparentimage(NULL, reimu.x, reimu.y, pixelreimu, 0X4afc3f);
				FlushBatchDraw();
				return;
			}



			else
			{
				int movetimes = reimu.speed;

				for (int i = 1; i <= movetimes; i++)
				{
					cleardevice();
					if (i < (movetimes / 3))
					{
						transparentimage(NULL, reimu.x, reimu.y, r1, 0X4afc3f);
						FlushBatchDraw();
					}
					else if (i > ((movetimes / 3)) * 2)
					{
						transparentimage(NULL, reimu.x, reimu.y, r2, 0X4afc3f);
						FlushBatchDraw();
					}
					else
					{
						transparentimage(NULL, reimu.x, reimu.y, r3, 0X4afc3f);
						FlushBatchDraw();
					}
					reimu.x += 1;
					FlushBatchDraw();
					tmove.Sleep(5);
					
				}
				cleardevice();
				oldtickmovetime = GetTickCount();
			}
			
		}
	}
	if (static_cast<long long>(newtickmovetime) - oldtickmovetime >= 40)
	{
		transparentimage(NULL, reimu.x, reimu.y, pixelreimu, 0X4afc3f);
		FlushBatchDraw();
	}

}


void escmenuflame();

int gamemain(int* signalp,int endsignal)
{
	setbkcolor(BLUE);
	cleardevice();
	//init
	reimu.type = endsignal;
	initreimu();

	Sleep(100);

	//��������ͼƬ
	IMAGE pixelreimu;
	loadimage(&pixelreimu, _T("resource\\pixelreimu.png"), 21, 28,false);
	IMAGE reimuleft1;
	loadimage(&reimuleft1, _T("resource\\reimul1.png"), 21, 28, false);
	IMAGE reimuleft2;
	loadimage(&reimuleft2, _T("resource\\reimul2.png"), 21, 28, false);
	IMAGE reimuleft3;
	loadimage(&reimuleft3, _T("resource\\reimul3.png"), 21, 28, false);

	IMAGE reimuright1;
	loadimage(&reimuright1, _T("resource\\reimur1.png"), 21, 28, false);
	IMAGE reimuright2;
	loadimage(&reimuright2, _T("resource\\reimur2.png"), 21, 28, false);
	IMAGE reimuright3;
	loadimage(&reimuright3, _T("resource\\reimur3.png"), 21, 28, false);

	Sleep(100);
	BeginBatchDraw();

	endbgm;
	startbgm(m\\(2).MID);

	
	MyTimer tt;
	int xk = 0;
	int xn = 0;

	while(1)
	{

		//��ʱ
		tt.Sleep(25);
		xk++;
		if (xk == 1000)
		{
			xk = 0;
		}


		//�ж��Ƿ���esc�˵�
		if (GETCMD() == CMD_ESC)
		{
			while (1)
			{
				escmenuflame();
				Sleep(100);
			}
		}

		//�������ƶ����ͼ��
		//��bug����˸��ֻ��һ��ͼ
		
		//���ƻ���Ƶ��



		moveinspect(&pixelreimu,&reimuleft1,&reimuleft2,&reimuleft3,&reimuright1,&reimuright2,&reimuright3,&xk,&xn);
		
		//���õĹŴ���դ
		/*putimage(reimu.x, reimu.y, &pixelreimu, SRCAND);
		putimage(reimu.x, reimu.y, &pixelreimu, SRCPAINT);*/
		


		FlushBatchDraw();
	}

	_getch();
	Sleep(9999999999);
	return 0;
}

//����Ϸ�������Ϸ���״̬��ֵ������л�����������
void drawgameflame();


//��esc�˵��Ŀ��
void escmenuflame()
{
	BeginBatchDraw();
	int points[8] = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 90,XSIZE / 2 - 45,YSIZE / 3 + 90 };
	setfillstyle(RED);
	fillpoly(4, points);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, _T("����"));
	settextcolor(BLACK);
	RECT r2 = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 30 }; rectangle(XSIZE / 2 - 45, YSIZE / 3, XSIZE / 2 + 45, YSIZE / 3 + 30);
	drawtext(_T("�ص���Ϸ"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3 = { XSIZE / 2 - 45,YSIZE / 3 + 30,XSIZE / 2 + 45,YSIZE / 3 + 60 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 30, XSIZE / 2 + 45, YSIZE / 3 + 60);
	drawtext(_T("���¿�ʼ"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4 = { XSIZE / 2 - 45,YSIZE / 3 + 60,XSIZE / 2 + 45,YSIZE / 3 + 90 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 60, XSIZE / 2 + 45, YSIZE / 3 + 90);
	drawtext(_T(" �� �� �� "), &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	FlushBatchDraw();
}

//�˵�ѡ�еĸ�������
void drawescmenu(int opt)//�ǵõ���optjudge
{
	setlinecolor(GREEN);
	int opt1[8] = { XSIZE / 2 - 43,YSIZE / 3,XSIZE / 2 + 43,YSIZE / 3, XSIZE / 2 - 43,YSIZE / 3 + 28,XSIZE / 2 - 43,YSIZE / 3 + 28 };
	int opt2[8] = { XSIZE / 2 - 43,YSIZE / 3 + 32,XSIZE / 2 + 43,YSIZE / 3 + 32, XSIZE / 2 - 43,YSIZE / 3 + 58,XSIZE / 2 - 43,YSIZE / 3 + 58 };
	int opt3[8] = { XSIZE / 2 - 43,YSIZE / 3 + 62,XSIZE / 2 + 43,YSIZE / 3 + 62, XSIZE / 2 - 43,YSIZE / 3 + 88,XSIZE / 2 - 43,YSIZE / 3 + 88 };

	switch (opt)
	{
	case 0:
		fillpoly(4, opt1);
		break;
	case 1:
		fillpoly(4, opt2);
		break;
	case 2:
		fillpoly(4, opt3);
		break;
	}
}

//�˵���ָ���
//����һ��ֵ�ȽϺã��ж��Ƿ��˳��˵�����
//��Ϸ�������˳���ͨ��endsignal
void cmdescmenu()
{

}