#include"menuh.h"

extern struct player_status reimu;

void drawmainmenufalme()
{
	//画出主菜单方框
	setlinestyle(PS_DASHDOTDOT | PS_JOIN_MITER, 4);
	setlinecolor(RED);
	rectangle(20*SIZEX/64, 26*SIZEY/48, 44*SIZEX/64, 44*SIZEY/48);//left,top,right,buttom

	//画主菜单文字
	settextcolor(WHITE);
	settextstyle(60, 0, _T("Consolas"));
	//标题
	outtextxy(11*SIZEX/32, SIZEY/6, _T("东方封魔录EX"));

	settextstyle(2*SIZEY/48, 0, _T("Consolas"));
	//选项
	outtextxy(265*SIZEX/640, 29*SIZEY/48, _T("Start Game"));
	outtextxy(265*SIZEX/640, 33*SIZEY/48, _T("Music Room"));
	outtextxy(28*SIZEX/64, 37*SIZEY/48, _T("Result"));
	outtextxy(29*SIZEX/64, 41*SIZEY/48, _T("Quit"));
	outtextxy(SIZEX - 200, SIZEY - 80, _T("V0.00c"));
	outtextxy(SIZEX - 320, SIZEY - 40, _T("星尘幻想研究所© 2022"));
}

int cmdmainmenu()
{
	endbgm;
	setbkcolor(BLACK);
	cleardevice();
	EndBatchDraw();
	int opt = 0;//0 1 2
	startbgm(m\\(1).mid);
	drawmainmenufalme();
	
	while(1)
	{
		//获得光标指令
		int optmove = GETCMD();
		
		opt = limitmenujudge(4,opt,optmove);
		
		//使用esc退出游戏
		if (opt == CMD_ESC)
		{
			return CMD_ESC;
		}
		
		//使用选中quit+z退出游戏
		if (opt == 3 && GETCMD()==CMD_CONFIRM)
		{
			return CMD_ESC;
		}

		//进入musicroom
		if (opt == 1 && GETCMD() == CMD_CONFIRM)
		{
			cmdmusicroommenu();
			Sleep(150);
		}

		//进入result
		if (opt == 2 && GETCMD() == CMD_CONFIRM)
		{
			seeresult();
			Sleep(150);
		}

		//进入选人界面
		if (opt == 0 && GETCMD() == CMD_CONFIRM)
		{
			cleardevice();
			int judgestartgame = cmdselect_reimu();

			//在选择角色页面退出，返回主界面
			if (judgestartgame == CMD_ESC)
			{
				Sleep(300);
				cleardevice();
				drawmainmenufalme();
				continue;
			}

			return judgestartgame;//已经选择角色，开始游戏
		}

		drawmainmenu(opt);
		Sleep(100);
	}

}


//菜单方框
void drawmainmenu(int topt)
{
	int opt = topt;//菜单的返回值



	//光标
	int x = 235*SIZEX/640;
	int y = 29*SIZEY/48 + opt * 40*SIZEY / 480;
	outtextxy(235*SIZEX/640, 29*SIZEY/48, _T(" "));
	outtextxy(235 * SIZEX / 640, 33 * SIZEY / 48, _T(" "));
	outtextxy(235 * SIZEX / 640, 37 * SIZEY / 48, _T(" "));
	outtextxy(235 * SIZEX / 640, 41 * SIZEY / 48, _T(" "));
	outtextxy(x, y, _T(">"));
}
