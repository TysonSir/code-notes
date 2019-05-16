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
// FileName:CPtrProcess.h
// Description:ָ���������
// Current Version: 3.3
// Author ��������
// complete time:2018.7.31 

#pragma once
#include"CSwitchItemImpl.h"
#include <sstream>
#include <string>
#include "CSaveLog.h"
using namespace std;
template<typename T>
class CPtrProcess: public CSwitchItemImpl
{
public:
	/*!	@brief ���캯�� */
	CPtrProcess<typename T>(T*& pItem);
	/*!	@brief ������������ */
	~CPtrProcess(void);

	/*!	@brief ���󴴽�ʱִ�еĲ��� */
	void Enter();
	/*!	@brief �������ʱִ�еĲ��� */
	void Exit();

private:
	/*!	@brief �����ö������� */
	T* m_ptr;

};

template<typename T>
void CPtrProcess<T>::Enter()
{
	m_saveLog->OutMessage(THIRD,"CPtrProcess::Enter():�˴��Դ���ָ�� ���в���\n");
	//��ָ������ ת���ַ���
	stringstream ss;
	ss << *m_ptr;
	//m_saveLog->OutMessage(THIRD,"ָ��ָ������ݣ�" + ss.str() + "\n");
	m_saveLog->OutMessage(THIRD,"ָ��ָ������ݣ�%s\n" ,ss.str().c_str());
}

template<typename T>
void CPtrProcess<T>::Exit()
{
	delete m_ptr;
	m_ptr = NULL;
	m_saveLog->OutMessage(THIRD,"CPtrProcess::Exit(): m_ptr�ռ����ͷ�\n");
}

template<typename T>
CPtrProcess<T>::CPtrProcess(T*& pItem)
{
	m_ptr = pItem;
}

template<typename T>
CPtrProcess<T>::~CPtrProcess(void)
{
	delete m_ptr;
	m_ptr = NULL;
}
