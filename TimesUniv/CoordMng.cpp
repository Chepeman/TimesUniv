#include "stdafx.h"  //_____________________________________________ CoordMng.cpp
#include "CoordMng.h"

void CoordMng::Window_Open(Win::Event& e)
{
	this->AlwaysOnTop(true);
	wstring cmd;
	//________________________________________________________ lvProfessor
	lvProfessor.Cols.Add(0, LVCFMT_LEFT, 250, L"Name");
	lvProfessor.Cols.Add(1, LVCFMT_RIGHT, 150, L"Email");
	lvProfessor.Cols.Add(2, LVCFMT_RIGHT, 80, L"Extension");
	//________________________________________________________ lvCourse
	lvCourse.Cols.Add(0, LVCFMT_LEFT, 150, L"Course Key");
	lvCourse.Cols.Add(1, LVCFMT_LEFT, 300, L"Course");
	try
	{
		Sql::SqlConnection conn;
		conn.OpenSession(DSN,USERNAME,PASSWORD);
		Sys::Format(cmd,L"SELECT p.professor_id,p.last_name_p+' '+p.last_name_m+', '+p.name,p.email,p.extension FROM professor p, program pr, department d \
						 WHERE p.department_id=d.department_id AND d.department_id=pr.department_id AND pr.program_id=%d ",career_id);
		conn.ExecuteSelect(cmd, 100, lvProfessor);
		Sys::Format(cmd,L"SELECT c.course_id, c.course_key, c.descr FROM course c, prog_course pc, program p WHERE c.course_id=pc.course_id AND pc.program_id=p.program_id AND pc.program_id=%d",career_id);
		conn.ExecuteSelect(cmd, 100, lvCourse);
		conn.ExecuteSelect(L"SELECT * FROM period ORDER BY period_id DESC", 100, ddPeriod);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	this->Text=L"Welcome Coordinator";
	ddPeriod.SelectedIndex=0;
	loadAssignments();
}
void CoordMng::Window_Close(Win::Event& e)
{
	this->EndDialog(TRUE);
}
void CoordMng::btAdd_Click(Win::Event& e)
{
	//_____________________________________________________________ Validate
	tr1::wregex regextbxCupo(L"[1-9][0-9]?");
	if (tr1::regex_match(tbxCupo.Text, regextbxCupo) == false)
	{
		tbxCupo.ShowBalloonTip(L"Invalid Quota", L"Please provide a number between 1 and 99", TTI_ERROR);
		return;
	}
	wstring cmd;
	char group='A';
	int course_id,professor_id,period_id,cupo,no_groups,rows,coord_id;

	const int course=lvCourse.GetSelectedIndex();
	if(course<0)
	{
		this->MessageBox(L"You have not selected a course",L"Invalid Course",MB_ICONERROR);
		return;
	}
	course_id=lvCourse.Items[course].Data;

	const int professor=lvProfessor.GetSelectedIndex();
	if(professor<0)
	{
		this->MessageBox(L"You have not selected a professor",L"Invalid Professor",MB_ICONERROR);
		return;
	}
	professor_id=lvProfessor.Items[professor].Data;

	const int period=ddPeriod.GetSelectedIndex();
	if(period<0)
	{
		this->MessageBox(L"You have not selected a period",L"Invalid Period",MB_ICONERROR);
		return;
	}
	period_id=ddPeriod.GetSelectedData();

	cupo=tbxCupo.GetInt();
	if(cupo<5 || cupo==0)
	{
		tbxCupo.ShowBalloonTip(L"Invalid Quota", L"The quota must be greater than 5", TTI_ERROR);
		return;
	}

	Sql::SqlConnection conn;
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		//conn.OpenSession(hWnd, CONNECTION_STRING);

		Sys::Format(cmd,L"SELECT COUNT(*) FROM assignment WHERE course_id=%d",course_id);
		no_groups=conn.GetInt(cmd);

		group+=no_groups;

		Sys::Format(cmd,L"SELECT coordinator_id FROM coordinator WHERE program_id=%d",career_id);
		coord_id=conn.GetInt(cmd);
		
		Sys::Format(cmd,L"INSERT INTO assignment VALUES(%d,%d,%d,%d,'%c',%d)",course_id,professor_id,period_id,cupo,group,coord_id);
		rows = conn.ExecuteNonQuery(cmd);
		if (rows!=1)
		{
			this->MessageBox(L"Registration could not be admitted", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	loadAssignments();
}
void CoordMng::btDelete_Click(Win::Event& e)
{
	Win::HourGlassCursor hgc(true);
	const int index=lvAsign.GetSelectedIndex();
	if (index<0)return;
	if (this->MessageBox(L"Are you sure you want to delete the selected record?",
		L"Delete Record", MB_YESNO | MB_ICONQUESTION) != IDYES) return;

	Sql::SqlConnection conn;
	wstring cmd;
	int coord_id=0;

	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		//conn.OpenSession(hWnd, CONNECTION_STRING);

		Sys::Format(cmd,L"SELECT coordinator_id FROM coordinator WHERE program_id=%d",career_id);
		coord_id=conn.GetInt(cmd);

		Sys::Format(cmd,L"SELECT property FROM assignment WHERE course_id=%d AND professor_id=%d AND period_id=%d AND grupo='%c'",
		assign[index].course_id,assign[index].professor_id,assign[index].period_id,assign[index].group[0]);
		if(coord_id!=conn.GetInt(cmd))
		{
			this->MessageBox(L"You're not allowed to delete this record", L"Error", MB_OK | MB_ICONERROR);
			return;
		}

		Sys::Format(cmd,L"DELETE FROM assignment WHERE course_id=%d AND professor_id=%d AND period_id=%d AND grupo='%c'",
		assign[index].course_id,assign[index].professor_id,assign[index].period_id,assign[index].group[0]);
		int rows = conn.ExecuteNonQuery(cmd);
		if (rows!=1)
		{
			this->MessageBox(L"Delete could not be admitted", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
		Sys::Format(cmd,L"SELECT COUNT(*) FROM perturbation WHERE course_id=%d AND grupo='%c'",assign[index].course_id,assign[index].group[0]);
		rows = conn.GetInt(cmd);
		if (rows==1)
		{
			Sys::Format(cmd,L"DELETE FROM perturbation WHERE course_id=%d AND grupo='%c'",assign[index].course_id,assign[index].group[0]);
			int rows = conn.ExecuteNonQuery(cmd);
			if (rows!=1)
			{
				this->MessageBox(L"Delete could not be admitted on perturbation", L"Error", MB_OK | MB_ICONERROR);
				return;
			}
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	assign.clear();
	loadAssignments();
}
void CoordMng::btClose_Click(Win::Event& e)
{
	this->EndDialog(TRUE);
}
void CoordMng::ddPeriod_SelChange(Win::Event& e)
{
	loadAssignments();
}
void CoordMng::loadAssignments()
{
	lvAsign.SetRedraw(false);
	lvAsign.Items.DeleteAll();
	lvAsign.Cols.DeleteAll();
	lvAsign.Cols.Add(0, LVCFMT_LEFT, 100, L"Course Key");
	lvAsign.Cols.Add(1, LVCFMT_LEFT, 200, L"Course");
	lvAsign.Cols.Add(2, LVCFMT_LEFT, 200, L"Professor");
	lvAsign.Cols.Add(3, LVCFMT_RIGHT, 60, L"Quota");
	lvAsign.Cols.Add(4, LVCFMT_RIGHT, 60, L"Group");

	Assign aux;
	wchar_t course_key[16],course[64],professor[256];
	int index=0,quota=0,period_id=ddPeriod.SelectedData;

	Sql::SqlConnection conn;
	wstring cmd;
	Sys::Format(cmd,L"SELECT c.course_id, p.professor_id, pe.period_id, c.course_key, c.descr,p.last_name_p+' '+ p.last_name_m+', '+p.name, a.cupo, a.grupo \
					  FROM assignment a, professor p, course c, prog_course pc, program pr, period pe\
					  WHERE a.course_id=c.course_id AND a.professor_id=p.professor_id AND a.period_id=pe.period_id AND c.course_id=pc.course_id \
					        AND pc.program_id=pr.program_id AND pc.program_id=%d AND a.period_id=%d", career_id, period_id);
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD);
		conn.ExecuteSelect(cmd);
		conn.BindColumn(1,aux.course_id);
		conn.BindColumn(2,aux.professor_id);
		conn.BindColumn(3,aux.period_id);
		conn.BindColumn(4,course_key,16);
		conn.BindColumn(5,course,64);
		conn.BindColumn(6,professor,128);
		conn.BindColumn(7,quota);
		conn.BindColumn(8,aux.group,2);

		while (conn.Fetch())
		{
			assign.push_back(aux);
			lvAsign.Items.Add(index,course_key,index);
			lvAsign.Items[index][1].Text=course;
			lvAsign.Items[index][2].Text=professor;
			lvAsign.Items[index][3].Text=Sys::Convert::ToString(quota);
			lvAsign.Items[index][4].Text=aux.group;
			index++;
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	lvAsign.SetRedraw(true);
}
void CoordMng::lvAsign_DblClk(Win::Event& e)
{
	btDelete_Click(e);
}