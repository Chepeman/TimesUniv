#include "stdafx.h"  //________________________________________ TimesUniv.cpp
#include "TimesUniv.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	TimesUniv app;
	app.CreateMainWindow(L"University Schedule", cmdShow, IDI_TIMESUNIV, NULL, (HBRUSH)(COLOR_WINDOW), hInstance);
	return app.MessageLoop(IDC_TIMESUNIV);
}
void TimesUniv::Window_Open(Win::Event& e)
{
	this->SetEnable(true);
	//_______________________________________________________ListView's ImageList
	imageList.Create(16,16,2);
	imageList.AddIcon(this->hInstance, IDI_DELETE);
	imageList.AddIcon(this->hInstance, IDI_VOID);

	toolbMain.Destroy();
	toolbMain.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | CCS_NORESIZE | CCS_NOPARENTALIGN | CCS_ADJUSTABLE | CCS_NODIVIDER | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS, 18, 1, 964, 42, hWnd, 1000);

	//________________________________________________________ toolbMain
	TBBUTTON tbButton[9];//<< EDIT HERE THE NUMBER OF BUTTONS

	toolbMain.imageList.Create(22, 22, 9);//<< EDIT HERE THE NUMBER OF IMAGES
	toolbMain.imageList.AddIcon(this->hInstance, IDI_COORDINATOR);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_PROFESSOR);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_CAREER);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_COURSE);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_DEPT);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_PERIOD);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_CLASSROOM);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_CLASSTIME);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_UPDOWN);

	toolbMain.SendMessage(TB_BUTTONSTRUCTSIZE, (WPARAM)(int)sizeof(TBBUTTON), 0); 
	toolbMain.SetImageList(toolbMain.imageList);
	//_____________________________________
	tbButton[0].iBitmap=MAKELONG(0, 0); //<< IMAGE INDEX
	tbButton[0].idCommand=IDM_COORDINATOR;
	tbButton[0].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[0].fsStyle=BTNS_BUTTON;
	tbButton[0].dwData=0L; 
	tbButton[0].iString= (LONG_PTR)L"Coordinator";
	//_____________________________________
	tbButton[1].iBitmap=MAKELONG(1, 0); //<< IMAGE INDEX
	tbButton[1].idCommand=IDM_PROFESSOR;
	tbButton[1].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[1].fsStyle=BTNS_BUTTON;
	tbButton[1].dwData=0L; 
	tbButton[1].iString= (LONG_PTR)L"Professor";
	//_____________________________________
	tbButton[2].iBitmap=MAKELONG(2, 0); //<< IMAGE INDEX
	tbButton[2].idCommand=IDM_CAREER;
	tbButton[2].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[2].fsStyle=BTNS_BUTTON;
	tbButton[2].dwData=0L; 
	tbButton[2].iString= (LONG_PTR)L"Program";
	//_____________________________________
	tbButton[3].iBitmap=MAKELONG(3, 0); //<< IMAGE INDEX
	tbButton[3].idCommand=IDM_COURSE;
	tbButton[3].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[3].fsStyle=BTNS_BUTTON;
	tbButton[3].dwData=0L; 
	tbButton[3].iString= (LONG_PTR)L"Course";
	//_____________________________________
	tbButton[4].iBitmap=MAKELONG(4, 0); //<< IMAGE INDEX
	tbButton[4].idCommand=IDM_DEPT;
	tbButton[4].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[4].fsStyle=BTNS_BUTTON;
	tbButton[4].dwData=0L; 
	tbButton[4].iString= (LONG_PTR)L"Department";
	//____________________________________
	tbButton[5].iBitmap=MAKELONG(5, 0); //<< IMAGE INDEX
	tbButton[5].idCommand=IDM_PERIOD;
	tbButton[5].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[5].fsStyle=BTNS_BUTTON;
	tbButton[5].dwData=0L; 
	tbButton[5].iString= (LONG_PTR)L"Period";
	//_____________________________________
	tbButton[6].iBitmap=MAKELONG(6, 0); //<< IMAGE INDEX
	tbButton[6].idCommand=IDM_CLASSROOM;
	tbButton[6].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[6].fsStyle=BTNS_BUTTON;
	tbButton[6].dwData=0L; 
	tbButton[6].iString= (LONG_PTR)L"Classroom";
	//_____________________________________
	tbButton[7].iBitmap=MAKELONG(7, 0); //<< IMAGE INDEX
	tbButton[7].idCommand=IDM_CLASSTIME;
	tbButton[7].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[7].fsStyle=BTNS_BUTTON;
	tbButton[7].dwData=0L; 
	tbButton[7].iString= (LONG_PTR)L"Time";
	//_____________________________________
	tbButton[8].iBitmap=MAKELONG(8, 0); //<< IMAGE INDEX
	tbButton[8].idCommand=IDM_UPDOWN;
	tbButton[8].fsState=TBSTATE_HIDDEN; // | TBSTATE_WRAP
	tbButton[8].fsStyle=BTNS_BUTTON;
	tbButton[8].dwData=0L; 
	tbButton[8].iString= (LONG_PTR)L"Up/Down";

	toolbMain.SetBitmapSize(20, 20);
	toolbMain.SetButtonSize(24, 22);
	toolbMain.AddButtons(tbButton, 9);// << EDIT HERE THE NUMBER OF BUTTONS
	toolbMain.SendMessage(TB_AUTOSIZE, 0, 0);
	toolbMain.SetMaxTextRows(1);// EDIT HERE TO DISPLAY THE BUTTON TEXT
	toolbMain.Show(SW_SHOWNORMAL);
	//________________________________________________________ ddCareer
	try
	{
		Sql::SqlConnection conn;
		conn.OpenSession(DSN,USERNAME,PASSWORD);
		conn.ExecuteSelect(L"SELECT program_id, career_name FROM program", 200, ddCareer);
		conn.ExecuteSelect(L"SELECT * FROM period ORDER BY period_id DESC", 100, ddPeriod);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	
	LoginDlg dlg;
	if (dlg.BeginDialog(hWnd) == TRUE) //__________________ Give Access
	{
		ddCareer.SelectedIndex=0;
		ddPeriod.SelectedIndex=0;
		loadAssignments();
		loadProposals();
		this->Text = L"Welcome Academic Secretary";
		this->Maximize();

		Sql::SqlConnection conn;
		wstring sqlCmd;
		wstring username=dlg.tbxUser.Text;
		wstring password=dlg.tbxPass.Text;
		//_______________________________Check the Up-Down date
		const int period=ddPeriod.GetSelectedIndex();
		if(period<0)return;
		current_period=ddPeriod.GetSelectedData();
		wstring udCmd;
		Sys::Format(udCmd,L"SELECT DATEDIFF(day, DATEADD(day,35,begin_date), GETDATE()) FROM period WHERE period_id=%d",current_period);
		int isActive=-1;
		try
		{
			conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
			//conn.OpenSession(hWnd, CONNECTION_STRING);

			//______________________________________________Is Active Up/Down period?
			isActive=conn.GetInt(udCmd);
			if(isActive<1)
			{
				toolbMain.HideButton(IDM_UPDOWN, false);
				toolbMain.EnableButton(IDM_UPDOWN, true);
			}
			//_____________________________________________ Is Admin?
			Sys::Format(sqlCmd,L"SELECT isAdmin FROM coordinator WHERE username='%s'",username.c_str());
			const bool isAdmin = conn.GetBool(sqlCmd);
			//
			if (isAdmin == false)
			{
				ddPeriod.Items.DeleteAll();
				ddCareer.Items.DeleteAll();
				lvProposal.Items.DeleteAll();
				lvAsign.Items.DeleteAll();
				this->SetEnable(false);
				this->Minimize();
				Sys::Format(sqlCmd,L"SELECT program_id FROM coordinator WHERE username='%s' AND pass='%s'",username.c_str(),password.c_str());
				CoordMng cdlg;
				cdlg.career_id=conn.GetInt(sqlCmd);
				cdlg.BeginDialog(hWnd);
				this->Window_Open(e);
			}
		}
		catch (Sql::SqlException e)
		{
			this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		}
		 
	}
	else
	{
		this->Window_Destroy(e); //________________________ Deny Access
	}
}
void TimesUniv::Window_Destroy(Win::Event& e)
{
	this->timer.Kill(MAIN_TIMER);
	::PostQuitMessage(0);
	e.returnValue = 0;
}
void TimesUniv::Window_Close(Win::Event& e)
{
	btClose_Click(e);
}
void TimesUniv::Window_Timer(Win::Event& e)
{
	if (e.wParam== MAIN_TIMER)
	{
		wchar_t info[128];
		wstring cmd;
		int sizei,sizej, cnt=-1;
		const double derror = error.Get(); 
		const double progress = threadObject.progress.Get(); 
		_snwprintf_s(info, 128, _TRUNCATE, L"error=%g,  progress=%g",derror, progress); 
		this->SetWindowText(info); 
		if (threadObject.running.Get()==false) 
		{ 
			this->timer.Kill(MAIN_TIMER); 
			threadObject.WaitForExit(); 
			this->MessageBox(L"The solution has been reached", L"Solution", MB_OK);
			//For solMon
			sizei=solution.solMon.size();
			sizej=solution.solMon[0].size();

			try
			{
				Sql::SqlConnection conn;
				conn.OpenSession(DSN, USERNAME, PASSWORD);
				for(int i=0; i<sizei; i++)
				{
					for(int j=0; j<sizej; j++)
					{
						if(solution.solMon[i][j].course!=0 && solution.solMon[i][j].hour!=0)
						{
							Sys::Format(cmd,L"INSERT INTO course_time(course_id,week_day_id,classtime_id,grupo)VALUES(%d,1,%d,'%c')",solution.solMon[i][j].course,solution.solMon[i][j].hour,solution.solMon[i][j].group[0]);
							conn.ExecuteNonQuery(cmd);
							Sys::Format(cmd,L"INSERT INTO course_time(course_id,week_day_id,classtime_id,grupo)VALUES(%d,3,%d,'%c')",solution.solMon[i][j].course,solution.solMon[i][j].hour,solution.solMon[i][j].group[0]);
							conn.ExecuteNonQuery(cmd);
							Sys::Format(cmd,L"INSERT INTO course_time(course_id,week_day_id,classtime_id,grupo)VALUES(%d,5,%d,'%c')",solution.solMon[i][j].course,solution.solMon[i][j].hour,solution.solMon[i][j].group[0]);
							conn.ExecuteNonQuery(cmd);
							Sys::Format(cmd,L"INSERT INTO perturbation(professor_id, course_id, classroom_id,grupo)VALUES(%d,%d,%d,'%c')",solution.solMon[i][j].professor,solution.solMon[i][j].course, solution.solMon[i][j].classroom,solution.solMon[i][j].group[0]);
							conn.ExecuteNonQuery(cmd);	
						}
					}
				}
				conn.CloseSession();
			}
			catch(Sql::SqlException e)
			{
				this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
			}

			//For solThu
			sizei=solution.solThu.size();
			sizej=solution.solThu[0].size();

			try
			{
				Sql::SqlConnection conn;
				conn.OpenSession(DSN, USERNAME, PASSWORD);
				for(int i=0; i<sizei; i++)
				{
					for(int j=0; j<sizej; j++)
					{
						if(solution.solThu[i][j].course!=0 && solution.solThu[i][j].hour!=0)
						{
							Sys::Format(cmd,L"INSERT INTO course_time(course_id,week_day_id,classtime_id,grupo)VALUES(%d,2,%d,'%c')",solution.solThu[i][j].course,solution.solThu[i][j].hour,solution.solThu[i][j].group[0]);
							conn.ExecuteNonQuery(cmd);
							Sys::Format(cmd,L"INSERT INTO course_time(course_id,week_day_id,classtime_id,grupo)VALUES(%d,4,%d,'%c')",solution.solThu[i][j].course,solution.solThu[i][j].hour,solution.solThu[i][j].group[0]);
							conn.ExecuteNonQuery(cmd);
							Sys::Format(cmd,L"INSERT INTO perturbation(professor_id, course_id, classroom_id,grupo)VALUES(%d,%d,%d,'%c')",solution.solThu[i][j].professor,solution.solThu[i][j].course, solution.solThu[i][j].classroom,solution.solThu[i][j].group[0]);
							conn.ExecuteNonQuery(cmd);		
						}
					}
				}
				conn.CloseSession();
			}
			catch(Sql::SqlException e)
			{
				this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
			}
		}
		loadProposals();
	}
}

void TimesUniv::Cmd_Coordinator(Win::Event& e)
{
	ListViewsDlg dlg;
	dlg.selected=COORDINATOR;
	dlg.BeginDialog(hWnd);
}
void TimesUniv::Cmd_Professor(Win::Event& e)
{
	ListViewsDlg dlg;
	dlg.selected=PROFESSOR;
	dlg.BeginDialog(hWnd);
}
void TimesUniv::Cmd_Career(Win::Event& e)
{
	ListViewsDlg dlg;
	dlg.selected=CAREER;
	dlg.BeginDialog(hWnd);
}
void TimesUniv::Cmd_Course(Win::Event& e)
{
	ListViewsDlg dlg;
	dlg.selected=COURSE;
	dlg.BeginDialog(hWnd);
}
void TimesUniv::Cmd_Dept(Win::Event& e)
{
	ListViewsDlg dlg;
	dlg.selected=DEPARTMENT;
	dlg.BeginDialog(hWnd);
}
void TimesUniv::Cmd_Period(Win::Event& e)
{
	ListViewsDlg dlg;
	dlg.selected=PERIOD;
	dlg.BeginDialog(hWnd);
}
void TimesUniv::Cmd_Classroom(Win::Event& e)
{
	ListViewsDlg dlg;
	dlg.selected=CLASSROOM;
	dlg.BeginDialog(hWnd);
}
void TimesUniv::Cmd_Classtime(Win::Event& e)
{
	ListViewsDlg dlg;
	dlg.selected=CLASSTIME;
	dlg.BeginDialog(hWnd);
}
void TimesUniv::Cmd_Updown(Win::Event& e)
{
	UpDownDlg dlg;
	dlg.cu_period=current_period;
	dlg.BeginDialog(hWnd);
	loadProposals();
	loadAssignments();
}

void TimesUniv::btClose_Click(Win::Event& e)
{
	ddPeriod.Items.DeleteAll();
	ddCareer.Items.DeleteAll();
	lvProposal.Items.DeleteAll();
	lvAsign.Items.DeleteAll();

	this->Minimize();
	this->SetEnable(false);
	this->Window_Open(e);
}
void TimesUniv::btGenerate_Click(Win::Event& e)
{
	int nHours, nCourse, nRooms,asign;
	wstring cmd;
	Sys::Format(cmd,L"SELECT COUNT(*) FROM assignment");
	//std::vector<Asignation> solution;
	const int period=ddPeriod.GetSelectedIndex();
	if(period<0)return;
	int period_id=ddPeriod.GetSelectedData();
	
	try
	{
		Sql::SqlConnection conn;
		conn.OpenSession(DSN, USERNAME, PASSWORD);
		asign=conn.GetInt(cmd);
		if(asign<=0)
		{
			this->MessageBoxW(L"You haven't insert anything to generate a solution", L"Error", MB_OK| MB_ICONERROR);
			return;
		}
		Sys::Format(cmd,L"SELECT COUNT(*) FROM classtime");
		nHours=conn.GetInt(cmd);
		Sys::Format(cmd,L"SELECT COUNT(*) FROM classroom");
		nRooms=conn.GetInt(cmd);
		Sys::Format(cmd,L"SELECT COUNT(*) FROM assignment");
		nCourse=conn.GetInt(cmd);
		Sys::Format(cmd,L"DELETE FROM perturbation");
		conn.ExecuteSelect(cmd);
		Sys::Format(cmd,L"DELETE FROM course_time");
		conn.ExecuteSelect(cmd);
		conn.CloseSession();
	}
	catch(Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	
	solution=Solution::Solution(nHours,nRooms,nCourse);
	solution.period_id=period_id;
	solutionWork1=Solution::Solution(nHours,nRooms,nCourse);
	solutionWork1.period_id=period_id;
	solutionWork2=Solution::Solution(nHours,nRooms,nCourse);
	solutionWork2.period_id=period_id;

	//simAnneal.goal = 1e-9; 
	simAnneal.goal = 0;
	simAnneal.initialTemp = 6; 
	simAnneal.finalTemp = 1; 
	simAnneal.numTemps = 2500; 
	simAnneal.numIterations = 5; 
	simAnneal.cycles = 10; 
	simAnneal.isCoolingScheduleLinear = false; 
	simAnneal.Setup(error, solution, solutionWork1, solutionWork2);
	threadObject.StartThread(simAnneal); 
	this->timer.Set(MAIN_TIMER, 1000);
}
void TimesUniv::btExport_Click(Win::Event& e)
{
	ScheduleDlg dlg;
	const int period=ddPeriod.GetSelectedIndex();
	if(period<0)return;
	int period_id=ddPeriod.GetSelectedData();
	dlg.period_id=period_id;
	dlg.BeginDialog(hWnd);
	loadProposals();
}

void TimesUniv::loadAssignments()
{
	lvAsign.SetRedraw(false);
	lvAsign.Items.DeleteAll();
	lvAsign.Cols.DeleteAll();
	lvAsign.Cols.Add(0, LVCFMT_LEFT, 90, L"Course Key");
	lvAsign.Cols.Add(1, LVCFMT_LEFT, 180, L"Course");
	lvAsign.Cols.Add(2, LVCFMT_LEFT, 180, L"Professor");
	lvAsign.Cols.Add(3, LVCFMT_RIGHT, 60, L"Quota");
	const int period2=ddPeriod.GetSelectedIndex();
	if(period2<0)return;
	int period_id2=ddPeriod.GetSelectedData();
	Sql::SqlConnection conn;
	int count;
	wstring cmd;
	Assign aux;
	wchar_t course_key[16],course[64],professor[128]; //grupo[2]
	int index=0,quota=0,career_id=-1,period_id=-1;

	const int career=ddCareer.GetSelectedIndex();
	career_id=ddCareer.Items[career].GetData();

	const int period=ddPeriod.GetSelectedIndex();
	period_id=ddPeriod.Items[period].GetData();
	try
	{
		Sys::Format(cmd, L"SELECT COUNT(*) FROM schedule WHERE period_id=%d", period_id2);
		conn.OpenSession(DSN, USERNAME, PASSWORD);
		count=conn.GetInt(cmd);
		conn.CloseSession();
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	if(count<1)
	{

		Sys::Format(cmd,L"SELECT c.course_id, p.professor_id, pe.period_id, c.course_key, c.descr,p.last_name_p+' '+ p.last_name_m+', '+p.name, a.cupo \
						  FROM assignment a, professor p, course c, prog_course pc, program pr, period pe \
						  WHERE a.course_id=c.course_id \
								AND a.professor_id=p.professor_id \
								AND a.period_id=pe.period_id \
								AND c.course_id=pc.course_id \
								AND pc.program_id=pr.program_id \
								AND pc.program_id=%d \
								AND a.period_id=%d", career_id, period_id);
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

			while (conn.Fetch())
			{
				assign.push_back(aux);
				lvAsign.Items.Add(index,course_key,index);
				lvAsign.Items[index][1].Text=course;
				lvAsign.Items[index][2].Text=professor;
				lvAsign.Items[index][3].Text=Sys::Convert::ToString(quota);
				index++;
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
		Sys::Format(cmd,L"SELECT c.course_id, p.professor_id, pe.period_id, c.course_key, c.descr,p.last_name_p+' '+ p.last_name_m+', '+p.name \
						  FROM schedule s, professor p, course c, prog_course pc, program pr, period pe, week_day w \
						  WHERE s.course_id=c.course_id \
								AND s.professor_id=p.professor_id \
								AND s.period_id=pe.period_id \
								AND c.course_id=pc.course_id \
								AND pc.program_id=pr.program_id \
								AND w.week_day_id=s.week_day_id\
								AND w.week_day_id BETWEEN 1 AND 2\
								AND pc.program_id=%d \
								AND s.period_id=%d", career_id, period_id);
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

			while (conn.Fetch())
			{
				assign.push_back(aux);
				lvAsign.Items.Add(index,course_key,index);
				lvAsign.Items[index][1].Text=course;
				lvAsign.Items[index][2].Text=professor;
				lvAsign.Items[index][3].Text=L"Don't Apply";
				index++;
			}
			conn.CloseSession();
		}
		catch (Sql::SqlException e)
		{
			this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		}
	}
	lvAsign.SetRedraw(true);
}
void TimesUniv::loadProposals() //finish this function
{
	int count=-1;
	Sql::SqlConnection conn;
	wstring cmd;
	const int period=ddPeriod.GetSelectedIndex();
	if(period<0)return;
	int period_id=ddPeriod.GetSelectedData();

	try
	{
		Sys::Format(cmd, L"SELECT COUNT(*) FROM schedule WHERE period_id=%d", period_id);
		conn.OpenSession(DSN, USERNAME, PASSWORD);
		count=conn.GetInt(cmd);
		conn.CloseSession();
	}
	catch(Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}

	if(count<1)
	{
		isCLickleable=true;
		CoursesID IDs;
		idsol.clear();
		lvProposal.SetRedraw(false);
		lvProposal.Items.DeleteAll();
		lvProposal.Cols.DeleteAll();
		lvProposal.Cols.Add(0, LVCFMT_LEFT, 90, L"Course Key");
		lvProposal.Cols.Add(1, LVCFMT_LEFT, 230, L"Course");
		lvProposal.Cols.Add(2, LVCFMT_LEFT, 200, L"Professor");
		lvProposal.Cols.Add(3, LVCFMT_LEFT, 70,  L"Classroom");
		lvProposal.Cols.Add(4, LVCFMT_LEFT, 80,  L"Days");
		lvProposal.Cols.Add(5, LVCFMT_LEFT, 150,  L"Classtime");
		lvProposal.Cols.Add(6, LVCFMT_LEFT, 70,  L"Group");
		lvProposal.SetImageList(imageList,true);
		Sys::Format(cmd,L"SELECT c.course_key,c.descr,p.last_name_p+' '+p.last_name_m+', '+p.name,cl.descr,\
								CASE w.week_day_id\
									WHEN 1 THEN 'Mon-Wen-Fri'\
									WHEN 2 THEN 'Thu-Tue'\
								END,\
								CONVERT(varchar(15),cte.begin_time,100) + ' - ' + CONVERT(varchar(15),cte.end_time,100), pt.grupo\
						  FROM course c,professor p, classroom cl, week_day w, course_time ct, classtime cte, perturbation pt\
						  WHERE c.course_id=pt.course_id\
								AND p.professor_id=pt.professor_id\
								AND cl.classroom_id=pt.classroom_id\
								AND c.course_id=ct.course_id\
								AND w.week_day_id=ct.week_day_id\
								AND cte.classtime_id=ct.classtime_id\
								AND w.week_day_id BETWEEN 1 AND 2\
								AND ct.grupo=pt.grupo ORDER BY c.course_id, pt.grupo");
		try
		{
			conn.OpenSession(DSN, USERNAME, PASSWORD);
			conn.ExecuteSelect(cmd,100,lvProposal);
			Sys::Format(cmd, L"SELECT course_id, professor_id, classroom_id, grupo FROM perturbation ORDER BY course_id, grupo");
			conn.ExecuteSelect(cmd);
			conn.BindColumn(1,IDs.course);
			conn.BindColumn(2,IDs.professor);
			conn.BindColumn(3,IDs.classroom);
			conn.BindColumn(4, IDs.group,2);
			while(conn.Fetch())
			{
				idsol.push_back(IDs);
			}
			conn.CloseSession();
		
		}
		catch (Sql::SqlException e)
		{
			this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		}

		int resultCheck=-1;
		//Putting the images
		int idsolSize=idsol.size();
		for(int i=0;i<idsolSize;i++)
		{
			resultCheck=checkImage(idsol[i].course, (char)idsol[i].group[0]);
			lvProposal.Items[i].SetImageIndex(resultCheck);
		}
		btGenerate.SetEnable(true);
	}
	else
	{
		isCLickleable=false;
		lvProposal.SetRedraw(false);
		lvProposal.Items.DeleteAll();
		lvProposal.Cols.DeleteAll();
		lvProposal.Cols.Add(0, LVCFMT_LEFT, 90, L"Course Key");
		lvProposal.Cols.Add(1, LVCFMT_LEFT, 230, L"Course");
		lvProposal.Cols.Add(2, LVCFMT_LEFT, 200, L"Professor");
		lvProposal.Cols.Add(3, LVCFMT_LEFT, 70,  L"Classroom");
		lvProposal.Cols.Add(4, LVCFMT_LEFT, 80,  L"Days");
		lvProposal.Cols.Add(5, LVCFMT_LEFT, 150,  L"Classtime");
		lvProposal.Cols.Add(6, LVCFMT_LEFT, 70,  L"Group");
		Sys::Format(cmd,L"SELECT c.course_key,c.descr,p.last_name_p+' '+p.last_name_m+', '+p.name,cl.descr,\
								CASE w.week_day_id\
									WHEN 1 THEN 'Mon-Wen-Fri'\
									WHEN 2 THEN 'Thu-Tue'\
								END,\
								CONVERT(varchar(15),cte.begin_time,100) + ' - ' + CONVERT(varchar(15),cte.end_time,100), s.grupo\
						  FROM course c,professor p, classroom cl, week_day w, classtime cte, schedule s\
						  WHERE c.course_id=s.course_id\
								AND p.professor_id=s.professor_id\
								AND cl.classroom_id=s.classroom_id\
								AND w.week_day_id=s.week_day_id\
								AND w.week_day_id BETWEEN 1 AND 2\
								AND s.classtime_id=cte.classtime_id\
								AND s.period_id=%d ORDER BY c.course_id, s.grupo", period_id);
		try
		{
			conn.OpenSession(DSN, USERNAME, PASSWORD);
			conn.ExecuteSelect(cmd,100,lvProposal);
			conn.CloseSession();
		}
		catch (Sql::SqlException e)
		{
			this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		}
		btGenerate.SetEnable(false);

	}
	lvProposal.SetRedraw(true);
}

void TimesUniv::ddPeriod_SelChange(Win::Event& e)
{
	loadAssignments();
	loadProposals();
}
void TimesUniv::ddCareer_SelChange(Win::Event& e)
{
	loadAssignments();
}
void TimesUniv::lvProposal_ColumnClick(Win::Event& e)
{
}
void TimesUniv::lvProposal_DblClk(Win::Event& e)
{
	if(isCLickleable==false) return;
	int index=-1;
	const int period=ddPeriod.GetSelectedIndex();
	if(period<0)return;
	int period_id=ddPeriod.GetSelectedData();
	EditCourseDlg dlg;
	index=lvProposal.GetSelectedIndex();
	if(index<0) return;
	if(idsol[index].course<=0) return;
	dlg.professor_id=idsol[index].professor;
	dlg.course_id=idsol[index].course;
	dlg.group=(char)idsol[index].group[0];
	dlg.classroom_id=idsol[index].classroom;
	dlg.errorDescr=checkErrorDescription(idsol[index].course, (char)idsol[index].group[0]);
	dlg.period_id=period_id;
	dlg.BeginDialog(hWnd);
	loadProposals();
}
int TimesUniv::checkImage(int course, char group)
{
	int solSize=solution.errorCourses.size();
	for(int i=0; i<solSize; i++)
	{
		if(solution.errorCourses[i].course_id==course && solution.errorCourses[i].grupo==group)
			return 0;
	}
	return 1;
}

wstring TimesUniv::checkErrorDescription(int course, char group)
{
	int solSize=solution.errorCourses.size();
	for(int i=0; i<solSize; i++)
	{
		if(solution.errorCourses[i].course_id==course && solution.errorCourses[i].grupo==group)
			return solution.errorCourses[i].descr;
	} 
	return L"There's no error on this assignation";
}