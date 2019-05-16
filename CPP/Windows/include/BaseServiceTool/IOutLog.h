/// �� BaseServiceToolģ���⣬����ģ�鲻������ã�
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
// FileName:IOutLog.h
// Description:��־���������
// Current Version: 4.3
// Author ��������
// complete time:2018.10.25 
#pragma once


#include "StringDef.h"
using namespace std;
class IOutLog
{
public:
	virtual void ShowMsg(const int level, const BaseString &str) = 0; // �����÷���Ҫ���õĳ�Ա���������ɴ��麯��
	virtual void ShowMsg(const TCHAR* LocateFile, const TCHAR* LocateFunc, const int& LocateLine,
						const int level, const BaseString &str) = 0;
	virtual void FlushLog() = 0;
	virtual ~IOutLog() {};// �����������������
protected:
	IOutLog() {}
};