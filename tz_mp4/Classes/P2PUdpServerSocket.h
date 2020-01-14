//////////////////////////////////////////////////////////////////////
//
// UDP SOCKET��װ��
// ͷ �� ��:P2PUdpServerSocket.h
// ʵ���ļ�:P2PUdpServerSocket.cpp
// ��    ��:Ф��ΰ
// ��    ��:2004��8��18��
// ������:2007��8��23��
// Windows��ʹ��ǰ���ȳ�ʼ������,��������:
//		WSADATA wsd;
//		WSAStartup(MAKEWORD(2,2),&wsd);
// Windows���ͷ�������Դ,��������:
//		WSACleanup();
//
//////////////////////////////////////////////////////////////////////
#ifndef _P2PUDPSERVERSOCKET_H_
#define _P2PUDPSERVERSOCKET_H_

#ifdef WIN32
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")	
#else
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

#include "MacroDefine.h"
#include "MutexInteger.h"
#include "VorxThread.h"
#include <list>
using namespace std;
namespace vfc
{
	// CKK ADD Begin for UDP NAT ��͸	 
	#define MSG_CONNECT         1 // P2P�ͻ�����������
	#define MSG_CONNECTACK      2 // P2P�����Ӧ
	#define MSG_RING            3 // P2P����
	#define MSG_OK              4 // P2P������ͨ
	#define MSG_ACTIVEQUERY     5 // P2P�����ѯ
	#define MSG_ACTIVEACK       6 // P2P�����ѯ��Ӧ
	struct Server_Addr_Info
	{
		char  m_ID[64];         // �ͻ���Ψһ��ʶ��WIN32�²���GUID
		char  m_sIP[50];        // �ͻ���ʵ��IP��ַ
		int   m_iPort;          // �ͻ���ʵ�ʶ˿�
		char  m_sP2PIP[50];     // �ͻ���P2P��ַ
		int   m_iP2PPort;       // �ͻ���P2P�˿�
		long  m_lActiveTime;    // �ͻ��˻�Ծʱ��
		BOOL  m_blOnline;       // �ͻ�������
		Server_Addr_Info()
		{
			memset(m_ID,0,64);
			memset(m_sIP,0,50);
			memset(m_sP2PIP,0,50);
			m_iPort = 0;
			m_iP2PPort = 0;
			m_lActiveTime = 0;
			m_blOnline = FALSE;
		}
		Server_Addr_Info operator = (const Server_Addr_Info& rAddrInfo)
		{
			strcpy(m_ID,rAddrInfo.m_ID);
			strcpy(m_sIP,rAddrInfo.m_sIP);
			strcpy(m_sP2PIP,rAddrInfo.m_sP2PIP);
			m_iPort = rAddrInfo.m_iPort;
			m_iP2PPort = rAddrInfo.m_iP2PPort;
			m_lActiveTime = rAddrInfo.m_lActiveTime;
			m_blOnline = rAddrInfo.m_blOnline;
			return *this;
		}
		bool operator == (const Server_Addr_Info& rAddrInfo) 
		{
			if((0 == strcmp(m_sIP,rAddrInfo.m_sIP)) && (m_iPort == rAddrInfo.m_iPort))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	};
	
	typedef struct
	{
		int       m_iMsgFlag;
		Server_Addr_Info m_addrInfo;
		
	}SERVER_MESSAGE,*PSERVER_MESSAGE;
	
	typedef void (*P2PClient_ACCEPT)(Server_Addr_Info * _pAddInfo,LPVOID _lpParam);
	// CKK ADD end
	
	typedef void (*RECV_CALLBACK)(char*,int,char*,int,LPVOID);
	
	
	class CP2PUdpServerSocket
	{
	public:
		//�����ر�
		BOOL IsCreated(){return (m_nLocalPort > 0);}
		BOOL Create(int nPort,BOOL bRecv,int nBuffSize,const char*szBindIP);//nPort-����˿� bRecv-�Ƿ�������� nBuffSize-���ջ����С szBindIP�󶨵�IP��ַ
		BOOL Close();
		BOOL SetRecvThreadPriority(int nPriority= 2);//�����߳����ȼ�

		//���뼰�˳��鲥��
		BOOL AddMembership(LPCTSTR sip);
		BOOL DropMembership(LPCTSTR sip);
		//�����С��TTL��������
		BOOL SetRecvBuffer(int nSize);
		BOOL SetSendBuffer(int nSize);
		BOOL SetMulticastTTL(int nTTL);
		//�������ݻص�����
		void SetCallBack(RECV_CALLBACK p,LPVOID pParam);
		//�����緢��UDP����
		int  SendTo(LPCTSTR p,int nLen,LPCTSTR sip,int port);
		int	 SendTo(LPCTSTR p,int nLen,sockaddr_in addr);
		//ȡ�ñ�SOCKET���󶨵Ķ˿�
		int GetBindedPort();
		const char * GetBindedIP();
		//���ý���RTPУ��,���ΪRTP��,���Զ�ȥ��RTPͷ
		void SetRTPCheck(BOOL bCheck){m_bRTPCheck = bCheck;}
		//ͳ�Ʋ�������
		int GetMaxRecvSize(){return m_nMaxRecvSize;}
		int GetMaxSendSize(){return m_nMaxSendSize;}
		
	private:
		BOOL			m_bRTPCheck;
		int				m_nRecvBufSize;
		char*			m_pRecvBuff;
		CMutexInteger	m_nMaxRecvSize;
		CMutexInteger	m_nMaxSendSize;
		static THREAD_RETURN_TYPE udp_recv_thread(void* lParam);
		
	private:
		SOCKET	sock_fd;
		int		m_nLocalPort;
		BOOL	m_bThreadRuning;
		HTHREAD	m_hThread;			//�����߳̾��
		//�ص�ָ�뼰����
		RECV_CALLBACK pOnReceive;	//�����������ݻص�����
		LPVOID m_pCallBackParam;	//���ջص������ĸ�������
	// CKK ADD for UDP NAT ��͸	
	public:
		void SetP2PClientAcceptCallBack(P2PClient_ACCEPT _pFunc,LPVOID _lpParam);
		void UpdateClientInfo(Server_Addr_Info _addrInfo);
		void GetClientAddrInfo(Server_Addr_Info & _addrInfo);
		BOOL TestP2PClientOnline(const char * _sClientIp,int _iClientPort,int _iTimeOut = 1000);
	private:
		list<Server_Addr_Info>    m_P2PClientList;      // �ͻ�����Ϣ�б�
		CVorxMutex         m_P2PClientListMutex; 
		LPVOID      m_lpParam;
		char        m_sLocalIP[50];

	// CKK ADD end
	public:
		//��������
		CP2PUdpServerSocket(int nBuffSize = 1024 * 100);
		virtual ~CP2PUdpServerSocket();
		
	};
}
#endif
