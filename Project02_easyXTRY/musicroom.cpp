#include"menuh.h"
#include<graphics.h>
#include<string.h>
#include<tchar.h>
#include<mciapi.h>
void cmdmusicroommenu()
{
	cleardevice();
	int opt = 0;
	
	

	//������
	rainbow();
	rainbow();

	//����flame
	settextcolor(WHITE);
	settextstyle(22, 0, _T("Consolas"));
	RECT songr = { 40, 40, 639, 479 };
	drawtext(_T("01 �|����ħ�h���� ������ݱ�_\n02 �������� Eastern Wind\n03 End of Daylight\n04 �É���\n05 �Ҥ������餵���ˤ⤨\n06 �|����ħ�h���� �Ļ�����\n07 She's in a temper!!\n08 ��ߤΤ�����\n09 ����ـ����\n10 ��ɫ�ޥ��å�\n11 Complete Darkness\n12 �hҰ��ɭ\n13 ��Ԓ�����`����\n14 �������ȥ���\n15 ��܇�ह��Τߤ���"), &songr, DT_LEFT);

	Sleep(20);

	//ѡ��
	while (1)
	{

		int optmove = GETCMD();
		opt = limitmenujudge(15, opt, optmove);

		//ʹ��esc�˳�������
		if (opt == CMD_ESC)
		{
			cleardevice();
			endbgm;
			startbgm(m\\(1).mid);
			drawmainmenufalme();
			return;
		}

		//ʹ��x�˳�������
		if (GETCMD() == CMD_CANCEL)
		{
			cleardevice();
			endbgm;
			startbgm(m\\(1).mid);
			drawmainmenufalme();
			return;
		}

		//����opt��ֵ���Ų�ͬ������
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
		if (opt == 9 && GETCMD() == CMD_CONFIRM)
		{
			endbgm;
			startbgm(m\\(10).MID);
		}
		if (opt == 10 && GETCMD() == CMD_CONFIRM)
		{
			endbgm;
			startbgm(m\\(11).MID);
		}
		if (opt ==11 && GETCMD() == CMD_CONFIRM)
		{
			endbgm;
			startbgm(m\\(12).MID);
		}
		if (opt == 12 && GETCMD() == CMD_CONFIRM)
		{
			endbgm;
			startbgm(m\\(13).MID);
		}
		if (opt == 13 && GETCMD() == CMD_CONFIRM)
		{
			endbgm;
			startbgm(m\\(14).MID);
		}
		if (opt == 14 && GETCMD() == CMD_CONFIRM)
		{
			endbgm;
			startbgm(m\\(15).MID);
		}

		//���ƹ��
		drawmusicroommenu(opt);
		Sleep(120);
	}
}


//���ƹ��
void drawmusicroommenu(int topt)
{


	int opt = topt;//�˵��ķ���ֵ

	settextcolor(WHITE);
	settextstyle(22, 0, _T("Consolas"));

	RECT selectr = { 10, 40, 639, 479 };
	drawtext(_T(" \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n"), &selectr, DT_LEFT);

	//���
	int x = 10;
	int y = 40 + opt * 22;

	outtextxy(x, y, _T(">"));

}