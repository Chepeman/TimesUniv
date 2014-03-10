#include "stdafx.h"  //_____________________________________________ AddCourseUD.cpp
#include "AddCourseUD.h"

void AddCourseUD::Window_Open(Win::Event& e)
{
	this->Text=L"Add new coourse";
	wstring cmd;
	Sql::SqlConnection conn;
	try
	{
		Sys::Format(cmd, L"SELECT program_id, descr");
		conn.OpenSession(DSN,USERNAME,PASSWORD);
		conn.ExecuteSelect(L"SELECT program_id, career_name FROM program",100, ddCareer);
		conn.ExecuteSelect(L"SELECT classroom_id, descr FROM classroom",100,ddClassroom);
		conn.ExecuteSelect(L" SELECT classtime_id, CONVERT(varchar(15),begin_time,100) + ' - ' + CONVERT(varchar(15),end_time,100) FROM classtime ", 100, ddClasstime);
		conn.CloseSession();
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	ddClassdays.Items.Add(L"Lun-Mie-Vie");
	ddClassdays.Items.Add(L"Mar-Jue");
	if(isEditing==1)
	{
		editingCourse();
	}
	else
	{
		ddClassdays.SelectedIndex=0;
		ddCareer.SelectedIndex=0;
		ddClassroom.SelectedIndex=0;
		ddClasstime.SelectedIndex=0;
		loadByCareer();
	}

	
}
void AddCourseUD::btAccept_Click(Win::Event& e)
{
	if(isEditing!=1)
	{
		int course_id=ddCourse.GetSelectedData();
		int professor_id=ddProfessor.GetSelectedData();
		int classroom_id=ddClassroom.GetSelectedData();
		int week_id=ddClassdays.GetSelectedIndex()+1;
		int classtime_id=ddClasstime.GetSelectedData();
		if(course_id>1 || professor_id>1 || classroom_id>1 || week_id >1 || classtime_id >1)
		{
			this->MessageBox(L"You haven't selected all the required data", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
		wstring cmd;
		char group='A';
		Sql::SqlConnection conn;
		int no_groups;
		try
		{
			conn.OpenSession(DSN, USERNAME, PASSWORD);
			Sys::Format(cmd,L"SELECT COUNT(*) FROM schedule WHERE course_id=%d AND period_id=%d AND week_day_id BETWEEN 1 AND 2",course_id, current_period);
			no_groups=conn.GetInt(cmd);
			group+=no_groups;

			if(week_id==1)
			{
				Sys::Format(cmd, L"INSERT INTO schedule(period_id,professor_id,course_id,grupo,classroom_id,classtime_id,week_day_id)VALUES(%d,%d,%d,'%c',%d,%d,1)",current_period,professor_id,course_id,group, classroom_id,classtime_id);
				conn.ExecuteNonQuery(cmd);
				Sys::Format(cmd, L"INSERT INTO schedule(period_id,professor_id,course_id,grupo,classroom_id,classtime_id,week_day_id)VALUES(%d,%d,%d,'%c',%d,%d,3)",current_period,professor_id,course_id,group, classroom_id,classtime_id);
				conn.ExecuteNonQuery(cmd);
				Sys::Format(cmd, L"INSERT INTO schedule(period_id,professor_id,course_id,grupo,classroom_id,classtime_id,week_day_id)VALUES(%d,%d,%d,'%c',%d,%d,5)",current_period,professor_id,course_id,group, classroom_id,classtime_id);
				conn.ExecuteNonQuery(cmd);
			}
			else
			{
				Sys::Format(cmd, L"INSERT INTO schedule(period_id,professor_id,course_id,grupo,classroom_id,classtime_id,week_day_id)VALUES(%d,%d,%d,'%c',%d,%d,2)",current_period,professor_id,course_id,group, classroom_id,classtime_id);
				conn.ExecuteNonQuery(cmd);
				Sys::Format(cmd, L"INSERT INTO schedule(period_id,professor_id,course_id,grupo,classroom_id,classtime_id,week_day_id)VALUES(%d,%d,%d,'%c',%d,%d,4)",current_period,professor_id,course_id,group, classroom_id,classtime_id);
				conn.ExecuteNonQuery(cmd);
			}
			conn.CloseSession();
		}
		catch (Sql::SqlException e)
		{
			this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		}
	}
	else
	{
		classroom_id=ddClassroom.GetSelectedData();
		classtime_id=ddClasstime.GetSelectedData();
		wstring cmd;
		int rows=0;
		Sql::SqlConnection conn;
		try
		{
			conn.OpenSession(DSN, USERNAME, PASSWORD);
			Sys::Format(cmd, L"SELECT COUNT(*) FROM schedule WHERE professor_id=%d AND classtime_id=%d",professor_id,classtime_id);
			rows=conn.GetInt(cmd);
			if(rows>0)
			{
				this->MessageBoxW(L"This Professor is already teaching at this hour", L"Error", MB_OK | MB_ICONERROR);
				return;
			}

			Sys::Format(cmd, L"SELECT COUNT(*) FROM schedule WHERE classroom_id=%d AND classtime_id=%d",classroom_id,classtime_id);
			rows=conn.GetInt(cmd);
			if(rows>0)
			{
				this->MessageBoxW(L"This CLassroom is already occupied", L"Error", MB_OK | MB_ICONERROR);
				return;
			}


			Sys::Format(cmd, L"SELECT isbase FROM professor WHERE professor_id=%d",professor_id);
			rows=conn.GetInt(cmd);
			if(rows==1 && classtime_id>=5)
			{
				this->MessageBoxW(L"This Professor is fulltime", L"Error", MB_OK | MB_ICONERROR);
				return;
			}

			Sys::Format(cmd, L"UPDATE schedule SET classroom_id=%d WHERE course_id=%d AND grupo='%c'",classroom_id,course_id,grupo);
			conn.ExecuteNonQuery(cmd);

			Sys::Format(cmd, L"UPDATE schedule SET classtime_id=%d WHERE course_id=%d AND grupo='%c'",classtime_id,course_id,grupo);
			conn.ExecuteNonQuery(cmd);

			conn.CloseSession();
		}
		catch (Sql::SqlException e)
		{
			this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		}

	}
	this->EndDialog(TRUE);
}
void AddCourseUD::btCancel_Click(Win::Event& e)
{
	this->EndDialog(TRUE);
}
void AddCourseUD::loadByCareer(void)
{
	int program=ddCareer.GetSelectedData();
	Sql::SqlConnection conn;
	wstring cmd;
	ddCourse.Items.DeleteAll();
	ddProfessor.Items.DeleteAll();
	int dept;
	Sys::Format(cmd,L"SELECT c.course_id, c.descr\
						FROM course c, prog_course pg, program p\
						WHERE c.course_id=pg.course_id\
							AND pg.program_id=p.program_id\
							AND p.program_id=%d", program);
	try
	{
		conn.OpenSession(DSN,USERNAME,PASSWORD);
		conn.ExecuteSelect(cmd, 100, ddCourse);
		Sys::Format(cmd,L"SELECT department_id FROM program WHERE program_id=%d",program);
		dept=conn.GetInt(cmd);
		if(dept!=1)
		{
			Sys::Format(cmd,L"SELECT p.professor_id, p.last_name_p+' '+p.last_name_m+', '+p.name\
					  FROM professor p, department d, program pg\
					  WHERE p.department_id=d.department_id AND pg.department_id=d.department_id AND pg.program_id=%d\
					  ORDER BY p.last_name_p",program);
		}
		else
		{
			Sys::Format(cmd,L"SELECT p.professor_id, p.last_name_p+' '+p.last_name_m+', '+p.name\
						    FROM professor p ORDER BY p.last_name_p");
		}
        conn.ExecuteSelect(cmd, 100, ddProfessor);
		conn.CloseSession();
	}
	catch (Sql::SqlException e)
	{
		
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		
	}
	ddCourse.SelectedIndex=0;
	ddProfessor.SelectedIndex=0;
}
void AddCourseUD::ddCareer_SelChange(Win::Event& e)
{
	loadByCareer();
}

void AddCourseUD::editingCourse(void)
{
	this->SetWindowTextW(L"Edit Course");
	btAccept.SetText(L"Update");
	ddCareer.SetSelectedByData(career_id);
	loadByCareer();
	ddCourse.SetSelectedByData(course_id);
	ddProfessor.SetSelectedByData(professor_id);
	ddClassroom.SetSelectedByData(classroom_id);
	ddClasstime.SetSelectedByData(classtime_id);
	if(classdays_id==1)
		ddClassdays.SetSelected(0);
	else
		ddClassdays.SetSelected(1);
	ddClassdays.SetEnable(false);
	ddCourse.SetEnable(false);
	ddProfessor.SetEnable(false);
	ddCareer.SetEnable(false);
}