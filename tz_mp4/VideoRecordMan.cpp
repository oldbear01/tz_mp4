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
	
	return m_pDecoder->init("D:\\RAW_DATA.h265",(HWND)hWnd);
}

bool CVideoRecordMan::play_pause()
{
    if(!m_pDecoder)
        return false;
    return m_pDecoder->pause(true);
    
}

bool CVideoRecordMan::play_step()
{
    if(!m_pDecoder)
        return false;
    return m_pDecoder->NextSingleFrame();
}

bool CVideoRecordMan::play_step_prev()
{
    if(!m_pDecoder)
        return false;
    return m_pDecoder->PreSingleFrame();
}
