// VorxThread.cpp: implementation of the CVorxThread class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "VorxThread.h"
#include "GlobalFunction.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace vfc
{
CVorxThread::CVorxThread()
{
	//�߳̿��Ʋ���
	m_hThread = 0;
	m_bThread = FALSE;
	m_bSuspend = FALSE;
	//�̶߳������
	m_lParam = 0;
	m_fun = 0;
	m_nCycle = 0;
	m_exit = 0;
	//
	m_nStackSize = 0;
}

CVorxThread::~CVorxThread()
{
	StopThread();
}

BOOL CVorxThread::SetParam(LPFUN_THREAD fun,LPVOID lParam,int nCycle,LPTHREAD_EXIT fpExit)
{
	if(m_bThread) return FALSE;
	m_fun = fun;
	m_exit = fpExit;
	m_lParam = lParam;
	m_nCycle = nCycle;
	return TRUE;
}

BOOL CVorxThread::StartThread()
{
	if(m_bThread || !m_fun) return FALSE;
	m_bThread = TRUE;
#ifdef WIN32
	m_hThread = (HANDLE)_beginthread(thread_func,m_nStackSize,this);
#else
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, m_nStackSize);
	pthread_create(&m_hThread,&attr,thread_func,this);
	pthread_attr_destroy(&attr);
#endif
	return (m_hThread != 0);
}

void CVorxThread::StopThread()
{
	if(m_bThread)
	{
		m_bThread = FALSE;
		//�����¼�,֪ͨ�߳̽���
		m_oEvent.Signal();
		Sleep(80);
		//�ȴ��̷߳���
		if(m_hThread)
		{
#ifdef WIN32
			if(WaitForSingleObject(m_hThread,1000) == WAIT_TIMEOUT)
			{
				DWORD dwExitCode;
				GetExitCodeThread(m_hThread,&dwExitCode);
				TerminateThread(m_hThread,dwExitCode);
			}
#else
			pthread_join(m_hThread,NULL);
#endif
		}
	}
}

void CVorxThread::Suspend()
{
	m_bSuspend = TRUE;
}

void CVorxThread::Resume()
{
	m_bSuspend = FALSE;
}

BOOL CVorxThread::SetPriority(int val)
{
	if(val < -3 || val > 3) return FALSE;
#ifdef WIN32
	int nVal = 0;
	switch(val)
	{
	case -3:
		nVal = THREAD_PRIORITY_IDLE;break;
	case -2:
		nVal = THREAD_PRIORITY_LOWEST;break;
	case -1:
		nVal = THREAD_PRIORITY_BELOW_NORMAL;break;
	case 0:
		nVal = THREAD_PRIORITY_NORMAL;break;
	case 1:
		nVal = THREAD_PRIORITY_ABOVE_NORMAL;break;
	case 2:
		nVal = THREAD_PRIORITY_HIGHEST;break;
	case 3:
		nVal = THREAD_PRIORITY_TIME_CRITICAL;break;
	}
	return SetThreadPriority(m_hThread,nVal);
#else
	struct sched_param  hThreadPrior;
	int policy;
	pthread_getschedparam(m_hThread, &policy, &hThreadPrior);
	policy = SCHED_RR;
	hThreadPrior.sched_priority = val;
	return (pthread_setschedparam(m_hThread,policy,&hThreadPrior) == 0);
#endif
}

void CVorxThread::SetStackSize(unsigned int nSize)
{
	m_nStackSize = nSize;
}

THREAD_RETURN CVorxThread::thread_func(void* lParam)
{
	CVorxThread* pThis = (CVorxThread*)lParam;

// 	UINT64 tTime;			// ����Խ��
// 	int nSleepTime;			//����Ҫ���ߵĺ�����
// 	int nAmendment = 0;		//�����ϴβ���������
	int nExecRes = 0;
	while(pThis->m_bThread)
	{
		if (pThis->m_bSuspend) // ��ͣ
		{
			if (50 > pThis->m_nCycle)
			{
				Sleep(pThis->m_nCycle);
			}
			else
			{
				int i, nCount = pThis->m_nCycle/50; // ??
				for (i = 0; i < nCount; ++i)
				{
					if (!pThis->m_bThread) break;
					Sleep(50);
				}
			}
			continue;
		}

		//ִ�к���
// 		tTime = VGAPI_GetMillisecond();
		if(pThis->m_fun)
		{
			nExecRes = pThis->m_fun(pThis->m_lParam);
		}
		if(!pThis->m_bThread)break;

		switch(nExecRes)
		{
		case 1://��һѭ��
			break;

		case 0://ʵ������,����Уʱ���ܻ��Ʒ�����
			if (50 > pThis->m_nCycle)
			{
				Sleep(pThis->m_nCycle);
			}
			else
			{
				int i, nCount = pThis->m_nCycle/50; // ??
				for (i = 0; i < nCount; ++i)
				{
					if (!pThis->m_bThread) break;
					Sleep(50);
				}
			}
/*
			if (3600000 >= VGAPI_GetMillisecond()-tTime) // һСʱ���ڵ�ֵ��Ч
			{
				nSleepTime = pThis->m_nCycle - (int)(VGAPI_GetMillisecond()-tTime) + nAmendment;
				if(nSleepTime > 0)
				{
					pThis->m_oEvent.WaitForSignal(nSleepTime);
				}
				nAmendment = pThis->m_nCycle - (int)(VGAPI_GetMillisecond()-tTime);
				if (-3600000 >= nAmendment) // ������ʱ��һСʱ������Ч
				{
					nAmendment = 0;
				}
			}
			else
			{
				nAmendment = 0;
			}
*/
			break;

		case -1: //�˳��߳�
			pThis->m_bThread = false;
			pThis->m_hThread = 0;
		}
	}
	if(pThis->m_exit)
	{
		pThis->m_exit(pThis->m_lParam);
	}
	return THREAD_VALUE;
}

BOOL CVorxThread::WaitTime(DWORD dwTime)
{
	m_oEvent.Unsignal();
	if(m_oEvent.WaitForSignal(dwTime))
	{
		return FALSE; // ���յ��˳��¼�
	}
	return TRUE; // �ȴ���dwtimeʱ��
}
}

