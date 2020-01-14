//////////////////////////////////////////////////////////////////////
// ServerSocket.h: interface for the CTcpServer class.
//
// ��SELECTģ��ʵ�ֵĴ��ڲ�����������
// ��    ��: Ф��ΰ
// ��    ��: 2005��6��
// ����޸�: 2009��5��4��
// ��Ȩ����: ��������ͨ�ż������޹�˾
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPORT_H__29647570_835A_493D_AC32_23AB4E18C98E__INCLUDED_)
#define AFX_COMPORT_H__29647570_835A_493D_AC32_23AB4E18C98E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MacroDefine.h"
#include "MutexInteger.h"

typedef void (*DATA_RECV)(void* pData,int nLen,void* lParam);

#ifdef WIN32
#define HCOM HANDLE
#else
#define HCOM int
#define INVALID_HANDLE_VALUE -1
#endif

namespace vfc
{
	class CComPort
	{
	private:
		HCOM   m_hCom;					//���ڶ�д���
		DATA_RECV m_fnOnDataRecv;		//�����ص�ָ��
		void* m_lParam;					//�����ص�����
		HTHREAD	m_hThread;				//�����߳̾��
		CMutexInteger m_bThreadRun;		//�����߳�״̬
		static THREAD_RETURN_TYPE read_thread(void* lParam);	//�������߳�

	public:
		void SetDataCallback(DATA_RECV fpDataRecv,void* lParam);
		BOOL Open(int nCom,int nBaudRate,int nDataBits,int nStopBits,int nParity,LPCTSTR sPrefix = NULL);
		void Close();
		BOOL SetParam(int nBaudRate,int nDataBits,int nStopBits,int nParity);
		BOOL WriteData(void* pData,int nLen);
		CComPort();
		virtual ~CComPort();
		
	};
}

#endif // !defined(AFX_COMPORT_H__29647570_835A_493D_AC32_23AB4E18C98E__INCLUDED_)
