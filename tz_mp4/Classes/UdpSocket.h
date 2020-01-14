//////////////////////////////////////////////////////////////////////
//
// UDP SOCKET��װ��
// ͷ �� ��:UdpSocket.h
// ʵ���ļ�:UdpSocket.cpp
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

#ifndef _UDPSOCKET_H_
#define _UDPSOCKET_H_

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

namespace vfc
{
	typedef void (*RECV_CALLBACK)(char*,int,char*,int,LPVOID);
	
	class CUdpSocket
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
		int  SendTo(const unsigned char * p, const int nLen, const char * sip, const int port);
		int	 SendTo(const unsigned char * p, const int nLen, const sockaddr_in &addr);
		//ȡ�ñ�SOCKET���󶨵Ķ˿�
		int GetBindedPort();
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
		
	public:
		//��������
		CUdpSocket(int nBuffSize = 1024 * 100);
		virtual ~CUdpSocket();
		
	};
}
#endif
