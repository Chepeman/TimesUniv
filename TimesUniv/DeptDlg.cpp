#include "stdafx.h"  //_____________________________________________ DeptDlg.cpp
#include "DeptDlg.h"

void DeptDlg::Window_Open(Win::Event& e)
{
	this->Text=L"Department";
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		//conn.OpenSession(hWnd, CONNECTION_STRING);
		if (department_id < 0) return;
		Sys::Format(cmd, L"SELECT descr FROM department WHERE department_id=%d ORDER BY department_id", department_id);
		conn.ExecuteSelect(cmd);
		//tbxDescr.MaxText = 40;
		conn.BindColumn(1, tbxDescr, 128);
		if (conn.Fetch() == false)
		{
			this->MessageBox(L"No data was returned", L"Error", MB_OK);
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}
void DeptDlg::btOK_Click(Win::Event& e)
{
	//_____________________________________________________________ Validate
	/*tr1::wregex regextbxDescr(L"[A-Za-z0-9]+");
	if (tr1::regex_match(tbxDescr.Text, regextbxDescr) == false)
	{
		tbxDescr.ShowBalloonTip(L"Invalid Descr", L"Please provide one or more characters", TTI_ERROR);
		return;
	}*/
	Sql::StringBuilder sb(L"department", L"department_id", department_id);
	sb.Bind(L"descr", tbxDescr);
	Sql::SqlConnection conn;
	int rows = 0;
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		//conn.OpenSession(hWnd, CONNECTION_STRING);
		rows = conn.ExecuteNonQuery(sb.GetString());
		if (rows!=1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of affected rows", MB_OK | MB_ICONERROR);
			return;
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		return;
	}
	this->EndDialog(TRUE);
}
void DeptDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}