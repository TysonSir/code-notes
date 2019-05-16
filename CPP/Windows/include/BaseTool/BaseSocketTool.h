#pragma once

//#ifndef  SOCKDLL_EXPORTS
//#define SOCKDLL _declspec(dllexport)
//#else
//#define SOCKDLL _declspec(dllimport)
//#endif

#include <string>
//�д��󣬶�������ĺ�
#define _WINSOCK_DEPRECATED_NO_WARNINGS
//����ͷ�ļ�
#include <WinSock2.h>
//������ļ�
#pragma comment(lib,"ws2_32.lib")
#include <iostream>
using namespace std;

#define LOGFILE "D:\\LF_Log\\CBaseSocketToolLog.txt"


class /*SOCKDLL*/ CBaseSocketTool
{
public:
	CBaseSocketTool(void);
	~CBaseSocketTool(void);
	//�ͻ������
	string Sendto(const string& strSendData, const string& strIP, const u_short& nPort);
	//���������
	bool Bind(const u_short& nPort);
	bool Start();
	static bool GetCloseStatus() { return m_bClose; }
	static void SetCloseStatus(bool val) { m_bClose = val; }
public:
	static bool m_haveInitWSA;
	// ������
	static DWORD ClientProc(LPARAM lparam);
	static int WriteToLog(char* str)
	{
		FILE* log;
		fopen_s(&log, LOGFILE, "a+");
		if (log == NULL)
			return -1;
		fprintf(log, "%s\n", str);
		fclose(log);
		return 0;
	}

	static int ConsoleOut(const string& str)
	{
		cout << str << endl;
		return 0;
	}
	static string m_strNewestData;
private:

	static bool m_bClose;
	bool m_isFirstSend;
	SOCKET  m_sServer;
	string  m_strIP;
	int  m_nPort;
};

