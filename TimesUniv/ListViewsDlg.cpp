#include "stdafx.h"  //_____________________________________________ ListViewsDlg.cpp
#include "ListViewsDlg.h"

void ListViewsDlg::Window_Open(Win::Event& e)
{
	lb1.SetEnable(false);
	ddCareer.SetEnable(false);
	//________________________________________________________ toolbMain
	TBBUTTON tbButton[7];//<< EDIT HERE THE NUMBER OF BUTTONS

	toolbMain.imageList.Create(20, 20, 6);//<< EDIT HERE THE NUMBER OF IMAGES
	toolbMain.imageList.AddIcon(this->hInstance, IDI_ADD);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_EDIT);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_DELETE);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_COPY);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_MSEXCEL);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_PRINT);
	toolbMain.SendMessage(TB_BUTTONSTRUCTSIZE, (WPARAM)(int)sizeof(TBBUTTON), 0); 
	toolbMain.SetImageList(toolbMain.imageList);
	//_____________________________________
	tbButton[0].iBitmap=MAKELONG(0, 0); //<< IMAGE INDEX
	tbButton[0].idCommand=IDM_INSERT;
	tbButton[0].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[0].fsStyle=BTNS_BUTTON;
	tbButton[0].dwData=0L; 
	tbButton[0].iString= (LONG_PTR)L"Insert";
	//_____________________________________
	tbButton[1].iBitmap=MAKELONG(1, 0); //<< IMAGE INDEX
	tbButton[1].idCommand=IDM_EDIT;
	tbButton[1].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[1].fsStyle=BTNS_BUTTON;
	tbButton[1].dwData=0L; 
	tbButton[1].iString= (LONG_PTR)L"Edit";
	//_____________________________________
	tbButton[2].iBitmap=MAKELONG(2, 0); //<< IMAGE INDEX
	tbButton[2].idCommand=IDM_DELETE;
	tbButton[2].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[2].fsStyle=BTNS_BUTTON;
	tbButton[2].dwData=0L; 
	tbButton[2].iString= (LONG_PTR)L"Delete";
	//________________________ A separator
	tbButton[3].iBitmap=-1;
	tbButton[3].idCommand=0;  
	tbButton[3].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[3].fsStyle=BTNS_SEP;  
	tbButton[3].dwData=0L;  
	tbButton[3].iString=0;  
	//_____________________________________
	tbButton[4].iBitmap=MAKELONG(3, 0); //<< IMAGE INDEX
	tbButton[4].idCommand=IDM_COPY;
	tbButton[4].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[4].fsStyle=BTNS_BUTTON;
	tbButton[4].dwData=0L; 
	tbButton[4].iString= (LONG_PTR)L"Copy";
	//_____________________________________
	tbButton[5].iBitmap=MAKELONG(4, 0); //<< IMAGE INDEX
	tbButton[5].idCommand=IDM_MSEXCEL;
	tbButton[5].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[5].fsStyle=BTNS_BUTTON;
	tbButton[5].dwData=0L; 
	tbButton[5].iString= (LONG_PTR)L"Export";
	//_____________________________________
	tbButton[6].iBitmap=MAKELONG(5, 0); //<< IMAGE INDEX
	tbButton[6].idCommand=IDM_PRINT;
	tbButton[6].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[6].fsStyle=BTNS_BUTTON;
	tbButton[6].dwData=0L; 
	tbButton[6].iString= (LONG_PTR)L"Print";
	
	toolbMain.SetBitmapSize(20, 20);
	toolbMain.SetButtonSize(24, 22);
	toolbMain.AddButtons(tbButton, 7);// << EDIT HERE THE NUMBER OF BUTTONS
	toolbMain.SendMessage(TB_AUTOSIZE, 0, 0);
	toolbMain.SetMaxTextRows(1);// EDIT HERE TO DISPLAY THE BUTTON TEXT
	toolbMain.Show(SW_SHOWNORMAL);
	//________________________________________________________ ddCareer
	try
	{
		Sql::SqlConnection conn;
		conn.OpenSession(DSN,USERNAME,PASSWORD);
		conn.ExecuteSelect(L"SELECT program_id, career_name FROM program", 100, ddCareer);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	//________________________________________________________ lvMain
	if(selected==COORDINATOR)
		UpdateLvCoord();
	if(selected==PROFESSOR)
	{
		lb1.SetEnable(true);
		ddCareer.SetEnable(true);
		ddCareer.SelectedIndex=0;
		UpdateLvProf();
	}
	if(selected==CAREER)
		UpdateLvCareer();
	if(selected==COURSE)
	{
		lb1.SetEnable(true);
		ddCareer.SetEnable(true);
		ddCareer.SelectedIndex=0;
		UpdateLvCourse();
	}
	if(selected==DEPARTMENT)
		UpdateLvDept();
	if(selected==PERIOD)
		UpdateLvPeriod();
	if(selected==CLASSROOM)
		UpdateLvClassroom();
	if(selected==CLASSTIME)
		UpdateLvTime();
}
void ListViewsDlg::btClose_Click(Win::Event& e)
{
	this->EndDialog(TRUE);
}

void ListViewsDlg::Cmd_Insert(Win::Event& e)
{
	if(selected==COORDINATOR)
	{
		CoordDlg dlg;
		dlg.BeginDialog(hWnd);
		UpdateLvCoord();
	}
	if(selected==PROFESSOR)
	{
		ProfDlg dlg;
		dlg.BeginDialog(hWnd);
		UpdateLvProf();
	}
	if(selected==CAREER)
	{
		ProgramDlg dlg;
		dlg.BeginDialog(hWnd);
		UpdateLvCareer();
	}
	if(selected==COURSE)
	{
		CourseDlg dlg;
		dlg.BeginDialog(hWnd);
		UpdateLvCourse();
	}
	if(selected==DEPARTMENT)
	{
		DeptDlg dlg;
		dlg.BeginDialog(hWnd);
		UpdateLvDept();
	}
	if(selected==PERIOD)
	{
		PeriodDlg dlg;
		dlg.BeginDialog(hWnd);
		UpdateLvPeriod();
	}
	if(selected==CLASSROOM)
	{
		ClassroomDlg dlg;
		dlg.BeginDialog(hWnd);
		UpdateLvClassroom();
	}
	if(selected==CLASSTIME)
	{
		TimeDlg dlg;
		dlg.BeginDialog(hWnd);
		UpdateLvTime();
	}
}
void ListViewsDlg::Cmd_Edit(Win::Event& e)
{
	int index=lvMain.GetSelectedIndex();
	if(index<0)return;
	const int ID=lvMain.Items[index].Data;
	if(selected==COORDINATOR)
	{
		CoordDlg dlg;
		dlg.coordinator_id=ID;
		dlg.BeginDialog(hWnd);
		UpdateLvCoord();
	}
	if(selected==PROFESSOR)
	{
		ProfDlg dlg;
		dlg.professor_id=ID;
		dlg.BeginDialog(hWnd);
		UpdateLvProf();
	}
	if(selected==CAREER)
	{
		ProgramDlg dlg;
		dlg.program_id=ID; 
		dlg.BeginDialog(hWnd);
		UpdateLvCareer();
	}
	if(selected==COURSE)
	{
		CourseDlg dlg;
		dlg.course_id=ID;
		dlg.BeginDialog(hWnd);
		UpdateLvCourse();
	}
	if(selected==DEPARTMENT)
	{
		DeptDlg dlg;
		dlg.department_id=ID;
		dlg.BeginDialog(hWnd);
		UpdateLvDept();
	}
	if(selected==PERIOD)
	{
		PeriodDlg dlg;
		dlg.period_id=ID;
		dlg.BeginDialog(hWnd);
		UpdateLvPeriod();
	}
	if(selected==CLASSROOM)
	{
		ClassroomDlg dlg;
		dlg.classroom_id=ID;
		dlg.BeginDialog(hWnd);
		UpdateLvClassroom();
	}
	if(selected==CLASSTIME)
	{
		TimeDlg dlg;
		dlg.classtime_id=ID;
		dlg.BeginDialog(hWnd);
		UpdateLvTime();
	}
}
void ListViewsDlg::Cmd_Delete(Win::Event& e)
{
	Win::HourGlassCursor hgc(true);
	int index=lvMain.GetSelectedIndex();
	if(index<0)return;
	//__________________________________________________ Ask the user
	if (this->MessageBox(L"Are you sure you want to delete the selected row?",L"Delete Item", MB_YESNO | MB_ICONQUESTION) != IDYES) return;
	const int ID=lvMain.Items[index].Data;
	wstring cmd;
	int rows = 0;
	Sql::SqlConnection conn;
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		//conn.OpenSession(hWnd, CONNECTION_STRING);
        if(selected==COORDINATOR)Sys::Format(cmd, L"DELETE FROM coordinator WHERE coordinator_id=%d",ID);
		if(selected==PROFESSOR)Sys::Format(cmd, L"DELETE FROM professor WHERE professor_id=%d",ID);
		if(selected==CAREER)Sys::Format(cmd, L"DELETE FROM program WHERE program_id=%d",ID);
		if(selected==COURSE)Sys::Format(cmd, L"DELETE FROM course WHERE course_id=%d",ID);
		if(selected==DEPARTMENT)Sys::Format(cmd, L"DELETE FROM department WHERE department_id=%d",ID);
		if(selected==PERIOD)Sys::Format(cmd, L"DELETE FROM period WHERE period_id=%d",ID);
		if(selected==CLASSROOM)Sys::Format(cmd, L"DELETE FROM classroom WHERE classroom_id=%d",ID);
		if(selected==CLASSTIME)Sys::Format(cmd, L"DELETE FROM classtime WHERE classtime_id=%d",ID);
        rows = conn.ExecuteNonQuery(cmd);
        if (rows!=1)
        {
			this->MessageBox(Sys::Convert::ToString(rows), L"Error - deleted rows", MB_OK | MB_ICONERROR);
        }
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	if(selected==COORDINATOR)UpdateLvCoord();
	if(selected==PROFESSOR)UpdateLvProf();
	if(selected==CAREER)UpdateLvCareer();
	if(selected==COURSE)UpdateLvCourse();
	if(selected==DEPARTMENT)UpdateLvDept();
	if(selected==PERIOD)UpdateLvPeriod();
	if(selected==CLASSROOM)UpdateLvClassroom();
	if(selected==CLASSTIME)UpdateLvTime();
}

void ListViewsDlg::Cmd_Copy(Win::Event& e)
{
	lvMain.CopyToClipboard();
}
void ListViewsDlg::Cmd_Msexcel(Win::Event& e)
{
	Win::FileDlg dlg;
	dlg.Clear();
	dlg.SetFilter(L"Archivos Excel(*.xlsx)\0*.xlsx\0\0",0,L"xlsx");
	if(dlg.BeginDialog(hWnd,L"Exportar a Excel",true))
		lvMain.ExportToMsExcel(dlg.GetFileNameFullPath());
	else
		this->MessageBox(L"No fue posible exportar la informacion",L"Exportar a Excel",MB_OK|MB_ICONERROR);
}
void ListViewsDlg::Cmd_Print(Win::Event& e)
{
	Win::PrintDoc document;
	document.Add(800,lvMain.Items.GetCount()+1,lvMain);
	Win::PrintPreviewDlg dlg;
	dlg.SetWidth(300);
	dlg.BeginDialog_(hWnd,&document);
}

void ListViewsDlg::UpdateLvCoord()
{
	this->Text=L"Timesuniv - Coordinators";
	lvMain.Items.DeleteAll();
	lvMain.Cols.DeleteAll();
	lvMain.Cols.Add(0, LVCFMT_LEFT, 250, L"Professor");
	lvMain.Cols.Add(1, LVCFMT_LEFT, 400, L"Program");
	lvMain.Cols.Add(2, LVCFMT_LEFT, 110, L"Program ID");
	lvMain.Cols.Add(3, LVCFMT_LEFT, 125, L"Username");
	Sql::SqlConnection conn;
    try
    {
         conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
         //conn.OpenSession(hWnd, CONNECTION_STRING);
         conn.ExecuteSelect(L"SELECT c.coordinator_id, p.last_name_p+' '+p.last_name_m+', '+p.name, pg.career_name, pg.descr, c.username\
							  FROM professor p, program pg, coordinator c\
							  WHERE c.program_id=pg.program_id AND c.professor_id=p.professor_id ORDER BY c.coordinator_id", 100, lvMain);
    }
    catch (Sql::SqlException e)
    {
         this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
    }
	lvMain.SetRedraw(true);
	toolbMain.EnableButton(IDM_EDIT,false);
	toolbMain.EnableButton(IDM_DELETE,false);
}
void ListViewsDlg::UpdateLvProf()
{
	this->Text=L"Timesuniv - Professors";
	lvMain.Items.DeleteAll();
	lvMain.Cols.DeleteAll();
	lvMain.Cols.Add(0, LVCFMT_LEFT, 270, L"Professor");
	lvMain.Cols.Add(1, LVCFMT_RIGHT, 180, L"Email");
	lvMain.Cols.Add(2, LVCFMT_CENTER, 100, L"Extension");
	lvMain.Cols.Add(3, LVCFMT_CENTER, 100, L"Promep");
	lvMain.Cols.Add(4, LVCFMT_CENTER, 100, L"SNI");

	int selection=ddCareer.SelectedData;
	wstring cmd;
	Sys::Format(cmd,L"SELECT p.professor_id, p.last_name_p+' '+p.last_name_m+', '+p.name, p.email, p.extension,\
							CASE WHEN p.promep = 1 THEN 'Yes' ELSE 'No' END,\
							CASE WHEN p.sni = 1 THEN 'Yes' ELSE 'No' END\
					  FROM professor p, department d, program pg\
					  WHERE p.department_id=d.department_id AND pg.department_id=d.department_id AND pg.program_id=%d\
					  ORDER BY p.last_name_p",selection);
	Sql::SqlConnection conn;
    try
    {
         conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
         //conn.OpenSession(hWnd, CONNECTION_STRING);
         conn.ExecuteSelect(cmd, 100, lvMain);
    }
    catch (Sql::SqlException e)
    {
         this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
    }
	lvMain.SetRedraw(true);
	toolbMain.EnableButton(IDM_EDIT,false);
	toolbMain.EnableButton(IDM_DELETE,false);
}
void ListViewsDlg::UpdateLvCareer()
{
	this->Text=L"TimesUniv - Programs";
	lvMain.Items.DeleteAll();
	lvMain.Cols.DeleteAll();
	lvMain.Cols.Add(0, LVCFMT_LEFT, 150, L"Program ID");
	lvMain.Cols.Add(1, LVCFMT_LEFT, 500, L"Program Name");
	lvMain.Cols.Add(2, LVCFMT_LEFT, 200, L"Department");
	Sql::SqlConnection conn;
    try
    {
         conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
         //conn.OpenSession(hWnd, CONNECTION_STRING);
         conn.ExecuteSelect(L"SELECT p.program_id, p.descr, p.career_name, d.descr\
							  FROM department d, program p\
							  WHERE d.department_id=p.department_id\
							  ORDER BY p.program_id", 150, lvMain);
    }
    catch (Sql::SqlException e)
    {
         this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
    }
	lvMain.SetRedraw(true);
	toolbMain.EnableButton(IDM_EDIT,false);
	toolbMain.EnableButton(IDM_DELETE,false);
}
void ListViewsDlg::UpdateLvCourse()
{
	this->Text=L"Timesuniv - Courses";
	lvMain.Items.DeleteAll();
	lvMain.Cols.DeleteAll();
	lvMain.Cols.Add(0, LVCFMT_LEFT, 100, L"Course Key");
	lvMain.Cols.Add(1, LVCFMT_LEFT, 350, L"Course");
	lvMain.Cols.Add(2, LVCFMT_CENTER, 100, L"Week Hours");
	lvMain.Cols.Add(3, LVCFMT_LEFT, 150, L"Laboratory");
	lvMain.Cols.Add(4, LVCFMT_CENTER, 100, L"Need Tables");


	int selection=ddCareer.SelectedData;
	wstring cmd;
	Sys::Format(cmd,L"SELECT c.course_id,c.course_key,c.descr,c.week_hours, l.descr,\
							CASE WHEN c.need_tables = 1 THEN 'Yes' ELSE 'No' END\
					  FROM course c, prog_course pc, program p, laboratories l\
					  WHERE c.course_id=pc.course_id AND pc.program_id=p.program_id	AND p.program_id=%d AND c.lab_id=l.lab_id\
					  ORDER BY c.descr",selection);
	Sql::SqlConnection conn;
    try
    {
         conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
         //conn.OpenSession(hWnd, CONNECTION_STRING);
         conn.ExecuteSelect(cmd, 100, lvMain);
    }
    catch (Sql::SqlException e)
    {
         this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
    }
	lvMain.SetRedraw(true);
	toolbMain.EnableButton(IDM_EDIT,false);
	toolbMain.EnableButton(IDM_DELETE,false);
}
void ListViewsDlg::UpdateLvDept()
{
	this->Text=L"TimesUniv - Departments";
	lvMain.Items.DeleteAll();
	lvMain.Cols.DeleteAll();
	lvMain.Cols.Add(0, LVCFMT_LEFT, 400, L"Department");
	Sql::SqlConnection conn;
    try
    {
         conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
         //conn.OpenSession(hWnd, CONNECTION_STRING);
         conn.ExecuteSelect(L"SELECT * FROM department ORDER BY descr", 150, lvMain);
    }
    catch (Sql::SqlException e)
    {
         this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
    }
	lvMain.SetRedraw(true);
	toolbMain.EnableButton(IDM_EDIT,false);
	toolbMain.EnableButton(IDM_DELETE,false);
}
void ListViewsDlg::UpdateLvPeriod()
{
	this->Text=L"TimesUniv - Periods";
	lvMain.Items.DeleteAll();
	lvMain.Cols.DeleteAll();
	lvMain.Cols.Add(0, LVCFMT_LEFT, 150, L"Period");
	lvMain.Cols.Add(1, LVCFMT_RIGHT, 150, L"Begin Date");
	lvMain.Cols.Add(2, LVCFMT_RIGHT, 150, L"End Date");
	
	Sql::SqlConnection conn;
    try
    {
         conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
         //conn.OpenSession(hWnd, CONNECTION_STRING);
         conn.ExecuteSelect(L"SELECT period_id,descr,CONVERT(NVARCHAR(14), begin_date, 107),CONVERT(NVARCHAR(14), end_date, 107) \
							  FROM period ORDER BY begin_date", 100, lvMain);
    }
    catch (Sql::SqlException e)
    {
         this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
    }
	lvMain.SetRedraw(true);
	toolbMain.EnableButton(IDM_EDIT,false);
	toolbMain.EnableButton(IDM_DELETE,false);
}
void ListViewsDlg::UpdateLvClassroom()
{
	this->Text=L"TimesUniv - Classrooms";
	lvMain.Items.DeleteAll();
	lvMain.Cols.DeleteAll();
	lvMain.Cols.Add(0, LVCFMT_LEFT, 300, L"Classroom");
	lvMain.Cols.Add(1, LVCFMT_CENTER, 100, L"No. Contacts");
	lvMain.Cols.Add(2, LVCFMT_CENTER, 100, L"No. Seats");
	lvMain.Cols.Add(3, LVCFMT_CENTER, 100, L"Has Projector");
	lvMain.Cols.Add(4, LVCFMT_CENTER, 100, L"Has Tables");
	
	Sql::SqlConnection conn;
    try
    {
         conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
         //conn.OpenSession(hWnd, CONNECTION_STRING);
         conn.ExecuteSelect(L"SELECT classroom_id, descr, contact_count, seat_count,\
							  CASE WHEN has_projector = 1 THEN 'Yes' ELSE 'No' END,\
							  CASE WHEN has_tables = 1 THEN 'Yes' ELSE 'No' END\
							  FROM classroom", 100, lvMain);
    }
    catch (Sql::SqlException e)
    {
         this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
    }
	lvMain.SetRedraw(true);
	toolbMain.EnableButton(IDM_EDIT,false);
	toolbMain.EnableButton(IDM_DELETE,false);
}
void ListViewsDlg::UpdateLvTime()
{
	this->Text=L"TimesUniv - Classtimes";
	lvMain.Items.DeleteAll();
	lvMain.Cols.DeleteAll();
	lvMain.Cols.Add(0, LVCFMT_CENTER, 150, L"Begin Time");
	lvMain.Cols.Add(1, LVCFMT_CENTER, 150, L"End Time");
	
	Sql::SqlConnection conn;
    try
    {
         conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
         //conn.OpenSession(hWnd, CONNECTION_STRING);
         conn.ExecuteSelect(L"SELECT classtime_id, CONVERT(varchar(15), begin_time, 100), CONVERT(varchar(15), end_time, 100)\
							  FROM classtime ORDER BY begin_time", 100, lvMain);
    }
    catch (Sql::SqlException e)
    {
         this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
    }
	lvMain.SetRedraw(true);
	toolbMain.EnableButton(IDM_EDIT,false);
	toolbMain.EnableButton(IDM_DELETE,false);
}

void ListViewsDlg::lvMain_ItemChanged(Win::Event& e)
{
	toolbMain.EnableButton(IDM_EDIT,true);
	toolbMain.EnableButton(IDM_DELETE,true);
}
void ListViewsDlg::lvMain_DblClk(Win::Event& e)
{
	Cmd_Edit(e);
}
void ListViewsDlg::ddCareer_SelChange(Win::Event& e)
{
	if(selected==PROFESSOR)
		UpdateLvProf();
	if(selected==COURSE)
		UpdateLvCourse();
}