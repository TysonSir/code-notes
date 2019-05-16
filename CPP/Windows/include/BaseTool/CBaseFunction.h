#pragma once
#include "StringDef.h"
#include <vector>
using namespace std;

class CBaseFunction
{
public:
	CBaseFunction(void);
	~CBaseFunction(void);
	static BaseString GenerateGuid();

	//splitString�����Ĳ���˵����  
	//����ֵ�Ƿָ���ַ��������С  
	//strSrc ԭʼ�ַ���  
	//strDelims �Զ���ķָ��ַ����ķָ�����  
	//strDest �ָ����ַ������飬���ô���  
	static int SplitString(const BaseString & strSrc, const BaseString& strDelims,  vector<BaseString>& strDest);
	//�ַ����滻
	static void ReplaceString(BaseString &strBig, const BaseString &strsrc, const BaseString &strdst);
};
