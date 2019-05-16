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
// FileName:ISwitchItem.h
// Description:通用开关接口类
// Current Version: 3.3
// Author ：陈泽众
// complete time:2018.7.31 

#pragma once

#include "stdafx.h"
namespace BASETOOLS
{
	class ISwitchItem
	{
	public:
		/*!	@brief 对象创建时执行的操作 */
		virtual void Enter() = 0;
		/*!	@brief 对象结束时执行的操作 */
		virtual void Exit() = 0;

		/** brief  直接执行此动作，一般不需要执行，  **/
		virtual void Execute() = 0;
		/*!	@brief 标记本对象是否已经执行Enter和Exit */
		virtual bool getExecute() const = 0;
		/*!	@brief 析构函数函数 */
		virtual ~ISwitchItem(void) {}

	protected:
		/*!	@brief 默认构造函数 */
		ISwitchItem(void) {}
	};
}

