#pragma once
#include <graphics.h>		// EasyX_20190219(beta)
#include <conio.h>
// 引用该库才能使用 TransparentBlt 函数


#ifndef     _transimg_
#define  _transimg_

//https://codebus.cn/yangw/transparent-putimage
// 透明贴图函数
// 参数：
//		dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
//		x, y:	目标贴图位置
//		srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体
//		transparentcolor: 透明色。srcimg 的该颜色并不会复制到 dstimg 上，从而实现透明贴图
//示例  transparentimage(NULL, 120, 0, &src, 0x00FFFFFF);
#pragma comment( lib, "MSIMG32.LIB")
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// 使用 Windows GDI 函数实现透明位图
	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
}

#endif