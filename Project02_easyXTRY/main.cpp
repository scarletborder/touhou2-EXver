#include"menuh.h"
/******************************************************************/
//�ǳ������о���
//����scarletborder
//�汾��v0.00c - ����Ԥ����
//ʱ�䣺2022��11��17��
//�汾˵��������:ǽ�ڣ�����ߣ��������书��;
//			�Ż�:����ϵͳ������;
//			�޸�:���浯Ļ����ʱ���ؿ���;
/******************************************************************/
#if 1
int main()
{
	initgraph(960, 720);
	
	//���˵������ź�
	//CMD_ESCΪû�н�����Ϸ��δ�������
	//1-4Ϊ���ֻ���
	int choose_charcter = 0;


	//��Ϸ���巵���ź�
	//�ɹ��������1->1
	//�ɹ��������2->2
	//�κλ����->3
	//��Ϸʧ��/��;�˳�->0
	short int endsignal = 0;


	//��Ļ
	starbk();
	cleardevice();
	_getch();


	//���˵�
	while(choose_charcter != CMD_ESC)
	{
		choose_charcter = cmdmainmenu();
		Sleep(50);

		//������˵������źŲ���esc����ʼ��Ϸ
		if (choose_charcter == CMD_ESC)
		{
			break;
		}

			//��ʼ��Ϸ
		Sleep(50);
		endsignal = gamemain(choose_charcter);
			
		
	}
	
	//����endsignal,�Ž�β


	EndBatchDraw();
	closegraph();
	return 0;
}
#endif