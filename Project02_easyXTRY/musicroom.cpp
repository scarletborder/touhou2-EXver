#include"menuh.h"
#include<graphics.h>
#include<string.h>
#include<tchar.h>
#include<mciapi.h>
void cmdmusicroommenu()
{
	cleardevice();
	int opt = 0;
	
	

	//画背景
	rainbow();
	rainbow();

	//绘制flame
	settextcolor(WHITE);
	settextstyle(22, 0, _T("Consolas"));
	RECT songr = { 40, 40, 639, 479 };
	drawtext(_T("01 東方封魔録　～ 浄土曼荼羅\n02 博麗　～ Eastern Wind\n03 End of Daylight\n04 幻夢界\n05 ひもろぎ、むらさきにもえ\n06 東方封魔録　～ 幽幻乱舞\n07 She's in a temper!!\n08 やみのちから\n09 死を賭して"), &songr, DT_LEFT);

	Sleep(20);

	//选项
	while (1)
	{

		int optmove = GETCMD();
		opt = limitmenujudge(9, opt, optmove);

		//使用esc退出音乐室
		if (opt == CMD_ESC)
		{
			cleardevice();
			endbgm;
			startbgm(m\\(1).mid);
			drawmainmenufalme();
			return;
		}

		//使用x退出音乐室
		if (GETCMD() == CMD_CANCEL)
		{
			cleardevice();
			endbgm;
			startbgm(m\\(1).mid);
			drawmainmenufalme();
			return;
		}

		//根据opt的值播放不同的音乐
		if (opt == 0 && GETCMD() == CMD_CONFIRM)
		{
			endbgm;
			startbgm(m\\(1).MID);
		}
		if (opt == 1 && GETCMD() == CMD_CONFIRM)
		{
			endbgm;
			startbgm(m\\(2).MID);
		}
		if (opt == 2 && GETCMD() == CMD_CONFIRM)
		{
			endbgm;
			startbgm(m\\(3).MID);
		}
		if (opt == 3 && GETCMD() == CMD_CONFIRM)
		{
			endbgm;
			startbgm(m\\(4).MID);
		}
		if (opt == 4 && GETCMD() == CMD_CONFIRM)
		{
			endbgm;
			startbgm(m\\(5).MID);
		}
		if (opt == 5 && GETCMD() == CMD_CONFIRM)
		{
			endbgm;
			startbgm(m\\(6).MID);
		}
		if (opt == 6 && GETCMD() == CMD_CONFIRM)
		{
			endbgm;
			startbgm(m\\(7).MID);
		}
		if (opt == 7 && GETCMD() == CMD_CONFIRM)
		{
			endbgm;
			startbgm(m\\(8).MID);
		}
		if (opt == 8 && GETCMD() == CMD_CONFIRM)
		{
			endbgm;
			startbgm(m\\(9).MID);
		}

		//绘制光标
		drawmusicroommenu(opt);
		Sleep(120);
	}
}


//绘制光标
void drawmusicroommenu(int topt)
{


	int opt = topt;//菜单的返回值

	settextcolor(WHITE);
	settextstyle(22, 0, _T("Consolas"));

	RECT selectr = { 10, 40, 639, 479 };
	drawtext(_T(" \n \n \n \n \n \n \n \n \n"), &selectr, DT_LEFT);

	//光标
	int x = 10;
	int y = 40 + opt * 22;

	outtextxy(x, y, _T(">"));

}