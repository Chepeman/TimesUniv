#include "stdafx.h"  //_____________________________________________ CoordDlg.cpp
#include "CoordDlg.h"

void CoordDlg::Window_Open(Win::Event& e)
{
	this->Text=L"Coordinator Insert/Edit";

	int prof_id;
	wstring cmd;
	Sql::SqlConnection conn;
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		//conn.OpenSession(hWnd, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT program_id, descr FROM program", 100, ddProgram);
		ddProgram.SelectedIndex=0;
		UpdateddProf();
		if (coordinator_id < 0) return;
		Sys::Format(cmd, L"SELECT professor_id, program_id, username, pass, isAdmin FROM coordinator WHERE coordinator_id=%d", coordinator_id);
		conn.ExecuteSelect(cmd);
		conn.BindColumn(1, ddProfessor);
		conn.BindColumn(2, ddProgram);
		//tbxUsername.MaxText = 13;
		conn.BindColumn(3, tbxUsername, 128);
		//tbxPass.MaxText = 13;
		conn.BindColumn(4, tbxPass, 128);
		conn.BindColumn(5, ckIsadmin);
		if (conn.Fetch() == false)
		{
			this->MessageBox(L"No data was returned", L"Error", MB_OK);
		}
		UpdateddProf();
		Sys::Format(cmd, L"SELECT professor_id FROM coordinator WHERE coordinator_id=%d", coordinator_id);
		prof_id=conn.GetInt(cmd);
		ddProfessor.SelectedData=prof_id;
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}
void CoordDlg::btOK_Click(Win::Event& e)
{
	//_____________________________________________________________ Validate
	tr1::wregex regextbxUsername(L"[A-Za-z0-9][A-Za-z0-9][A-Za-z0-9][A-Za-z0-9]+");
	if (tr1::regex_match(tbxUsername.Text, regextbxUsername) == false)
	{
		tbxUsername.ShowBalloonTip(L"Invalid Username", L"Please provide four or more alphanumeric characters (A-Z, a-z or 0-9)", TTI_ERROR);
		return;
	}
	tr1::wregex regextbxPass(L"[A-Za-z0-9][A-Za-z0-9][A-Za-z0-9]+");
	if (tr1::regex_match(tbxPass.Text, regextbxPass) == false)
	{
		tbxPass.ShowBalloonTip(L"Invalid Pass", L"Please provide three or more alphanumeric characters (A-Z, a-z or 0-9)", TTI_ERROR);
		return;
	}
	Sql::StringBuilder sb(L"coordinator", L"coordinator_id", coordinator_id);
	sb.Bind(L"professor_id", ddProfessor);
	sb.Bind(L"program_id", ddProgram);
	sb.Bind(L"username", tbxUsername);
	sb.Bind(L"pass", tbxPass);
	sb.Bind(L"isAdmin", ckIsadmin);
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
void CoordDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}
void CoordDlg::UpdateddProf()
{
	ddProfessor.SetRedraw(false);
	ddProfessor.Items.DeleteAll();
	wstring cmd;
	int program_id;
	program_id=ddProgram.SelectedData;

	Sql::SqlConnection conn;
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		//conn.OpenSession(hWnd, CONNECTION_STRING);
		Sys::Format(cmd, L"SELECT p.professor_id, p.last_name_p+' '+p.last_name_m+', '+p.name AS Prof\
						  FROM professor p, department d, program pg\
						  WHERE p.department_id=d.department_id\
								AND d.department_id=pg.department_id\
								AND pg.program_id=%d\
								ORDER BY Prof", program_id);
		conn.ExecuteSelect(cmd, 100, ddProfessor);
		//ddProfessor.SelectedIndex=0;
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	ddProfessor.SetRedraw(true);
}
void CoordDlg::ddProgram_SelChange(Win::Event& e)
{
	UpdateddProf();
}
