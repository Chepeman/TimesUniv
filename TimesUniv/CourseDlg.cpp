#include "stdafx.h"  //_____________________________________________ CourseDlg.cpp
#include "CourseDlg.h"

void CourseDlg::Window_Open(Win::Event& e)
{
	int lab_id=0,hours=0;
	bool tables;
	this->Text=L"Course";
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		//conn.OpenSession(hWnd, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT lab_id, descr FROM laboratories", 100, ddLab);
		clProgram.Cols.Add(0, LVCFMT_LEFT, 200, L"Program");
		conn.ExecuteSelect(L"SELECT program_id, career_name FROM program ORDER BY program_id", 200, clProgram);
		if (course_id < 0)
		{
			ddLab.SelectedIndex=lab_id;
			return;
		}
		Sys::Format(cmd, L"SELECT course_key, descr, lab_id, need_tables, week_hours FROM course WHERE course_id=%d", course_id);
		conn.ExecuteSelect(cmd);
		//tbxCourse_key.MaxText = 11;
		conn.BindColumn(1, tbxCourse_key, 128);
		//tbxDescr.MaxText = 80;
		conn.BindColumn(2, tbxDescr, 128);
		conn.BindColumn(3, lab_id);
		conn.BindColumn(4, tables);
		tbxWeek_hours.Number=true;
		conn.BindColumn(5, hours);
		if (conn.Fetch() == false)
		{
			this->MessageBox(L"No data was returned", L"Error", MB_OK);
		}

		int id;
		Sys::Format(cmd, L"SELECT program_id FROM prog_course WHERE course_id=%d",course_id);
		conn.ExecuteSelect(cmd);
		conn.BindColumn(1,id);
		while(conn.Fetch())
		{
			clProgram.Items[id-1].Checked=true;
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	ddLab.SelectedIndex=lab_id-1;
	if(tables)ckNeed_tables.Checked=true;
	tbxWeek_hours.SetText(Sys::Convert::ToString(hours));
}
void CourseDlg::btOK_Click(Win::Event& e)
{
	//_____________________________________________________________ Validate
	tr1::wregex regextbxCourse_key(L"[A-Z0-9\.]+");
	if (tr1::regex_match(tbxCourse_key.Text, regextbxCourse_key) == false)
	{
		tbxCourse_key.ShowBalloonTip(L"Invalid Course key", L"Can only use capital letters, numbers and dots", TTI_ERROR);
		return;
	}
	tr1::wregex regextbxDescr(L"[A-Z0-9аимсз\\s]+");
	if (tr1::regex_match(tbxDescr.Text, regextbxDescr) == false)
	{
		tbxDescr.ShowBalloonTip(L"Invalid Description", L"Can only use capital letters andno numbers", TTI_ERROR);
		return;
	}
	Sql::StringBuilder sb(L"course", L"course_id", course_id);
	sb.Bind(L"course_key", tbxCourse_key);
	sb.Bind(L"descr", tbxDescr);
	sb.Bind(L"lab_id", ddLab);
	sb.Bind(L"need_tables", ckNeed_tables);
	sb.Bind(L"week_hours", tbxWeek_hours);
	Sql::SqlConnection conn;
	int rows = 0;
	wstring cmd;
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
		int i,num_prog;
		num_prog=conn.GetInt(L"SELECT COUNT(*) FROM program");
		Sys::Format(cmd,L"DELETE FROM prog_course WHERE course_id=%d",course_id);
		conn.ExecuteNonQuery(cmd);
		for(i=0;i<num_prog;i++)
		{
			if(clProgram.Items[i].Checked)
			{
				Sys::Format(cmd,L"INSERT INTO prog_course VALUES(%d,%d)",i+1,course_id);
				rows = conn.ExecuteNonQuery(cmd);
				if (rows!=1)
				{
					this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of affected rows", MB_OK | MB_ICONERROR);
					return;
				}
			}
		}

	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		return;
	}
	this->EndDialog(TRUE);
}
void CourseDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}
