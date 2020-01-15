#include "VideoRecordMan.h"

CVideoRecordMan::CVideoRecordMan(const char* sFilePath, unsigned int w,unsigned int h,unsigned int frameRate)
:m_pDecoder(NULL)
{
}

CVideoRecordMan::~CVideoRecordMan(void)
{
}

bool CVideoRecordMan::play_start(unsigned int hWnd)
{
	if(!m_pDecoder)
		m_pDecoder = new CDecoder;
	if(!m_pDecoder)
		return false;
	m_pDecoder->init("D:\\RAW_DATA.h265",(HWND)hWnd);
	return true;
}
