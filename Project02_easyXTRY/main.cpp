#include"menuh.h"
#if 1

int main()
{
	initgraph(640, 480);
	
	//游戏结束信号
	//0为没有进行游戏或未正常完成
	//1为bad_end
	//2为good_end
	//3为已经选择完角色，继续游戏
	int endsignal = 0;
	int* signalp = &endsignal;

	//开幕
	starbk();
	cleardevice();
	_getch();

	//主菜单
	endsignal = cmdmainmenu(signalp);

	//如果没有按esc，则开始游戏
	if (endsignal != CMD_ESC)
	{
		//开始游戏
		gamemain(signalp,endsignal);
		closegraph();
		return 0;
	}
	

	//

	EndBatchDraw();
	closegraph();
	return 0;
}
#endif