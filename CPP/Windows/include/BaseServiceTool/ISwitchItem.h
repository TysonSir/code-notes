//                               ��Ȩ��������
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
// Description:ͨ�ÿ��ؽӿ���
// Current Version: 3.3
// Author ��������
// complete time:2018.7.31 

#pragma once

#include "stdafx.h"
namespace BASETOOLS
{
	class ISwitchItem
	{
	public:
		/*!	@brief ���󴴽�ʱִ�еĲ��� */
		virtual void Enter() = 0;
		/*!	@brief �������ʱִ�еĲ��� */
		virtual void Exit() = 0;

		/** brief  ֱ��ִ�д˶�����һ�㲻��Ҫִ�У�  **/
		virtual void Execute() = 0;
		/*!	@brief ��Ǳ������Ƿ��Ѿ�ִ��Enter��Exit */
		virtual bool getExecute() const = 0;
		/*!	@brief ������������ */
		virtual ~ISwitchItem(void) {}

	protected:
		/*!	@brief Ĭ�Ϲ��캯�� */
		ISwitchItem(void) {}
	};
}

