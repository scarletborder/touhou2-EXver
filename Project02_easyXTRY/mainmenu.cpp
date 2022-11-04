#include"menuh.h"

extern struct player_status reimu;

void drawmainmenufalme()
{
	//�������˵�����
	setlinestyle(PS_DASHDOTDOT | PS_JOIN_MITER, 4);
	setlinecolor(RED);
	rectangle(200, 260, 440, 440);//left,top,right,buttom

	//�����˵�����
	settextcolor(WHITE);
	settextstyle(40, 0, _T("Consolas"));
	//����
	outtextxy(220, 50, _T("������ħ¼EX"));

	settextstyle(22, 0, _T("Consolas"));
	//ѡ��
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
		//��ù��ָ��
		int optmove = GETCMD();
		
		opt = limitmenujudge(4,opt,optmove);
		
		//ʹ��esc�˳���Ϸ
		if (opt == CMD_ESC)
		{
			return CMD_ESC;
		}
		
		//ʹ��ѡ��quit+z�˳���Ϸ
		if (opt == 3 && GETCMD()==CMD_CONFIRM)
		{
			return CMD_ESC;
		}

		//����musicroom
		if (opt == 1 && GETCMD() == CMD_CONFIRM)
		{
			cmdmusicroommenu();
		}

		//����result
		if (opt == 2 && GETCMD() == CMD_CONFIRM)
		{
			seeresult();
		}

		//����ѡ�˽���
		if (opt == 0 && GETCMD() == CMD_CONFIRM)
		{
			cleardevice();
			int judgestartgame = cmdselect_reimu();

			//��ѡ���ɫҳ���˳�������������
			if (judgestartgame == CMD_ESC)
			{
				Sleep(100);
				cleardevice();
				drawmainmenufalme();
				continue;
			}

			return 3;//�Ѿ�ѡ���ɫ����ʼ��Ϸ
		}

		drawmainmenu(opt);
		Sleep(80);
	}

}


//�˵�����
void drawmainmenu(int topt)
{
	int opt = topt;//�˵��ķ���ֵ



	//���
	int x = 235;
	int y = 290 + opt * 40;
	outtextxy(235, 290, _T(" "));
	outtextxy(235, 330, _T(" "));
	outtextxy(235, 370, _T(" "));
	outtextxy(235, 410, _T(" "));
	outtextxy(x, y, _T(">"));
}
