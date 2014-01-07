#include "stdafx.h"  //_____________________________________________ ScheduleDlg.cpp
#include "ScheduleDlg.h"

void ScheduleDlg::Window_Open(Win::Event& e)
{
	this->SetText(L"Academic Schedule");
	//________________________________________________________ lvSchedule
	Sql::SqlConnection conn;
	try
	{
		lvSchedule.Cols.Add(0,LVCFMT_LEFT, 100, L"Clave de seloseProg");
		lvSchedule.Cols.Add(1,LVCFMT_LEFT, 100, L"Clave de Mat");
		lvSchedule.Cols.Add(2,LVCFMT_LEFT, 100, L"Materia");
		lvSchedule.Cols.Add(3,LVCFMT_LEFT, 100, L"Lunes");
		lvSchedule.Cols.Add(4,LVCFMT_LEFT, 100, L"Martes");
		lvSchedule.Cols.Add(5,LVCFMT_LEFT, 100, L"Miércoles");
		lvSchedule.Cols.Add(6,LVCFMT_LEFT, 100, L"Jueves");
		lvSchedule.Cols.Add(7,LVCFMT_LEFT, 100, L"Viernes");
		lvSchedule.Cols.Add(8,LVCFMT_LEFT, 100, L"Grupo");
		lvSchedule.Cols.Add(9,LVCFMT_LEFT, 100, L"Aula");
		lvSchedule.Cols.Add(10,LVCFMT_LEFT, 100, L"Profesor");

		conn.OpenSession(DSN, USERNAME, PASSWORD);
		conn.ExecuteSelect(L"SELECT * FROM vw_schedule ORDER BY 'Clave de Prog', 'Materia', 'Grupo'",100, lvSchedule);
		conn.CloseSession();
	}
	catch(Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}



void ScheduleDlg::btOk_Click(Win::Event& e)
{
	Sql::SqlConnection conn;
	wstring cmd;
	ScheduleID s;
	Win::FileDlg dlg;
	int ss;
	dlg.Clear();
	dlg.SetFilter(L"Archivos Excel(*.xlsx)\0*.xlsx\0\0",0,L"xlsx");
	if(dlg.BeginDialog(hWnd,L"Exportar a Excel",true))
		lvSchedule.ExportToMsExcel(dlg.GetFileNameFullPath());
	else
	{
		this->MessageBox(L"No fue posible exportar la informacion",L"Exportar a Excel",MB_OK|MB_ICONERROR);
		return;
	}
	
	Sys::Format(cmd, L"SELECT pt.professor_id, pt.course_id, pt.classroom_id, pt.grupo,  ct.classtime_id, ct.week_day_id FROM perturbation pt, course c, course_time ct WHERE c.course_id=pt.course_id  AND c.course_id=ct.course_id AND pt.grupo=ct.grupo;");
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD);
		conn.ExecuteSelect(cmd);
		conn.BindColumn(1, s.professor_id);
		conn.BindColumn(2,s.course_id);
		conn.BindColumn(3, s.classroom_id);
		conn.BindColumn(4, s.grupo,2);
		conn.BindColumn(5, s.classtime);
		conn.BindColumn(6, s.week_day);
		while(conn.Fetch())
			schedule.push_back(s);
		
		ss=schedule.size();

		for(int i=0; i<ss;i++)
		{
			Sys::Format(cmd, L"INSERT INTO schedule (period_id, professor_id, course_id, grupo, classroom_id, classtime_id, week_day_id) VALUES(%d,%d,%d,'%c',%d, %d, %d)",period_id,schedule[i].professor_id,schedule[i].course_id,schedule[i].grupo[0], schedule[i].classroom_id, schedule[i].classtime, schedule[i].week_day);
			conn.ExecuteNonQuery(cmd);
		}

		Sys::Format(cmd,L"DELETE FROM perturbation");
		conn.ExecuteSelect(cmd);
	    Sys::Format(cmd,L"DELETE FROM course_time");
		conn.ExecuteSelect(cmd);
		Sys::Format(cmd,L"DELETE FROM assignment");
		conn.ExecuteSelect(cmd);
		conn.CloseSession();
	}

	catch(Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}

	this->EndDialog(TRUE);
}

void ScheduleDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}


