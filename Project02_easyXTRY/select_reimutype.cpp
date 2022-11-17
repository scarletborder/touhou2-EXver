#include"menuh.h"

void drawselectflame_reimu()
{


	settextcolor(WHITE);
	settextstyle(80, 0, _T("Consolas"));
	outtextxy(200,40,_T("请选择你的机型"));

	settextcolor(WHITE);
	settextstyle(44, 0, _T("Consolas"));
	RECT songr = { 40, 200, SIZEX, SIZEY };
	drawtext(_T("  平衡型:资源平均  \n  高攻击型:Bomb伤害更高  \n  高防御型:残机多，抱B撞重生获得额外B  "), &songr, DT_LEFT);

	Sleep(40);

}

int cmdselect_reimu()
{
	int opt = 0;//0 1 2
	cleardevice;
	drawselectflame_reimu();

	Sleep(100);
	short int cheatdebug = 0;
	while (1)
	{
		//获得光标指令
		int optmove = GETCMD();

		opt = limitmenujudge(3, opt, optmove);

		//返回选择的机型
		if (opt == 0 && GETCMD() == CMD_CONFIRM)
		{
			return 1;
		}
		if (opt == 1 && GETCMD() == CMD_CONFIRM)
		{
			return 2;
		}
		if (opt == 2 && GETCMD() == CMD_CONFIRM)
		{
			return 3;
		}
		if (GETCMD() == CMD_SPECIAL)
		{
			if (cheatdebug == 2)
			{
				cheatdebug = 3;
			}
			else if (cheatdebug == 3)
			{
				return 4;
			}
			Sleep(100);
		}
		if (GETCMD() == CMD_LEFT)
		{
			if (cheatdebug == 0)
			{
				cheatdebug = 1;

			}
		}
		if (GETCMD() == CMD_RIGHT)
		{

			if (cheatdebug == 1)
			{
				cheatdebug = 2;
			}
		}
		if (GETCMD() == CMD_ESC || GETCMD() == CMD_CANCEL)
		{
			return CMD_ESC;
		}

		drawselect_reimu(opt);
		Sleep(50);
	}

}
void drawselect_reimu(int topt)
{
	int opt = topt;//菜单的返回值

	settextcolor(WHITE);
	settextstyle(44, 0, _T("Consolas"));

	RECT selectr = { 30, 200, 639, 479 };
	drawtext(_T(" \n \n \n "), &selectr, DT_LEFT);

	//光标
	int x = 30;
	int y = 200 + opt * 44;

	outtextxy(x, y, _T(">"));
}