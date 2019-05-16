#pragma once
#include <vector>
#include <set>

namespace LBIM
{
	namespace GeometryPrimitiveResource
	{
		class CLBIMPosition;
	}
}
namespace BASETOOLS
{

#pragma region sysPath
	/** brief  ·����� **/
	AFX_API_EXPORT CString				GetSystemPath(void);
	/**@brief ȡ���ļ���MD5��*/
	AFX_API_EXPORT CString	GetFileMD5(const CString& strFilePath);

	/**@brief ȡ���ַ�����MD5��*/
	AFX_API_EXPORT CString	GetStreamMD5(const CString& strStream);

#pragma endregion sysPath

#pragma region ResoureLoad
	///////////////////////////////////��Դ����///////////////////////////////////
	AFX_API_EXPORT HBITMAP				LoadPic(const CString & strPicFileName);
	AFX_API_EXPORT HICON				LoadIcon(const CString & strPicFileName);
#pragma endregion ResoureLoad


#pragma region StringOperate
	///////////////////////////////////�ַ���������///////////////////////////////////
	AFX_API_EXPORT void					TransStrToAry(CString string, CStringArray &strAry, const CString &strSymbol);
	AFX_API_EXPORT void					TransStrToAry(CString string, std::vector<CString> &strVec, const CString &strSymbol);
	AFX_API_EXPORT void					TransStrToAry(const CString& str, std::vector<int>& vec, const CString &strSymbol);
    AFX_API_EXPORT void                 TransStrToAryEx(const CString& str, std::vector<CString>& strVec, const CString& FSymbol,const CString& SSymbol );
	///  TransStrToAry(_T("[1,2,3][4,5,6]"),vec,_T("["),_T("]"));
	///  vec��_T("1,2,3")��_T("4,5,6")
	AFX_API_EXPORT void					TransStrToAry(const CString& str, std::vector<CString>& strVec, const CString& lSymbol,const CString& rSymbol, bool bIncludeSymble = false);

	//�γ��ַ����ĺ���
	AFX_API_EXPORT void					TransAryToStr(const std::vector<int> &cVec, CString& strOut,const CString& strSymbol);
	AFX_API_EXPORT void					TransAryToStr(const std::vector<double> &cVec, CString& strOut,const CString& strSymbol);
	AFX_API_EXPORT void					TransAryToStr(const std::vector<CString> &cVec, CString& strOut,const CString& strSymbol);

	/// strAryΪ����һ�飬��һ��Ϊkey���ڶ���Ϊvalue
	AFX_API_EXPORT CString				GetStrVal(const CStringArray& strAry, CString strKey, bool bMatchCase = false);
	AFX_API_EXPORT CString				GetStrVal(CString strPara, CString strKey, const CString &strSymbol, bool bMatchCase = false);
    AFX_API_EXPORT CString				GetStrVal(const std::vector<CString>& strAry, CString strKey, bool bMatchCase = false);
	AFX_API_EXPORT int					FindVarBySymbol(CString szPara, CString szKey, CString szSymbol);
	/// �ҵ�str�е������ַ�����ֻ֧��unicode������unicode�����ַ���Χ����4E00-9FBF,�ο�unicode�ַ������
	AFX_API_EXPORT void					FindChineseStr(const CString& str, std::vector<CString>& chineseVec);
	AFX_API_EXPORT bool					IsChineseChar(TCHAR c);

	///���������������� ����ǰ׺ƥ������ж�
	AFX_API_EXPORT	void SortDataByOrder(std::vector<CString>& vctData, const std::vector<CString>& vctOrder );

	
	/**@brief char to wchar_t
	 * @note ת������ַ������Լ��ֶ�ɾ���������ڴ�й¶
	 */
	AFX_API_EXPORT bool					Char2WideChar(const char* str, wchar_t *& ustr);
	AFX_API_EXPORT bool					WideChar2Char(const wchar_t* ustr, char *& str);

	/**@brief ����ת��*/
	AFX_API_EXPORT int					GB2312ToUtf8(const char* gb2312, std::string & utf8);
	AFX_API_EXPORT int					Utf8ToGB2312(const char* utf8, std::string& strGB2312);
	AFX_API_EXPORT int					GB2312ToUnicode(const char* gb2312, std::wstring & strUnicode);
	AFX_API_EXPORT int					UnicodeToGB2312(const wchar_t* unicode, std::string & strGb2312);
	AFX_API_EXPORT int					Utf8ToUnicode(const char* utf8, std::wstring & strUnicode);
	AFX_API_EXPORT int					UnicodeToUtf8(const wchar_t * unicode, std::string& strUtf8);



	/// �ֽ�����б�������Ƿ�Ϸ�
	AFX_API_EXPORT bool					IsNameLegal(const CString& strName, CString& strErrMsg = CString(_T("")));
	/// �滻�Ƿ��ַ�����
	AFX_API_EXPORT bool					ReplaceIllegalCharacters( CString& strName, const CString& strReplace = CString(_T(' ')));



	  /**
     * @brief  �Ƚ������汾�ŵĴ�С
     * 
     * @param[in]  strVer1
     * @param[in]  strVer2
     * @return  strVer1 ��= strVer2 ʱ������ture
     *
     * @author shaojun 
     * @date   2010-10-25 (19:51)
     */
	AFX_API_EXPORT bool					CompareVersion(CString strVer1,CString strVer2);


	/**@brief ��ʽ��dΪ�ַ�����������ֿ�ѧ�������������0����ȥ��������С�������6λ
	 *@code
	 *ASSERT(FormatDoubleToString(1.0001) == _T("1.0001"));
	 *ASSERT(FormatDoubleToString(1.00010000000000000000) == _T("1.001"));
	 *ASSERT(FormatDoubleToString(1.00000000000000000000) == _T("1"));
	 *ASSERT(FormatDoubleToString(1.00000000000000000001) == _T("1"));
	 *ASSERT(FormatDoubleToString(12000) == _T("1200"));
	 *ASSERT(FormatDoubleToString(12000.) == _T("1200"));
	 *ASSERT(FormatDoubleToString(.1200) == _T(".12"));
	 *ASSERT(FormatDoubleToString(4.0e-006) == _T("0.000004"));
	 *ASSERT(FormatDoubleToString(4.0e-007) == _T("0"));
	 *@endcode
	 */
	AFX_API_EXPORT CString				FormatDoubleToString(double dValue);

	AFX_API_EXPORT bool IsNumber(const CString& str);

	/// �ж��Ƿ��Ǹ�������ʽ
	//AFX_API_EXPORT bool					IsFloatNum(const CString& strVal);
	/// �ж��Ƿ���������
	AFX_API_EXPORT bool					IsPositiveInteger(const CString& strVal);
	/// �ж��Ƿ��Ǹ���
	//AFX_API_EXPORT bool					IsNegativeFloatNum(const CString& strVal);
	/// ��ʽ�������ַ������������ַ�����������0��ȥ��
	AFX_API_EXPORT CString				FormatStrClearZeroTail(const CString& strNum);


	AFX_API_EXPORT CString				CreateGuid();

	    /**
     * @brief  ��strNameΪģ�崴�������ơ�strName������֣�����Ѿ��������������
     * 
     * @param [in]  strName ģ������
     * @param [in]  strExistentNameVec ��ǰ���ڵ�����,�����жϷ��ص����Ʋ�����
     * @return  �µ�����
	 * @code 
	 * CString strName = _T("JLQ2");
	 * vector<CString> strExistentNameVec;
	 * strExistentNameVec.push_back(_T("JLQ2"));
	 * strExistentNameVec.push_back(_T("JLQ3"));
	 * ASSERT(GetNewName(strName,strExistentNameVec) == _T("JLQ4"));
	 * @endcode  
     * @author chaojun
     * @date   2011-08-03 (13:15)
     */
	AFX_API_EXPORT CString				CreateNewName(const CString& strName, const std::vector<CString>& strExistentNameVec);

    /**
     * @brief  ��strNameΪģ�崴�������ơ�strName���_���֣�����Ѿ��������������
     * 
     * @param [in]  strName ģ������
     * @param [in]  strExistentNameVec ��ǰ���ڵ�����,�����жϷ��ص����Ʋ�����
     * @return  �µ�����
     *
     * @code 
	 * CString strName = _T("JLQ2");
	 * vector<CString> strExistentNameVec;
	 * strExistentNameVec.push_back(_T("JLQ2_1"));
	 * ASSERT(GetNewName(strName,strExistentNameVec) == _T("JLQ2_2"));
     * @endcode  
     * @author chaojun
     * @date   2011-08-03 (13:39)
     */
	AFX_API_EXPORT CString				CreateNewName_N(const CString& strName, const std::vector<CString>& strExistentNameVec);

#pragma endregion StringOperate




#pragma region colorConvert
	///////////////////////////////////��ɫת��///////////////////////////////////
	// ��255,255,255�ĸ�ʽת��ΪCOLORREF
	AFX_API_EXPORT COLORREF				StrToCOLORREF(const CString& strRGB);
	AFX_API_EXPORT CString				COLORREFToStr(COLORREF clr);
	AFX_API_EXPORT   void               GetRGB(const COLORREF rgb, int& nR, int& nG, int& nB);
	AFX_API_EXPORT void RGBToHSV( double R, double G, double B, double& H, double& S, double&V );
	AFX_API_EXPORT    bool              IsLikeColor( COLORREF color1, COLORREF color2 );
	AFX_API_EXPORT    COLORREF          GetComparisonColor( COLORREF color1);

#pragma endregion colorConvert




	





///�ʺ�С��ģ��Ⱥ
//AFX_API_EXPORT	void FiltRepeatPoint(std::vector<LBIM::GeometryPrimitiveResource::CLBIMPosition>& vctPt, const double dMinDistance);

}
