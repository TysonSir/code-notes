#include "CMdbOper.h"

CMdbOper::CMdbOper(void)
{
}

CMdbOper::CMdbOper(const BaseString& strMdbPath)
:m_strMdbPath(strMdbPath),m_strError(_T(""))
{
	MdbInit();
}

bool CMdbOper::MdbInit()
{
	::CoInitialize(NULL);//初始化OLE/COM库环境，为访问ADO接口做准备
	//_RecordsetPtr智能指针，可以用来打开库内数据表，并可以对表内的记录、字段等进行各种操作
	m_pRecordset = _RecordsetPtr(_T("ADODB.Recordset"));//定义记录集对象
	//_ConnectionPtr智能指针，通常用于打开、关闭一个库连接或用它的Execute方法来执行一个不返回结果的命令语句
	m_pConnection = _ConnectionPtr(_T("ADODB.Connection"));//定义数据库连接对象
	try
	{
		m_pConnection.CreateInstance(_T("ADODB.Connection"));//创建Connection对象
		/*****************************************************************************************************************/
		//设置连接字符串
		//_bstr_t strConnect = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=F:\\MyPro\\VS2008Pro\\Win32_mdbOper\\Win32_mdbOper\\Result.MDB";
		_bstr_t strConnect = BaseString(BaseString(_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=")) + m_strMdbPath).c_str();
		/*****************************************************************************************************************/
		m_pConnection->Open(strConnect,"","",adModeUnknown);//NULL、adConnectUnspecified、//建立与服务器连接
		if (m_pConnection ==NULL)
		{
			//cerr<<"Lind data ERROR!\n";
			m_strError = _T("error: Open mdb Fail! Path: ");
			m_strError += m_strMdbPath;
			return false;
		}

	}
	catch (_com_error e)//捕捉异常
	{
		//cerr<<"\nERROR:"<<(char*)e.Description();//抛出异常
		m_strError = _T("error: ");
		m_strError += e.Description();
		return false;
	}
	return true;
}

CMdbOper::~CMdbOper(void)
{
	if (m_pConnection->State)
	{
		m_pConnection->Close();
	}
	::CoUninitialize();
}

bool CMdbOper::Query(const BaseString& strSql, vector<vector<BaseString>>& vetRes)
{
	int i;
	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));//创建记录集对象
		/*****************************************************************************************************************/
		//在此输入查询条件
		//m_pRecordset->Open("select [税号],[金额]from BHG卷票信息 where 日期'20120101' ",m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		m_pRecordset->Open(strSql.c_str(), m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		/*****************************************************************************************************************/
		vector<BaseString> tmpVetStr;
		for(i=0;i<=m_pRecordset->GetFields()->Count-1;i++)
		{
			//cout<<(_bstr_t)m_pRecordset->GetFields()->GetItem(long(i))->GetName()<<" ";//打印列名
			tmpVetStr.push_back(
				((_bstr_t)m_pRecordset->GetFields()->GetItem(long(i))->GetName()).GetBSTR()
				);//打印列名
		}
		vetRes.push_back(tmpVetStr);//保存列名
		tmpVetStr.clear();

		//cout<<"\n";
		//查询结果
		if (m_pRecordset->EndOfFile)
		{
			//cout<<"无结果\n";
			m_strError = _T("warning: Recordset is Empty!");
			m_pRecordset->Close();//关闭记录集
			::CoUninitialize();
			return true;
		}

		//system("pause");
		while (!m_pRecordset->EndOfFile)//打印记录
		{
			for(i=0;i<=m_pRecordset->GetFields()->Count-1;i++)
			{
				tmpVetStr.push_back(
					((_bstr_t)m_pRecordset->GetCollect(m_pRecordset->GetFields()->GetItem(long(i))->GetName())).GetBSTR()
					);
			}
			//cout<<"\n";
			vetRes.push_back(tmpVetStr);//保存一行
			tmpVetStr.clear();
			m_pRecordset->MoveNext();//移动下一条记录
		}
		m_pRecordset->Close();//关闭记录集
	}
	catch (_com_error e)//捕捉异常
	{
		//cerr<<"\nERROR:"<<(char*)e.Description();//抛出异常
		m_strError = _T("error: ");
		m_strError += e.Description();
		return false;
	}
	return true;
}

bool CMdbOper::Execute(const BaseString& strSql)
{

	return true;
}

BaseString CMdbOper::GetError()
{
	return m_strError;
}
