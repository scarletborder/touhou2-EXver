#pragma once
#include <graphics.h>		// EasyX_20190219(beta)
#include <conio.h>
// ���øÿ����ʹ�� TransparentBlt ����


#ifndef     _transimg_
#define  _transimg_

//https://codebus.cn/yangw/transparent-putimage
// ͸����ͼ����
// ������
//		dstimg: Ŀ�� IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
//		x, y:	Ŀ����ͼλ��
//		srcimg: Դ IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
//		transparentcolor: ͸��ɫ��srcimg �ĸ���ɫ�����Ḵ�Ƶ� dstimg �ϣ��Ӷ�ʵ��͸����ͼ
//ʾ��  transparentimage(NULL, 120, 0, &src, 0x00FFFFFF);
#pragma comment( lib, "MSIMG32.LIB")
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// ʹ�� Windows GDI ����ʵ��͸��λͼ
	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
}

#endif