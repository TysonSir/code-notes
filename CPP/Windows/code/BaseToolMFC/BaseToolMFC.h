// BaseToolMFC.h : BaseToolMFC DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBaseToolMFCApp
// �йش���ʵ�ֵ���Ϣ������� BaseToolMFC.cpp
//

class CBaseToolMFCApp : public CWinApp
{
public:
	CBaseToolMFCApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
