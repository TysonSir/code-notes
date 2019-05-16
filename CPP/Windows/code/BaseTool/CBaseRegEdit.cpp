#include "CBaseRegEdit.h"
#include "StringFormat.h"
#include "CWriteLog.h"


CBaseRegEdit::CBaseRegEdit()
{
}


CBaseRegEdit::CBaseRegEdit(const BaseString& strKeyPath, const BaseString& strKeyNew)
	:m_strAppRootPath(strKeyPath),m_strAppRootName(strKeyNew)
{
	//�����йص�hKEY,�ڲ�ѯ����ʱҪ�ر�
	
	//BaseString m_name = "China";
	//LPBYTE m_name_Set = (LPBYTE)(LPCSTR)(m_name.c_str());//����x������
	//DWORD length = m_name.length() + 1;//�������ݳ���

	//����·��data_Set��ص�hKEY
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
		BASELOG_INFO(_T("ע���򿪳ɹ���%s"), strKeyPath.c_str());
		m_bOpenState = true;
		// ʹ��hKey������data_Set���KEY�����ֵ��
		if (ERROR_SUCCESS == ::RegCreateKey(m_hParentKey, data_New, &m_hAppRootKey))
		{
			BASELOG_INFO(_T("ע�������ɹ���HKEY_CURRENT_USER\\%s\\%s"), strKeyPath.c_str(),strKeyNew.c_str());
		}
		else
		{
			BASELOG_INFO(_T("ע������ʧ�ܣ�HKEY_CURRENT_USER\\%s\\%s"), strKeyPath.c_str(), strKeyNew.c_str());
		}
	}
	else
	{
		BASELOG_INFO(_T("ע����ʧ�ܣ�%s"), strKeyPath.c_str());
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
		//AfxMessageBox(_T("����ʧ��"));
		BASELOG_INFO(_T("��ע���ʧ�ܣ�����λ�ã�HKEY_CURRENT_USER\\%s"), strKeyPath.c_str());
		m_strOpenPath = _T("");//GetOpenPathΪ�ձ�ʾ������
		m_bOpenState = false;
	}
	else
	{
		BASELOG_INFO(_T("��ע���ɹ�����λ�ã�HKEY_CURRENT_USER\\%s"), strKeyPath.c_str());
		m_bOpenState = true;
	}
}

CBaseRegEdit::~CBaseRegEdit()
{
	if (m_strAppRootPath.length() > 0 && m_hParentKey != NULL)
	{//��һ�������Ĺ��캯��������m_hParentKey
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
	HKEY hKEY;//�����йص�hKEY,�ڲ�ѯ����ʱҪ�ر�
			  //����·��data_Set��ص�hKEY
	LPCTSTR data_Set = strKeyPath.c_str();
	long ret;
	//����ע���hKEY�򱣴�˺������򿪵ļ��ľ��
	if (ERROR_SUCCESS == ::RegOpenKeyEx(rootKey, data_Set, 0, KEY_READ, &hKEY))
	{
		BaseChar dwValue[1024];
		DWORD dwSzType = REG_SZ;
		DWORD dwSize = sizeof(dwValue);

		
		if ((ret = ::RegQueryValueEx(hKEY, strKey.c_str(), 0, &dwSzType, (LPBYTE)&dwValue, &dwSize)) != ERROR_SUCCESS)
		{
			//AfxMessageBox(_T("�����޷���ѯ�йص�ע�����Ϣ"));
			BASELOG_INFO(_T("�����޷���ѯ�йص�ע�����Ϣ"));
			::RegCloseKey(hKEY);
			return ret;
		}

		refStrValue = BaseString(dwValue);
		BASELOG_INFO(_T("��ȡע�����Ϣ�ɹ���%s"),/* strKeyPath, strKey, */refStrValue);
		//����������رմ򿪵�hKEY
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
	LPBYTE m_name_Set = (LPBYTE)(LPCSTR)(strValue.c_str());//����x������
	DWORD length = strValue.length() + 1;//�������ݳ���

	long ret;
	if (ERROR_SUCCESS == (ret = ::RegSetValueEx(m_hAppRootKey, strKey.c_str(), 0, REG_SZ, m_name_Set, length)))
	{
		BASELOG_INFO(_T("����ע���ֵ��%s = %s"),strKey.c_str(),strValue.c_str());
	}
	else
	{
		BASELOG_INFO(_T("����ע���ֵ��%s ����ʧ��"), strKey.c_str());
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
		//AfxMessageBox(_T("�����޷���ѯ�йص�ע�����Ϣ"));
		BASELOG_INFO(_T("�����޷���ѯ�йص�ע�����Ϣ:%s"), strKey.c_str());
		return ret;
	}
	refStrValue = BaseString(dwValue);
	BASELOG_INFO(_T("�ɹ���ѯ��ע�����Ϣ��%s = %s"),strKey.c_str(),refStrValue.c_str());
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
	//HKEY hKey;//�����йص�hKEY,�ڲ�ѯ����ʱҪ�ر�
			  //����·��data_Set��ص�hKEY
	//LPCTSTR data_Set = _T("Software//�人����Ϣ�������޹�˾");
	//if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_CURRENT_USER, data_Set, 0, KEY_SET_VALUE, &hKey))
	//{
		// ʹ��hKey������data_Set���KEY�����ֵ��
	long ret;
	if (ERROR_SUCCESS != (ret = ::RegDeleteKey(m_hParentKey, m_strAppRootName.c_str())))
	{
		//AfxMessageBox(_T("�ͷŴ���"));
		BASELOG_INFO(_T("�ͷŴ���"));
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
		BASELOG_INFO(_T("ɾ��ע�����ʧ�ܣ�%s"), strKey.c_str());
	}
	else
	{
		BASELOG_INFO(_T("ɾ��ע�����ɹ���%s"), strKey.c_str());
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
