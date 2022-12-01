#include<graphics.h>
#define SIZEX 960
#define SIZEY 720

/************************************************/
//用途：用于boss关卡前的对话和（未来的）ending图片播放
//输入：无
//输出：无

//对话框开始聊天
#define startchat \
cleardevice(); \
textpositon = { 50, SIZEY - 240, SIZEX - 50, SIZEY }; \
cleardevice()

//下一条聊天内容
#define nexttext \
FlushBatchDraw(); \
Sleep(2000);\
cleardevice()

RECT textpositon;

//添加一句话所用到的函数
//drawtext(_T(""), &textpositon, DT_LEFT);

//stage5对话
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