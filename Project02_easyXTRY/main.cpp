#include"menuh.h"
#if 1

int main()
{
	initgraph(640, 480);
	
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

	//���˵�
	endsignal = cmdmainmenu(signalp);

	//���û�а�esc����ʼ��Ϸ
	if (endsignal != CMD_ESC)
	{
		//��ʼ��Ϸ
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