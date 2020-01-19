#pragma once

/*
	录像处理管理类
*/
#ifndef _VIDEO_RECORD_MAN_H_
#define	_VIDEO_RECORD_MAN_H_
#include "Decoder.h"
class CVideoRecordMan
{
public:
	CVideoRecordMan(const char* sFilePath, unsigned int w,unsigned int h,unsigned int frameRate);
	~CVideoRecordMan(void);
public:
    static void MyON_VEDIO_DATA(int width, int height, VPicture* pic, void* lParam);

	bool play_start(unsigned int hWnd);
    bool play_pause();
    bool play_resume();
    bool play_step();
    bool play_step_prev();
    bool play_speed(int speed);
    bool play_snap(const char* sFilePath);
private:
	CDecoder* m_pDecoder;
    

};
#endif