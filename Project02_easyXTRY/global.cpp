#include"menuh.h"



int GETCMD()
{
	int cmd = 0;
	/*---------------------start getchar-------------------------------*/
	//��ü����������cmd���
	

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

	//������ӳ���int������ֵ
	// ���ϼ�Ϊ 8
	//û�а���ʱ����0
	
}

//��ѡ������Ĳ˵����ƶ�����ж��Ƿ�Ϸ�
//ѡ������������飬����optnumд����ʵ����������һ��ѡ���optֵΪ0
//���룺ѡ�����ʵ���������ڵ�ѡ����ţ�0��1��2����ѡ���move(����optmove)
//�����������ѡ����ţ�0,1,2��
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


//���֣��Ƿ������Ϻ���
//���ܣ��ڵ�һ������ɵ�����£��Ƿ������ϰ���
//�жϰ����Ƿ��£��Ƿ���1���񷵻�0
int isDUkey_s(char key)//�жϰ����Ƿ��£��Ƿ���1���񷵻�0
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
//			while (delayT)//������һ�������£�ÿһ������һ����������û��ͬʱ����
//			{
//				kw = isDUkey_s('W');
//				ka = isDUkey_s('A');
//				if (kw == 0)
//					kwl = kw;
//				if (ka == 0)
//					kal = ka;
//				if (kw == 1 && kwl != kw && ka == 1 && kal != ka)
//				{
//					printf("W��A��ͬʱ������\n");
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