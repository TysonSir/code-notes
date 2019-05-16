#include "CBaseRegEdit.h"
#include "StringFormat.h"
#include "CWriteLog.h"


CBaseRegEdit::CBaseRegEdit()
{
}


CBaseRegEdit::CBaseRegEdit(const BaseString& strKeyPath, const BaseString& strKeyNew)
	:m_strAppRootPath(strKeyPath),m_strAppRootName(strKeyNew)
{
	//定义有关的hKEY,在查询结束时要关闭
	
	//BaseString m_name = "China";
	//LPBYTE m_name_Set = (LPBYTE)(LPCSTR)(m_name.c_str());//定义x轴名称
	//DWORD length = m_name.length() + 1;//定义数据长度

	//打开与路径data_Set相关的hKEY
//#ifdef UNICODE
//	wBaseString wstrKeyPath = CBaseStringFormat::A2U(strKeyPath);
//	wBaseString wstrKeyNew = CBaseStringFormat::A2U(strKeyNew);
//	LPCTSTR data_Set = wstrKeyPath.c_str();
//	LPCTSTR data_New = wstrKeyNew.c_str();
//#else
	LPCTSTR data_Set = strKeyPath.c_str();
	LPCTSTR data_New = strKeyNew.c_str();
//#endif
	if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_CURRENT_USER, data_Set, 0, KEY_SET_VALUE, &m_hParentKey))
	{
		BASELOG_INFO(_T("注册表打开成功：%s"), strKeyPath.c_str());
		m_bOpenState = true;
		// 使用hKey来操作data_Set这个KEY里面的值。
		if (ERROR_SUCCESS == ::RegCreateKey(m_hParentKey, data_New, &m_hAppRootKey))
		{
			BASELOG_INFO(_T("注册表项创建成功：HKEY_CURRENT_USER\\%s\\%s"), strKeyPath.c_str(),strKeyNew.c_str());
		}
		else
		{
			BASELOG_INFO(_T("注册表项创建失败：HKEY_CURRENT_USER\\%s\\%s"), strKeyPath.c_str(), strKeyNew.c_str());
		}
	}
	else
	{
		BASELOG_INFO(_T("注册表打开失败：%s"), strKeyPath.c_str());
		m_bOpenState = false;
	}

	
}

CBaseRegEdit::CBaseRegEdit(const BaseString& strKeyPath)
	:m_strOpenPath(strKeyPath)
{
//#ifdef UNICODE
//	wBaseString wstrKeyPath = CBaseStringFormat::A2U(strKeyPath);
//	LPCTSTR data_Set = wstrKeyPath.c_str();
//#else
	LPCTSTR data_Set = strKeyPath.c_str();
//#endif
	if (ERROR_SUCCESS != ::RegOpenKeyEx(HKEY_CURRENT_USER, data_Set, 0, KEY_SET_VALUE | KEY_READ, &m_hAppRootKey))
	{
		//AfxMessageBox(_T("键打开失败"));
		BASELOG_INFO(_T("打开注册表失败！欲打开位置：HKEY_CURRENT_USER\\%s"), strKeyPath.c_str());
		m_strOpenPath = _T("");//GetOpenPath为空表示不存在
		m_bOpenState = false;
	}
	else
	{
		BASELOG_INFO(_T("打开注册表成功！打开位置：HKEY_CURRENT_USER\\%s"), strKeyPath.c_str());
		m_bOpenState = true;
	}
}

CBaseRegEdit::~CBaseRegEdit()
{
	if (m_strAppRootPath.length() > 0 && m_hParentKey != NULL)
	{//用一个参数的构造函数，不打开m_hParentKey
		::RegCloseKey(m_hParentKey);
		m_hParentKey = NULL;
	}
	if (m_hAppRootKey != NULL)
	{
		::RegCloseKey(m_hAppRootKey);
		m_hAppRootKey = NULL;
	}
}

long CBaseRegEdit::Query(const BaseString& strKeyPath, const BaseString& strKey, BaseString& refStrValue, HKEY rootKey/* = HKEY_CURRENT_USER*/)
{
	HKEY hKEY;//定义有关的hKEY,在查询结束时要关闭
			  //打开与路径data_Set相关的hKEY
	LPCTSTR data_Set = strKeyPath.c_str();
	long ret;
	//访问注册表，hKEY则保存此函数所打开的键的句柄
	if (ERROR_SUCCESS == ::RegOpenKeyEx(rootKey, data_Set, 0, KEY_READ, &hKEY))
	{
		BaseChar dwValue[1024];
		DWORD dwSzType = REG_SZ;
		DWORD dwSize = sizeof(dwValue);

		
		if ((ret = ::RegQueryValueEx(hKEY, strKey.c_str(), 0, &dwSzType, (LPBYTE)&dwValue, &dwSize)) != ERROR_SUCCESS)
		{
			//AfxMessageBox(_T("错误：无法查询有关的注册表信息"));
			BASELOG_INFO(_T("错误：无法查询有关的注册表信息"));
			::RegCloseKey(hKEY);
			return ret;
		}

		refStrValue = BaseString(dwValue);
		BASELOG_INFO(_T("读取注册表信息成功！%s"),/* strKeyPath, strKey, */refStrValue);
		//程序结束，关闭打开的hKEY
		::RegCloseKey(hKEY);
	}
	return ret;
}

HKEY CBaseRegEdit::GetRootKey()
{
	return m_hAppRootKey;
}

long CBaseRegEdit::SetValue(const BaseString& strKey, const BaseString& strValue)
{
	//BaseString m_name = "China";
	LPBYTE m_name_Set = (LPBYTE)(LPCSTR)(strValue.c_str());//定义x轴名称
	DWORD length = strValue.length() + 1;//定义数据长度

	long ret;
	if (ERROR_SUCCESS == (ret = ::RegSetValueEx(m_hAppRootKey, strKey.c_str(), 0, REG_SZ, m_name_Set, length)))
	{
		BASELOG_INFO(_T("设置注册表值：%s = %s"),strKey.c_str(),strValue.c_str());
	}
	else
	{
		BASELOG_INFO(_T("设置注册表值：%s 设置失败"), strKey.c_str());
	}
	
	return ret;
}

long CBaseRegEdit::GetValue(const BaseString& strKey, BaseString& refStrValue)
{
	BaseChar dwValue[1024];
	DWORD dwSzType = REG_SZ;
	DWORD dwSize = sizeof(dwValue);

	long ret;
	if (ERROR_SUCCESS != (ret = ::RegQueryValueEx(m_hAppRootKey, strKey.c_str(), 0, &dwSzType, (LPBYTE)&dwValue, &dwSize)))
	{
		//AfxMessageBox(_T("错误：无法查询有关的注册表信息"));
		BASELOG_INFO(_T("错误：无法查询有关的注册表信息:%s"), strKey.c_str());
		return ret;
	}
	refStrValue = BaseString(dwValue);
	BASELOG_INFO(_T("成功查询到注册表信息：%s = %s"),strKey.c_str(),refStrValue.c_str());
	return ret;
}

BaseString CBaseRegEdit::GetValue(const BaseString& strKey)
{
	BaseString tmpStrValue = _T("");
	GetValue(strKey, tmpStrValue);
	return tmpStrValue;
}

long CBaseRegEdit::Destroy()
{
	//HKEY hKey;//定义有关的hKEY,在查询结束时要关闭
			  //打开与路径data_Set相关的hKEY
	//LPCTSTR data_Set = _T("Software//武汉帷幄信息技术有限公司");
	//if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_CURRENT_USER, data_Set, 0, KEY_SET_VALUE, &hKey))
	//{
		// 使用hKey来操作data_Set这个KEY里面的值。
	long ret;
	if (ERROR_SUCCESS != (ret = ::RegDeleteKey(m_hParentKey, m_strAppRootName.c_str())))
	{
		//AfxMessageBox(_T("释放错误"));
		BASELOG_INFO(_T("释放错误"));
		//::RegCloseKey(hKey);
		
	}
	return ret;
	//}
	//::RegCloseKey(hKey);
}

long CBaseRegEdit::DeleteKey(const BaseString& strKey)
{
	long ret;
	if (ERROR_SUCCESS != (ret = ::RegDeleteKey(m_hAppRootKey, strKey.c_str())))
	{
		BASELOG_INFO(_T("删除注册表项失败！%s"), strKey.c_str());
	}
	else
	{
		BASELOG_INFO(_T("删除注册表项成功！%s"), strKey.c_str());
	}
	return ret;
}

BaseString CBaseRegEdit::GetSelfPath()
{
	return m_strAppRootPath + _T("\\") + m_strAppRootName;
}

BaseString CBaseRegEdit::GetOpenPath()
{
	return m_strOpenPath;
}

bool CBaseRegEdit::IsOpenSuccess()
{
	return m_bOpenState;
}
