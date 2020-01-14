//////////////////////////////////////////////////////////////////////
//
// UDP SOCKET封装类
// 头 文 件:P2PUdpServerSocket.h
// 实现文件:P2PUdpServerSocket.cpp
// 作    者:肖可伟
// 日    期:2004年8月18日
// 最后更新:2007年8月23日
// Windows下使用前请先初始化网络,代码如下:
//		WSADATA wsd;
//		WSAStartup(MAKEWORD(2,2),&wsd);
// Windows下释放网络资源,代码如下:
//		WSACleanup();
//
//////////////////////////////////////////////////////////////////////
#ifndef _P2PUDPCLIENTSOCKET_H_
#define _P2PUDPCLIENTSOCKET_H_

#include "MacroDefine.h"
#include "MutexInteger.h"
#include "VorxThread.h"

//#include "StdAfx.h"
namespace vfc
{
	// CKK ADD Begin for UDP NAT 穿透	 
	#define MSG_CONNECT         1 // P2P客户端请求连接
	#define MSG_CONNECTACK      2 // P2P请求回应
	#define MSG_RING            3 // P2P呼叫
	#define MSG_OK              4 // P2P测试联通
	#define MSG_ACTIVEQUERY     5 // P2P保活查询
	#define MSG_ACTIVEACK       6 // P2P保活查询回应
	struct Addr_Info
	{
		char  m_ID[64];         // 客户端唯一标识，WIN32下采用GUID
		char  m_sIP[50];        // 客户端实际IP地址
		int   m_iPort;          // 客户端实际端口
		char  m_sP2PIP[50];     // 客户端P2P地址
		int   m_iP2PPort;       // 客户端P2P端口
		long  m_lActiveTime;    // 客户端活跃时间
		BOOL  m_blOnline;       // 客户端在线
		Addr_Info()
		{
			memset(m_ID,0,64);
			memset(m_sIP,0,50);
			memset(m_sP2PIP,0,50);
			m_iPort = 0;
			m_iP2PPort = 0;
			m_lActiveTime = 0;
			m_blOnline = FALSE;
		}
		Addr_Info operator = (const Addr_Info& rAddrInfo)
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
		bool operator == (const Addr_Info& rAddrInfo) 
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
		Addr_Info m_addrInfo;
		
	}MESSAGE,*PMESSAGE;
	
	// CKK ADD end
	typedef void (*RECV_CALLBACK)(char*,int,char*,int,LPVOID);
	
	class CP2PUdpClientSocket
	{
	public:
		//创建关闭
		BOOL IsCreated(){return (m_nLocalPort > 0);}
		BOOL Create(int nPort,BOOL bRecv,int nBuffSize,const char*szBindIP);//nPort-网络端口 bRecv-是否接收数据 nBuffSize-接收缓冲大小 szBindIP绑定的IP地址
		BOOL Close();
		BOOL SetRecvThreadPriority(int nPriority= 2);//设置线程优先级

		//加入及退出组播组
		BOOL AddMembership(LPCTSTR sip);
		BOOL DropMembership(LPCTSTR sip);
		//缓冲大小及TTL参数设置
		BOOL SetRecvBuffer(int nSize);
		BOOL SetSendBuffer(int nSize);
		BOOL SetMulticastTTL(int nTTL);
		//接收数据回调设置
		void SetCallBack(RECV_CALLBACK p,LPVOID pParam);
		//向网络发送UDP数据
		int  SendTo(LPCTSTR p,int nLen,LPCTSTR sip,int port);
		int	 SendTo(LPCTSTR p,int nLen,sockaddr_in addr);
		//取得本SOCKET所绑定的端口
		int GetBindedPort();
		const char * GetBindedIP();
		//设置接收RTP校验,如果为RTP包,则自动去掉RTP头
		void SetRTPCheck(BOOL bCheck){m_bRTPCheck = bCheck;}
		//统计参数函数
		int GetMaxRecvSize(){return m_nMaxRecvSize;}
		int GetMaxSendSize(){return m_nMaxSendSize;}
		
	private:
		MMRESULT		timer_id;//定时器id
		BOOL			m_bRTPCheck;
		int				m_nRecvBufSize;
		char*			m_pRecvBuff;
		CMutexInteger	m_nMaxRecvSize;
		CMutexInteger	m_nMaxSendSize;
		static THREAD_RETURN_TYPE udp_recv_thread(void* lParam);
		static THREAD_RETURN_TYPE HeartSend(void* lParam);
		static void WINAPI onTimeFunc(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
	private:
		SOCKET	sock_fd;
		int		m_nLocalPort;
		BOOL	m_bThreadRuning;
		HTHREAD	m_hThread;			//接收线程句柄
		HTHREAD m_hHeartThread;		//心跳线程
		char	m_strSvrIP[32];		//服务器端发送流的socket绑定ip
		int		m_nSvrPort;			//服务器端发送流的socket绑定端口
		//回调指针及参数
		RECV_CALLBACK pOnReceive;	//接收网络数据回调函数
		LPVOID m_pCallBackParam;	//接收回调函数的附带参数
	// CKK ADD for UDP NAT 穿透	
	public:
		BOOL ConnectP2PServer(const char * _sRemoteIp,int _iRemotePort,int _iTimeOut = 1000);
		char m_sLocalIP[50];
	private:
		bool m_blConnected;
		
	// CKK ADD end
	public:
		//构造析构
		CP2PUdpClientSocket(int nBuffSize = 1024 * 100);
		virtual ~CP2PUdpClientSocket();
		
	};
}
#endif
