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
// FileName:CPublicBase.h
// Description:���ض����ϲ�����࣬
// Current Version: 2.1
// Author ��������
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
		/*!	@brief ���캯��������б�ӿ� */
		CMonitorSwitch(const list<ISwitchItem*> &mylist);

		/*!	@brief �������� */
		~CMonitorSwitch(void);

	private:
		/*! @brief ���ڱ������༯��*/
		list<ISwitchItem*> m_list;

		/*! @brief ���������Ϣ*/
		CSaveLog* m_saveLog;
	};

	class  AFX_EXT_CLASS CMonitorSwitchOdd
	{
	public:
		/*!	@brief ���캯��������б�ӿ� */
		CMonitorSwitchOdd(ISwitchItem * pSwitch);

		/*!	@brief �������� */
		~CMonitorSwitchOdd(void);

	private:
		/*! @brief ���ڱ������༯��*/
		ISwitchItem  * m_pSwitch;

		/*! @brief ���������Ϣ*/
		CSaveLog* m_saveLog;
	};
}


