//////////////////////////////////////////////////////////////////////
//
// VorxProto.h: interface for the CVorxProto class.
// ���ڴ���Э�����
// ��    ��:Ф��ΰ
// ʱ    ��:2008-3-8
// ����޸�:2008-3-8
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VORXPROTO_H__08A98483_1B7C_4A1E_838E_94EE6AB987DC__INCLUDED_)
#define AFX_VORXPROTO_H__08A98483_1B7C_4A1E_838E_94EE6AB987DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _MSC_VER
#pragma warning (disable:4786)
#endif

#include <list>
using namespace std;
#include "MutexInteger.h"

namespace vfc
{
class CProtoCollect;

enum VORX_PROTO_TYPE
{
	PROTOTYPE_UNKNOWN		= 'U',	//δ֪��
	PROTOTYPE_QUERY			= 'Q',	//�����
	PROTOTYPE_RESPOND		= 'R',	//��Ӧ��
	PROTOTYPE_REPORT		= 'P',	//�ϱ���
	PROTOTYPE_CONFIRM		= 'C',	//ȷ�ϰ�
};

class CVorxProto  
{
public:
/*
	struct PACK_HEAD
	{
		WORD synch;			//ͬ���ֽ�
		BYTE version;		//Э��汾
		BYTE type;			//������
		DWORD sn;			//�����к�
		DWORD fun;			//�����ܺ�
		DWORD sub;			//�ӹ��ܺ�
		DWORD datalen;		//�������ܳ�
		DWORD retcode;		//������
		WORD total;			//���ķ�Ƭ����
		WORD index;			//���ķ�Ƭ���,��0��ʼ
		BYTE patch[3];		//��λ�ֽ�,ʹ�ṹ������Ӧ4�ֽڶ��뷽ʽ
		BYTE checksum;		//���У���
	} m_head;
*/
	struct PACK_HEAD // �½ṹ�������ͳ����޹�
	{
		ULONG synch   :16;		//ͬ���ֽ�
		ULONG version : 8;		//Э��汾
		ULONG type    : 8;		//������
		ULONG sn      :32;		//�����к�
		ULONG fun     :32;		//�����ܺ�
		ULONG sub     :32;		//�ӹ��ܺ�
		ULONG datalen :32;		//�������ܳ�
		ULONG retcode :32;		//������
		ULONG total   :16;		//���ķ�Ƭ����
		ULONG index   :16;		//���ķ�Ƭ���,��0��ʼ
		ULONG patch   :24;		//��λ�ֽ�,ʹ�ṹ������Ӧ4�ֽڶ��뷽ʽ
		ULONG checksum: 8;		//���У���
	} m_head;

	struct PACK_BODY
	{
		BYTE* data;
		unsigned len;
	} m_body;

	char m_sRemoteIP[50];	//Զ��IP��ַ(��Դ��Ŀ��)
	int  m_nRemotePort;		//Զ�̶˿�  (��Դ��Ŀ��)

	DWORD m_time;			//���ڼ�ⷢ�Ͱ���ʱ
	CVorxEvent m_event;		//����ʱ���ڵȴ���Ӧ��
	CVorxProto* m_pReturn;	//����ʱ���ڽ��ջ�Ӧ��
public:
	//����Э������
	BOOL ParseData(BYTE* pData,int nLen);
	void CloneProto(CVorxProto* p);
	//����Э���
	void BuildRespondHead(CVorxProto* pQuery,int nRetCode = 0);
	void BuildQueryHead(DWORD fun,DWORD sub);
	void BuildReportHead(DWORD fun,DWORD sub);
	void SetBodyData(BYTE* pData,int nLen);
	void SyncHeadField();
	long GetPackLength();
	void GetPackData(BYTE* pData,BYTE* pKey,int nKeyLen);
	//���ߺ���
	void SetRemoteParam(LPCTSTR sIP,int nPort);
	void ReleaseBody();
	inline BYTE CheckSum();
	inline BOOL IsDataValid();
	BOOL IsNotSplitted();
	BOOL IsTimeOut(DWORD curTime,int nLimite);
	int SplitToPackets(CProtoCollect& lst,int nSize);

	static void AdjustByteOrder(char* p,int nLen);
	static void SwapFormat(PACK_HEAD* p);

public:
	//������������
	CVorxProto();
	virtual ~CVorxProto();

};

typedef vector<CVorxProto*> CProtoList;
typedef CProtoList::iterator CProtoPos;

typedef CVorxProto::PACK_HEAD CPackHead;
typedef CVorxProto::PACK_BODY CPackBody;
}
#endif // !defined(AFX_VORXPROTO_H__08A98483_1B7C_4A1E_838E_94EE6AB987DC__INCLUDED_)
