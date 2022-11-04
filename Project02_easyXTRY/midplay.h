#pragma once
/*
midplay.h
用于播放mid音乐的头函数
by scb
*/

//需要<graphics.h>头函数
//下载地址:
//https://easyx.cn/easyx
// 引用 Windows Multimedia API

#include <graphics.h>

//循环播放音乐
//这里的song规范是 xxx.mid
//debug模式下，音乐文件请放在项目文件夹，如test14/music.mid
//release模式下，请把音乐文件和编译的 exe 放在一起
#define startbgm(song) \
mciSendString(_T("open "#song" type MPEGVideo alias current_bgm"), NULL, 0, NULL);\
mciSendString(_T("play current_bgm repeat"), NULL, 0, NULL)

//结束当前音乐
#define endbgm \
mciSendString(_T("stop current_bgm"), NULL, 0, NULL); \
mciSendString(_T("close current_bgm"), NULL, 0, NULL)