#include"menuh.h"
#if 1

int main()
{
	initgraph(960, 720);
	
	//��Ϸ�����ź�
	//0Ϊû�н�����Ϸ��δ�������
	//1Ϊbad_end
	//2Ϊgood_end
	//3Ϊ�Ѿ�ѡ�����ɫ��������Ϸ
	int endsignal = 0;
	int* signalp = &endsignal;

	//��Ļ
	starbk();
	cleardevice();
	_getch();
	int escgame = 0;

	//���˵�
	while(endsignal != CMD_ESC)
	{
		endsignal = cmdmainmenu(signalp);
		Sleep(50);
		//���û�а�esc����ʼ��Ϸ
		if (endsignal == CMD_ESC)
		{
			break;
		}
			//��ʼ��Ϸ
		Sleep(50);
			gamemain(signalp, endsignal);
			
		
	}
	

	//

	EndBatchDraw();
	closegraph();
	return 0;
}
#endif