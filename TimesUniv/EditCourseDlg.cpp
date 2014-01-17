#include "stdafx.h"  //_____________________________________________ EditCourseDlg.cpp
#include "EditCourseDlg.h"

void EditCourseDlg::Window_Open(Win::Event& e)
{
	wchar_t course[80], professor[80], classroom[70], grupo[2];
	int cupo=-1, classtime=-1;
	//________________________________________________________ ddHours

	Sql::SqlConnection conn;
	wstring cmd;
	Sys::Format(cmd, L"SELECT c.descr, p.last_name_p+' '+p.last_name_m+', '+p.name,cl.descr, pt.grupo, a.cupo, ca.classtime_id \
					  FROM course c, professor p, perturbation pt, assignment a, classroom cl, course_time ct, classtime ca \
					  WHERE pt.classroom_id=cl.classroom_id \
					  AND c.course_id=a.course_id \
					  AND pt.course_id=c.course_id \
					  AND p.professor_id=pt.professor_id \
					  AND p.professor_id=a.professor_id \
					  AND pt.grupo=a.grupo \
					  AND pt.grupo=ct.grupo \
					  AND c.course_id=ct.course_id \
					  AND ca.classtime_id=ct.classtime_id \
					  AND c.course_id=%d \
					  AND p.professor_id=%d \
					  AND cl.classroom_id=%d \
					  AND pt.grupo='%c';", course_id, professor_id, classroom_id, group);
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD);
		conn.ExecuteSelect(cmd);
		conn.BindColumn(1, course, 80);
		conn.BindColumn(2, professor,80);
		conn.BindColumn(3, classroom, 70);
		conn.BindColumn(4, grupo, 2);
		conn.BindColumn(5, cupo);
		conn.BindColumn(6, classtime);
		conn.Fetch();

		Sys::Format(cmd, L"SELECT classroom_id, descr FROM classroom ");
		conn.ExecuteSelect(cmd,100, ddClassroom);

		Sys::Format(cmd, L" SELECT classtime_id, CONVERT(varchar(15),begin_time,100) + ' - ' + CONVERT(varchar(15),end_time,100) FROM classtime ");
		conn.ExecuteSelect(cmd, 100, ddHours);

		Sys::Format(cmd, L"SELECT week_hours FROM course WHERE course_id=%d", course_id);
		classhours=conn.GetInt(cmd);
		conn.CloseSession();
	}
	catch(Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}

	tbxCourse.Text+=course;
	tbxProfessor.Text+=professor;
	tbxGroup.Text+=grupo;
	tbxQuota.Text=Sys::Convert::ToString(cupo);
	tbxError.Text=errorDescr;
	//________________________________________________________ ddClassroom
	ddClassroom.SetSelectedByData(classroom_id);
	ddHours.SetSelectedByData(classtime);
}
void EditCourseDlg::btOk_Click(Win::Event& e)
{
	int rows=-1;
	int hor=ddHours.GetSelectedIndex();
	if(hor<0)return;
	int classtime_id=ddHours.GetSelectedData();
	int clroom=ddClassroom.GetSelectedIndex();
	int cupo=tbxQuota.GetInt();
	if(clroom<0)return;
	int clasroom_id=ddClassroom.GetSelectedData();
	Sql::SqlConnection conn;
	wstring cmd;
	Sys::Format(cmd,L"UPDATE perturbation SET classroom_id=%d WHERE course_id=%d AND grupo='%c'",clasroom_id,course_id,group);
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD);
		rows=conn.ExecuteNonQuery(cmd);
		if (rows!=1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of affected rows", MB_OK | MB_ICONERROR);
			return;
		}
		Sys::Format(cmd,L"UPDATE assignment SET cupo=%d WHERE course_id=%d AND grupo='%c' AND period_id=%d",cupo,course_id,group,period_id);
		conn.ExecuteNonQuery(cmd);
		if (rows!=1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of affected rows", MB_OK | MB_ICONERROR);
			return;
		}
		if(classhours==4)
		{
			Sys::Format(cmd,L"UPDATE course_time SET classtime_id=%d WHERE course_id=%d AND grupo='%c' AND week_day_id=2",classtime_id, course_id, group);
			conn.ExecuteNonQuery(cmd);
			if (rows!=1)
			{
				this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of affected rows", MB_OK | MB_ICONERROR);
				return;
			}
			Sys::Format(cmd,L"UPDATE course_time SET classtime_id=%d WHERE course_id=%d AND grupo='%c' AND week_day_id=4",classtime_id, course_id, group);
			conn.ExecuteNonQuery(cmd);
			if (rows!=1)
			{
				this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of affected rows", MB_OK | MB_ICONERROR);
				return;
			}

		}
		else
		{
			Sys::Format(cmd,L"UPDATE course_time SET classtime_id=%d WHERE course_id=%d AND grupo='%c' AND week_day_id=1",classtime_id, course_id, group);
			conn.ExecuteNonQuery(cmd);
			if (rows!=1)
			{
				this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of affected rows", MB_OK | MB_ICONERROR);
				return;
			}
			Sys::Format(cmd,L"UPDATE course_time SET classtime_id=%d WHERE course_id=%d AND grupo='%c' AND week_day_id=3",classtime_id, course_id, group);
			conn.ExecuteNonQuery(cmd);
			if (rows!=1)
			{
				this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of affected rows", MB_OK | MB_ICONERROR);
				return;
			}
			Sys::Format(cmd,L"UPDATE course_time SET classtime_id=%d WHERE course_id=%d AND grupo='%c' AND week_day_id=5",classtime_id, course_id, group);
			conn.ExecuteNonQuery(cmd);
			if (rows!=1)
			{
				this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of affected rows", MB_OK | MB_ICONERROR);
				return;
			}
		}
	}
	catch(Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	this->EndDialog(TRUE);
}
void EditCourseDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}
