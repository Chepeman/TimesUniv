#pragma once  //______________________________________ TimesUniv.h  
#include "resource.h"
#include "AboutDlg.h"
#include "Solution.h"
#include "LoginDlg.h"
#include "ListViewsDlg.h"
#include "CoordMng.h"
#include "EditCourseDlg.h"
#include "ScheduleDlg.h"
#include "UpDownDlg.h"

#define MAIN_TIMER 1

struct CoursesID //Needs to be modified, adding the quota and professor hours
{
	int course;
	int professor;
	int classroom;
	wchar_t group[2];
	int err;
};

class TimesUniv: public Win::Window
{
public:
	TimesUniv()
	{
		
	}
	~TimesUniv()
	{
	}
	void loadAssignments();
	void loadProposals();
	void LoadPeriod();
	void DeleteSchedule();
	vector<Assign> assign;
	Mt::DoubleTs error;
	Solution solution, solutionWork1, solutionWork2; 
	Math::SimulatedAnnealing simAnneal; 
	Mt::ThreadObject threadObject;
	Win::ImageList imageList;
	std::vector<struct CoursesID> idsol;
	const wchar_t * GetClassName(){return L"TIMESUNIV";}
	int checkImage(int course, char group);
	wstring checkErrorDescription(int course, char group);
	bool isCLickleable;
	int current_period;
	void UpDownLoad(int period_idd);
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Toolbar toolbMain;
	Win::Button gbox1;
	Win::Button gbox2;
	Win::DropDownList ddCareer;
	Win::ListView lvAsign;
	Win::ListView lvProposal;
	Win::Button btGenerate;
	Win::Button btClose;
	Win::Button btExport;
	Win::Textbox tbxPeriod;
	Win::Label lb1;
	Win::Button ckOnline;
protected:
	Win::Gdi::Font fontArial014A;
	void GetWindowInformation(CREATESTRUCT& createStruct)
	{
		createStruct.dwExStyle = WS_EX_STATICEDGE;
		createStruct.style = WS_CLIPCHILDREN | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_OVERLAPPEDWINDOW | WS_THICKFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"TimesUniv";
		toolbMain.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | CCS_NORESIZE | CCS_NOPARENTALIGN | CCS_ADJUSTABLE | CCS_NODIVIDER | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS, 18, 1, 964, 42, hWnd, 1000);
		gbox1.Create(WS_EX_TRANSPARENT, NULL, WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 4, 38, 396, 519, hWnd, 1001);
		gbox2.Create(WS_EX_TRANSPARENT, NULL, WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 407, 38, 586, 519, hWnd, 1002);
		ddCareer.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 14, 54, 379, 27, hWnd, 1003);
		lvAsign.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_REPORT, 13, 85, 379, 463, hWnd, 1004);
		lvProposal.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_REPORT, 415, 85, 568, 463, hWnd, 1005);
		btGenerate.Create(NULL, L"Generate", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 763, 561, 110, 28, hWnd, 1006);
		btClose.Create(NULL, L"Close", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 650, 561, 110, 28, hWnd, 1007);
		btExport.Create(NULL, L"Save && Export", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 876, 561, 110, 28, hWnd, 1008);
		tbxPeriod.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_READONLY | ES_LEFT | ES_WINNORMALCASE, 466, 54, 280, 26, hWnd, 1009);
		lb1.Create(NULL, L"Period:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 415, 63, 48, 16, hWnd, 1010);
		ckOnline.Create(NULL, L"Show schedule online:", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT | BS_LEFT | BS_VCENTER, 821, 57, 162, 24, hWnd, 1011);
		lvAsign.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		lvProposal.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		gbox1.Font = fontArial014A;
		gbox2.Font = fontArial014A;
		ddCareer.Font = fontArial014A;
		lvAsign.Font = fontArial014A;
		lvProposal.Font = fontArial014A;
		btGenerate.Font = fontArial014A;
		btClose.Font = fontArial014A;
		btExport.Font = fontArial014A;
		tbxPeriod.Font = fontArial014A;
		lb1.Font = fontArial014A;
		ckOnline.Font = fontArial014A;
		gbox1.SetDock(DOCK_BORDER, DOCK_BORDER, DOCK_CENTER, DOCK_BORDER);
		gbox2.SetDock(DOCK_CENTER, DOCK_BORDER, DOCK_BORDER, DOCK_BORDER);
		ddCareer.SetDock(DOCK_BORDER, DOCK_BORDER, DOCK_CENTER, DOCK_NONE);
		lvAsign.SetDock(DOCK_BORDER, DOCK_BORDER, DOCK_CENTER, DOCK_BORDER);
		lvProposal.SetDock(DOCK_CENTER, DOCK_BORDER, DOCK_BORDER, DOCK_BORDER);
		btGenerate.SetDock(DOCK_NONE, DOCK_NONE, DOCK_BORDER, DOCK_BORDER);
		btClose.SetDock(DOCK_NONE, DOCK_NONE, DOCK_BORDER, DOCK_BORDER);
		btExport.SetDock(DOCK_NONE, DOCK_NONE, DOCK_BORDER, DOCK_BORDER);
		tbxPeriod.SetDock(DOCK_CENTER, DOCK_BORDER, DOCK_BORDER, DOCK_NONE);
		lb1.SetDock(DOCK_CENTER, DOCK_BORDER, DOCK_NONE, DOCK_NONE);
		ckOnline.SetDock(DOCK_NONE, DOCK_BORDER, DOCK_BORDER, DOCK_NONE);
	}
	//_________________________________________________
	void ddCareer_SelChange(Win::Event& e);
	void lvProposal_ColumnClick(Win::Event& e);
	void lvProposal_DblClk(Win::Event& e);
	void btGenerate_Click(Win::Event& e);
	void btClose_Click(Win::Event& e);
	void btExport_Click(Win::Event& e);
	void Window_Close(Win::Event& e);
	void Window_Destroy(Win::Event& e);
	void Window_Open(Win::Event& e);
	void Window_Timer(Win::Event& e);
	void Cmd_Coordinator(Win::Event& e);
	void Cmd_Professor(Win::Event& e);
	void Cmd_Career(Win::Event& e);
	void Cmd_Course(Win::Event& e);
	void Cmd_Dept(Win::Event& e);
	void Cmd_Classroom(Win::Event& e);
	void Cmd_Classtime(Win::Event& e);
	void Cmd_Updown(Win::Event& e);
	void Cmd_Addsch(Win::Event& e);
	void Cmd_Deletesch(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (ddCareer.IsEvent(e, CBN_SELCHANGE)) {ddCareer_SelChange(e); return true;}
		if (lvProposal.IsEvent(e, LVN_COLUMNCLICK)) {lvProposal_ColumnClick(e); return true;}
		if (lvProposal.IsEvent(e, NM_DBLCLK)) {lvProposal_DblClk(e); return true;}
		if (btGenerate.IsEvent(e, BN_CLICKED)) {btGenerate_Click(e); return true;}
		if (btClose.IsEvent(e, BN_CLICKED)) {btClose_Click(e); return true;}
		if (btExport.IsEvent(e, BN_CLICKED)) {btExport_Click(e); return true;}
		if (this->IsEvent(e, IDM_COORDINATOR)) {Cmd_Coordinator(e); return true;}
		if (this->IsEvent(e, IDM_PROFESSOR)) {Cmd_Professor(e); return true;}
		if (this->IsEvent(e, IDM_CAREER)) {Cmd_Career(e); return true;}
		if (this->IsEvent(e, IDM_COURSE)) {Cmd_Course(e); return true;}
		if (this->IsEvent(e, IDM_DEPT)) {Cmd_Dept(e); return true;}
		if (this->IsEvent(e, IDM_CLASSROOM)) {Cmd_Classroom(e); return true;}
		if (this->IsEvent(e, IDM_CLASSTIME)) {Cmd_Classtime(e); return true;}
		if (this->IsEvent(e, IDM_UPDOWN)) {Cmd_Updown(e); return true;}
		if (this->IsEvent(e, IDM_ADDSCH)) {Cmd_Addsch(e); return true;}
		if (this->IsEvent(e, IDM_DELETESCH)) {Cmd_Deletesch(e); return true;}
		return false;
	}
};
