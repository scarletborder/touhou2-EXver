#include"menuh.h"

void drawselectflame_reimu()
{


	settextcolor(WHITE);
	settextstyle(80, 0, _T("Consolas"));
	outtextxy(200,40,_T("��ѡ����Ļ���"));

	settextcolor(WHITE);
	settextstyle(44, 0, _T("Consolas"));
	RECT songr = { 40, 200, SIZEX, SIZEY };
	drawtext(_T("  ƽ����:��Դƽ��  \n  �߹�����:Bomb�˺�����  \n  �߷�����:�л��࣬��Bײ������ö���B  "), &songr, DT_LEFT);

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
		//��ù��ָ��
		int optmove = GETCMD();

		opt = limitmenujudge(3, opt, optmove);

		//����ѡ��Ļ���
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
	int opt = topt;//�˵��ķ���ֵ

	settextcolor(WHITE);
	settextstyle(44, 0, _T("Consolas"));

	RECT selectr = { 30, 200, 639, 479 };
	drawtext(_T(" \n \n \n "), &selectr, DT_LEFT);

	//���
	int x = 30;
	int y = 200 + opt * 44;

	outtextxy(x, y, _T(">"));
}