//                               版权声明部分
// Copyright (c) 2007 by Lubansoft, LLC.
// The information contained herein is confidential and proprietary to
// LuBan Soft, LLC., and considered a trade secret as defined under
// civil and criminal statutes. Lubansoft shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Lubansoft, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// FileName:CPublicBase.h
// Description:开关对象上层控制类，
// Current Version: 2.1
// Author ：陈泽众
// complete time:2018.7.25 

#pragma once
#include "stdafx.h"
#include <list>

using namespace std;
namespace BASETOOLS
{
	class CSaveLog;
	class ISwitchItem;
	class  AFX_EXT_CLASS CMonitorSwitch
	{
	public:
		/*!	@brief 构造函数，获得列表接口 */
		CMonitorSwitch(const list<ISwitchItem*> &mylist);

		/*!	@brief 析构函数 */
		~CMonitorSwitch(void);

	private:
		/*! @brief 用于保存子类集合*/
		list<ISwitchItem*> m_list;

		/*! @brief 用于输出信息*/
		CSaveLog* m_saveLog;
	};

	class  AFX_EXT_CLASS CMonitorSwitchOdd
	{
	public:
		/*!	@brief 构造函数，获得列表接口 */
		CMonitorSwitchOdd(ISwitchItem * pSwitch);

		/*!	@brief 析构函数 */
		~CMonitorSwitchOdd(void);

	private:
		/*! @brief 用于保存子类集合*/
		ISwitchItem  * m_pSwitch;

		/*! @brief 用于输出信息*/
		CSaveLog* m_saveLog;
	};
}


