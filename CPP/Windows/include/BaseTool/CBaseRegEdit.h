#pragma once
#include <windows.h>
#include "StringDef.h"
using namespace std;
class CBaseRegEdit
{
public:
	CBaseRegEdit();
	CBaseRegEdit(const BaseString& strKeyPath, const BaseString& strKeyNew);
	CBaseRegEdit(const BaseString& strKeyPath);
	~CBaseRegEdit();
	static long Query(const BaseString& strKeyPath, const BaseString& strKey, BaseString& refStrValue, HKEY rootKey = HKEY_CURRENT_USER);
	HKEY GetRootKey();
	long SetValue(const BaseString& strKey, const BaseString& strValue);
	long GetValue(const BaseString& strKey, BaseString& refStrValue);
	BaseString GetValue(const BaseString& strKey);
	long Destroy();
	long DeleteKey(const BaseString& strKey);
	BaseString GetSelfPath();
	BaseString GetOpenPath();
	bool IsOpenSuccess();
private:
	HKEY m_hParentKey;
	HKEY m_hAppRootKey;
	BaseString m_strAppRootName;
	BaseString m_strAppRootPath;
	BaseString m_strOpenPath;
	bool m_bOpenState;
};

