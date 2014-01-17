#include "stdafx.h"  //_____________________________________________ UpDownDlg.cpp
#include "UpDownDlg.h"

void UpDownDlg::Window_Open(Win::Event& e)
{
	Sql::SqlConnection conn;
	//________________________________________________________ ddCareer
	try
	{
		Sql::SqlConnection conn;
		conn.OpenSession(DSN,USERNAME,PASSWORD);
		conn.ExecuteSelect(L"SELECT program_id, career_name FROM program", 200, ddCareer);
		conn.CloseSession();
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	//________________________________________________________ lvModify
	ddCareer.SelectedIndex=0;
	loadSchedule();
}
void UpDownDlg::btAddC_Click(Win::Event& e)
{
	AddCourseUD dlg;
	dlg.current_period=cu_period;
	dlg.BeginDialog(hWnd);
	loadSchedule();
}
void UpDownDlg::btDeleteM_Click(Win::Event& e)
{
	int course_id;
	char group;
	wstring mat;
	int index=lvModify.GetSelectedIndex();
	course_id=lvModify.Items[index].GetData();
	group=(char)lvModify.Items[index][8].GetText()[0];
	mat=lvModify.Items[index][2].GetText();
	if(this->MessageBox(L"Do you want to delete "+mat+L" Group "+lvModify.Items[index][8].GetText(), L"Are you sure?", MB_YESNO | MB_ICONQUESTION)==IDYES)
	{
		wstring cmd;
		Sql::SqlConnection conn;
		Sys::Format(cmd,L"DELETE FROM schedule WHERE period_id=%d AND course_id=%d AND grupo='%c'",cu_period,course_id,group);
		try
		{
			conn.OpenSession(DSN,USERNAME,PASSWORD);
			conn.ExecuteNonQuery(cmd);
			conn.CloseSession();
		}
		catch (Sql::SqlException e)
		{
			this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		}
		loadSchedule();
	}
	else return;
}
void UpDownDlg::btClose_Click(Win::Event& e)
{
	this->EndDialog(TRUE);
}
void UpDownDlg::ddCareer_SelChange(Win::Event& e)
{
	loadSchedule();
}
void UpDownDlg::loadSchedule(void)
{
	wstring cmd;
	lvModify.SetRedraw(false);
	lvModify.Items.DeleteAll();
	lvModify.Cols.DeleteAll();
	lvModify.Cols.Add(0,LVCFMT_LEFT, 100, L"Clave de Prog");
	lvModify.Cols.Add(1,LVCFMT_LEFT, 100, L"Clave de Mat");
	lvModify.Cols.Add(2,LVCFMT_LEFT, 100, L"Materia");
	lvModify.Cols.Add(3,LVCFMT_LEFT, 100, L"Lunes");
	lvModify.Cols.Add(4,LVCFMT_LEFT, 100, L"Martes");
	lvModify.Cols.Add(5,LVCFMT_LEFT, 100, L"Miércoles");
	lvModify.Cols.Add(6,LVCFMT_LEFT, 100, L"Jueves");
	lvModify.Cols.Add(7,LVCFMT_LEFT, 100, L"Viernes");
	lvModify.Cols.Add(8,LVCFMT_LEFT, 100, L"Grupo");
	lvModify.Cols.Add(9,LVCFMT_LEFT, 100, L"Aula");
	lvModify.Cols.Add(10,LVCFMT_LEFT, 100, L"Profesor");
	const int career=ddCareer.GetSelectedIndex();
	int career_id=ddCareer.Items[career].GetData();
	Sys::Format(cmd,L"SELECT s.course_id,p.descr AS 'Clave de Prog', \
		c.course_key AS 'Clave de Mat', \
		c.descr AS Materia, \
		dbo.check_day_s(s.course_id, s.grupo, 1) AS Lunes,\
		dbo.check_day_s(s.course_id, s.grupo, 2) AS Martes,\
		dbo.check_day_s(s.course_id, s.grupo, 3) AS Miércoles,\
		dbo.check_day_s(s.course_id, s.grupo, 4) AS Jueves,\
		dbo.check_day_s(s.course_id, s.grupo, 5) AS Viernes,\
		s.grupo AS Grupo,\
		cl.descr AS Aula,\
		pr.name AS Profe\
	FROM	program p, course c, schedule s, professor pr, prog_course pc, classroom cl\
	WHERE	p.program_id=pc.program_id\
		AND pc.course_id=c.course_id\
		AND c.course_id=s.course_id\
		AND pr.professor_id=s.professor_id\
		AND cl.classroom_id=s.classroom_id\
		AND s.week_day_id BETWEEN 1 AND 2\
		AND s.period_id=%d\
		AND p.program_id=%d",cu_period,career_id);
		
	Sql::SqlConnection conn;
	try
	{
		conn.OpenSession(DSN,USERNAME,PASSWORD);
		conn.ExecuteSelect(cmd,100,lvModify);
		conn.CloseSession();
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	lvModify.SetRedraw(true);
}
