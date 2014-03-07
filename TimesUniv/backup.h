#pragma once   //_____________________________________________ CoordMng.h  
#include "resource.h"

class Assign
{
public:
	Assign()
	{
		course_id=-1;
		professor_id=-1;
		period_id=-1;
	}
	
	~Assign()
	{
	}
	int course_id;
	int professor_id;
	int period_id;
	wchar_t group[2];
};

class CoordMng: public Win::Dialog
{
public:
	CoordMng()
	{
		career_id=-1;
	}
	~CoordMng()
	{
	}
	vector<Assign> assign;
	int career_id;
	void loadAssignments();
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Button gbox2;
	Win::Button gbox1;
	Win::ListView lvProfessor;
	Win::ListView lvCourse;
	Win::Label lb1;
	Win::Label lb2;
	Win::Button btAdd;
	Win::ListView lvAsign;
	Win::Label lb3;
	Win::Textbox tbxCupo;
	Win::Label lb4;
	Win::Label lb5;
	Win::Textbox tbxPeriod;
	Win::Button btDelete;
	Win::Button btClose;
	Win::Button btSched;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(1198);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(564);
		dlgTemplate.style = WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		gbox2.Create(WS_EX_TRANSPARENT, NULL, WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 527, 2, 651, 542, hWnd, 1000);
		gbox1.Create(WS_EX_TRANSPARENT, NULL, WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 12, 2, 508, 542, hWnd, 1001);
		lvProfessor.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_SHOWSELALWAYS | LVS_REPORT, 18, 32, 495, 219, hWnd, 1002);
		lvCourse.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_SHOWSELALWAYS | LVS_REPORT, 18, 279, 495, 219, hWnd, 1003);
		lb1.Create(NULL, L"Courses", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 18, 261, 57, 16, hWnd, 1004);
		lb2.Create(NULL, L"Professors", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 18, 14, 74, 16, hWnd, 1005);
		btAdd.Create(NULL, L"Add", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 444, 504, 67, 28, hWnd, 1006);
		lvAsign.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_SHOWSELALWAYS | LVS_REPORT, 535, 32, 634, 466, hWnd, 1007);
		lb3.Create(NULL, L"Enlist:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 535, 14, 74, 16, hWnd, 1008);
		tbxCupo.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 70, 504, 110, 27, hWnd, 1009);
		lb4.Create(NULL, L"Quota:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 23, 510, 45, 16, hWnd, 1010);
		lb5.Create(NULL, L"Period:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 538, 511, 48, 16, hWnd, 1011);
		tbxPeriod.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_READONLY | ES_LEFT | ES_WINNORMALCASE, 587, 504, 299, 25, hWnd, 1012);
		btDelete.Create(NULL, L"Delete", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 1016, 503, 67, 28, hWnd, 1013);
		btClose.Create(NULL, L"Close", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 946, 503, 67, 28, hWnd, 1014);
		btSched.Create(NULL, L"Schedule", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 1086, 503, 81, 28, hWnd, 1015);
		lvProfessor.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		lvCourse.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		lvAsign.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		this->SetDefaultButton(btAdd);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		gbox2.Font = fontArial014A;
		gbox1.Font = fontArial014A;
		lvProfessor.Font = fontArial014A;
		lvCourse.Font = fontArial014A;
		lb1.Font = fontArial014A;
		lb2.Font = fontArial014A;
		btAdd.Font = fontArial014A;
		lvAsign.Font = fontArial014A;
		lb3.Font = fontArial014A;
		tbxCupo.Font = fontArial014A;
		lb4.Font = fontArial014A;
		lb5.Font = fontArial014A;
		tbxPeriod.Font = fontArial014A;
		btDelete.Font = fontArial014A;
		btClose.Font = fontArial014A;
		btSched.Font = fontArial014A;
		gbox2.SetDock(DOCK_CENTER, DOCK_BORDER, DOCK_BORDER, DOCK_BORDER);
		gbox1.SetDock(DOCK_BORDER, DOCK_BORDER, DOCK_CENTER, DOCK_BORDER);
		lvProfessor.SetDock(DOCK_BORDER, DOCK_BORDER, DOCK_CENTER, DOCK_CENTER);
		lvCourse.SetDock(DOCK_BORDER, DOCK_CENTER, DOCK_CENTER, DOCK_BORDER);
		lb1.SetDock(DOCK_BORDER, DOCK_NONE, DOCK_NONE, DOCK_CENTER);
		lb2.SetDock(DOCK_NONE, DOCK_NONE, DOCK_NONE, DOCK_NONE);
		btAdd.SetDock(DOCK_NONE, DOCK_NONE, DOCK_CENTER, DOCK_BORDER);
		lvAsign.SetDock(DOCK_CENTER, DOCK_BORDER, DOCK_BORDER, DOCK_BORDER);
		lb3.SetDock(DOCK_CENTER, DOCK_BORDER, DOCK_BORDER, DOCK_NONE);
		tbxCupo.SetDock(DOCK_BORDER, DOCK_NONE, DOCK_NONE, DOCK_BORDER);
		lb4.SetDock(DOCK_BORDER, DOCK_NONE, DOCK_NONE, DOCK_BORDER);
		lb5.SetDock(DOCK_CENTER, DOCK_NONE, DOCK_NONE, DOCK_BORDER);
		tbxPeriod.SetDock(DOCK_CENTER, DOCK_NONE, DOCK_NONE, DOCK_BORDER);
		btDelete.SetDock(DOCK_NONE, DOCK_NONE, DOCK_BORDER, DOCK_BORDER);
		btClose.SetDock(DOCK_NONE, DOCK_NONE, DOCK_BORDER, DOCK_BORDER);
		btSched.SetDock(DOCK_NONE, DOCK_NONE, DOCK_BORDER, DOCK_BORDER);
	}
	//_________________________________________________
	void btAdd_Click(Win::Event& e);
	void lvAsign_DblClk(Win::Event& e);
	void btDelete_Click(Win::Event& e);
	void btClose_Click(Win::Event& e);
	void btSched_Click(Win::Event& e);
	void Window_Close(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (btAdd.IsEvent(e, BN_CLICKED)) {btAdd_Click(e); return true;}
		if (lvAsign.IsEvent(e, NM_DBLCLK)) {lvAsign_DblClk(e); return true;}
		if (btDelete.IsEvent(e, BN_CLICKED)) {btDelete_Click(e); return true;}
		if (btClose.IsEvent(e, BN_CLICKED)) {btClose_Click(e); return true;}
		if (btSched.IsEvent(e, BN_CLICKED)) {btSched_Click(e); return true;}
		return false;
	}
};
