#include"menuh.h"
void rainbow()
{
	BeginBatchDraw();
	// ����������(ͨ������������)
	float H = 190;		// ɫ��
	float S = 1;		// ���Ͷ�
	float L = 0.7f;		// ����
	for (int y = 0; y < SIZEY; y++)
	{
		L += 0.0002f;
		setlinecolor(HSLtoRGB(H, S, L));
		line(0, y, SIZEX - 1, y);
	}

	// ���ʺ�(ͨ��ɫ��������)
	H = 0;
	S = 1;
	L = 0.5f;
	setlinestyle(PS_SOLID, 2);		// �����߿�Ϊ 2
	for (int r = 400; r > 344; r--)
	{
		H += 5;
		setlinecolor(HSLtoRGB(H, S, L));
		circle(500, 480, r);
	}
	EndBatchDraw();
}
