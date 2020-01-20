#include "VideoRecordMan.h"

CVideoRecordMan::CVideoRecordMan(const char* sFilePath, unsigned int w,unsigned int h,unsigned int frameRate)
:m_pDecoder(NULL)
{
}

CVideoRecordMan::~CVideoRecordMan(void)
{
    //D3D_VIDEO_RENDER::D3D_Video_Render_Destroy(m_pD3DRender);
}

void CVideoRecordMan::MyON_VEDIO_DATA(int width, int height, VPicture* pic, void* lParam)
{

}

bool CVideoRecordMan::play_start(unsigned int hWnd)
{
	if(!m_pDecoder)
		m_pDecoder = new CDecoder;
	if(!m_pDecoder)
		return false;
    

	//m_pDecoder->SetVideoCallBack(MyON_VEDIO_DATA,(void*)this);
    //return m_pDecoder->init("D:\\RAW_DATA.h265",(HWND)hWnd);
	return m_pDecoder->init("D:\\RAW_DATA.mp4",(HWND)hWnd);
}

bool CVideoRecordMan::play_pause()
{
    if(!m_pDecoder)
        return false;
    return m_pDecoder->play_pause();    
}

bool CVideoRecordMan::play_resume()
{
    if(!m_pDecoder)
        return false;
    return m_pDecoder->play_resume();
}

bool CVideoRecordMan::play_step()
{
    if(!m_pDecoder)
        return false;
    return m_pDecoder->NextSingleFrame();
}

bool CVideoRecordMan::play_seek(unsigned int ntime)
{
	if(!m_pDecoder)
		return false;
	return m_pDecoder->play_seek(ntime);
}

bool CVideoRecordMan::play_step_prev()
{
    if(!m_pDecoder)
        return false;
    return m_pDecoder->PreSingleFrame();
}

bool CVideoRecordMan::play_speed(int speed)
{
    if(!m_pDecoder)
        return false;
    return m_pDecoder->play_speed(speed);
}

bool CVideoRecordMan::play_snap(const char* sFilePath)
{
    if(!m_pDecoder)
        return false;
    return m_pDecoder->snapshot(sFilePath);
}
