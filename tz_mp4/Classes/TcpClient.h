//////////////////////////////////////////////////////////////////////
// ServerSocket.h: interface for the CTcpServer class.
//
// ��SELECTģ��ʵ�ֵ�TCP SOCKET�ͻ�����
// ֧��TCP SOCKET������
// ��    ��: Ф��ΰ
// ��    ��: 2005��6��
// ����޸�: 2009��5��4��
// ��Ȩ����: ��������ͨ�ż������޹�˾
// 
// �����ʼ��
// WSADATA wsd;
// WSAStartup(MAKEWORD(2,2),&wsd);
//
// �ͷ�������Դ
// WSACleanup();
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCPCLIENT_H__66703156_62AA_49B7_9A51_C660704E8B07__INCLUDED_)
#define AFX_TCPCLIENT_H__66703156_62AA_49B7_9A51_C660704E8B07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib ")	
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
#include "CyclePipe.h"
#include "../rtpdef.h"
#include "Packetbuf.h"

#define SOCKET_REC_BUF	1024*1024
class CPaketbuf;
namespace vfc
{
	typedef void (*TCPCLIENT_RECVE)(void* pData,int nLen,LPVOID lParam);
	typedef void (*TCPCLIENT_CLOSE)(LPVOID lParam);
	
	class CTcpClient  
	{
	private:
		HTHREAD m_hThread;
		BOOL m_bThreadRuning;
		static THREAD_RETURN_TYPE tcp_recv_thread(void* lParam);
		HTHREAD m_hDealRecvBufThread;
		BOOL m_bDealRecvBufThreadRuning;
		static THREAD_RETURN_TYPE tcp_DealRecvBuf_thread(void* lParam);
		
		SOCKET sock_fd;
		sockaddr_in m_raddr;
		TCPCLIENT_RECVE m_pOnReceive;
		TCPCLIENT_CLOSE m_pOnClose;
		LPVOID m_lFuncParam;
		int		m_nLocalPort;

	public:
		BOOL Create(int nLocalPort,LPCTSTR sRemoteIP,int nRemotePort,BOOL bRecv);
		BOOL ConnectTcpServer(const char* sSerIp,int nPort);
		BOOL IsConnected();
		void Close(BOOL bWaitForThread = TRUE);
		BOOL Send(void* pData,int nLen);
		BOOL IsCreated(){return sock_fd != INVALID_SOCKET;}
		void GetServerInfo(char *sIP,int* nPort);
		BOOL SetRecBuffer(int nSize);//���ý��ջ���
		BOOL SetRecvThreadPriority(int nPriority= 2);//�����߳����ȼ�

		void SetCallback(TCPCLIENT_RECVE pOnReceive,TCPCLIENT_CLOSE pOnClose,LPVOID lParam);
		int GetTcpPort(){return m_nLocalPort;};
		CTcpClient();
		virtual ~CTcpClient();
	public:
		BOOL m_bIsTcpSocket;			//�Ƿ�TCP����
		BOOL m_bIsConnected;			//�Ƿ��Ѿ����ӳɹ�
		CPaketbuf m_recvTcpDataPipe;   //���ݽ��ն���
		
	};
}
#endif // !defined(AFX_TCPCLIENT_H__66703156_62AA_49B7_9A51_C660704E8B07__INCLUDED_)
