#include"menuh.h"
#define XSIZE 960
#define YSIZE 720

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
#if 0
	RECT r3 = { XSIZE / 2 - 45,YSIZE / 3 + 30,XSIZE / 2 + 45,YSIZE / 3 + 60 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 30, XSIZE / 2 + 45, YSIZE / 3 + 60);
	drawtext(_T("重新开始"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
#endif
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

		FlushBatchDraw();


		break;
	case 1:
		fillpoly(4, opt2);
	
		FlushBatchDraw();

		break;
	case 2:
		fillpoly(4, opt3);

		FlushBatchDraw();
	
		break;
	}
}

//菜单的指令功能
//返回一个值比较好，判断是否退出菜单功能
//游戏非正常退出的通用endsignal
int cmdescmenu()
{

	int c_opt = 0;
	escmenuflame();
	
	Sleep(40);

	while (1)
	{
		if (GETCMD() == CMD_CONFIRM)
		{
			cleardevice();
			FlushBatchDraw();
			break;
		}
		Sleep(100);
	}
#if 0
	while(1)
	{
		int optmove = GETCMD();
		c_opt = limitmenujudge(3, c_opt, optmove);
		if (c_opt == 0)
		{
			cleardevice();
			FlushBatchDraw();
			break;
		}
		drawescmenu(c_opt);
		Sleep(100);
	}
#endif
	return c_opt;

}