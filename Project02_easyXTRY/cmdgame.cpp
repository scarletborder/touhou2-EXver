#include"menuh.h"
#define XSIZE 640
#define YSIZE 480

/******************************************************/
#pragma comment( lib, "MSIMG32.LIB")
//// 透明贴图函数
//// 参数：
////		dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
////		x, y:	目标贴图位置
////		srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体
////		transparentcolor: 透明色。srcimg 的该颜色并不会复制到 dstimg 上，从而实现透明贴图
//// 
////     透明色是BGR格式，使用时RGB反过来 
//// 
////	transparentimage(NULL, 120, 0, &src, 0x3ffc4a);
//void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
//{
//	HDC dstDC = GetImageHDC(dstimg);
//	HDC srcDC = GetImageHDC(srcimg);
//	int w = srcimg->getwidth();
//	int h = srcimg->getheight();
//
//	// 使用 Windows GDI 函数实现透明位图
//	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
//}

// 透明贴图函数
// 参数：
//		dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
//		x, y:	目标贴图位置
//		srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体
//		transparentcolor: 透明色。srcimg 的该颜色并不会复制到 dstimg 上，从而实现透明贴图
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
{
	// 变量初始化
	DWORD* dst = GetImageBuffer(dstimg);
	DWORD* src = GetImageBuffer(srcimg);
	int src_width = srcimg->getwidth();
	int src_height = srcimg->getheight();
	int dst_width = (dstimg == NULL ? getwidth() : dstimg->getwidth());
	int dst_height = (dstimg == NULL ? getheight() : dstimg->getheight());

	// 计算贴图的实际长宽
	int iwidth = (x + src_width > dst_width) ? dst_width - x : src_width;
	int iheight = (y + src_height > dst_height) ? dst_height - y : src_height;

	// 修正贴图起始位置
	dst += dst_width * y + x;

	// 修正透明色，显示缓冲区中的数据结构为 0xaarrggbb
	transparentcolor = 0xff000000 | BGR(transparentcolor);

	// 实现透明贴图
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
// 程序名称：精确到微秒的延时类（基于多媒体定时器）
// 程序编写：yangw80 <yw80@qq.com>
// 最后修改：2011-5-4
//
#pragma once
#include <windows.h>

class MyTimer
{
private:
	LARGE_INTEGER m_clk;

	// 保存时钟信息
	LONGLONG m_oldclk;


	// 保存开始时钟和结束时钟
	int m_freq;




	// 时钟频率(时钟时间换算率)，时间差

public:
	MyTimer();
	void Sleep(int ms);
	void Reset();
};

// 构造函数
MyTimer::MyTimer()
{
	QueryPerformanceFrequency(&m_clk);
	m_freq = (int)m_clk.QuadPart / 1000;

	// 获得计数器的时钟频率
	m_oldclk = 0;
}

// 延时
void MyTimer::Sleep(int ms)
{
	unsigned int c = ms * m_freq;

	if (m_oldclk == 0)
	{

		// 开始计时

		QueryPerformanceCounter(&m_clk);

		m_oldclk = m_clk.QuadPart;



		// 获得开始时钟
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
			// 获得终止时钟

		}

	while (m_clk.QuadPart < m_oldclk);
}

// 重置延时器
void MyTimer::Reset()
{
	m_oldclk = 0;
}
/****************************************************/



//用于定义游戏正文中用到的元素

typedef struct bullets
{
	int x;//x坐标
	int y;//y坐标
	double moverad;//偏移角度
	double speed;//弹幕速度
	int type;//弹幕类型
}BULLET;

typedef struct lasers
{
	int x;//x坐标
	int y;//y坐标
	int length;//激光长度
	double moverad;//偏移角度
	double speed;//激光速度
	int type;//激光类型
}LASER;

typedef struct rewards
{
	int x;//x坐标
	int y;//y坐标
	int type;//奖励的类型,11=点,22=B,33=残
}REWARD;

static struct player_status
{
	int x;//x坐标
	int y;//y坐标，固定
	double speed;//灵梦的速度，不同机型速度不同
	//int isunbreak;//是否无敌，如重生，放b
	int type;//机型
}reimu = { 310,445,10,0 };

static struct game_score
{
	int c_score;//当前分数
	int hi_score;//历史最高分
	int heartnum;//残机个数
	int bombnum;//炸弹个数
	int stagenum;//当前关卡数
}cscore = { 0,0,0,0,1 };



//重生
//后期在做重生时要考虑场上弹幕全消
void respawn()
{
	//残机-1
	cscore.heartnum --;

	//根据机体不同，重生时获得不同数量的资源
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

	//播放被弹音效
	mciSendString(_T("open m\\playerdie.mp3 alias respawn"), NULL, 0, NULL);
	mciSendString(_T("play respawn"), NULL, 0, NULL);
	Sleep(50);
	
	//重新定位灵梦
	reimu.x = 310;
	reimu.y = 445;
}

//初始化灵梦数值
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

//侦测灵梦动作，并绘制灵梦移动路径，动画
//之后要适配新的按键映射函数，以及御札，滑铲，灵击
static DWORD oldtickmovetime;
static DWORD newtickmovetime;
void moveinspect(IMAGE* pixelreimu,IMAGE*l1,IMAGE*l2,IMAGE*l3,IMAGE*r1,IMAGE*r2,IMAGE*r3,int* xk,int* xn)
{
	MyTimer tmove;

	int optmove = GETCMD();
	int firstdo = 0;//优先占用：部分操作会使该值变为1，跳过之后的所有移动检测
	int isx = 0;



	newtickmovetime = GetTickCount();

	//int ismove = 0;//是否按下了移动键，0为无，1为左，2为右

	//判断灵梦的各种操作
	//动作分为：母 (+ 子)
	//优先级：
	// C = 灵击炸弹
	//移动+X = 滑铲  结尾若有+Z = 御札连射
	//移动 = 普通移动    &&  Z = 单发御札

	/******弃置的移动检测*******/
	//if (optmove == CMD_LEFT)//首先判断操作母体是否是移动
	//{
	//	ismove = 1;//左移
	//}
	//if (optmove == CMD_RIGHT)//首先判断操作母体是否是移动
	//{
	//	ismove = 2;//右移
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
		//暂时没做
			/************滑铲*************/
			//是否在移动同时按下了x键，从而发生滑铲
		if ((isx == 1))// && (optmove == CMD_LEFT))
		{
			firstdo = 1;
			double speedx = 1.5 * reimu.x;//滑铲中灵梦变速
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
			double speedx = 1.5 * reimu.x;//滑铲中灵梦变速
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





		/******普通移动********/

		if (optmove == CMD_LEFT && firstdo == 0)//普通左移
		{
			//首先是否可以移动，免得穿墙
			//接着进行移动操作，改变一次坐标并穿插着进行移动时的图片动画
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

		if (optmove == CMD_RIGHT && firstdo == 0)//普通右移
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

	//加载灵梦图片
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

		//延时
		tt.Sleep(25);
		xk++;
		if (xk == 1000)
		{
			xk = 0;
		}


		//判断是否按下esc菜单
		if (GETCMD() == CMD_ESC)
		{
			while (1)
			{
				escmenuflame();
				Sleep(100);
			}
		}

		//画灵梦移动后的图像
		//修bug，闪烁和只有一张图
		
		//控制滑铲频率



		moveinspect(&pixelreimu,&reimuleft1,&reimuleft2,&reimuleft3,&reimuright1,&reimuright2,&reimuright3,&xk,&xn);
		
		//弃置的古代光栅
		/*putimage(reimu.x, reimu.y, &pixelreimu, SRCAND);
		putimage(reimu.x, reimu.y, &pixelreimu, SRCPAINT);*/
		


		FlushBatchDraw();
	}

	_getch();
	Sleep(9999999999);
	return 0;
}

//画游戏过程中上方的状态数值栏，如残机数，分数等
void drawgameflame();


//画esc菜单的框架
void escmenuflame()
{
	BeginBatchDraw();
	int points[8] = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 90,XSIZE / 2 - 45,YSIZE / 3 + 90 };
	setfillstyle(RED);
	fillpoly(4, points);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, _T("黑体"));
	settextcolor(BLACK);
	RECT r2 = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 30 }; rectangle(XSIZE / 2 - 45, YSIZE / 3, XSIZE / 2 + 45, YSIZE / 3 + 30);
	drawtext(_T("回到游戏"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3 = { XSIZE / 2 - 45,YSIZE / 3 + 30,XSIZE / 2 + 45,YSIZE / 3 + 60 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 30, XSIZE / 2 + 45, YSIZE / 3 + 60);
	drawtext(_T("重新开始"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4 = { XSIZE / 2 - 45,YSIZE / 3 + 60,XSIZE / 2 + 45,YSIZE / 3 + 90 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 60, XSIZE / 2 + 45, YSIZE / 3 + 90);
	drawtext(_T(" 主 菜 单 "), &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	FlushBatchDraw();
}

//菜单选中的高亮绘制
void drawescmenu(int opt)//记得调用optjudge
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

//菜单的指令功能
//返回一个值比较好，判断是否退出菜单功能
//游戏非正常退出的通用endsignal
void cmdescmenu()
{

}