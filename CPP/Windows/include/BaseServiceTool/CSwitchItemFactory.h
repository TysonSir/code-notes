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
// FileName:CSwitchItemFactory.h
// Description:创建开关对象工厂
// Current Version: 2.4
// Author ：陈泽众
// complete time:2018.7.25 

#pragma once
#include "stdafx.h"
#include <memory>
namespace BASETOOLS
{
	class ISwitchItem;
	class AFX_EXT_CLASS  CSwitchItemFactory
	{
	public:
		~CSwitchItemFactory() {}
		CSwitchItemFactory * GetInstance();
		ISwitchItem* CreateFlagSwitch(bool& b_src, bool bStatus);
	private:
		CSwitchItemFactory() {}
	private:
		static std::auto_ptr<CSwitchItemFactory> m_pinstance;
	};
}

