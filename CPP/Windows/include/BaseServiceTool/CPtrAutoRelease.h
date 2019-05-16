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
// FileName:CPtrProcess.h
// Description:指针过程子类
// Current Version: 3.3
// Author ：陈泽众
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
	/*!	@brief 构造函数 */
	CPtrProcess<typename T>(T*& pItem);
	/*!	@brief 析构函数函数 */
	~CPtrProcess(void);

	/*!	@brief 对象创建时执行的操作 */
	void Enter();
	/*!	@brief 对象结束时执行的操作 */
	void Exit();

private:
	/*!	@brief 测试用对象数据 */
	T* m_ptr;

};

template<typename T>
void CPtrProcess<T>::Enter()
{
	m_saveLog->OutMessage(THIRD,"CPtrProcess::Enter():此处对传入指针 进行操作\n");
	//将指针内容 转成字符串
	stringstream ss;
	ss << *m_ptr;
	//m_saveLog->OutMessage(THIRD,"指针指向的内容：" + ss.str() + "\n");
	m_saveLog->OutMessage(THIRD,"指针指向的内容：%s\n" ,ss.str().c_str());
}

template<typename T>
void CPtrProcess<T>::Exit()
{
	delete m_ptr;
	m_ptr = NULL;
	m_saveLog->OutMessage(THIRD,"CPtrProcess::Exit(): m_ptr空间已释放\n");
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
