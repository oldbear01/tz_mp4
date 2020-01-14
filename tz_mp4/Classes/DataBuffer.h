// DataBuffer.h: interface for the CDataBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABUFFER_H__739488FD_3063_4869_9B2B_D0AE3530829E__INCLUDED_)
#define AFX_DATABUFFER_H__739488FD_3063_4869_9B2B_D0AE3530829E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MutexInteger.h"

namespace vfc
{
	class CDataBuffer  
	{
	private:
		char *m_pData;			//����ָ��
		int  m_nBuffLen;		//�ڴ泤��
		int  m_nDataLen;		//���ݳ���
		CVorxMutex m_mutex;		//������
		BOOL m_bAutoAdd;
		void ScanHexString(LPCTSTR sText,BYTE* pData,int* nLen);
		
	public:
		//׷������
		void PushData(void* pData,int nLen);
		//�Ƴ�����
		void RemoveData(int nLen);
		//�������
		void ClearData();
		//�����ڴ�
		void AssertBuffLen(int nLen);
		//�����ݴ�ӡ��ʮ�������ı�
		void PrintToHexString(char* sText);
		//��ʮ�������ı�ת��������
		void PushFromHexString(const char* sText);

		//ȡ������ָ��
		void* DataPtr(){return m_pData;}
		//ȡ�����ݳ���
		int DataLen(){return m_nDataLen;}
		//��������
		void Lock(){m_mutex.Lock();}
		//��������
		void Unlock(){m_mutex.Unlock();}

		//�������ֵ
		void SetAllBits(int val);
		//���ñ���ֵ,nByte��nBit��0��ʼ
		bool SetBitVal(int nByte,int nBit,int val);
		//��ȡ����ֵ,nByte��nBit��0��ʼ
		int GetBitVal(int nByte,int nBit);

		//��ѯ����
		void* SearchData(void* pData,int nLen,void* pFrom = NULL,BOOL bLock = TRUE);
		BOOL IsInData(void* p);

		//������������
		CDataBuffer(int nBuffLen = 1024,BOOL bAutoMaloc = TRUE);
		virtual ~CDataBuffer();
		
	};

	class CDataParser
	{
	private:
		char* m_pData;
		vector<int> m_aSubList;

	public:
		char* sub(int nIndex);
		int GetSubNum(){return m_aSubList.size();}
		CDataParser(LPCTSTR sData,char flag);
		~CDataParser();
	};
}

#endif // !defined(AFX_DATABUFFER_H__739488FD_3063_4869_9B2B_D0AE3530829E__INCLUDED_)
