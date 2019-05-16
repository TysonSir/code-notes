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
	::CoInitialize(NULL);//��ʼ��OLE/COM�⻷����Ϊ����ADO�ӿ���׼��
	//_RecordsetPtr����ָ�룬���������򿪿������ݱ������ԶԱ��ڵļ�¼���ֶεȽ��и��ֲ���
	m_pRecordset = _RecordsetPtr(_T("ADODB.Recordset"));//�����¼������
	//_ConnectionPtr����ָ�룬ͨ�����ڴ򿪡��ر�һ�������ӻ�������Execute������ִ��һ�������ؽ�����������
	m_pConnection = _ConnectionPtr(_T("ADODB.Connection"));//�������ݿ����Ӷ���
	try
	{
		m_pConnection.CreateInstance(_T("ADODB.Connection"));//����Connection����
		/*****************************************************************************************************************/
		//���������ַ���
		//_bstr_t strConnect = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=F:\\MyPro\\VS2008Pro\\Win32_mdbOper\\Win32_mdbOper\\Result.MDB";
		_bstr_t strConnect = BaseString(BaseString(_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=")) + m_strMdbPath).c_str();
		/*****************************************************************************************************************/
		m_pConnection->Open(strConnect,"","",adModeUnknown);//NULL��adConnectUnspecified��//���������������
		if (m_pConnection ==NULL)
		{
			//cerr<<"Lind data ERROR!\n";
			m_strError = _T("error: Open mdb Fail! Path: ");
			m_strError += m_strMdbPath;
			return false;
		}

	}
	catch (_com_error e)//��׽�쳣
	{
		//cerr<<"\nERROR:"<<(char*)e.Description();//�׳��쳣
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
		m_pRecordset.CreateInstance(__uuidof(Recordset));//������¼������
		/*****************************************************************************************************************/
		//�ڴ������ѯ����
		//m_pRecordset->Open("select [˰��],[���]from BHG��Ʊ��Ϣ where ����'20120101' ",m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		m_pRecordset->Open(strSql.c_str(), m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		/*****************************************************************************************************************/
		vector<BaseString> tmpVetStr;
		for(i=0;i<=m_pRecordset->GetFields()->Count-1;i++)
		{
			//cout<<(_bstr_t)m_pRecordset->GetFields()->GetItem(long(i))->GetName()<<" ";//��ӡ����
			tmpVetStr.push_back(
				((_bstr_t)m_pRecordset->GetFields()->GetItem(long(i))->GetName()).GetBSTR()
				);//��ӡ����
		}
		vetRes.push_back(tmpVetStr);//��������
		tmpVetStr.clear();

		//cout<<"\n";
		//��ѯ���
		if (m_pRecordset->EndOfFile)
		{
			//cout<<"�޽��\n";
			m_strError = _T("warning: Recordset is Empty!");
			m_pRecordset->Close();//�رռ�¼��
			::CoUninitialize();
			return true;
		}

		//system("pause");
		while (!m_pRecordset->EndOfFile)//��ӡ��¼
		{
			for(i=0;i<=m_pRecordset->GetFields()->Count-1;i++)
			{
				tmpVetStr.push_back(
					((_bstr_t)m_pRecordset->GetCollect(m_pRecordset->GetFields()->GetItem(long(i))->GetName())).GetBSTR()
					);
			}
			//cout<<"\n";
			vetRes.push_back(tmpVetStr);//����һ��
			tmpVetStr.clear();
			m_pRecordset->MoveNext();//�ƶ���һ����¼
		}
		m_pRecordset->Close();//�رռ�¼��
	}
	catch (_com_error e)//��׽�쳣
	{
		//cerr<<"\nERROR:"<<(char*)e.Description();//�׳��쳣
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
