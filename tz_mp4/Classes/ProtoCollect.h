//////////////////////////////////////////////////////////////////////
//
// ProtoCollect.h: interface for the CProtoCollect class.
// ר�����ڴ�����Э���Ƭ�㼯���ϳɵ���
// ��    ��:Ф��ΰ
// ʱ    ��:2008-3-8
// ����޸�:2008-3-8
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROTOCOLLECT_H__2379CD39_0DF4_41B1_B1C1_EF946D720DD1__INCLUDED_)
#define AFX_PROTOCOLLECT_H__2379CD39_0DF4_41B1_B1C1_EF946D720DD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _MSC_VER
#pragma warning (disable:4786)
#endif

#include <map>
using namespace std;

#include "VorxProto.h"

namespace vfc
{
class CTaskBase;
class CProtoCollect  
{
public:
	map<WORD,CVorxProto*> m_aFragments;			//Э���Ƭ
	CVorxMutex m_mutexFragments;				//��Ƭ������
	CPackHead m_head;							//��ͷ��Ϣ
	DWORD m_time;								//���ڳ�ʱ���

public:
	//���⹦�ܺ���
	void AddFragment(CVorxProto* p,BOOL bAddClone);
	BOOL CombineFragments(CVorxProto& pack);
	BOOL IsTimeout(DWORD curTime,unsigned int nLimite);
	//�ڲ����ߺ���
	BOOL HaveAllFrags();						//���ڽ���->�ϰ�
	inline BOOL IsNeddedPacket(CVorxProto* p);	//���ڽ���->�ϰ�
	BOOL SendAllFragments(CTaskBase* pTask);	//���ڷְ�->����
	int SendAllFragmentsAndWaitRet(CTaskBase* pTask,CVorxProto* pRet,int nTimeout);	//���ڷְ�->����

public:
	//������������
	CProtoCollect(CPackHead* pHead);
	virtual ~CProtoCollect();

};
typedef vector<CProtoCollect*> CColList;
typedef CColList::iterator CColPos;
}
#endif // !defined(AFX_PROTOCOLLECT_H__2379CD39_0DF4_41B1_B1C1_EF946D720DD1__INCLUDED_)
