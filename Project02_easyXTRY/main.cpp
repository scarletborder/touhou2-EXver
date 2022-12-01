#include"menuh.h"
/******************************************************************/
//星尘幻想研究所
//程序：scarletborder
//版本：v0.00c - 开发预览版
//时间：2022年11月17日
//版本说明：更新:墙壁，点道具，御札连射功能;
//			优化:分数系统更合理;
//			修复:画面弹幕过多时严重卡顿;
/******************************************************************/
#if 1
int main()
{
	initgraph(960, 720);
	
	//主菜单返回信号
	//CMD_ESC为没有进行游戏或未正常完成
	//1-4为四种机体
	int choose_charcter = 0;


	//游戏本体返回信号
	//成功完成主线1->1
	//成功完成主线2->2
	//任何坏结局->3
	//游戏失败/中途退出->0
	short int endsignal = 0;


	//开幕
	starbk();
	cleardevice();
	_getch();


	//主菜单
	while(choose_charcter != CMD_ESC)
	{
		choose_charcter = cmdmainmenu();
		Sleep(50);

		//如果主菜单返回信号不是esc，则开始游戏
		if (choose_charcter == CMD_ESC)
		{
			break;
		}

			//开始游戏
		Sleep(50);
		endsignal = gamemain(choose_charcter);
			
		
	}
	
	//根据endsignal,放结尾


	EndBatchDraw();
	closegraph();
	return 0;
}
#endif