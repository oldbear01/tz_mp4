//////////////////////////////////////////////////////////////////////
//
// �ļ� : SharedMemory.h: interface for the CSharedMemory class.
// ���� : ����֮�乲���ڴ漰��ͬ��������
// ���� : Ф��ΰ
// ���� : 2009����9��18��
// ��Ȩ : ��������ͨ�ż����������ι�˾
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAREDMEMORY_H__31E8C1DC_BC12_4936_8012_9CDF704C4AF4__INCLUDED_)
#define AFX_SHAREDMEMORY_H__31E8C1DC_BC12_4936_8012_9CDF704C4AF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MacroDefine.h"

namespace vfc
{
#ifndef WIN32
	union semun 
	{ 
		int val; 
		struct semid_ds *buf; 
		unsigned short int *array; 
		struct seminfo *__buf; 
	}; 
#endif

	class CSharedMemory  
	{
	private:
		void *m_pMemoryAddr;	//Shared Memory Address
#ifdef WIN32
		HANDLE m_hHandle;
		HANDLE m_hSemaphore;
#else
		int m_nMemoryID;
		int m_nSemID;
#endif
		
	public:
		BOOL Create(int nKey,int nLen);
		BOOL Release();
		void* GetPoint(){return m_pMemoryAddr;}
		void Lock();
		void Unlock();
		CSharedMemory();
		virtual ~CSharedMemory();
		
	};
}

#endif // !defined(AFX_SHAREDMEMORY_H__31E8C1DC_BC12_4936_8012_9CDF704C4AF4__INCLUDED_)
