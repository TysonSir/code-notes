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
		//ʹ��winsock֮ǰ������������³�ʼ��
		//ÿ�����̳�ʼ��һ�Ρ���������main������д
		WSADATA wsa;
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		{
			printf("WSAStartup failed\n");
			exit(-1);
		}
		m_haveInitWSA = true;
	}
	ConsoleOut("WSAStartup OK");
	// 1.����һ��socket�ӿ� SOCKET HANDLE... ʵ������һ������
	// �ں�����һ���ӿڵı�ʶ
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
	// ��β
	closesocket(m_sServer);
	WSACleanup();
}




std::string CBaseSocketTool::Sendto(const string& strSendData, const string& strIP, const u_short& nPort)
{
	//IP��ַ�Ͷ˿���ԭ��������ͬʱ����Ҫ���½�������
	if (strIP != m_strIP || nPort != m_nPort)
	{
		m_strIP = strIP;
		m_nPort = nPort;
		m_isFirstSend = true;
	}

	if (m_isFirstSend)
	{
		// 2.ָ��һ�������ַ��ָ������������IP���˿�	
		SOCKADDR_IN addrServ;//sockaddr �� SOCKADDR_IN�ڴ��ַһ������ת��
		addrServ.sin_family = AF_INET;//����Э����
		addrServ.sin_port = htons(m_nPort);// �������˿�
		addrServ.sin_addr.S_un.S_addr = inet_addr(m_strIP.c_str());//��������ַ

																   //����socket���������
		int ret = connect(m_sServer, (sockaddr *)&addrServ, sizeof(sockaddr));//��ʼ����
		if (SOCKET_ERROR == ret)
		{
			int nError = WSAGetLastError();//��ȡ������Ϣ
			printf("socket connect failed\n");
			WSACleanup();//����ʼ��
			closesocket(m_sServer);//�ر�socket
			return "";
		}
		m_isFirstSend = false;
	}

	//Sleep(1000);
	// ������ӳɹ����Ϳ���ֱ��ͨ�š���˫��ͨ��
	// 3.��������
	/************************************************************************/
	/*  ���͵���������  */
	//string strTmp = MakeSendString(strSendData);
	char* sendMsg = new char[strSendData.length() + 1];
	strcpy_s(sendMsg, strSendData.length() + 1, strSendData.c_str());
	/************************************************************************/
	int ret = send(m_sServer, sendMsg, strlen(sendMsg), 0);//��������
	if (SOCKET_ERROR == ret)
	{
		printf("socket send failed\n");
		return "";
	}

	// 4.��������
	char buf[1024];
	memset(buf, 0, 1024);
	ret = recv(m_sServer, buf, sizeof(buf), 0);
	if (SOCKET_ERROR == ret)
	{
		printf("socket recv failed\n");
		closesocket(m_sServer);//�ر�socket
		return "";
	}
	/************************************************************************/
	/* ʹ�ý��յ�����*/
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

	// 2.�������ַ	
	SOCKADDR_IN addrServ;//sockaddr �� SOCKADDR_IN�ڴ��ַһ������ת��
	addrServ.sin_family = AF_INET;//����Э����
	addrServ.sin_port = htons(m_nPort);// htons = host to network style���������ֽ���ת�������ֽ���
	addrServ.sin_addr.S_un.S_addr = INADDR_ANY;//inet_addr("14.215.177.38")�ɰ��κ�IP��ַ("0")
											   //��socket�󶨵�һ��ָ���������ַ��
	int ret = bind(m_sServer, (sockaddr *)&addrServ, sizeof(sockaddr));
	if (SOCKET_ERROR == ret)
	{
		WriteToLog("socket bind failed");
		printf("socket bind failed\n");
		WSACleanup();//����ʼ��
		closesocket(m_sServer);//�ر�socket
		return false;
	}
	ConsoleOut("socket bind OK");

	// 3.����,�����Ƿ������ӹ���
	ret = listen(m_sServer, SOMAXCONN);//SOMAXCONNΪ�����������Ĭ��Ϊ5
	if (SOCKET_ERROR == ret)
	{
		WriteToLog("socket listen failed\n");
		printf("socket listen failed\n");
		WSACleanup();//����ʼ��
		closesocket(m_sServer);//�ر�socket
		return false;
	}
	ConsoleOut("socket listen OK");
	return true;
}

//bool CBaseSocketTool::Start()
//{
//	// 4.��������
//	SOCKADDR_IN addrClient;//����ͻ��˵�������Ϣ
//	int addrClientLen = sizeof(SOCKADDR_IN);
//	while (true)
//	{
//		SOCKET* sClient = new SOCKET;//�ͻ���socket
//		//��������accept: 1.ָ��socket, 2.����˭���� 
//		*sClient = accept(m_sServer,(sockaddr*)&addrClient,&addrClientLen);
//		if (INVALID_SOCKET == *sClient)//���ܵ�socket��Ч
//		{
//			printf("socket accept failed\n");
//			WSACleanup();//����ʼ��
//			closesocket(m_sServer);//�ر�socket
//			return false;
//		}
//
//		// 5.�����û����ӡ��������߳�
//		CreateThread(0,0,(LPTHREAD_START_ROUTINE)ClientProc/*�̺߳���*/,(LPVOID)sClient/*�̺߳�������*/,0,0);
//		Sleep(10);
//		//delete sClient;
//	}
//}

bool CBaseSocketTool::Start()
{
	// 4.��������
	SOCKADDR_IN addrClient;//����ͻ��˵�������Ϣ
	int addrClientLen = sizeof(SOCKADDR_IN);
	while (true)
	{
		SOCKET* sClient = new SOCKET;//�ͻ���socket,�˴�����ʹ��ָ�룬�������ͻ������ӳ�����
		//��������accept: 1.ָ��socket, 2.����˭���� 
		*sClient = accept(m_sServer, (sockaddr*)&addrClient, &addrClientLen);
		if (INVALID_SOCKET == *sClient)//���ܵ�socket��Ч
		{
			WriteToLog("socket accept failed\n");
			printf("socket accept failed\n");
			WSACleanup();//����ʼ��
			closesocket(m_sServer);//�ر�socket
			return false;
		}
		ConsoleOut("socket accept OK");
		// 5.�����û����ӡ��������߳�
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ClientProc/*�̺߳���*/, (LPVOID)sClient/*�̺߳�������*/, 0, 0);
		Sleep(10);
		//delete sClient;//�˴�����delete���������ӻ������
	}
}

// ������
DWORD CBaseSocketTool::ClientProc(LPARAM lparam)
{
	//�������n+1��socket��n���ͻ���+1������������socket
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
		// recv ���н�������
		int ret = recv(*sockClient, buf, sizeof(buf), 0);//0����ͬ��IO��������ʵ�������ݳ���
		if (SOCKET_ERROR == ret)//���ӳ���
		{
			WriteToLog("socket recv failed");
			printf("socket recv failed\n");
			closesocket(*sockClient);
			return -1;
		}
		if (0 == ret)//���ճ���Ϊ0�����ӹر�
		{
			WriteToLog("client close connection");
			printf("client close connection\n");
			closesocket(*sockClient);
			return -1;
		}
		/************************************************************************/
		/* ʹ�ý��յ�������                                                                     */
		printf("recv msg: %s \n", buf);
		/************************************************************************/

		/************************************************************************/
		/* ���ͷ������ݵ�����*/
		char sendMsg[1024] = { 0 };
		strcpy_s(sendMsg, 1024, buf);
		/************************************************************************/
		/* �������� 1.����Ŀ��socket 2.������ʼ��ַ 3.���ͳ���*/
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