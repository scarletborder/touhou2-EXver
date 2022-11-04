#include"menuh.h"
#if 1
void seeresult()
{
	cleardevice();
	//获得玩家的名字
	FILE* score_name;
	score_name = fopen("result\\player.txt", "r");
	char playername[10][15] = {0};

	int i = 0;

	for (i = 0; i <= 9; i++)
	{
		//printf("%d:\\ %s", i, playername[i]);
		fgets(playername[i], 14, (FILE*)score_name);
	}
	fclose(score_name);

	//获得玩家分数
	FILE* score_num;
	score_num = fopen("result\\score.txt", "r");
	char playerscore[11][15] = { 0 };

	i = 0;
	
	for (i = 0; i <= 9; i++)
	{
		//printf("%d:\\ %s", i, playername[i]);
		fgets(playerscore[i], 14, (FILE*)score_num);
	}
	fclose(score_num);

	settextcolor(WHITE);
	settextstyle(40, 0, _T("Consolas"));
	outtextxy(200, 60, _T("playersscore"));

	//开始打印玩家名字
	settextcolor(WHITE);
	settextstyle(22, 0, _T("Consolas"));

	for(i = 0; i <= 9;i++)
	{
		RECT result_scorer = { 200, 150 + 25*i, 639, 479 };
		TCHAR* result_display = char2TCAHR(playername[i]);
		drawtext(result_display, &result_scorer, DT_LEFT);
	}

	//开始打印玩家分数
	settextcolor(WHITE);
	settextstyle(22, 0, _T("Consolas"));

	for (i = 0; i <= 9; i++)
	{
		RECT result_scorer = { 350, 150 + 25 * i, 639, 479 };
		TCHAR* result_display = char2TCAHR(playerscore[i]);
		drawtext(result_display, &result_scorer, DT_LEFT);
	}

	//退出
	while (1)
	{
		int opt = GETCMD();
		//使用esc
		if (opt == CMD_ESC)
		{
			cleardevice();
			drawmainmenufalme();
			return;
		}

		//使用x
		if (GETCMD() == CMD_CANCEL)
		{
			cleardevice();
			drawmainmenufalme();
			return;
		}

		Sleep(150);
	}


}
#endif

#if 0
//游戏结束保存分数
void saveresult()
{



}
#endif