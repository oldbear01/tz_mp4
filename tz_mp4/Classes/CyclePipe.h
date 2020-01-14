//////////////////////////////////////////////////////////////////////
//
// CycleBuffer.h: interface for the CCycleBuffer class.
// ѭ���ܵ�������,�����ڴ�������/����Ƶ�ȶ�ý�����ݴ���
// ����:Ф��ΰ
// ����:2007��3��
// �޸�:2007��9��
// ��Ȩ:��������ͨ�ż����������ι�˾
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CYCLEBUFFER_H__527CF46D_4518_4BC3_B169_C7F9B7AE0330__INCLUDED_)
#define AFX_CYCLEBUFFER_H__527CF46D_4518_4BC3_B169_C7F9B7AE0330__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MacroDefine.h"
#include "MutexInteger.h"
class CCyclePipe  
{
private:
	BYTE*	m_pBuffer;
	int		m_nSize;
	BOOL	m_bOverWrite;
	BYTE*	m_pHead;
	BYTE*	m_pTail;

public:
	//��ʼ��
	void  Initialize(int nSize,BOOL bOverWrite);
	//��������
	int   PushPipe(BYTE* pData,int nDataLen);
	//ȡ������
	int   PopPipe(BYTE* pRet,int nDataLen);	
public:
	//����Ч�����ݿ�ʼ��������
	BYTE* SeekData(BYTE* pSeek,int nLen);
	//������...֮ǰ������
	int ChuckData(BYTE * pData);
	//��ȡ��ǰ��Ч�����ݣ������ı�ָ��λ��
	int GetPipeData(BYTE* pRet,int nDataLen);
	//������е�����
	void ResetPipeData();
	int   GetPayloadSize();	
	int   GetFreeSize();
private:
	//��������
	BYTE* SeekData(BYTE* pBegin,BYTE* pSeek,int nLen);

	//��������
	int   GetBuffSize(){return m_nSize;};
	int   GetDataSize(BYTE* pStart,BYTE* pEnd);	
	BYTE* GetHeadPoint(){return m_pHead;}
	BYTE* GetNextPoint(BYTE* p,int n = 1);
	BYTE* GetPrevPoint(BYTE* p,int n = 1);
	BOOL  IsInDataArea(BYTE* p);
	BOOL  IsInFreeArea(BYTE* p);
public:
	CCyclePipe(int nSize = 0,BOOL bOverWrite = TRUE);
	virtual ~CCyclePipe();
	void TraceDataSize();

private:
	vfc::CVorxMutex m_Mutex;
	time_t m_dwLastCntTime;
};

#endif // !defined(AFX_CYCLEBUFFER_H__527CF46D_4518_4BC3_B169_C7F9B7AE0330__INCLUDED_)
