#include "CDllTool.h"
#include "StringFormat.h"

CDllTool::CDllTool(void)
{
}

CDllTool::CDllTool(const BaseString& strDllPath,const BaseString& strFuncName)
:m_strDllPath(strDllPath),m_strFuncName(strFuncName),m_strError(_T(""))
{

}

CDllTool::~CDllTool(void)
{
	if (NULL == m_hDll)
	{
		FreeLibrary(m_hDll);
		m_hDll = NULL;
	}	
}

void* CDllTool::GetExportFunction()
{
	BaseString strDllPath_1 = m_strDllPath;
	m_hDll =LoadLibrary(strDllPath_1.c_str());
	if (NULL == m_hDll)
	{
		m_strError = _T("error: Dll Load Fail! Path: ");
		m_strError += m_strDllPath;
		return NULL;
	}

	BaseString strFuncName_1 = m_strFuncName;
	void* pFunc = (void*)GetProcAddress(m_hDll, (LPCSTR)CStringFormat::U2A(strFuncName_1).c_str());
	if (NULL == pFunc)
	{
		m_strError = _T("error: Dll Function Get Fail! Name: ");
		m_strError += m_strFuncName;
		return NULL;
	}
	return pFunc;
}

void* CDllTool::GetExportFunction(const BaseString& strFuncName)
{
	BaseString strDllPath_1 = m_strDllPath;
	if (NULL == m_hDll)
	{
		m_hDll =LoadLibrary(strDllPath_1.c_str());
	}
	if (NULL == m_hDll)
	{
		m_strError = _T("error: Dll Load Fail! Path: ");
		m_strError += m_strDllPath;
		return NULL;
	}

	BaseString strFuncName_1 = strFuncName;
	void* pFunc = (void*)GetProcAddress(m_hDll, (LPCSTR)CStringFormat::U2A(strFuncName_1).c_str());
	if (NULL == pFunc)
	{
		m_strError = _T("error: Dll Function Get Fail! Name: ");
		m_strError += m_strFuncName;
		return NULL;
	}
	return pFunc;
}

BaseString CDllTool::GetError()
{
	return m_strError;
}
