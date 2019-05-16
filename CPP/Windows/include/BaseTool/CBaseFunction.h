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

	//splitString函数的参数说明：  
	//返回值是分割后字符串数组大小  
	//strSrc 原始字符串  
	//strDelims 自定义的分割字符串的分割数组  
	//strDest 分割后的字符串数组，引用传递  
	static int SplitString(const BaseString & strSrc, const BaseString& strDelims,  vector<BaseString>& strDest);
	//字符串替换
	static void ReplaceString(BaseString &strBig, const BaseString &strsrc, const BaseString &strdst);
};
