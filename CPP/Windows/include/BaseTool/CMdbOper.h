#pragma once
#include <tchar.h>
#include"windows.h"
#include"StringDef.h"
#include <vector>
using namespace std;
//����ADO�����˵��,·�������Ը����Լ�ϵͳ��װ��ADO֧���ļ���·���������趨
//#improt�����ڹ��̿�ִ�г������Ŀ¼�в��������ļ����ֱ�Ϊ*.tlh(���Ϳ�ͷ�ļ�)��*.tli(���Ϳ�ʵ���ļ�)
//���no_namespace˵��ADO����ʹ�������ռ䣬rename("EOF", "EndOfFile")˵����ADO�н�����־EOF��ΪEndOfFile���Ա�������������������ͻ
#import"msado15.dll" no_namespace rename("EOF","EndOfFile")

class CMdbOper
{
public:
	CMdbOper(void);
	CMdbOper(const BaseString& strMdbPath);
	~CMdbOper(void);
	bool Query(const BaseString& strSql, vector<vector<BaseString>>& vetRes);
	bool Execute(const BaseString& strSql);
	BaseString GetError();
private:
	bool MdbInit();
private:
	BaseString m_strError;
	BaseString m_strMdbPath;
	_RecordsetPtr m_pRecordset;
	_ConnectionPtr m_pConnection;
};
