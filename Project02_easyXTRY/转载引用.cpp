#include"menuh.h"
//����͸����ͼ����
#if 1
/******************************************************/
#pragma comment( lib, "MSIMG32.LIB")
//// ͸����ͼ����
//// ������
////		dstimg: Ŀ�� IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
////		x, y:	Ŀ����ͼλ��
////		srcimg: Դ IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
////		transparentcolor: ͸��ɫ��srcimg �ĸ���ɫ�����Ḵ�Ƶ� dstimg �ϣ��Ӷ�ʵ��͸����ͼ
//// 
////     ͸��ɫ��BGR��ʽ��ʹ��ʱRGB������ 
//// 
////	transparentimage(NULL, 120, 0, &src, 0x3ffc4a);
//void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
//{
//	HDC dstDC = GetImageHDC(dstimg);
//	HDC srcDC = GetImageHDC(srcimg);
//	int w = srcimg->getwidth();
//	int h = srcimg->getheight();
//
//	// ʹ�� Windows GDI ����ʵ��͸��λͼ
//	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
//}

// ͸����ͼ����
// ������
//		dstimg: Ŀ�� IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
//		x, y:	Ŀ����ͼλ��
//		srcimg: Դ IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
//		transparentcolor: ͸��ɫ��srcimg �ĸ���ɫ�����Ḵ�Ƶ� dstimg �ϣ��Ӷ�ʵ��͸����ͼ
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer(dstimg);
	DWORD* src = GetImageBuffer(srcimg);
	int src_width = srcimg->getwidth();
	int src_height = srcimg->getheight();
	int dst_width = (dstimg == NULL ? getwidth() : dstimg->getwidth());
	int dst_height = (dstimg == NULL ? getheight() : dstimg->getheight());

	// ������ͼ��ʵ�ʳ���
	int iwidth = (x + src_width > dst_width) ? dst_width - x : src_width;
	int iheight = (y + src_height > dst_height) ? dst_height - y : src_height;

	// ������ͼ��ʼλ��
	dst += dst_width * y + x;

	// ����͸��ɫ����ʾ�������е����ݽṹΪ 0xaarrggbb
	transparentcolor = 0xff000000 | BGR(transparentcolor);

	// ʵ��͸����ͼ
	for (int iy = 0; iy < iheight; iy++)
	{
		for (int ix = 0; ix < iwidth; ix++)
		{
			if (src[ix] != transparentcolor)
				dst[ix] = src[ix];
		}
		dst += dst_width;
		src += src_width;
	}
}
#endif


