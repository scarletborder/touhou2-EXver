#include"menuh.h"

extern struct player_status reimu;

void drawmainmenufalme()
{
	//画出主菜单方框
	setlinestyle(PS_DASHDOTDOT | PS_JOIN_MITER, 4);
	setlinecolor(RED);
	rectangle(200, 260, 440, 440);//left,top,right,buttom

	//画主菜单文字
	settextcolor(WHITE);
	settextstyle(40, 0, _T("Consolas"));
	//标题
	outtextxy(220, 50, _T("东方封魔录EX"));

	settextstyle(22, 0, _T("Consolas"));
	//选项
	outtextxy(265, 290, _T("Start Game"));
	outtextxy(265, 330, _T("Music Room"));
	outtextxy(280, 370, _T("Result"));
	outtextxy(290, 410, _T("Quit"));
}

int cmdmainmenu(int* signalp)
{
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
		}

		//进入result
		if (opt == 2 && GETCMD() == CMD_CONFIRM)
		{
			seeresult();
		}

		//进入选人界面
		if (opt == 0 && GETCMD() == CMD_CONFIRM)
		{
			cleardevice();
			int judgestartgame = cmdselect_reimu();

			//在选择角色页面退出，返回主界面
			if (judgestartgame == CMD_ESC)
			{
				Sleep(100);
				cleardevice();
				drawmainmenufalme();
				continue;
			}

			return 3;//已经选择角色，开始游戏
		}

		drawmainmenu(opt);
		Sleep(80);
	}

}


//菜单方框
void drawmainmenu(int topt)
{
	int opt = topt;//菜单的返回值



	//光标
	int x = 235;
	int y = 290 + opt * 40;
	outtextxy(235, 290, _T(" "));
	outtextxy(235, 330, _T(" "));
	outtextxy(235, 370, _T(" "));
	outtextxy(235, 410, _T(" "));
	outtextxy(x, y, _T(">"));
}
