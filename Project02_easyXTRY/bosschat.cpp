#include<graphics.h>
#define SIZEX 960
#define SIZEY 720



//��ʼ����
#define startchat \
cleardevice(); \
textpositon = { 50, SIZEY - 240, SIZEX - 50, SIZEY }; \
cleardevice()

//��һ��
#define nexttext \
FlushBatchDraw(); \
Sleep(4000);\
cleardevice()

RECT textpositon;

//drawtext(_T(""), &textpositon, DT_LEFT);

void chat1()
{
	settextcolor(WHITE);
	settextstyle(30, 0, _T("����"));
	startchat;
	drawtext(_T("����\n�������ռ�ҵ������ǰ�\n�������ٰ�������"), &textpositon, DT_LEFT);
	nexttext;
	drawtext(_T("���㣺\n������ȱ𼱣������п϶������"), &textpositon, DT_LEFT);
	nexttext;
	drawtext(_T("���Σ�\n��˵���棬�������Σ���"), &textpositon, DT_LEFT);
	nexttext;

}