#include<graphics.h>
#define SIZEX 960
#define SIZEY 720



//开始聊天
#define startchat \
cleardevice(); \
textpositon = { 50, SIZEY - 240, SIZEX - 50, SIZEY }; \
cleardevice()

//下一条
#define nexttext \
FlushBatchDraw(); \
Sleep(4000);\
cleardevice()

RECT textpositon;

//drawtext(_T(""), &textpositon, DT_LEFT);

void chat1()
{
	settextcolor(WHITE);
	settextstyle(30, 0, _T("宋体"));
	startchat;
	drawtext(_T("灵梦\n就是你霸占我的神社是吧\n看我速速把你退治"), &textpositon, DT_LEFT);
	nexttext;
	drawtext(_T("里香：\n大姐你先别急，这其中肯定有误会"), &textpositon, DT_LEFT);
	nexttext;
	drawtext(_T("灵梦：\n多说无益，妖怪退治！！"), &textpositon, DT_LEFT);
	nexttext;

}