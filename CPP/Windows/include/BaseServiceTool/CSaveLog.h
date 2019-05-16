//                               版权声明部分
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
// Description:日志输出控制类 适配器
// Current Version: 4.3
// Author ：陈泽众
// complete time:2018.10.25 
#pragma once

#include <string>
#include <Windows.h>
#include "IOutLog.h" // 包含抽象类从而使用接口
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
		/*!	@brief 获得本类单例对象 */
		static CSaveLog* GetInstance();
		/*!	@brief 输出日志信息 */
		//void OutMessage(const Rank& refLevel, const CString& refLog);
		//void OutMessage(const Rank& refLevel, const TCHAR* pFormat, ...);
		//void OutMessage(const char* LocateFile, const char* LocateFunc, const int& LocateLine,
		//const Rank& refLevel, const CString& refLog);
		void OutMessage(const TCHAR* LocateFile, const TCHAR* LocateFunc, const int& LocateLine,
			const Rank& refLevel, const TCHAR* pFormat, ...);

		void FlushLog();
	private:

		void InitDll();
		/*!	@brief 默认构造函数 */
		CSaveLog();
		//把复制构造函数和=操作符也设为私有,防止被复制
		CSaveLog(const CSaveLog&);
		CSaveLog& operator=(const CSaveLog&);

		/*!	@brief 获得DLL中类的对象指针 */
		IOutLog* GetObjectPointer(const HINSTANCE& hDll, const CString & strKey);
		void ReleaseObjPtr(const HINSTANCE& hDll, const CString & strKey );
		/*!	@brief 刷新输出数据 */
		
	private:
		/*!	@brief DLL句柄 */
		HINSTANCE m_hDll;
		/*!	@brief DLL中类的对象指针 */
		IOutLog *m_pOutLogObj;
		/*!	@brief 判断DLL是否存在 */
		bool m_havaDll;

		/*!	@brief 单例对象保存地址 */
		static std::auto_ptr<CSaveLog>  m_instance;
	};
}

