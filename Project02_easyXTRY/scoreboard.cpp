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
	//�����ҵ�����
	FILE* score_name;
	score_name = fopen("result\\player.txt", "r");
	

	int i = 0;

	for (i = 0; i < 10; i++)
	{
		//printf("%d:\\ %s", i, playername[i]);
		fgets(player[i].playername, 14, (FILE*)score_name);
	}
	fclose(score_name);

	//�����ҷ���
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

	//��ʼ��ӡ�������
	settextcolor(WHITE);
	settextstyle(33, 0, _T("Consolas"));

	for(i = 0; i <= 9;i++)
	{
		RECT result_scorer = { 300, 200 + 35*i, SIZEX, SIZEY };
		TCHAR* result_display = char2TCAHR(player[i].playername);
		drawtext(result_display, &result_scorer, DT_LEFT);
	}

	//��ʼ��ӡ��ҷ���
	settextcolor(WHITE);
	settextstyle(33, 0, _T("Consolas"));

	for (i = 0; i <= 9; i++)
	{
		RECT result_scorer = { 600, 200 + 35 * i, SIZEX, SIZEY };
		TCHAR* result_display = char2TCAHR(player[i].playerscore);
		drawtext(result_display, &result_scorer, DT_LEFT);
	}

	//�˳�
	while (1)
	{
		int opt = GETCMD();
		//ʹ��esc
		if (opt == CMD_ESC)
		{
			cleardevice();
			drawmainmenufalme();
			return;
		}

		//ʹ��x
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
//��Ϸ�����������
void saveresult(int cscore)
{
	//�Ȼ�ȡ��ʷ����
#if 1
	//�����ҵ�����
	FILE* score_name;
	score_name = fopen("result\\player.txt", "r");


	int i = 0;

	for (i = 0; i < 10; i++)
	{
		//printf("%d:\\ %s", i, playername[i]);
		fgets(player[i].playername, 14, (FILE*)score_name);
	}
	fclose(score_name);

	//�����ҷ���
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
	settextstyle(40, 0, _T("����"));
	settextcolor(BLACK);

	char cscorestr[15] = { 0 };
	sprintf(cscorestr, "%d", cscore);

	outtextxy(50, 200, _T("��ϲͨ�ؿ���Ԥ����v0.00b,��ķ���Ϊ"));
	outtextxy(50, 245, char2TCAHR(cscorestr));

	//������¼��Ҫ��
	if (cscore <= player[9].scorenum)
	{
		outtextxy(50, 290, _T("���а���ͷ�Ϊ"));
		outtextxy(50, 335, char2TCAHR(player[9].playerscore));
		outtextxy(50, 380, _T("����Ŭ���ɣ�"));
		return;
	}


	//����¼��Ҫ��
	int numi = 8;
	for (; numi >= 0; numi--)
	{
		if (cscore <= player[numi].scorenum)
		{
			break;			
		}

	}

	//�滻���Ϊ0��Ҳ���ǵ�һ������
	if(numi < 0)
	{
		outtextxy(50, 290, _T("�ﵽ��ʷ�¼�¼������"));
	}

	//�滻���Ϊi+1������
	for (int sei = 8; sei >= numi + 1; sei--)
	{
		strcpy(player[sei + 1].playerscore,player[sei].playerscore);
	}
	sprintf(player[numi + 1].playerscore, "%d\n", cscore);


	outtextxy(50, 335, _T("�Ƿְ���δ֪ԭ��ͣ��,��֧�ּ�¼���������س�������"));//����������ҵ����֣�����14��
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