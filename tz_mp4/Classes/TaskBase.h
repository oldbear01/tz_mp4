//////////////////////////////////////////////////////////////////////
//
// TaskCenter.h: interface for the CTaskBase class.
// ���ڴ���Э�����Ƭ�ϳ�/���͵ȴ������������
// ��    ��:Ф��ΰ
// ʱ    ��:2008-3-8
// ����޸�:2008-3-8
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKCENTER_H__C3B26ACF_9AB1_4D5F_9B04_3606D992C8EF__INCLUDED_)
#define AFX_TASKCENTER_H__C3B26ACF_9AB1_4D5F_9B04_3606D992C8EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VorxProto.h"
#include "UdpSocket.h"
#include "NodeQueue.h"
#include "ProtoCollect.h"
#include "MacroDefine.h"

namespace vfc
{
class CTaskBase
{
private:
	//////////////////////////////////////////////////////////////////////////
	// test
	int m_bWriteQuery;
	int m_bWriteReturn;
	//////////////////////////////////////////////////////////////////////////
	/*�������ݽ�������*/
	CUdpSocket m_sock;
	BYTE* m_pEncryptKey;	//������Կ
	int m_nKeyLength;		//��Կ����
	static void OnUdpReceive(char* pData,int nLen,char* sIP,int nPort,LPVOID lParam);
	/*������д�������*/
	CNodeQueue<CVorxProto> m_aQueryQueue;
	CNodeQueue<CVorxProto> m_aReturnQueue;
	CVorxThread m_oTaskThread[2];

	static BOOL QueryDealThread(LPVOID lParam);
	static BOOL ReturnDealThread(LPVOID lParam);
	/*��Ӧ��Ƭ���ݴ���*/
	CColList m_aWaitList;
	CVorxMutex m_waitMutex;
	CProtoCollect* GetWaitPos(unsigned int sn);
	bool DeleteWaitItem(CProtoCollect* p);
	void ReleaseWaitList();
	/*�������ݵȴ�����*/
	CProtoList m_aSendList;
	CVorxMutex m_sendMutex;
	CVorxProto* GetSendPos(unsigned int sn);
	void ReleaseSendList();
	BOOL RemoveSendNode(CVorxProto* pSend);
	/*���̹��ߺ���*/
	void DealPacketFragment(CVorxProto* pTask);
	void DealIntegratedTask(CVorxProto* pTask);
	/*�ص�ָ�뼰����*/
	OUTPUT_LOG m_pLogCallback;
	LPVOID m_pLogParam;
protected:
	ASYN_RET m_pAsynCallback;
	LPVOID m_pAsynParam;

private:
	/*1.������ʵ�ֵĴ��麯��*/
	virtual bool OnTaskStart() = 0;
	virtual void OnTaskStop() = 0;
	virtual void OnDealReportTask(CVorxProto* pTask) = 0;
	virtual void OnDealQueryTask(CVorxProto* pTask) = 0;
	virtual void OnDealHeartReturn(CVorxProto* pTask) = 0;
	virtual void OnDealHeartQuery(CVorxProto* pTask) = 0;
protected:
	// �ṩĬ��ʵ�ֵ��麯��
	virtual void OnDealAsnyReturn(CVorxProto *pTask);

public:
	/*2.����̬�⵼���Ľӿں���*/
	bool Create(int nPort, const char *szBindIP);
	void Close();
	void SetEncrypt(void* pKey,int nKeyLen);
	void SetLogCallback(OUTPUT_LOG fun,LPVOID lParam);
	void SetAsynCallback(ASYN_RET fun,LPVOID lParam);

	/*3.���ⲿģ����õĽӿں���*/
	void OutputLog(int nCode,LPCTSTR sText);
	void AsnyNotify(CVorxProto* p);
	int  GetSocketPort();
	BOOL GetNearestLocalAddr(LPCTSTR sRemote,char* sLocal);
	BOOL SendRespondProto(CVorxProto* pSend,long nMaxBodySize = 1000);
	long SendQueryProto(CVorxProto* pSend,CVorxProto* pRet,int nTimeout);
	long SendQueryProtoEx(CVorxProto* pSend,CVorxProto* pRet,int nTimeout,long nMaxBodySize=1000);
	void RespondErrorCommand(CVorxProto* pTask,long nErrCode);
	bool AddMulticastMemberShip(LPCTSTR sMulticastIP);

	/*���캯������������*/
	CTaskBase();
	virtual ~CTaskBase();

};
}
#endif // !defined(AFX_TASKCENTER_H__C3B26ACF_9AB1_4D5F_9B04_3606D992C8EF__INCLUDED_)
