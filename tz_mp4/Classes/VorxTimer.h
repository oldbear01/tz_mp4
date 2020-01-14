// VorxTimer.h: interface for the CVorxTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VORXTIMER_H__F919A1C6_8F65_4BCE_8B14_30EF0B93491E__INCLUDED_)
#define AFX_VORXTIMER_H__F919A1C6_8F65_4BCE_8B14_30EF0B93491E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef WIN32
#include <Mmsystem.h>
#pragma comment(lib,"Winmm.lib") 
#else
#include <signal.h>
#include <time.h>
#endif
#include "MacroDefine.h"

//////////////////////////////////////////////////////////////
typedef int (*LFTIMER_PROC)(LPVOID lParam);
// ����˵�� : �߳���������ѭ��ִ�еĻص�������ʽ����
// �� �� ֵ : 0:���� 1:������ -1:�˳��߳�
// ע������ : �ص��������Ͻ�����UI����
typedef void (*LFTIMER_EXIT)(LPVOID lParam);
// ����˵�� : �߳��˳�ʱִ�еĻص�����
// ע������ : �ص��������Ͻ�����UI����
//////////////////////////////////////////////////////////////

namespace vfc
{
	class CVorxTimer  
	{
	private:
		LFTIMER_PROC m_fpProc;
		LFTIMER_EXIT m_fpExit;
		void* m_lParam;
		long m_msCycle;

	public:
#ifdef WIN32
		UINT m_hTimer;
		static void CALLBACK TimerProc(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
#else
		timer_t m_hTimer;
		static void TimerProc(sigval_t v);
#endif
		
	public:
		//���ò���
		void SetParam(LFTIMER_PROC fpFunc,LPVOID lParam,int msCycle,LFTIMER_EXIT fpExit = NULL);
		//������ʱ��
		BOOL StartTimer();
		BOOL Start(){return StartTimer();}
		//ֹͣ��ʱ��
		void StopTimer();
		void Stop(){StopTimer();}
		//�Ƿ�����
		BOOL IsRuning(){return m_hTimer != NULL;}
		//������������
		CVorxTimer();
		virtual ~CVorxTimer();
		
	};
}
#endif // !defined(AFX_VORXTIMER_H__F919A1C6_8F65_4BCE_8B14_30EF0B93491E__INCLUDED_)
