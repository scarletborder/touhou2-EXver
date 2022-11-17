#include"menuh.h"



int GETCMD()
{
	int cmd = 0;
	/*---------------------start getchar-------------------------------*/
	//获得键盘命令并返回cmd序号
	

	if (GetAsyncKeyState(37) & 0x8000)
		cmd |= CMD_LEFT;
	if (GetAsyncKeyState(39) & 0x8000)
		cmd |= CMD_RIGHT;
	if (GetAsyncKeyState(38) & 0x8000)
		cmd |= CMD_UP;
	if (GetAsyncKeyState(40) & 0x8000)
		cmd |= CMD_DOWN;
	if (GetAsyncKeyState(27) & 0x8000)
		cmd |= CMD_ESC;



	if ((GetAsyncKeyState('Z') & 0x8000) || ((GetAsyncKeyState('z') & 0x8000)))
		cmd |= CMD_CONFIRM;
	if ((GetAsyncKeyState('X') & 0x8000) || ((GetAsyncKeyState('x') & 0x8000)))
		cmd |= CMD_CANCEL;
	if ((GetAsyncKeyState('C') & 0x8000) || ((GetAsyncKeyState('c') & 0x8000)))
		cmd |= CMD_SPECIAL;


	return cmd;
	/*-------------------------------end getchar-------------------------------*/

	//按键所映射的int类型数值
	// 如上键为 8
	//没有按键时返还0
	
}

//有选项个数的菜单，移动光标判断是否合法
//选项个数类似数组，允许optnum写入真实个数，但第一个选项的opt值为0
//输入：选项的真实个数；现在的选项序号（0，1，2）；选项的move(接受optmove)
//输出：后来的选项序号（0,1,2）
int limitmenujudge(int optnum, int c_opt, int optmove)
{
	switch (optmove)
	{
	case CMD_UP:
		if (c_opt >= 1)
		{
			c_opt--;
			break;
		}
		break;
	case CMD_DOWN:
		if (c_opt < optnum - 1)
		{
			c_opt++;
			break;
		}
		break;
	case CMD_ESC:
		return CMD_ESC;
	}

	return c_opt;
}


//名字：是否完成组合函数
//功能：在第一个键完成的情况下，是否完成组合按键
//判断按键是否按下，是返回1，否返回0
int isDUkey_s(char key)//判断按键是否按下，是返回1，否返回0
{
	int down = 0;
	down = GetKeyState(key);
	if (down < 0)
		return 1;
	if (down > 0)
		return 0;
	return -1;
}
//int isDUkey()
//{
//	int kw = 0, kwl = 0, ka = 0, kal = 0;
//	while (1)
//	{
//		kw = isDUkey_s('W');
//		ka = isDUkey_s('A');
//		if ((kw == 1 && kwl != kw) || (ka == 1 && kal != ka))
//		{
//			while (delayT)//当其中一个键按下，每一毫秒检查一次两个键有没有同时按下
//			{
//				kw = isDUkey_s('W');
//				ka = isDUkey_s('A');
//				if (kw == 0)
//					kwl = kw;
//				if (ka == 0)
//					kal = ka;
//				if (kw == 1 && kwl != kw && ka == 1 && kal != ka)
//				{
//					printf("W、A键同时被按下\n");
//					kwl = kw;
//					kal = ka;
//					break;
//				}
//				Sleep(1);
//			}
//		}
//		if (kw == 0)
//			kwl = kw;
//		if (ka == 0)
//			kal = ka;
//	}
//	return 0;
//}
/***************END*************************/