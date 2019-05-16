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
	/** brief  路径相关 **/
	AFX_API_EXPORT CString				GetSystemPath(void);
	/**@brief 取得文件的MD5码*/
	AFX_API_EXPORT CString	GetFileMD5(const CString& strFilePath);

	/**@brief 取得字符流的MD5码*/
	AFX_API_EXPORT CString	GetStreamMD5(const CString& strStream);

#pragma endregion sysPath

#pragma region ResoureLoad
	///////////////////////////////////资源加载///////////////////////////////////
	AFX_API_EXPORT HBITMAP				LoadPic(const CString & strPicFileName);
	AFX_API_EXPORT HICON				LoadIcon(const CString & strPicFileName);
#pragma endregion ResoureLoad


#pragma region StringOperate
	///////////////////////////////////字符串处处理///////////////////////////////////
	AFX_API_EXPORT void					TransStrToAry(CString string, CStringArray &strAry, const CString &strSymbol);
	AFX_API_EXPORT void					TransStrToAry(CString string, std::vector<CString> &strVec, const CString &strSymbol);
	AFX_API_EXPORT void					TransStrToAry(const CString& str, std::vector<int>& vec, const CString &strSymbol);
    AFX_API_EXPORT void                 TransStrToAryEx(const CString& str, std::vector<CString>& strVec, const CString& FSymbol,const CString& SSymbol );
	///  TransStrToAry(_T("[1,2,3][4,5,6]"),vec,_T("["),_T("]"));
	///  vec中_T("1,2,3")和_T("4,5,6")
	AFX_API_EXPORT void					TransStrToAry(const CString& str, std::vector<CString>& strVec, const CString& lSymbol,const CString& rSymbol, bool bIncludeSymble = false);

	//形成字符串的函数
	AFX_API_EXPORT void					TransAryToStr(const std::vector<int> &cVec, CString& strOut,const CString& strSymbol);
	AFX_API_EXPORT void					TransAryToStr(const std::vector<double> &cVec, CString& strOut,const CString& strSymbol);
	AFX_API_EXPORT void					TransAryToStr(const std::vector<CString> &cVec, CString& strOut,const CString& strSymbol);

	/// strAry为两个一组，第一个为key，第二个为value
	AFX_API_EXPORT CString				GetStrVal(const CStringArray& strAry, CString strKey, bool bMatchCase = false);
	AFX_API_EXPORT CString				GetStrVal(CString strPara, CString strKey, const CString &strSymbol, bool bMatchCase = false);
    AFX_API_EXPORT CString				GetStrVal(const std::vector<CString>& strAry, CString strKey, bool bMatchCase = false);
	AFX_API_EXPORT int					FindVarBySymbol(CString szPara, CString szKey, CString szSymbol);
	/// 找到str中的中文字符串，只支持unicode，根据unicode中文字符范围查找4E00-9FBF,参考unicode字符编码表
	AFX_API_EXPORT void					FindChineseStr(const CString& str, std::vector<CString>& chineseVec);
	AFX_API_EXPORT bool					IsChineseChar(TCHAR c);

	///按照已有数据排序， 按照前缀匹配进行判断
	AFX_API_EXPORT	void SortDataByOrder(std::vector<CString>& vctData, const std::vector<CString>& vctOrder );

	
	/**@brief char to wchar_t
	 * @note 转化后的字符串需自己手动删除，否则内存泄露
	 */
	AFX_API_EXPORT bool					Char2WideChar(const char* str, wchar_t *& ustr);
	AFX_API_EXPORT bool					WideChar2Char(const wchar_t* ustr, char *& str);

	/**@brief 编码转换*/
	AFX_API_EXPORT int					GB2312ToUtf8(const char* gb2312, std::string & utf8);
	AFX_API_EXPORT int					Utf8ToGB2312(const char* utf8, std::string& strGB2312);
	AFX_API_EXPORT int					GB2312ToUnicode(const char* gb2312, std::wstring & strUnicode);
	AFX_API_EXPORT int					UnicodeToGB2312(const wchar_t* unicode, std::string & strGb2312);
	AFX_API_EXPORT int					Utf8ToUnicode(const char* utf8, std::wstring & strUnicode);
	AFX_API_EXPORT int					UnicodeToUtf8(const wchar_t * unicode, std::string& strUtf8);



	/// 钢筋软件中编号名称是否合法
	AFX_API_EXPORT bool					IsNameLegal(const CString& strName, CString& strErrMsg = CString(_T("")));
	/// 替换非法字符名称
	AFX_API_EXPORT bool					ReplaceIllegalCharacters( CString& strName, const CString& strReplace = CString(_T(' ')));



	  /**
     * @brief  比较两个版本号的大小
     * 
     * @param[in]  strVer1
     * @param[in]  strVer2
     * @return  strVer1 〉= strVer2 时，返回ture
     *
     * @author shaojun 
     * @date   2010-10-25 (19:51)
     */
	AFX_API_EXPORT bool					CompareVersion(CString strVer1,CString strVer2);


	/**@brief 格式化d为字符串，不会出现科学计数法，多余的0将被去掉，精度小数点后面6位
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

	/// 判断是否是浮点数格式
	//AFX_API_EXPORT bool					IsFloatNum(const CString& strVal);
	/// 判断是否是正整数
	AFX_API_EXPORT bool					IsPositiveInteger(const CString& strVal);
	/// 判断是否是负数
	//AFX_API_EXPORT bool					IsNegativeFloatNum(const CString& strVal);
	/// 格式化数字字符串，把数字字符串后面多余的0都去掉
	AFX_API_EXPORT CString				FormatStrClearZeroTail(const CString& strNum);


	AFX_API_EXPORT CString				CreateGuid();

	    /**
     * @brief  以strName为模板创建新名称。strName后加数字，如果已经存在则递增数字
     * 
     * @param [in]  strName 模板名称
     * @param [in]  strExistentNameVec 当前存在的名称,用于判断返回的名称不重名
     * @return  新的名称
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
     * @brief  以strName为模板创建新名称。strName后加_数字，如果已经存在则递增数字
     * 
     * @param [in]  strName 模板名称
     * @param [in]  strExistentNameVec 当前存在的名称,用于判断返回的名称不重名
     * @return  新的名称
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
	///////////////////////////////////颜色转换///////////////////////////////////
	// 将255,255,255的格式转化为COLORREF
	AFX_API_EXPORT COLORREF				StrToCOLORREF(const CString& strRGB);
	AFX_API_EXPORT CString				COLORREFToStr(COLORREF clr);
	AFX_API_EXPORT   void               GetRGB(const COLORREF rgb, int& nR, int& nG, int& nB);
	AFX_API_EXPORT void RGBToHSV( double R, double G, double B, double& H, double& S, double&V );
	AFX_API_EXPORT    bool              IsLikeColor( COLORREF color1, COLORREF color2 );
	AFX_API_EXPORT    COLORREF          GetComparisonColor( COLORREF color1);

#pragma endregion colorConvert




	





///适合小规模点群
//AFX_API_EXPORT	void FiltRepeatPoint(std::vector<LBIM::GeometryPrimitiveResource::CLBIMPosition>& vctPt, const double dMinDistance);

}
