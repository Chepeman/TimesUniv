#include "stdafx.h"  //_____________________________________________ AddCourseUD.cpp
#include "AddCourseUD.h"

void AddCourseUD::Window_Open(Win::Event& e)
{

	wstring cmd;
	Sql::SqlConnection conn;
	try
	{
		Sys::Format(cmd, L"SELECT program_id, descr");
		conn.OpenSession(DSN,USERNAME,PASSWORD);
		conn.ExecuteSelect(L"SELECT program_id, descr FROM program",100, ddCareer);
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
	ddClassdays.SelectedIndex=0;
	ddCareer.SelectedIndex=0;
	ddClassroom.SelectedIndex=0;
	ddClasstime.SelectedIndex=0;
	loadByCareer();
	//________________________________________________________ ddCourse
	ddCourse.Items.Add(L"Item 0 with value 10", 10);
	ddCourse.Items.Add(L"Item 1 with value 20", 20);
	//________________________________________________________ ddProfessor
	ddProfessor.Items.Add(L"Item 0 with value 10", 10);
	ddProfessor.Items.Add(L"Item 1 with value 20", 20);
}



void AddCourseUD::btAccept_Click(Win::Event& e)
{
}

void AddCourseUD::btCancel_Click(Win::Event& e)
{
}

void AddCourseUD::loadByCareer(void)
{

}
