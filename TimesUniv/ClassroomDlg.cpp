#include "stdafx.h"  //_____________________________________________ ClassroomDlg.cpp
#include "ClassroomDlg.h"

void ClassroomDlg::Window_Open(Win::Event& e)
{
	this->Text=L"Classroom";
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		//conn.OpenSession(hWnd, CONNECTION_STRING);
		if (classroom_id < 0) return;
		Sys::Format(cmd, L"SELECT descr, contact_count, seat_count, has_projector, has_tables FROM classroom WHERE classroom_id=%d", classroom_id);
		conn.ExecuteSelect(cmd);
		//tbxDescr.MaxText = 70;
		conn.BindColumn(1, tbxDescr, 128);
		tbxContact_count.Number=true;
		conn.BindColumn(2, tbxContact_count, 128);
		tbxSeat_count.Number=true;
		conn.BindColumn(3, tbxSeat_count, 128);
		conn.BindColumn(4, ckHas_projector);
		conn.BindColumn(5, ckHas_tables);
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
void ClassroomDlg::btOK_Click(Win::Event& e)
{
	//_____________________________________________________________ Validate
	tr1::wregex regextbxDescr(L"[A-Za-z0-9]+");
	if (tr1::regex_match(tbxDescr.Text, regextbxDescr) == false)
	{
		tbxDescr.ShowBalloonTip(L"Invalid Descr", L"Please provide one or more characters", TTI_ERROR);
		return;
	}
	tr1::wregex regextbxContact_count(L"[1-9][0-9]?");
	if (tr1::regex_match(tbxContact_count.Text, regextbxContact_count) == false)
	{
		tbxContact_count.ShowBalloonTip(L"Invalid Contact Count", L"Please provide a number between 1 and 99", TTI_ERROR);
		return;
	}
	tr1::wregex regextbxSeat_count(L"[1-9][0-9]?");
	if (tr1::regex_match(tbxSeat_count.Text, regextbxSeat_count) == false)
	{
		tbxSeat_count.ShowBalloonTip(L"Invalid Seat Count", L"Please provide a number between 1 and 99", TTI_ERROR);
		return;
	}
	Sql::StringBuilder sb(L"classroom", L"classroom_id", classroom_id);
	sb.Bind(L"descr", tbxDescr);
	sb.Bind(L"contact_count", tbxContact_count);
	sb.Bind(L"seat_count", tbxSeat_count);
	sb.Bind(L"has_projector", ckHas_projector);
	sb.Bind(L"has_tables", ckHas_tables);
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
void ClassroomDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}
