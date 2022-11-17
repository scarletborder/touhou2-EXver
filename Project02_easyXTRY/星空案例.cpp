#include <graphics.h> 
#include <time.h>
#include <conio.h>


#define MAXSTAR 200	// ��������
#if 1
struct STAR
{
	double	x;
	int		y;
	double	step;
	int		color;
};

STAR star[MAXSTAR];

// ��ʼ������
void InitStar(int i)
{
	star[i].x = 0;
	star[i].y = rand() % 720;
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// �ٶ�Խ�죬��ɫԽ��
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}

// �ƶ�����
void MoveStar(int i)
{
	// ����ԭ��������
	putpixel((int)star[i].x, star[i].y, 0);

	// ������λ��
	star[i].x += star[i].step;
	if (star[i].x > 960)	InitStar(i);

	// ��������
	putpixel((int)star[i].x, star[i].y, star[i].color);
}

// ������
void starbk()
{
	srand((unsigned)time(NULL));	// �������
	//initgraph(640, 480);			// ������ͼ����

	// ��ʼ����������
	for (int i = 0; i < MAXSTAR; i++)
	{
		InitStar(i);
		star[i].x = rand() % 960;
	}

	// �����ǿգ���������˳�
	while (!_kbhit())
	{
		settextstyle(50, 0, _T("Consolas"));
		//����
		settextcolor(RED);
		outtextxy(320, 180, _T("�ǳ������о���"));
		outtextxy(360, 300, _T("Project 01"));
		for (int i = 0; i < MAXSTAR; i++)
			MoveStar(i);
		Sleep(20);
	}

	//closegraph();					// �رջ�ͼ����
	return;
}
#endif