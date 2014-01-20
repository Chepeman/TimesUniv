#include "stdafx.h"  //_____________________________________________ ProfDlg.cpp
#include "ProfDlg.h"

void ProfDlg::Window_Open(Win::Event& e)
{
	int dept_id=0;
	bool promep,sni;
	this->Text=L"Professor";
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		//conn.OpenSession(hWnd, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT department_id, descr FROM department ORDER BY department_id", 100, ddDepartment);
		clDays.Cols.Add(0, LVCFMT_LEFT, 100, L"Day");
		conn.ExecuteSelect(L"SELECT * FROM week_day ORDER BY week_day_id", 100, clDays);
		clHours.Cols.Add(0, LVCFMT_LEFT, 100, L"Hours");
		conn.ExecuteSelect(L"SELECT classtime_id, CONVERT(varchar(15),begin_time,100) + ' - ' + CONVERT(varchar(15),end_time,100)\
							 FROM classtime ORDER BY classtime_id", 100, clHours);
		if (professor_id < 0)
		{
			ddDepartment.SelectedIndex=dept_id;
			return;
		}
		Sys::Format(cmd, L"SELECT last_name_p, last_name_m, name, email, extension, department_id, promep, sni FROM professor WHERE professor_id=%d", professor_id);
		conn.ExecuteSelect(cmd);
		//tbxLast_name_p.MaxText = 20;
		conn.BindColumn(1, tbxLast_name_p, 128);
		//tbxLast_name_m.MaxText = 20;
		conn.BindColumn(2, tbxLast_name_m, 128);
		//tbxName.MaxText = 40;
		conn.BindColumn(3, tbxName, 128);
		//tbxEmail.MaxText = 60;
		conn.BindColumn(4, tbxEmail, 128);
		tbxExtension.Number=true;
		conn.BindColumn(5, tbxExtension, 128);
		conn.BindColumn(6, dept_id);
		conn.BindColumn(7, promep);
		conn.BindColumn(8, sni);
		if (conn.Fetch() == false)
		{
			this->MessageBox(L"No data was returned", L"Error", MB_OK);
		}
		
		int id;
		Sys::Format(cmd,L"SELECT week_day_id FROM time_prof WHERE professor_id=%d GROUP BY week_day_id",professor_id);
		conn.ExecuteSelect(cmd);
		conn.BindColumn(1,id);
		while(conn.Fetch())
		{
			clDays.Items[id-1].Checked=true;
		}
		Sys::Format(cmd,L"SELECT classtime_id FROM time_prof WHERE professor_id=%d GROUP BY classtime_id",professor_id);
		conn.ExecuteSelect(cmd);
		conn.BindColumn(1,id);
		while(conn.Fetch())
		{
			clHours.Items[id-1].Checked=true;
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	ddDepartment.SelectedIndex=dept_id-1;
	if(promep)ckPromep.Checked=true;
	if(sni)ckSni.Checked=true;
}
void ProfDlg::btOK_Click(Win::Event& e)
{
	//_____________________________________________________________ Validate
	/*tr1::wregex regextbxLast_name_p(L"[A-Za-z0-9]+");
	if (tr1::regex_match(tbxLast_name_p.Text, regextbxLast_name_p) == false)
	{
		tbxLast_name_p.ShowBalloonTip(L"Invalid Last name p", L"Please provide one or more characters", TTI_ERROR);
		return;
	}
	tr1::wregex regextbxLast_name_m(L"[A-Za-z0-9]+");
	if (tr1::regex_match(tbxLast_name_m.Text, regextbxLast_name_m) == false)
	{
		tbxLast_name_m.ShowBalloonTip(L"Invalid Last name m", L"Please provide one or more characters", TTI_ERROR);
		return;
	}
	tr1::wregex regextbxName(L"[A-Za-z0-9]+");
	if (tr1::regex_match(tbxName.Text, regextbxName) == false)
	{
		tbxName.ShowBalloonTip(L"Invalid Name", L"Please provide one or more characters", TTI_ERROR);
		return;
	}
	tr1::wregex regextbxEmail(L"[A-Za-z0-9]+");
	if (tr1::regex_match(tbxEmail.Text, regextbxEmail) == false)
	{
		tbxEmail.ShowBalloonTip(L"Invalid Email", L"Please provide one or more characters", TTI_ERROR);
		return;
	}*/
	Sql::StringBuilder sb(L"professor", L"professor_id", professor_id);
	sb.Bind(L"last_name_p", tbxLast_name_p);
	sb.Bind(L"last_name_m", tbxLast_name_m);
	sb.Bind(L"name", tbxName);
	sb.Bind(L"email", tbxEmail);
	sb.Bind(L"extension", tbxExtension);
	sb.Bind(L"department_id", ddDepartment);
	sb.Bind(L"promep", ckPromep);
	sb.Bind(L"sni", ckSni);
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
		if(professor_id==-1)professor_id=conn.GetInt(L"SELECT SCOPE_IDENTITY() FROM professor");
		
		int i, j, days, hours, day_id, hour_id;
		days=conn.GetInt(L"SELECT COUNT(*) FROM week_day");
		hours=conn.GetInt(L"SELECT COUNT(*) FROM classtime");
		Sys::Format(cmd,L"DELETE FROM time_prof WHERE professor_id=%d",professor_id);
		conn.ExecuteNonQuery(cmd);
		for(i=0;i<days;i++)
		{
			if(clDays.Items[i].Checked)
			{
				day_id=clDays.Items[i].Data;
				for(j=0;j<hours;j++)
				{
					if(clHours.Items[j].Checked)
					{
						hour_id=clHours.Items[j].Data;
						Sys::Format(cmd,L"INSERT INTO time_prof VALUES(%d,%d,%d)",professor_id,hour_id,day_id);
						rows = conn.ExecuteNonQuery(cmd);
						if (rows!=1)
						{
							this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of affected rows", MB_OK | MB_ICONERROR);
							return;
						}
					}
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
void ProfDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}
