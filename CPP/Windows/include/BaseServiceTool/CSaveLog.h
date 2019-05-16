//                               ��Ȩ��������
// Copyright (c) 2018 by Lubansoft, LLC.
// The information contained herein is confidential and proprietary to
// LuBan Soft, LLC., and considered a trade secret as defined under
// civil and criminal statutes. Lubansoft shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Lubansoft, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// FileName:CSaveLog.h
// Description:��־��������� ������
// Current Version: 4.3
// Author ��������
// complete time:2018.10.25 
#pragma once

#include <string>
#include <Windows.h>
#include "IOutLog.h" // ����������Ӷ�ʹ�ýӿ�
#include <iostream>
#include <memory>
#define LOCATE __FILE__,__FUNCTION__,__LINE__

#ifdef UNICODE
#define ACCESS _waccess
#define OUTINFO std::wcout
typedef std::wifstream Inputstream;
typedef std::wofstream Outputstream;
#else
#define ACCESS _access
#define OUTINFO std::cout
typedef std::ifstream Inputstream;
typedef std::ofstream Outputstream;
#endif

#define  BASELOG_INFO(nLevel, strFormat, ...)       BASETOOLS::CSaveLog::GetInstance()->OutMessage(_T(__FILE__),_T(__FUNCTION__), __LINE__, nLevel, strFormat,## __VA_ARGS__)
#define  BASELOG_FORCE_WRITE()                      BASETOOLS::CSaveLog::GetInstance()->FlushLog()


using namespace std;

namespace BASETOOLS
{
	typedef int Rank;
	class AFX_EXT_CLASS CSaveLog
	{
	public:
		~CSaveLog();
		//CSaveLog::~CSaveLog()
		/*!	@brief ��ñ��൥������ */
		static CSaveLog* GetInstance();
		/*!	@brief �����־��Ϣ */
		//void OutMessage(const Rank& refLevel, const CString& refLog);
		//void OutMessage(const Rank& refLevel, const TCHAR* pFormat, ...);
		//void OutMessage(const char* LocateFile, const char* LocateFunc, const int& LocateLine,
		//const Rank& refLevel, const CString& refLog);
		void OutMessage(const TCHAR* LocateFile, const TCHAR* LocateFunc, const int& LocateLine,
			const Rank& refLevel, const TCHAR* pFormat, ...);

		void FlushLog();
	private:

		void InitDll();
		/*!	@brief Ĭ�Ϲ��캯�� */
		CSaveLog();
		//�Ѹ��ƹ��캯����=������Ҳ��Ϊ˽��,��ֹ������
		CSaveLog(const CSaveLog&);
		CSaveLog& operator=(const CSaveLog&);

		/*!	@brief ���DLL����Ķ���ָ�� */
		IOutLog* GetObjectPointer(const HINSTANCE& hDll, const CString & strKey);
		void ReleaseObjPtr(const HINSTANCE& hDll, const CString & strKey );
		/*!	@brief ˢ��������� */
		
	private:
		/*!	@brief DLL��� */
		HINSTANCE m_hDll;
		/*!	@brief DLL����Ķ���ָ�� */
		IOutLog *m_pOutLogObj;
		/*!	@brief �ж�DLL�Ƿ���� */
		bool m_havaDll;

		/*!	@brief �������󱣴��ַ */
		static std::auto_ptr<CSaveLog>  m_instance;
	};
}

