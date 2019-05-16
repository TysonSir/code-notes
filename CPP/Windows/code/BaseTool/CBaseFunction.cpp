#include "CBaseFunction.h"
#include "StringFormat.h"
#include "windows.h"

CBaseFunction::CBaseFunction(void)
{
}

CBaseFunction::~CBaseFunction(void)
{
}

BaseString CBaseFunction::GenerateGuid()
{
	GUID guid;
	CoCreateGuid(&guid);
	char cBuffer[64] = { 0 };
	sprintf_s(cBuffer, sizeof(cBuffer),
		"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		guid.Data1, guid.Data2,
		guid.Data3, guid.Data4[0],
		guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4],
		guid.Data4[5], guid.Data4[6],
		guid.Data4[7]);
#ifdef UNICODE
	return CStringFormat::A2U(string(cBuffer));
#else
	return BaseString(cBuffer);
#endif
}

int CBaseFunction::SplitString(const BaseString & strSrc, const BaseString& strDelims, vector<BaseString>& strDest)
{
	typedef BaseString::size_type ST;
	BaseString delims = strDelims;
	BaseString STR;
	if (delims.empty()) delims = _T("/n/r");
	ST pos = 0, LEN = strSrc.size();
	while (pos < LEN) {
		STR = _T("");
		while ((delims.find(strSrc[pos]) != BaseString::npos) && (pos <  LEN)) ++pos;
		if (pos == LEN) return strDest.size();
		while ((delims.find(strSrc[pos]) == BaseString::npos) && (pos <  LEN)) STR += strSrc[pos++];
		//std::cout << "[" << STR << "]";  
		if (!STR.empty()) strDest.push_back(STR);
	}
	return strDest.size();
}

void CBaseFunction::ReplaceString(BaseString &strBig, const BaseString &strsrc, const BaseString &strdst)
{
	BaseString::size_type pos = 0;
	BaseString::size_type srclen = strsrc.size();
	BaseString::size_type dstlen = strdst.size();

	while ((pos = strBig.find(strsrc, pos)) != BaseString::npos)
	{
		strBig.replace(pos, srclen, strdst);
		pos += dstlen;
	}
}
