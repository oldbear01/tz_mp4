#pragma once

#include "common.h"

#define OUTPUT_YUV420P 0
#define LOAD_YUV420P 1

typedef struct AvPicture {
	uint8_t *data[4];
	int linesize[4];       ///< number of bytes per line
} AvPicture;


class CDecoder
{
public:
	CDecoder(void);
	~CDecoder(void);
public:
	bool init(const char* sFilePath,HWND hWnd);
	void stopdecoder();
	void d3dinit();
	bool pause(bool bPause);
	void fastPlay(int nPlayRate);
	void slowPlay(int nPlayRte);
	void play();
	void CapTure();
	bool NextSingleFrame();
    bool PreSingleFrame();
	IDirect3D9 *m_pDirect3D9;
	IDirect3DDevice9 *m_pDirect3DDevice;
	IDirect3DSurface9 *m_pDirect3DSurfaceRender;
	CRITICAL_SECTION  m_critial;
	RECT m_rtViewport;
	int m_screen_w;
	int m_screen_h;
	int m_nFrameRate;

    int64_t  m_curPts;

	HRESULT m_lRet;
private:
	int InitD3D( HWND hwnd, unsigned long lWidth, unsigned long lHeight );
	void Cleanup();
	void ConvertYUV2RGB24(unsigned char *src0,unsigned char *src1,unsigned char *src2,unsigned char *dst_ori,int width,int height);
	BOOL SaveToFile(const char * pFilename, unsigned char * pSurFrame, int w, int h);
	void initFilter(const char* filter);
private:
	AVFormatContext	*m_pFormatCtx;
	AVCodecContext	*m_pCodecCtx;
	
	AVFrame	*m_pFrame;
	

	AVFilterContext *m_pBuffersink_ctx;
	AVFilterContext *m_pBuffersrc_ctx;
	AVFilterGraph *m_pFilter_graph;

	
	CTzThread m_hThread;
	int m_videoindex;
	int m_audioindex;
	HWND m_hWnd;
	bool m_bPause;
	bool m_bCapTure;
	float m_nPlayRate;
	
	static int thread_fun(LPVOID lParam);
};
