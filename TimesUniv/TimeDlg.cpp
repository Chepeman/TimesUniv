#include "stdafx.h"  //_____________________________________________ TimeDlg.cpp
#include "TimeDlg.h"

void TimeDlg::Window_Open(Win::Event& e)
{
	this->Text=L"Classtime";
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		//conn.OpenSession(hWnd, CONNECTION_STRING);
		if (classtime_id < 0) return;
		Sys::Format(cmd, L"SELECT CONVERT(varchar(15), begin_time, 100), CONVERT(varchar(15), end_time, 100)\
						   FROM classtime WHERE classtime_id=%d", classtime_id);
		conn.ExecuteSelect(cmd);
		conn.BindColumn(1, tbxBeginTime, 100);
		conn.BindColumn(2, tbxEndTime, 100);
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
void TimeDlg::btOK_Click(Win::Event& e)
{
	//_____________________________________________________________ Validate
	Sql::StringBuilder sb(L"classtime", L"classtime_id", classtime_id);
	sb.Bind(L"begin_time", tbxBeginTime);
	sb.Bind(L"end_time", tbxEndTime);
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
void TimeDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}
