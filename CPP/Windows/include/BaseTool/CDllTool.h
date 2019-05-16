#pragma once
#include "StringDef.h"
#include <windows.h>
#define DLLNAME _T("AnyOneExport.dll")

class CDllTool
{
public:
	CDllTool(void);
	CDllTool(const BaseString& strDllPath,const BaseString& strFuncName);
	~CDllTool(void);
	void* GetExportFunction();
	void* GetExportFunction(const BaseString& strFuncName);
	BaseString GetError();

private:
	HINSTANCE m_hDll;

	BaseString m_strDllPath;
	BaseString m_strFuncName;

	BaseString m_strError;
};

