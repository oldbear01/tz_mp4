#pragma once

/*
	¼���������
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
	bool play_start(unsigned int hWnd);
private:
	CDecoder* m_pDecoder;
};
#endif