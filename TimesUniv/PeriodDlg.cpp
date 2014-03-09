#include "stdafx.h"  //_____________________________________________ PeriodDlg.cpp
#include "PeriodDlg.h"

void PeriodDlg::Window_Open(Win::Event& e)
{
	this->Text=L"Period";
}
void PeriodDlg::btOK_Click(Win::Event& e)
{
	int period_id = 1;
	wstring descr = tbxDescr.GetText();
	wstring fecha1=dtboxBegin_date.GetText();
	wstring fecha2=dtboxEnd_date.GetText();
	wstring cmd;
	/*Sql::StringBuilder sb(L"period", L"period_id", period_id);
	sb.Bind(L"descr", tbxDescr);
	sb.Bind(L"begin_date", dtboxBegin_date, L"MMMM dd,yyyy");
	sb.Bind(L"end_date", dtboxEnd_date, L"MMMM dd,yyyy");*/
	Sql::SqlConnection conn;
	int rows = 0;

	Sys::Format(cmd,L"INSERT INTO period VALUES (%d,'%s','%s','%s',0)",period_id, descr.c_str(), fecha1.c_str(), fecha2.c_str());
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		//conn.OpenSession(hWnd, CONNECTION_STRING);
		rows = conn.ExecuteNonQuery(cmd);
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