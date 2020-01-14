

#if !defined(AFX_MUTEXOBJECT_H__7CC50D8D_A571_414F_AC1A_A82D574A4489__INCLUDED_)
#define AFX_MUTEXOBJECT_H__7CC50D8D_A571_414F_AC1A_A82D574A4489__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef WIN32
#include <pthread.h>
#define INFINITE	0xFFFFFFFF
#endif
#include "MacroDefine.h"


namespace vfc
{
	/////////////////////////////////////////////////////////////////////
	//���������
	
	class CTzMutex
	{

	private:
		HANDLE m_hObject;
	public:
		void Lock(){WaitForSingleObject(m_hObject,INFINITE);}
		void Unlock(){ReleaseMutex(m_hObject);}
		bool TryLock(){return WAIT_OBJECT_0 ==WaitForSingleObject(m_hObject,0);}

		CTzMutex(){m_hObject = CreateMutex(NULL,FALSE,NULL);}
		virtual ~CTzMutex(){CloseHandle(m_hObject);}
		CTzMutex(const CTzMutex &ref){m_hObject = CreateMutex(NULL,FALSE,NULL);}

	};
	
	/////////////////////////////////////////////////////////////////////
	//�Զ�������
	class CAutoMutex
	{
	private:
		CTzMutex* m_pMutex;
		
	public:
		CAutoMutex(CTzMutex* p){m_pMutex=p;m_pMutex->Lock();}
		virtual ~CAutoMutex(){m_pMutex->Unlock();}
	};
	
	/////////////////////////////////////////////////////////////////////
	//����������
	class CMutexInteger
	{
	private:
		int m_nValue;
		CTzMutex m_mutex;
		
	public:
		void operator&=(const int nParam);
		int  operator&(const int nParam);
		void operator|=(const int nParam);
		int  operator|(const int nParam);
		const CMutexInteger& operator=(const int nParam);
		const CMutexInteger& operator=(const CMutexInteger& nParam);
		void operator+=(const int nParam);
		void operator++();
		void operator--();
		int  operator+(const int nParam);
		void operator-=(const int nParam);
		int  operator-(const int nParam);
		bool operator==(const int nParam);
		bool operator!();
		bool operator>(const int nParam);
		bool operator>=(const int nParam);
		bool operator<(const int nParam);
		bool operator<=(const int nParam);
		bool operator!=(const int nParam);
		operator int();
		int GetAndSetValue(const int nVal);
		CMutexInteger();
		CMutexInteger(const CMutexInteger &ref);
		CMutexInteger(const int nVal);
		virtual ~CMutexInteger();
	};

	/////////////////////////////////////////////////////////////////////
	//�¼�������
	class CTzEvent
	{
	private:
#ifndef USE_CHECK_EVENT
		HANDLE m_hEvent;
#else
		BOOL m_bSignal;
		CTzMutex m_mutex;
#endif

	public:
		CTzEvent(const CTzEvent &ref);
		BOOL WaitForSignal(int nTimeOut);	//��λ:ms,���غ��Զ���Ϊ���ź�
		void Signal();						//����Ϊ���ź�
		void Unsignal();					//�����ź�
		CTzEvent();						//��ʼ״̬Ϊ���ź�״̬
		virtual ~CTzEvent();
	};
	
}
#endif // !defined(AFX_MUTEXOBJECT_H__7CC50D8D_A571_414F_AC1A_A82D574A4489__INCLUDED_)
