#pragma once
#include <tchar.h>
#include"windows.h"
#include"StringDef.h"
#include <vector>
using namespace std;
//导入ADO相关类说明,路径名可以根据自己系统安装的ADO支持文件的路径来自行设定
//#improt语句会在工程可执行程序输出目录中产生两个文件，分别为*.tlh(类型库头文件)及*.tli(类型库实现文件)
//语句no_namespace说明ADO对象不使用命名空间，rename("EOF", "EndOfFile")说明将ADO中结束标志EOF改为EndOfFile，以避免和其它库中命名相冲突
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
