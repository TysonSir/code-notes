#pragma once

class __declspec( dllexport ) CFileSysOper
{
public:
	CFileSysOper(void);
	~CFileSysOper(void);
	static BOOL IsDirectory(const char *pDir);
	static BOOL DeleteDirectory(const char * DirName);
};
