#include"menuh.h"
//绘制透明贴图函数
#if 1
/******************************************************/
#pragma comment( lib, "MSIMG32.LIB")
//// 透明贴图函数
//// 参数：
////		dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
////		x, y:	目标贴图位置
////		srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体
////		transparentcolor: 透明色。srcimg 的该颜色并不会复制到 dstimg 上，从而实现透明贴图
//// 
////     透明色是BGR格式，使用时RGB反过来 
//// 
////	transparentimage(NULL, 120, 0, &src, 0x3ffc4a);
//void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
//{
//	HDC dstDC = GetImageHDC(dstimg);
//	HDC srcDC = GetImageHDC(srcimg);
//	int w = srcimg->getwidth();
//	int h = srcimg->getheight();
//
//	// 使用 Windows GDI 函数实现透明位图
//	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
//}

// 透明贴图函数
// 参数：
//		dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
//		x, y:	目标贴图位置
//		srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体
//		transparentcolor: 透明色。srcimg 的该颜色并不会复制到 dstimg 上，从而实现透明贴图
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
{
	// 变量初始化
	DWORD* dst = GetImageBuffer(dstimg);
	DWORD* src = GetImageBuffer(srcimg);
	int src_width = srcimg->getwidth();
	int src_height = srcimg->getheight();
	int dst_width = (dstimg == NULL ? getwidth() : dstimg->getwidth());
	int dst_height = (dstimg == NULL ? getheight() : dstimg->getheight());

	// 计算贴图的实际长宽
	int iwidth = (x + src_width > dst_width) ? dst_width - x : src_width;
	int iheight = (y + src_height > dst_height) ? dst_height - y : src_height;

	// 修正贴图起始位置
	dst += dst_width * y + x;

	// 修正透明色，显示缓冲区中的数据结构为 0xaarrggbb
	transparentcolor = 0xff000000 | BGR(transparentcolor);

	// 实现透明贴图
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


