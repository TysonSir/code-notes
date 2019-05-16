#include "CWriteLog.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include <atltime.h>
#include "StringFormat.h"

bool CWriteLog::m_bOpenLogFilter = true;//trueʱ������־��Ϣ
vector<string> CWriteLog::m_strArrLoseSrc = vector<string>();
vector<LogReplaceStr> CWriteLog::m_strReplaceSrc = vector<LogReplaceStr>();

CWriteLog::CWriteLog()
{
}


CWriteLog::~CWriteLog()
{
}

void CWriteLog::OutMessage(const BaseString LocateFile, const int& LocateLine, const BaseString LocateFunc, const BaseChar* pFormat, ...)
{
	if (!PathFileExists(_T("D:\\LF_Log\\")))
	{
		return;
	}
	//BaseChar buf[10240] = {0};
	//BaseChar* pBuf = buf;
	//va_list args;
	//va_start(args, pFormat);
	//_vstprintf_s(pBuf, MAX_PATH, pFormat, args);
	//va_end(args);
	//write(LocateFile, LocateLine,LocateFunc, buf);// ͨ����ָ��������Ա����

	CString strTemp = _T("");
	va_list paramList;
	va_start(paramList, pFormat);
	strTemp.FormatV(pFormat, paramList);
	va_end(paramList);
	if (strTemp.IsEmpty())
	{
		strTemp = _T("��־��������");
	}
	write(LocateFile, LocateLine, LocateFunc, strTemp.GetBuffer(0));// ͨ����ָ��������Ա����

}

void CWriteLog::write(const BaseString& strFile, const int& strLine, const BaseString& strFunc,const BaseString& strLog)
{
	if (m_bOpenLogFilter)
	{
		SettingRules();
	}

#if UNICODE
	wofstream fout;
#else
	ofstream fout;
#endif
	fout.open(_T("D:\\LF_Log\\LF_Log_DLL.txt"), ios::app);
	//std::locale("chs");
	fout.imbue(std::locale("chs"));
	//fout.imbue(locale(locale(), _T(""), LC_CTYPE));
	if (!fout)
	{
		//MessageBox(NULL, _T("��־�ļ���ʧ��"), _T("��־����"), NULL);
		return;
	}
	fout << GetTime() <<_T(" ");
	fout << strFile << _T("(") << strLine << _T("): ");
	if (!m_bOpenLogFilter)
	{
		fout << strFunc << endl;
	}

	if (m_bOpenLogFilter)
	{	
#if UNICODE
	fout << CStringFormat::A2U(LogFilter(CStringFormat::U2A(strLog))) << endl << endl;
#else
	fout << LogFilter(strLog) << endl << endl;
#endif
	}
	else
	{
		fout << strLog << endl << endl;
	}
	fout.close();
}

BaseString CWriteLog::GetTime()
{
	CTime t = CTime::GetCurrentTime();
	int d = t.GetDay(); //��ü���
	int y = t.GetYear(); //��ȡ���
	int m = t.GetMonth(); //��ȡ��ǰ�·�
	int h = t.GetHour(); //��ȡ��ǰΪ��ʱ 
	int mm = t.GetMinute(); //��ȡ����
	int s = t.GetSecond(); //��ȡ��
	int w = t.GetDayOfWeek(); //��ȡ���ڼ���ע��1Ϊ�����죬7Ϊ������</span>
	unsigned long long ms = getTimeStamp() % 1000;

#ifdef UNICODE
	std::wostringstream ss;
#else
	std::ostringstream ss;
#endif
	ss << setw(4) << setfill(_T('0')) << y << _T("-")
		<< setw(2) << setfill(_T('0')) << m << _T("-")
		<< setw(2) << setfill(_T('0')) << d << _T(" ")
		<< setw(2) << setfill(_T('0')) << h << _T(":")
		<< setw(2) << setfill(_T('0')) << mm << _T(":")
		<< setw(2) << setfill(_T('0')) << s << _T(" ")
		<< setw(3) << setfill(_T('0')) << ms;
	return ss.str();
}

std::time_t CWriteLog::getTimeStamp()
{
	struct timeval tv;
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;

	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tv.tv_sec = clock;
	tv.tv_usec = wtm.wMilliseconds * 1000;
	return ((unsigned long long)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000);
}

void CWriteLog::SettingRules()
{
	m_strArrLoseSrc.push_back("C:\\");
	m_strArrLoseSrc.push_back("c:\\");
	m_strArrLoseSrc.push_back("�ļ�");
	m_strArrLoseSrc.push_back("·��");

	m_strReplaceSrc.push_back(LogReplaceStr("����", "��"));
	m_strReplaceSrc.push_back(LogReplaceStr("�ϴ�", "����"));
}

void CWriteLog::string_replace(std::string &strBig, const std::string &strsrc, const std::string &strdst)
{
	std::string::size_type pos = 0;
	std::string::size_type srclen = strsrc.size();
	std::string::size_type dstlen = strdst.size();

	while ((pos = strBig.find(strsrc, pos)) != std::string::npos)
	{
		strBig.replace(pos, srclen, strdst);
		pos += dstlen;
	}
}

std::string CWriteLog::LogFilterReplace(const string& strSrc)
{
	string strSrc_1 = strSrc;
	for (auto it = m_strReplaceSrc.begin();it != m_strReplaceSrc.end();it++)
	{
		if (-1 != strSrc_1.find(it->GetStrOld()))
		{
			string_replace(strSrc_1, it->GetStrOld(), it->GetStrNew());//��first�滻��second
		}
	}
	return strSrc_1;
}

std::string CWriteLog::LogFilter(const string& strSrc)
{
	for (auto it = m_strArrLoseSrc.begin();it != m_strArrLoseSrc.end();it++)
	{
		if (-1 != strSrc.find(*it))
		{
			return string("");
		}
	}
	return LogFilterReplace(strSrc);
}

