#include"menuh.h"

struct playerdata
{
	char playername[15];
	char playerscore[15];
	int scorenum;
}player[10] = { 0 };
#if 1
void seeresult()
{
	cleardevice();
	//获得玩家的名字
	FILE* score_name;
	score_name = fopen("result\\player.txt", "r");
	

	int i = 0;

	for (i = 0; i < 10; i++)
	{
		//printf("%d:\\ %s", i, playername[i]);
		fgets(player[i].playername, 14, (FILE*)score_name);
	}
	fclose(score_name);

	//获得玩家分数
	FILE* score_num;
	score_num = fopen("result\\score.txt", "r");
	

	i = 0;
	
	for (i = 0; i < 10; i++)
	{
		//printf("%d:\\ %s", i, playername[i]);
		fgets(player[i].playerscore, 14, (FILE*)score_num);
	}
	fclose(score_num);

	settextcolor(WHITE);
	settextstyle(60, 0, _T("Consolas"));
	outtextxy(340, 60, _T("playersscore"));

	//开始打印玩家名字
	settextcolor(WHITE);
	settextstyle(33, 0, _T("Consolas"));

	for(i = 0; i <= 9;i++)
	{
		RECT result_scorer = { 300, 200 + 35*i, SIZEX, SIZEY };
		TCHAR* result_display = char2TCAHR(player[i].playername);
		drawtext(result_display, &result_scorer, DT_LEFT);
	}

	//开始打印玩家分数
	settextcolor(WHITE);
	settextstyle(33, 0, _T("Consolas"));

	for (i = 0; i <= 9; i++)
	{
		RECT result_scorer = { 600, 200 + 35 * i, SIZEX, SIZEY };
		TCHAR* result_display = char2TCAHR(player[i].playerscore);
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

#if 1
//游戏结束保存分数
void saveresult(int cscore)
{
	//先获取历史数据
#if 1
	//获得玩家的名字
	FILE* score_name;
	score_name = fopen("result\\player.txt", "r");


	int i = 0;

	for (i = 0; i < 10; i++)
	{
		//printf("%d:\\ %s", i, playername[i]);
		fgets(player[i].playername, 14, (FILE*)score_name);
	}
	fclose(score_name);

	//获得玩家分数
	FILE* score_num;
	score_num = fopen("result\\score.txt", "r");


	i = 0;

	for (i = 0; i < 10; i++)
	{
		//printf("%d:\\ %s", i, playername[i]);
		fgets(player[i].playerscore, 14, (FILE*)score_num);
	}
	fclose(score_num);
#endif
	for (int i = 0; i < 10; i++)
	{
		player[i].scorenum = atoi(player[i].playerscore);
	}

	
	setbkcolor(GREEN);
	cleardevice();
	EndBatchDraw();
	settextstyle(40, 0, _T("黑体"));
	settextcolor(BLACK);

	char cscorestr[15] = { 0 };
	sprintf(cscorestr, "%d", cscore);

	outtextxy(50, 200, _T("恭喜通关开发预览版v0.00b,你的分数为"));
	outtextxy(50, 245, char2TCAHR(cscorestr));

	//不符合录入要求
	if (cscore <= player[9].scorenum)
	{
		outtextxy(50, 290, _T("排行榜最低分为"));
		outtextxy(50, 335, char2TCAHR(player[9].playerscore));
		outtextxy(50, 380, _T("继续努力吧！"));
		return;
	}


	//符合录入要求
	int numi = 8;
	for (; numi >= 0; numi--)
	{
		if (cscore <= player[numi].scorenum)
		{
			break;			
		}

	}

	//替换序号为0，也就是第一个数据
	if(numi < 0)
	{
		outtextxy(50, 290, _T("达到历史新纪录！！！"));
	}

	//替换序号为i+1的数据
	for (int sei = 8; sei >= numi + 1; sei--)
	{
		strcpy(player[sei + 1].playerscore,player[sei].playerscore);
	}
	sprintf(player[numi + 1].playerscore, "%d\n", cscore);


	outtextxy(50, 335, _T("记分板因未知原因停用,仅支持记录分数，按回车键继续"));//，请输入玩家的名字，少于14字
	fflush(stdin);
	Sleep(1000);
	fflush(stdin);
	Sleep(1000);
	char newname[15] = { 0 };
	scanf_s("%s", newname, 15);

	//int namei = 0;
	//for (namei = 0; newname[namei] != '\n'; namei++)
	//{

	//}
	//newname[namei] = '\0';

	strcpy(player[numi + 1].playername, newname);

	int linenum = 0;
	score_name = fopen("result\\player.txt", "w");




	
	while (linenum < 10)
	{
		for (int j = 0; newname[j] != '\0'; j++)
		{
			if (newname[j] == '\n')
			{
				newname[j] = ' ';
			}

		}

		linenum++;
	}
	i = 0;
	while (i < 10)
	{
		fputs(player[i].playername,score_name );
		
		i++;
	}
	fclose(score_name);



	linenum = 0;
	score_num = fopen("result\\score.txt", "w");
	while (linenum < 10)
	{
		fputs(player[linenum].playerscore, score_num);
		//fputs("\n", score_num);
		linenum++;
	}
	fclose(score_num);
	return;
}
#endif