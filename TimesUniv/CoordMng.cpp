#include "stdafx.h"  //_____________________________________________ CoordMng.cpp
#include "CoordMng.h"

void CoordMng::Window_Open(Win::Event& e)
{
	this->AlwaysOnTop(true);
	int dept;
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
		Sys::Format(cmd,L"SELECT department_id FROM program WHERE program_id=%d",career_id);
		dept=conn.GetInt(cmd);
		if(dept!=1)
		{
			Sys::Format(cmd,L"SELECT p.professor_id,p.last_name_p+' '+p.last_name_m+', '+p.name,p.email,p.extension FROM professor p, program pr, department d \
						 WHERE p.department_id=d.department_id AND d.department_id=pr.department_id AND pr.program_id=%d ORDER BY p.last_name_p",career_id);
		}
		else
		{
			Sys::Format(cmd,L"SELECT p.professor_id,p.last_name_p+' '+p.last_name_m+', '+p.name,p.email,p.extension FROM professor p ORDER BY p.last_name_p");
		}
		conn.ExecuteSelect(cmd, 100, lvProfessor);
		Sys::Format(cmd,L"SELECT c.course_id, c.course_key, c.descr FROM course c, prog_course pc, program p WHERE c.course_id=pc.course_id AND pc.program_id=p.program_id AND pc.program_id=%d",career_id);
		conn.ExecuteSelect(cmd, 100, lvCourse);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	this->Text=L"Welcome Coordinator";
	loadAssignments();
	LoadPeriod();
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
		tbxCupo.ShowBalloonTip(L"Invalid Quota", L"Please provide a number between 5 and 99", TTI_ERROR);
		return;
	}
	wstring cmd;
	char group='A';
	int course_id,professor_id,period_id,cupo,no_groups,rows,coord_id,count;

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

	const int period=1;
	period_id=1;

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
		Sys::Format(cmd, L"SELECT COUNT(*) FROM schedule WHERE period_id=%d", period_id);
		count=conn.GetInt(cmd);
		if(count>0)
		{
			this->MessageBox(L"Schedule of this period already been generated", L"Registration could not be admitted", MB_OK | MB_ICONERROR);
			return;
		}

		Sys::Format(cmd, L"SELECT COUNT(*) FROM assignment WHERE professor_id=%d AND course_id=%d", professor_id, course_id);
		count=conn.GetInt(cmd);
		if(count>0)
		{
			Sys::Format(cmd,L"There are %d group(s) of this course with that professor, sure you want to add another?",count);
			if(this->MessageBox(cmd, L"Already exists", MB_YESNO | MB_ICONQUESTION)==IDNO) return;
		}
		
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
void CoordMng::btSched_Click(Win::Event& e)
{
}
void CoordMng::btDelete_Click(Win::Event& e)
{
	int period_id=1, count=0;
	wstring cmd;

	Sql::SqlConnection conn;
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); 
		Sys::Format(cmd, L"SELECT COUNT(*) FROM schedule WHERE period_id=%d", period_id);
		count=conn.GetInt(cmd);
		if(count>0)
		{
			this->MessageBox(L"Schedule of this period already been generated", L"Registration could not be admitted", MB_OK | MB_ICONERROR);
			return;
		}
		conn.CloseSession();
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}

	Win::HourGlassCursor hgc(true);
	const int index=lvAsign.GetSelectedIndex();
	if (index<0)return;
	if (this->MessageBox(L"Are you sure you want to delete the selected record?",
		L"Delete Record", MB_YESNO | MB_ICONQUESTION) != IDYES) return;

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

	wstring cmd;
	int count=0;
	const int period=1;
	if(period<0)return;
	Sql::SqlConnection conn;
	try
	{
		Sys::Format(cmd, L"SELECT COUNT(*) FROM schedule WHERE period_id=%d", period);
		conn.OpenSession(DSN, USERNAME, PASSWORD);
		count=conn.GetInt(cmd);
		conn.CloseSession();
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	
	Assign aux;
	wchar_t course_key[16],course[64],professor[256];
	int index=0,quota=0,period_id=1;
	if(count<1)
	{
		Sys::Format(cmd,L"SELECT c.course_id, p.professor_id, pe.period_id, c.course_key, c.descr,p.last_name_p+' '+ p.last_name_m+', '+p.name, a.cupo, a.grupo \
					  FROM assignment a, professor p, course c, prog_course pc, program pr, period pe\
					  WHERE a.course_id=c.course_id AND a.professor_id=p.professor_id AND a.period_id=pe.period_id AND c.course_id=pc.course_id \
					        AND pc.program_id=pr.program_id AND pc.program_id=%d AND a.period_id=%d", career_id, period_id);
	}
	else
	{
		Sys::Format(cmd,L"SELECT s.course_id, s.professor_id, s.period_id, c.course_key, c.descr, p.last_name_p+' '+ p.last_name_m+', '+p.name, 0, s.grupo \
					  FROM schedule s, professor p, course c, prog_course pc, program pr, period pe\
					  WHERE s.course_id=c.course_id AND s.professor_id=p.professor_id AND s.period_id=pe.period_id AND c.course_id=pc.course_id \
					        AND pc.program_id=pr.program_id AND s.week_day_id BETWEEN 1 AND 2 AND pc.program_id=%d AND s.period_id=%d", career_id, period_id);
	}
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
			if(count<1)lvAsign.Items[index][3].Text=Sys::Convert::ToString(quota);
			else lvAsign.Items[index][3].Text=L"Don't Apply";
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
void CoordMng::LoadPeriod()
{
	Sql::SqlConnection conn;
	int rows = 0;
	wstring period, descr, date1, date2;

	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.GetString(L"SELECT descr FROM period WHERE period_id = 1", descr, 100);
		conn.GetString(L"SELECT CONVERT(NVARCHAR(14), begin_date, 107) FROM period WHERE period_id = 1", date1, 100);
		conn.GetString(L"SELECT CONVERT(NVARCHAR(14), end_date, 107) FROM period WHERE period_id = 1", date2, 100);
		conn.CloseSession();
		
		period+=descr;
		period+=L"\t(";
		period+=date1;
		period+=L"  -  ";
		period+=date2;
		period+=L")";
		tbxPeriod.SetText(period);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		return;
	}
}
void CoordMng::lvAsign_DblClk(Win::Event& e)
{
	btDelete_Click(e);
}