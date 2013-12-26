#include "stdafx.h"  //_____________________________________________ ProgramDlg.cpp
#include "ProgramDlg.h"

void ProgramDlg::Window_Open(Win::Event& e)
{
	this->Text=L"Program";
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		//conn.OpenSession(hWnd, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT department_id, descr FROM department", 100, ddDepartment);
		if (program_id < 0) return;
		Sys::Format(cmd, L"SELECT descr, career_name, department_id FROM program WHERE program_id=%d", program_id);
		conn.ExecuteSelect(cmd);
		//tbxDescr.MaxText = 30;
		conn.BindColumn(1, tbxDescr, 128);
		//tbxCareer_name.MaxText = 100;
		conn.BindColumn(2, tbxCareer_name, 128);
		conn.BindColumn(3, ddDepartment);
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
void ProgramDlg::btOK_Click(Win::Event& e)
{
	//_____________________________________________________________ Validate
	/*tr1::wregex regextbxDescr(L"[A-Za-z0-9]+");
	if (tr1::regex_match(tbxDescr.Text, regextbxDescr) == false)
	{
		tbxDescr.ShowBalloonTip(L"Invalid Descr", L"Please provide one or more characters", TTI_ERROR);
		return;
	}
	tr1::wregex regextbxCareer_name(L"[A-Za-z0-9]+");
	if (tr1::regex_match(tbxCareer_name.Text, regextbxCareer_name) == false)
	{
		tbxCareer_name.ShowBalloonTip(L"Invalid Career name", L"Please provide one or more characters", TTI_ERROR);
		return;
	}*/
	Sql::StringBuilder sb(L"program", L"program_id", program_id);
	sb.Bind(L"descr", tbxDescr);
	sb.Bind(L"career_name", tbxCareer_name);
	sb.Bind(L"department_id", ddDepartment);
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
void ProgramDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}