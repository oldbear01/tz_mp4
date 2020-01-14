//////////////////////////////////////////////////////////////////////
//
// VorxThread.h: interface for the CVorxThread class.
// ����:�߳�����ֹͣ������,�ɿ�Windows/Linux˫ƽ̨
// ˵��:�߳�������,�����Ե�ѭ������ָ���Ĺ��ܺ���
// ����:Ф��ΰ
// ����:2007��9��10��
// �޸�:2007��9��10��
// ��Ȩ:��������ͨ�ż����������ι�˾
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VORXTHREAD_H__4CD68B43_1A04_42E5_8EA0_978D749196E5__INCLUDED_)
#define AFX_VORXTHREAD_H__4CD68B43_1A04_42E5_8EA0_978D749196E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MacroDefine.h"
#include "MutexInteger.h"

#ifdef WIN32
#include <windows.h>
#include <process.h>

#define THREAD_RETURN void
#define THREAD_VALUE
#define pthread_t HANDLE
#else
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/times.h>

#define THREAD_RETURN void*
#define THREAD_VALUE 0

#endif

namespace vfc
{
	//////////////////////////////////////////////////////////////
	typedef int (*LPFUN_THREAD)(LPVOID lParam);
	// ����˵�� : �߳���������ѭ��ִ�еĻص�������ʽ����
	// �� �� ֵ : 0:���� 1:������ -1:�˳��߳�
	typedef void (*LPTHREAD_EXIT)(LPVOID lParam);
	// ����˵�� : �߳��˳�ʱִ�еĻص�����
	//////////////////////////////////////////////////////////////
	
	class CVorxThread
	{
	private:
		void*	m_lParam;		//�ⲿ������̲߳���
		LPFUN_THREAD m_fun;		//�ⲿ����ĺ���ָ��
		LPTHREAD_EXIT m_exit;	//�߳��˳�ָ��
		
		pthread_t m_hThread;	//�߳̿��ƾ��
		BOOL      m_bThread;	//�����߳�������ֹͣ
		BOOL      m_bSuspend;	//�����߳���ͣ
		int		  m_nCycle;		//����ִ������(ms)
		unsigned int m_nStackSize; // �߳�ջ��С
		CVorxEvent m_oEvent;	//�̵߳ȴ��¼�
		static THREAD_RETURN thread_func(void* lParam);
		
	public:
		//���ò���
		BOOL SetParam(LPFUN_THREAD fpFunc,LPVOID lParam,int msCycle,LPTHREAD_EXIT fpExit = NULL);
		//�����߳�
		BOOL StartThread();
		BOOL Start(){return StartThread();}
		//ֹͣ�߳�
		void StopThread();
		void Stop(){StopThread();}
		//��ͣ
		void Suspend();
		// �ָ�
		void Resume();
		//�������ȼ�,ֵ��Χ -3 ~ 3
		BOOL SetPriority(int val);
		//����ջ��С,�ֽ���,�߳�����ǰ������Ч
		void SetStackSize(unsigned int nSize);
		//��ȡ����״̬
		BOOL IsRuning(){return m_bThread;}
		//��������״̬
		void Waken(){m_oEvent.Signal();}
		//�ȴ�ʱ��
		BOOL WaitTime(DWORD dwTime);
		
		CVorxThread();
		virtual ~CVorxThread();
		
	};
}
#endif // !defined(AFX_VORXTHREAD_H__4CD68B43_1A04_42E5_8EA0_978D749196E5__INCLUDED_)
