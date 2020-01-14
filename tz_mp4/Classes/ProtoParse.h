//////////////////////////////////////////////////////////////////////
//
// ProtoParse.h: interface for the CProtoParse class.
// ˵��:VORX XMLЭ�������
// ����:Ф��ΰ
// ��Ȩ:��������ͨ�ż����������ι�˾
// ����:2007-9-5
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROTOPARSE_H__C2F9607E_CA16_4449_8F57_9B341D57042C__INCLUDED_)
#define AFX_PROTOPARSE_H__C2F9607E_CA16_4449_8F57_9B341D57042C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./TinyXml/tinyxml.h"
#include "UdpSocket.h"


enum PROTO_TYPE
{
	PROTOTYPE_UNKNOWN	= 'U',
	PROTOTYPE_QUERY		= 'Q',
	PROTOTYPE_RESPOND	= 'R',
	PROTOTYPE_REPORT	= 'P',
};

class CProtoParam
{
private:
	TiXmlDocument m_doc;
	TiXmlElement* m_pItem;

public:
	//����ת��,�Ƿ���Ч
	operator bool(){return (m_pItem != NULL);}

	//ȡֵ���Ӳ���
	CProtoParam GetFirstChildParam(LPCTSTR sName);
	CProtoParam GetNextSiblingParam(LPCTSTR sName);
	LPCTSTR GetValue(LPCTSTR sName);
	BOOL GetValue(char* sRet,LPCTSTR sName);
	int GetValueInt(LPCTSTR sName);
	void SetValue(LPCTSTR sName,LPCTSTR sVal);
	void SetValue(LPCTSTR sName,int nVal);
	void AddChildParam(CProtoParam child);

	//��������
	CProtoParam GetClone();
	TiXmlElement GetXmlElement(){return *m_pItem;}

public:
	//������������
	CProtoParam(const CProtoParam& ct){m_pItem = ct.m_pItem;}	//�������캯��
	CProtoParam(LPCTSTR sName = NULL);							//�����ƹ���һ������
	CProtoParam(TiXmlElement* p){m_pItem = p;}					//����ڵ㹹�����
	~CProtoParam();

};

class CProtoParse 
{
public:
	TiXmlDocument m_doc;
	TiXmlElement* m_pRoot;

public:
	//����ת��,�Ƿ���Ч
	operator bool(){return (m_pRoot != NULL);}
	CProtoParse& operator =(const CProtoParse& other);

	BOOL ParseString(LPCTSTR sText);
	CProtoParam GetFirstParam(LPCTSTR sName);
	void AddParam(CProtoParam pm);
	void ClearParam();

	//����ֵ
	void SetMainFun(DWORD fun);
	void SetSubFun(DWORD sub);
	void SetSerialNumber(int sn = 0);
	void SetType(PROTO_TYPE type);
	void SetVersion(LPCTSTR sVer);
	void SetRetCode(int nRetCode);

	//ȡֵ
	DWORD GetMainFun();
	DWORD GetSubFun();
	int GetSerialNumber();
	PROTO_TYPE GetType();
	LPCTSTR GetVersion();
	int GetRetCode();

	//����Э���ַ���
	BOOL Send(CUdpSocket* pSock,sockaddr_in addr);
	BOOL Send(CUdpSocket* pSock,LPCTSTR sIP,int nPort);
	BOOL Send(SOCKET s);

	//������������
	CProtoParse(DWORD fun=0,DWORD sub=0,PROTO_TYPE type=PROTOTYPE_QUERY);
	virtual ~CProtoParse();

public:
	//���ߺ���
	static DWORD str2dw(LPCTSTR str);
	static char* dw2str(DWORD dw);
	static char* pt2str(PROTO_TYPE val);
	static PROTO_TYPE str2pt(LPCTSTR str);
	
private:
	char m_sTemp[5];	//����ת��ʱ��ʱ����

};

#endif // !defined(AFX_PROTOPARSE_H__C2F9607E_CA16_4449_8F57_9B341D57042C__INCLUDED_)
