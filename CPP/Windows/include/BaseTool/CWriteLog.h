#pragma once
#include "StringDef.h"
#include <ctime>
#include <vector>
#include <map>
using namespace std;

#define  BASELOG_INFO_S(strLog)  CWriteLog::write(_T(__FILE__), __LINE__, _T(__FUNCTION__), strLog)
#define  BASELOG_INFO(strFormat, ...)   CWriteLog::OutMessage(_T(__FILE__),__LINE__, _T(__FUNCTION__), strFormat,## __VA_ARGS__)

class LogReplaceStr
{
public:
	LogReplaceStr(const string& strOld,const string& strNew):m_strOld(strOld),m_strNew(strNew){}
	string GetStrOld() const { return m_strOld; }
	void SetStrOld(string val) { m_strOld = val; }
	string GetStrNew() const { return m_strNew; }
	void SetStrNew(string val) { m_strNew = val; }
private:
	string m_strOld;
	string m_strNew;
};

class CWriteLog
{
public:
	CWriteLog();
	~CWriteLog();
	static void OutMessage(const BaseString LocateFile, const int& LocateLine, const BaseString LocateFunc, const BaseChar* pFormat, ...);
	static void write(const BaseString& strFile, const int& strLine, const BaseString& strFunc, const BaseString& strLog);
	static BaseString GetTime();
	// 把字符串的strsrc替换成strdst
	static void string_replace(std::string &strBig, const std::string &strsrc, const std::string &strdst);
private:
	static bool m_bOpenLogFilter;
	static vector<string> m_strArrLoseSrc;
	static vector<LogReplaceStr> m_strReplaceSrc;
	static std::time_t  getTimeStamp();

	static void SettingRules();
	static string LogFilterReplace(const string& strSrc);
	//过滤日志输出内容
	static string LogFilter(const string& strSrc);
};

