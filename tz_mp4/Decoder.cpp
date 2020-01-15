#include "Decoder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <atlstr.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

CDecoder::CDecoder(void)
:m_nFrameRate(25)
{
	m_bPause = false;
	m_nPlayRate = 1;
	m_pDirect3D9= NULL;
	m_pDirect3DDevice= NULL;
	m_pDirect3DSurfaceRender= NULL;
	lRet = 0;
	screen_h = 0;
	screen_w = 0;
	m_bCapTure = false;
}

CDecoder::~CDecoder(void)
{
}



int CDecoder::thread_fun(LPVOID lParam)
{
	CDecoder* pThis = (CDecoder*)lParam;
	if(pThis)
	{
		
		int got_picture = 0;
		int ret = 0;
		AVPacket* m_pPacket=(AVPacket *)av_malloc(sizeof(AVPacket));
		av_init_packet(m_pPacket);
	
		if(pThis->m_bPause)
		{

		}
		else if (av_read_frame(pThis->m_pFormatCtx,m_pPacket)>=0)
		{
			if(m_pPacket->stream_index == pThis->m_videoindex)
			{
				
				//char* sErr = new char[128];
				ret = avcodec_decode_video2(pThis->m_pCodecCtx,pThis->m_pFrame,&got_picture,m_pPacket);
				if(ret < 0)
				{
					
					//sErr = av_make_error_string(sErr,128,ret);
					//return -1;
				}
				if(got_picture)
				{
					
					
					int y_size=pThis->m_pCodecCtx->width*pThis->m_pCodecCtx->height;
#if OUTPUT_YUV420P
					y_size=m_pCodecCtx->width*m_pCodecCtx->height;  
					fwrite(m_pFrameYUV->data[0],1,y_size,fp_yuv);    //Y 
					fwrite(m_pFrameYUV->data[1],1,y_size/4,fp_yuv);  //U
					fwrite(m_pFrameYUV->data[2],1,y_size/4,fp_yuv);  //V
#endif
					
					uint8_t *py = pThis->m_pFrame->data[0];
					uint8_t *pu = pThis->m_pFrame->data[1];
					uint8_t *pv = pThis->m_pFrame->data[2];
					int sizey = pThis->m_pFrame->linesize[0];
					int sizeu = pThis->m_pFrame->linesize[1];
					int sizev = pThis->m_pFrame->linesize[2];
					if(pThis->m_bCapTure)
					{
						/*AvPicture* pic = new AvPicture;
						memset(pic,0,sizeof(AvPicture));*/
					//	unsigned char* pic = new unsigned char[y_size*3];
					//	pThis->ConvertYUV2RGB24(py,pu,pv,pic,pThis->screen_w,pThis->screen_h);
					//	pThis->SaveToFile("D:\\123.bmp",pic,pThis->screen_w,pThis->screen_h);
						pThis->m_bCapTure = false;
					//	if(pic)
						{
					//		delete[] pic;
					//		pic = NULL;
						}
					}
					
					if(pThis->m_pDirect3DSurfaceRender == NULL)
						return -1;
					D3DLOCKED_RECT d3d_rect;
					pThis->lRet = pThis->m_pDirect3DSurfaceRender->LockRect(&d3d_rect,NULL,D3DLOCK_DONOTWAIT);
					if(FAILED(pThis->lRet))
						return -1;
					byte* pData = new byte[y_size*12/8];
					memset(pData,0,y_size);
					byte* pDest = (BYTE *)d3d_rect.pBits;
					int stride = d3d_rect.Pitch;
					unsigned long i = 0;
					
					for (int i=0; i<pThis->screen_h; i++)//Y数据拷贝
					{//每次拷贝screen_w个数据
						memcpy(pData+i*pThis->screen_w, py+i*sizey, pThis->screen_w);
					}
					for (int i=0; i<pThis->screen_h/2; i++)//U数据拷贝
					{
						memcpy(pData+pThis->screen_w*pThis->screen_h+i*pThis->screen_w/2, pu+i*sizeu, pThis->screen_w/2);
					}
					for (int i=0; i<pThis->screen_h/2; i++)//V数据拷贝
					{
						memcpy(pData+5*pThis->screen_w*pThis->screen_h/4+i*pThis->screen_w/2, pv+i*sizev, pThis->screen_w/2);
					}


					for(int i = 0;i < pThis->screen_h;i ++){
						memcpy(pDest + i * stride,pData + i * pThis->screen_w, pThis->screen_w);
					}					
					for(int i = 0;i < pThis->screen_h/2;i ++){
						memcpy(pDest + stride * pThis->screen_h + stride * pThis->screen_h / 4 + i * stride / 2,
							pData + pThis->screen_w * pThis->screen_h + i * pThis->screen_w / 2, pThis->screen_w / 2);
					}
					for(int i = 0;i < pThis->screen_h/2;i ++){
						memcpy(pDest + stride * pThis->screen_h + i * stride / 2,
							pData + pThis->screen_w * pThis->screen_h + pThis->screen_w * pThis->screen_h / 4 + i * pThis->screen_w / 2, pThis->screen_w / 2);
					}
					

					pThis->lRet=pThis->m_pDirect3DSurfaceRender->UnlockRect();
					if(FAILED(pThis->lRet))
						return -1;

					if (pThis->m_pDirect3DDevice == NULL)
						return -1;

					pThis->m_pDirect3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
					pThis->m_pDirect3DDevice->BeginScene();
					IDirect3DSurface9 * pBackBuffer = NULL;
					pThis->m_pDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
					pThis->m_pDirect3DDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&pBackBuffer);
					pThis->m_pDirect3DDevice->StretchRect(pThis->m_pDirect3DSurfaceRender,NULL,pBackBuffer,&pThis->m_rtViewport,D3DTEXF_LINEAR);
					pThis->m_pDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
					pThis->m_pDirect3DDevice->EndScene();
					pThis->m_pDirect3DDevice->Present( NULL, NULL, NULL, NULL );
					pBackBuffer->Release();
					//Sleep(20/(DWORD)pThis->m_nPlayRate);
					Sleep(1000/(pThis->m_nFrameRate*2));
					if(pData)
					{
						delete[] pData;
						pData = NULL;
					}
				}
			}
			av_free_packet(m_pPacket);
		}
				
	}
	return 0;
}

void CDecoder::initFilter(const char* filter)
{
	char sreg[512]={0};

	int ret = 0;

	const AVFilter* bufferSrc = avfilter_get_by_name("buffer");
	const AVFilter *buffersink = avfilter_get_by_name("ffbuffersink");
	AVFilterInOut *outputs = avfilter_inout_alloc();
	AVFilterInOut *inputs  = avfilter_inout_alloc();
	enum AVPixelFormat pix_fmts[] = { AV_PIX_FMT_YUV420P, AV_PIX_FMT_NONE };
//	AVBufferSinkParams *buffersink_params=NULL;

	m_pFilter_graph = avfilter_graph_alloc();

	/* buffer video source: the decoded frames from the decoder will be inserted here. */
	
	sprintf(sreg, /*sizeof(sreg),*/
		"video_size=%dx%d:pix_fmt=%d:time_base=%d/%d:pixel_aspect=%d/%d",
		m_pCodecCtx->width, m_pCodecCtx->height, m_pCodecCtx->pix_fmt,
		m_pCodecCtx->time_base.num, m_pCodecCtx->time_base.den,
		m_pCodecCtx->sample_aspect_ratio.num, m_pCodecCtx->sample_aspect_ratio.den);


	//buffersink_params = av_buffersink_params_alloc();


}

void CDecoder::Cleanup()
{
	EnterCriticalSection(&m_critial);
	if(m_pDirect3DSurfaceRender)
		m_pDirect3DSurfaceRender->Release();
	if(m_pDirect3DDevice)
		m_pDirect3DDevice->Release();
	if(m_pDirect3D9)
		m_pDirect3D9->Release();
	LeaveCriticalSection(&m_critial);
}


int CDecoder::InitD3D( HWND hwnd, unsigned long lWidth, unsigned long lHeight )
{
	HRESULT lRet;
	InitializeCriticalSection(&m_critial);
	Cleanup();

	m_pDirect3D9 = Direct3DCreate9( D3D_SDK_VERSION );
	if( m_pDirect3D9 == NULL )
		return -1;

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	GetClientRect(hwnd,&m_rtViewport);

	lRet=m_pDirect3D9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &m_pDirect3DDevice );
	if(FAILED(lRet))
		return -1;

#if LOAD_BGRA
	lRet=m_pDirect3DDevice->CreateOffscreenPlainSurface(
		lWidth,lHeight,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_pDirect3DSurfaceRender,
		NULL);
#elif LOAD_YUV420P
	lRet=m_pDirect3DDevice->CreateOffscreenPlainSurface(
		lWidth,lHeight,
		//m_rtViewport.right-m_rtViewport.left,m_rtViewport.bottom-m_rtViewport.top,
		(D3DFORMAT)MAKEFOURCC('Y', 'V', '1', '2'),
		D3DPOOL_DEFAULT,
		&m_pDirect3DSurfaceRender,
		NULL);
#endif
	if(FAILED(lRet))
		return -1;
	return 0;
}

void CDecoder::pause(bool bPause)
{
	m_bPause = bPause;
	int got_picture = 0;
	AVPacket* m_pPacket=(AVPacket *)av_malloc(sizeof(AVPacket));
	av_init_packet(m_pPacket);
}

void CDecoder::init(const char* sFilePath,HWND hWnd)
{
	m_hWnd = hWnd;
	FILE *fp_yuv=NULL;
	int y_size=0;
	unsigned char *out_buffer=NULL;
	struct SwsContext *img_convert_ctx=NULL;
	
	av_register_all();
	avformat_network_init();
	m_pFormatCtx = avformat_alloc_context();
	if(avformat_open_input(&m_pFormatCtx,sFilePath,NULL,NULL)!=0){
		printf("Couldn't open input stream.\n");
		return ;
	}
	if(avformat_find_stream_info(m_pFormatCtx,NULL)<0){
		printf("Couldn't find stream information.\n");
		return ;
	}
	
	m_videoindex = -1;
	m_nFrameRate = 25;
	for(int i=0; i<(int)m_pFormatCtx->nb_streams; i++) 
	{
		if(m_pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			m_videoindex=i;
			m_nFrameRate = m_pFormatCtx->streams[i]->avg_frame_rate.num / m_pFormatCtx->streams[i]->avg_frame_rate.den;
		}
		
	}
	
	if(m_videoindex==-1)
	{
		printf("Didn't find a video stream.\n");
		return ;
	}
	m_pCodecCtx=m_pFormatCtx->streams[m_videoindex]->codec;
	AVCodec *m_pCodec=avcodec_find_decoder(m_pCodecCtx->codec_id);
	if(avcodec_open2(m_pCodecCtx, m_pCodec,NULL)<0){
		printf("Could not open video codec.\n");
		return ;
	}
    int bit_rate = m_pCodecCtx->bit_rate;

	m_pFrame = av_frame_alloc();
	
	m_pFrame->data[0] = 0;
	m_pFrame->linesize[0] = 0;
	
	screen_w = m_pCodecCtx->width;
	screen_h = m_pCodecCtx->height;
	InitD3D(m_hWnd,screen_w,screen_h);
#if OUTPUT_YUV420P 
	fp_yuv=fopen("output.yuv","wb+");  
#endif 	
 	m_hThread.SetParam(thread_fun,this,1);
 	m_hThread.Start();
}

void CDecoder::stopdecoder()
{
	//Cleanup();
	m_hThread.Stop();

	if (m_pFrame != NULL)
	{
		av_free(m_pFrame);
		m_pFrame = NULL;
	}	
	if (m_pCodecCtx != NULL)
	{
		avcodec_close(m_pCodecCtx);
		av_free(m_pCodecCtx);
		m_pCodecCtx = NULL;
	}
	/*if (m_pFormatCtx != NULL)
	{
		avformat_free_context(m_pFormatCtx);
	}*/
}

void CDecoder::fastPlay(int nPlayRate)
{
	m_nPlayRate = (float)nPlayRate;
}

void CDecoder::slowPlay(int nPlayRte)
{
	if(nPlayRte == -1)
	{
		m_nPlayRate = 0.25;
	}
}

void CDecoder::play()
{
	m_bPause = false;
	m_nPlayRate = 1.0;
}

void CDecoder::CapTure()
{
	m_bCapTure = true;
}

void CDecoder::SingleFrame()
{
	m_bPause = true;
	int lRet = 0;
	int got_picture = -1;
	AVPacket* m_pPacket=(AVPacket *)av_malloc(sizeof(AVPacket));
	if(av_read_frame(m_pFormatCtx,m_pPacket)>=0)
	{	
		if(m_pPacket->stream_index == m_videoindex)
		{			
			
			int ret = avcodec_decode_video2(m_pCodecCtx,m_pFrame,&got_picture,m_pPacket);
			if(ret < 0)
			{
				return;
			}
			if(got_picture)
			{
				int y_size=m_pCodecCtx->width*m_pCodecCtx->height;
	#if OUTPUT_YUV420P
				y_size=m_pCodecCtx->width*m_pCodecCtx->height;  
				fwrite(m_pFrameYUV->data[0],1,y_size,fp_yuv);    //Y 
				fwrite(m_pFrameYUV->data[1],1,y_size/4,fp_yuv);  //U
				fwrite(m_pFrameYUV->data[2],1,y_size/4,fp_yuv);  //V
	#endif
				
				uint8_t *py = m_pFrame->data[0];
				uint8_t *pu = m_pFrame->data[1];
				uint8_t *pv = m_pFrame->data[2];
				int sizey = m_pFrame->linesize[0];
				int sizeu = m_pFrame->linesize[1];
				int sizev = m_pFrame->linesize[2];
			
				
				if(m_pDirect3DSurfaceRender == NULL)
					return ;
				D3DLOCKED_RECT d3d_rect;
				lRet = m_pDirect3DSurfaceRender->LockRect(&d3d_rect,NULL,D3DLOCK_DONOTWAIT);
				if(FAILED(lRet))
					return ;
				byte* pData = new byte[y_size*12/8];
				memset(pData,0,y_size);
				byte* pDest = (BYTE *)d3d_rect.pBits;
				int stride = d3d_rect.Pitch;
				unsigned long i = 0;
				
				for (int i=0; i<screen_h; i++)//Y数据拷贝
				{//每次拷贝screen_w个数据
					memcpy(pData+i*screen_w, py+i*sizey, screen_w);
				}
				for (int i=0; i<screen_h/2; i++)//U数据拷贝
				{
					memcpy(pData+screen_w*screen_h+i*screen_w/2, pu+i*sizeu, screen_w/2);
				}
				for (int i=0; i<screen_h/2; i++)//V数据拷贝
				{
					memcpy(pData+5*screen_w*screen_h/4+i*screen_w/2, pv+i*sizev, screen_w/2);
				}


				for(int i = 0;i < screen_h;i ++){
					memcpy(pDest + i * stride,pData + i * screen_w, screen_w);
				}					
				for(int i = 0;i < screen_h/2;i ++){
					memcpy(pDest + stride * screen_h + stride * screen_h / 4 + i * stride / 2,
						pData + screen_w * screen_h + i * screen_w / 2,screen_w / 2);
				}
				for(int i = 0;i < screen_h/2;i ++){
					memcpy(pDest + stride * screen_h + i * stride / 2,
						pData + screen_w * screen_h + screen_w * screen_h / 4 + i * screen_w / 2,screen_w / 2);
				}
				

				lRet=m_pDirect3DSurfaceRender->UnlockRect();
				if(FAILED(lRet))
					return ;

				if (m_pDirect3DDevice == NULL)
					return ;

				m_pDirect3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
				m_pDirect3DDevice->BeginScene();
				IDirect3DSurface9 * pBackBuffer = NULL;
				m_pDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
				m_pDirect3DDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&pBackBuffer);
				m_pDirect3DDevice->StretchRect(m_pDirect3DSurfaceRender,NULL,pBackBuffer,&m_rtViewport,D3DTEXF_LINEAR);
				m_pDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
				m_pDirect3DDevice->EndScene();
				m_pDirect3DDevice->Present( NULL, NULL, NULL, NULL );
				pBackBuffer->Release();
				//Sleep(40/(DWORD)m_nPlayRate);
				if(pData)
				{
					delete[] pData;
					pData = NULL;
				}
			}
		}
	}
	av_free_packet(m_pPacket);
}

void CDecoder::ConvertYUV2RGB24(unsigned char *src0,unsigned char *src1,unsigned char *src2,unsigned char *dst_ori,int width,int height)
{
	for(int i = 0; i<width*height/4;i++)    
	{        
		dst_ori[i*3+2] = src0[i]+1.772*(src1[i]-128);  //B = Y +1.779*(U-128)       
		dst_ori[i*3+1] = src0[i]-0.34413*(src1[i]-128)-0.71414*(src2[i]-128);//G = Y-0.3455*(U-128)-0.7169*(V-128)        
		dst_ori[i*3+0] = src0[i]+1.402*(src2[i]-128);//R = Y+1.4075*(V-128)    
	}

	//long int crv_tab[256];
	//long int cbu_tab[256];
	//long int cgu_tab[256];
	//long int cgv_tab[256];
	//long int tab_76309[256];
	//unsigned char clp[1024];   //for clip in CCIR601
	//long int crv,cbu,cgu,cgv;
	//int ii,ind;   

	//crv = 104597; cbu = 132201;  /* fra matrise i global.h */ 
	//cgu = 25675;  cgv = 53279;

	//for (ii = 0; ii < 256; ii++) {
	//	crv_tab[ii] = (ii-128) * crv;
	//	cbu_tab[ii] = (ii-128) * cbu;
	//	cgu_tab[ii] = (ii-128) * cgu;
	//	cgv_tab[ii] = (ii-128) * cgv;
	//	tab_76309[ii] = 76309*(ii-16);
	//}

	//for (ii=0; ii<384; ii++)
	//	clp[ii] =0;
	//ind=384;
	//for (ii=0;ii<256; ii++)
	//	clp[ind++]=ii;
	//ind=640;
	//for (ii=0;ii<384;ii++)
	//	clp[ind++]=255;


	//int y1=0,y2=0,u=0,v=0;
	//unsigned char *py1=0,*py2=0;
	//int i=0,j=0, c1=0, c2=0, c3=0, c4=0;
	//unsigned char *d1=0, *d2=0;

	//py1=src0;
	//py2=py1+width;
	//d1=dst_ori;
	//d2=d1+3*width;
	//for (j = 0; j < height; j += 2) { 
	//	for (i = 0; i < width; i += 2) {

	//		u = *src1++;
	//		v = *src2++;

	//		c1 = crv_tab[v];
	//		c2 = cgu_tab[u];
	//		c3 = cgv_tab[v];
	//		c4 = cbu_tab[u];

	//		//up-left
	//		y1 = tab_76309[*py1++]; 
	//		*d1++ = clp[384+((y1 + c1)>>16)];  
	//		*d1++ = clp[384+((y1 - c2 - c3)>>16)];
	//		*d1++ = clp[384+((y1 + c4)>>16)];

	//		//down-left
	//		y2 = tab_76309[*py2++];
	//		*d2++ = clp[384+((y2 + c1)>>16)];  
	//		*d2++ = clp[384+((y2 - c2 - c3)>>16)];
	//		*d2++ = clp[384+((y2 + c4)>>16)];

	//		//up-right
	//		y1 = tab_76309[*py1++];
	//		*d1++ = clp[384+((y1 + c1)>>16)];  
	//		*d1++ = clp[384+((y1 - c2 - c3)>>16)];
	//		*d1++ = clp[384+((y1 + c4)>>16)];

	//		//down-right
	//		y2 = tab_76309[*py2++];
	//		*d2++ = clp[384+((y2 + c1)>>16)];  
	//		*d2++ = clp[384+((y2 - c2 - c3)>>16)];
	//		*d2++ = clp[384+((y2 + c4)>>16)];
	//	}
	//	d1 += 3*width;
	//	d2 += 3*width;
	//	py1+=   width;
	//	py2+=   width;
	//}  
}

BOOL CDecoder::SaveToFile(const char * pFilename, unsigned char * pSurFrame, int w, int h)
{	
	unsigned char *lpbuffer;
	unsigned char *word;
	//AvPicture * pFrame = (AvPicture*)pSurFrame;
	//unsigned char * pDIBImage = pFrame->data[0];
	unsigned char * pDIBImage  = pSurFrame;
	BITMAPFILEHEADER  bf; //bmp文件头
	BITMAPINFOHEADER  bi; //bmp信息头
	bi.biSize = 40;  //位图信息头大小
	bi.biWidth = w;  //图像宽度
	bi.biHeight = h;  //图像高度
	bi.biPlanes = 1;   //位平面树=1
	bi.biBitCount = 24;  //单位像素的位数
	bi.biCompression = 0;  //图片的压缩属性，bmp不压缩，等于0
	//bi.biSizeImage = WIDTHBYTES(bi.biWidth * bi.biBitCount) * bi.biHeight;
	bi.biSizeImage = w * h * bi.biBitCount;
	//表示bmp图片数据区的大小，当上一个属性biCompression等于0时，这里的值可以省略不填

	bi.biXPelsPerMeter = 0; //水平分辨率
	bi.biYPelsPerMeter = 0; //垂直分辨率
	bi.biClrUsed = 0;   //表示使用了多少哥颜色索引表，一般biBitCount属性小于16才会用到，等于0时表示有2^biBitCount个颜色索引表
	bi.biClrImportant = 0;  //表示有多少个重要的颜色，等于0时表示所有颜色都很重要

	//Set BITMAPFILEHEADER  设置bmp图片的文件头格式
	bf.bfType = 0x4d42;  //2个字节，恒等于0x4d42，ascii字符“BM”
	bf.bfSize = 54 + bi.biSizeImage; //文件大小，以4个字节为单位
	bf.bfReserved1 = 0;  //备用
	bf.bfReserved2 = 0;  //备用
	bf.bfOffBits = 54;   //数据区在文件中的位置偏移量

	FILE *  fp =  fopen(pFilename, "wb");
	if(fp == NULL)
	{
		int err = GetLastError();
		return FALSE;
	}
	fwrite(&bf, 14, 1, fp); //向文件中写入图片文件头
	fwrite(&bi, 40, 1, fp); //向文件中写入图片信息头
	fseek(fp, 0x36, SEEK_SET);
	lpbuffer = pDIBImage+w*3*(h - 1);
	for(int i=0; i<h; i++)    //bmp file scan line is arraned by BGR|BGR|BGR|........
	{
		word = lpbuffer;
		for(int j=0; j<w; j++)
		{
			/*************add in 2011 8.2 23:04*****************/
			fputc( *(word+2), fp); // B
			fputc( *(word+1), fp); // G
			fputc( *(word+0), fp); // R			
			/***********************************************/
			/*fputc( *(word+2), fp); // B
			fputc( *(word+1), fp); // G
			fputc( *(word+0), fp); // R*/
			word+=3;
		}
		lpbuffer -= w*3; // 指针转到上一行的开始
	}
	fclose(fp);
	return TRUE;
}