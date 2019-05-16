/**
@file:        StringDef.h
@brief:       ×Ö·û´®¶¨Òå
@author:      tiansj
@date:        2018-8-22 (9:16)
**/
#pragma once

#include <string>
using namespace std;
#ifdef UNICODE
typedef std::wstring BaseString;
#else
typedef std::string BaseString;
#endif

#include <tchar.h>
#ifdef UNICODE
typedef wchar_t BaseChar;
#else
typedef char BaseChar;
#endif


