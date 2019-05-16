#include "BaseSocketTool.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#define SOCKDLL_EXPORTS
using namespace std;

bool CBaseSocketTool::m_haveInitWSA = false;
string CBaseSocketTool::m_strNewestData = "";

bool CBaseSocketTool::m_bClose = false;

CBaseSocketTool::CBaseSocketTool(void)
	:m_isFirstSend(true), m_strIP("0.0.0.0"), m_nPort(65535)
{
	if (false == m_haveInitWSA)
	{
		//使用winsock之前，必须进行如下初始化
		//每个进程初始化一次——建议在main函数中写
		WSADATA wsa;
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		{
			printf("WSAStartup failed\n");
			exit(-1);
		}
		m_haveInitWSA = true;
	}
	ConsoleOut("WSAStartup OK");
	// 1.建立一个socket接口 SOCKET HANDLE... 实际上是一个整数
	// 内核里面一个接口的标识
	m_sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sServer == INVALID_SOCKET)
	{
		printf("socket create failed\n");
		exit(-1);
	}
	ConsoleOut("socket create OK");
}


CBaseSocketTool::~CBaseSocketTool(void)
{
	// 收尾
	closesocket(m_sServer);
	WSACleanup();
}




std::string CBaseSocketTool::Sendto(const string& strSendData, const string& strIP, const u_short& nPort)
{
	//IP地址和端口与原来有所不同时，需要重新进行连接
	if (strIP != m_strIP || nPort != m_nPort)
	{
		m_strIP = strIP;
		m_nPort = nPort;
		m_isFirstSend = true;
	}

	if (m_isFirstSend)
	{
		// 2.指定一个网络地址，指明服务所处的IP及端口	
		SOCKADDR_IN addrServ;//sockaddr 和 SOCKADDR_IN内存地址一样，可转换
		addrServ.sin_family = AF_INET;//网络协议族
		addrServ.sin_port = htons(m_nPort);// 服务器端口
		addrServ.sin_addr.S_un.S_addr = inet_addr(m_strIP.c_str());//服务器地址

																   //连接socket到服务端上
		int ret = connect(m_sServer, (sockaddr *)&addrServ, sizeof(sockaddr));//开始连接
		if (SOCKET_ERROR == ret)
		{
			int nError = WSAGetLastError();//获取错误信息
			printf("socket connect failed\n");
			WSACleanup();//反初始化
			closesocket(m_sServer);//关闭socket
			return "";
		}
		m_isFirstSend = false;
	}

	//Sleep(1000);
	// 如果连接成功，就可以直接通信——双方通信
	// 3.发送数据
	/************************************************************************/
	/*  发送的数据内容  */
	//string strTmp = MakeSendString(strSendData);
	char* sendMsg = new char[strSendData.length() + 1];
	strcpy_s(sendMsg, strSendData.length() + 1, strSendData.c_str());
	/************************************************************************/
	int ret = send(m_sServer, sendMsg, strlen(sendMsg), 0);//发送数据
	if (SOCKET_ERROR == ret)
	{
		printf("socket send failed\n");
		return "";
	}

	// 4.接收数据
	char buf[1024];
	memset(buf, 0, 1024);
	ret = recv(m_sServer, buf, sizeof(buf), 0);
	if (SOCKET_ERROR == ret)
	{
		printf("socket recv failed\n");
		closesocket(m_sServer);//关闭socket
		return "";
	}
	/************************************************************************/
	/* 使用接收的数据*/
	//printf("client recv buf: %s \n",buf);
	string strRecv(buf);
	//DisposeReceiveString(strRecv);
	return strRecv;
	/************************************************************************/

}


bool CBaseSocketTool::Bind(const u_short& nPort)
{
	m_strIP = "0.0.0.0";
	m_nPort = nPort;

	// 2.绑定网络地址	
	SOCKADDR_IN addrServ;//sockaddr 和 SOCKADDR_IN内存地址一样，可转换
	addrServ.sin_family = AF_INET;//网络协议族
	addrServ.sin_port = htons(m_nPort);// htons = host to network style——本机字节序转成网络字节序
	addrServ.sin_addr.S_un.S_addr = INADDR_ANY;//inet_addr("14.215.177.38")可绑定任何IP地址("0")
											   //把socket绑定到一个指定的网络地址上
	int ret = bind(m_sServer, (sockaddr *)&addrServ, sizeof(sockaddr));
	if (SOCKET_ERROR == ret)
	{
		WriteToLog("socket bind failed");
		printf("socket bind failed\n");
		WSACleanup();//反初始化
		closesocket(m_sServer);//关闭socket
		return false;
	}
	ConsoleOut("socket bind OK");

	// 3.监听,监听是否有连接过来
	ret = listen(m_sServer, SOMAXCONN);//SOMAXCONN为最大连接数，默认为5
	if (SOCKET_ERROR == ret)
	{
		WriteToLog("socket listen failed\n");
		printf("socket listen failed\n");
		WSACleanup();//反初始化
		closesocket(m_sServer);//关闭socket
		return false;
	}
	ConsoleOut("socket listen OK");
	return true;
}

//bool CBaseSocketTool::Start()
//{
//	// 4.接受连接
//	SOCKADDR_IN addrClient;//保存客户端的连接信息
//	int addrClientLen = sizeof(SOCKADDR_IN);
//	while (true)
//	{
//		SOCKET* sClient = new SOCKET;//客户端socket
//		//接受连接accept: 1.指定socket, 2.接了谁进来 
//		*sClient = accept(m_sServer,(sockaddr*)&addrClient,&addrClientLen);
//		if (INVALID_SOCKET == *sClient)//接受的socket无效
//		{
//			printf("socket accept failed\n");
//			WSACleanup();//反初始化
//			closesocket(m_sServer);//关闭socket
//			return false;
//		}
//
//		// 5.处理用户连接——创建线程
//		CreateThread(0,0,(LPTHREAD_START_ROUTINE)ClientProc/*线程函数*/,(LPVOID)sClient/*线程函数参数*/,0,0);
//		Sleep(10);
//		//delete sClient;
//	}
//}

bool CBaseSocketTool::Start()
{
	// 4.接受连接
	SOCKADDR_IN addrClient;//保存客户端的连接信息
	int addrClientLen = sizeof(SOCKADDR_IN);
	while (true)
	{
		SOCKET* sClient = new SOCKET;//客户端socket,此处必须使用指针，否则多个客户端连接出问题
		//接受连接accept: 1.指定socket, 2.接了谁进来 
		*sClient = accept(m_sServer, (sockaddr*)&addrClient, &addrClientLen);
		if (INVALID_SOCKET == *sClient)//接受的socket无效
		{
			WriteToLog("socket accept failed\n");
			printf("socket accept failed\n");
			WSACleanup();//反初始化
			closesocket(m_sServer);//关闭socket
			return false;
		}
		ConsoleOut("socket accept OK");
		// 5.处理用户连接——创建线程
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ClientProc/*线程函数*/, (LPVOID)sClient/*线程函数参数*/, 0, 0);
		Sleep(10);
		//delete sClient;//此处不能delete，否则连接会出问题
	}
}

// 服务处理
DWORD CBaseSocketTool::ClientProc(LPARAM lparam)
{
	//服务端有n+1个socket，n个客户端+1个服务器监听socket
	SOCKET* sockClient = (SOCKET*)lparam;
	char buf[1024];
	while (true)
	{
		if (GetCloseStatus())
		{
			closesocket(*sockClient);
			return -1;
		}
		memset(buf, 0, sizeof(buf));
		// recv 进行接收数据
		int ret = recv(*sockClient, buf, sizeof(buf), 0);//0代表同步IO，返回真实接收数据长度
		if (SOCKET_ERROR == ret)//连接出错
		{
			WriteToLog("socket recv failed");
			printf("socket recv failed\n");
			closesocket(*sockClient);
			return -1;
		}
		if (0 == ret)//接收长度为0，连接关闭
		{
			WriteToLog("client close connection");
			printf("client close connection\n");
			closesocket(*sockClient);
			return -1;
		}
		/************************************************************************/
		/* 使用接收到的数据                                                                     */
		printf("recv msg: %s \n", buf);
		/************************************************************************/

		/************************************************************************/
		/* 发送返回数据的内容*/
		char sendMsg[1024] = { 0 };
		strcpy_s(sendMsg, 1024, buf);
		/************************************************************************/
		/* 发送数据 1.发送目标socket 2.发送起始地址 3.发送长度*/
		ret = send(*sockClient, buf, strlen(buf), 0);//
		if (SOCKET_ERROR == ret)
		{
			WriteToLog("socket send failed");
			printf("socket send failed\n");
			return -1;
		}

	}
	closesocket(*sockClient);
	return 0;
}