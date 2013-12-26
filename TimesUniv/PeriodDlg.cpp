#include "stdafx.h"  //_____________________________________________ PeriodDlg.cpp
#include "PeriodDlg.h"

void PeriodDlg::Window_Open(Win::Event& e)
{
	this->Text=L"Period";
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		//conn.OpenSession(hWnd, CONNECTION_STRING);
		if (period_id < 0) return;
		Sys::Format(cmd, L"SELECT descr, begin_date, end_date FROM period WHERE period_id=%d", period_id);
		conn.ExecuteSelect(cmd);
		//tbxDescr.MaxText = 15;
		conn.BindColumn(1, tbxDescr, 128);
		dtboxBegin_date.SetFormat(L"MMMM dd,yyyy"); 
		conn.BindColumn(2, dtboxBegin_date);
		dtboxEnd_date.SetFormat(L"MMMM dd,yyyy"); 
		conn.BindColumn(3, dtboxEnd_date);
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

void PeriodDlg::btOK_Click(Win::Event& e)
{
	//_____________________________________________________________ Validate
	/*tr1::wregex regextbxDescr(L"[A-Za-z0-9]+");
	if (tr1::regex_match(tbxDescr.Text, regextbxDescr) == false)
	{
		tbxDescr.ShowBalloonTip(L"Invalid Descr", L"Please provide one or more characters", TTI_ERROR);
		return;
	}*/
	Sql::StringBuilder sb(L"period", L"period_id", period_id);
	sb.Bind(L"descr", tbxDescr);
	sb.Bind(L"begin_date", dtboxBegin_date, L"MM-dd-yyyy");
	sb.Bind(L"end_date", dtboxEnd_date, L"MM-dd-yyyy");
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

void PeriodDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}