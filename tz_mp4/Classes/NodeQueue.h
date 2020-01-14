//////////////////////////////////////////////////////////////////////
//
// BufferQueue.h: interface for the CNodeQueue class.
// ѭ��������CNodeQueueͷ�ļ�,ʹ��ǰ����Intialize()������ʼ��
// ʹ��:GetBuffer() -> Enqueue(),Dequeue() -> Recycle()
// ע��:Enqueue()��Recycle()��������ΪGetBuffer()��Dequeue()����
// ����:Ф��ΰ
// ����:2006��4��11��(2007��8��15���޸�)
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUFFERQUEUE_H__6BC6E26E_AE9C_4F50_98F7_2DB189057F33__INCLUDED_)
#define AFX_BUFFERQUEUE_H__6BC6E26E_AE9C_4F50_98F7_2DB189057F33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MacroDefine.h"
#include "MutexInteger.h"

#include <queue>
using namespace std;

namespace vfc
{
template <typename T>
class CNodeQueue
{
public:
	//��ʼ������
	BOOL Initialize(int nQueueSize,BOOL bOverWrite);
	//���ٺ���
	void Destroy();
	//���ݽڵ����к���
	void Enqueue(T* pBuffer);
	//���ݽڵ���к���
	T* Dequeue();
	//�����ڴ�ڵ㺯��
	T* GetBuffer(BOOL* bOverWrited = NULL);
	//�����ڴ�ڵ㺯��
	void Recycle(T* pBuffer);
	//�������нڵ�
	void ResetQueue();
	// ���нڵ����
	int FreeSize();
	// ʹ�ý�����
	int DataSize();

public:
	//������������
	CNodeQueue()
	{
		m_bOverWrite = FALSE;
	}
	virtual ~CNodeQueue()
	{
		Destroy();
	}

private:
	CMutexInteger m_bOverWrite;		//�Ƿ񸲸�
	CVorxMutex m_mutex;

	//����
	queue<T*> m_aFreeArray;//���ж���
	queue<T*> m_aDataArray;//���ݶ���

};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//nQueueSize �����нڵ����
//bOverWrite �Ƿ񸲸�,�������д���ʱ,�Ƿ񸲸�ԭ������
template <typename T>
BOOL CNodeQueue<T>::Initialize(int nQueueSize,BOOL bOverWrite)
{
	m_bOverWrite = bOverWrite;

	Destroy();
	{
		CAutoMutex am(&m_mutex);
		for(int i=0;i<nQueueSize;i++)
		{
			m_aFreeArray.push(new T);
		}
	}
	return TRUE;
}

template <typename T>
void CNodeQueue<T>::ResetQueue()
{
	T* p = NULL;
	while((p = Dequeue()))
	{
		Recycle(p);
	}
}

template <typename T>
void CNodeQueue<T>::Destroy()
{
	CAutoMutex am(&m_mutex);
	while(!m_aDataArray.empty())
	{
		T* p = m_aDataArray.front();
		delete p;
		m_aDataArray.pop();
	}

	while(!m_aFreeArray.empty())
	{
		T* p = m_aFreeArray.front();
		delete p;
		m_aFreeArray.pop();
	}
}

template <typename T>
void CNodeQueue<T>::Enqueue(T* pBuffer)
{
	CAutoMutex am(&m_mutex);
	if(pBuffer)m_aDataArray.push(pBuffer);
}

template <typename T>
T* CNodeQueue<T>::Dequeue()
{
	CAutoMutex am(&m_mutex);
	T* pRet = NULL;
	if(!m_aDataArray.empty())
	{
		pRet = m_aDataArray.front();
		m_aDataArray.pop();
	}
	return pRet;
}

template <typename T>
T* CNodeQueue<T>::GetBuffer(BOOL* bOverWrited)
{
	CAutoMutex am(&m_mutex);
	T* pRet = NULL;
	if(!m_aFreeArray.empty())
	{
		if(bOverWrited)*bOverWrited = FALSE;
		pRet = m_aFreeArray.front();
		m_aFreeArray.pop();
	}
	else if(m_bOverWrite && !m_aDataArray.empty())
	{
		if(bOverWrited) *bOverWrited = TRUE;
		pRet = m_aDataArray.front();
		m_aDataArray.pop();
	}
	return pRet;
}

template <typename T>
void CNodeQueue<T>::Recycle(T* pBuffer)
{
	CAutoMutex am(&m_mutex);
	if(pBuffer)m_aFreeArray.push(pBuffer);
}

template <typename T>
int CNodeQueue<T>::FreeSize()
{
	CAutoMutex am(&m_mutex);
	return m_aFreeArray.size();
}

template <typename T>
int CNodeQueue<T>::DataSize()
{
	CAutoMutex am(&m_mutex);
	return m_aDataArray.size();
}

}
#endif // !defined(AFX_BUFFERQUEUE_H__6BC6E26E_AE9C_4F50_98F7_2DB189057F33__INCLUDED_)
