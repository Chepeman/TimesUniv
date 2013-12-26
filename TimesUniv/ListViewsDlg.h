#pragma once   //_____________________________________________ ListViewsDlg.h  
#include "resource.h"
#include "CoordDlg.h"
#include "ProfDlg.h"
#include "ProgramDlg.h"
#include "CourseDlg.h"
#include "DeptDlg.h"
#include "PeriodDlg.h"
#include "ClassroomDlg.h"
#include "TimeDlg.h"

#define COORDINATOR 1
#define PROFESSOR 2
#define CAREER 3
#define COURSE 4
#define DEPARTMENT 5
#define PERIOD 6
#define CLASSROOM 7
#define CLASSTIME 8

class ListViewsDlg: public Win::Dialog
{
public:
	ListViewsDlg()
	{
		selected=-1;
	}
	~ListViewsDlg()
	{
	}
	int selected;
	void UpdateLvCoord();
	void UpdateLvProf();
	void UpdateLvCareer();
	void UpdateLvCourse();
	void UpdateLvDept();
	void UpdateLvPeriod();
	void UpdateLvClassroom();
	void UpdateLvTime();
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Toolbar toolbMain;
	Win::ListView lvMain;
	Win::Button btClose;
	Win::DropDownList ddCareer;
	Win::Label lb1;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(930);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(545);
		dlgTemplate.style = WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_POPUP | WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		toolbMain.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | CCS_NORESIZE | CCS_NOPARENTALIGN | CCS_ADJUSTABLE | CCS_NODIVIDER | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS, 17, 16, 676, 44, hWnd, 1000);
		lvMain.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_REPORT, 17, 63, 893, 428, hWnd, 1001);
		btClose.Create(NULL, L"Close", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 808, 497, 102, 28, hWnd, 1002);
		ddCareer.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 697, 34, 213, 25, hWnd, 1003);
		lb1.Create(NULL, L"Career:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 697, 18, 50, 15, hWnd, 1004);
		lvMain.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lvMain.Font = fontArial014A;
		btClose.Font = fontArial014A;
		ddCareer.Font = fontArial014A;
		lb1.Font = fontArial014A;
		toolbMain.SetDock(DOCK_BORDER, DOCK_BORDER, DOCK_BORDER, DOCK_NONE);
		lvMain.SetDock(DOCK_BORDER, DOCK_BORDER, DOCK_BORDER, DOCK_BORDER);
		btClose.SetDock(DOCK_NONE, DOCK_NONE, DOCK_BORDER, DOCK_BORDER);
	}
	//_________________________________________________
	void lvMain_ItemChanged(Win::Event& e);
	void lvMain_DblClk(Win::Event& e);
	void btClose_Click(Win::Event& e);
	void ddCareer_SelChange(Win::Event& e);
	void Window_Open(Win::Event& e);
	void Cmd_Print(Win::Event& e);
	void Cmd_Insert(Win::Event& e);
	void Cmd_Delete(Win::Event& e);
	void Cmd_Edit(Win::Event& e);
	void Cmd_Copy(Win::Event& e);
	void Cmd_Msexcel(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (lvMain.IsEvent(e, LVN_ITEMCHANGED)) {lvMain_ItemChanged(e); return true;}
		if (lvMain.IsEvent(e, NM_DBLCLK)) {lvMain_DblClk(e); return true;}
		if (btClose.IsEvent(e, BN_CLICKED)) {btClose_Click(e); return true;}
		if (ddCareer.IsEvent(e, CBN_SELCHANGE)) {ddCareer_SelChange(e); return true;}
		if (this->IsEvent(e, IDM_PRINT)) {Cmd_Print(e); return true;}
		if (this->IsEvent(e, IDM_INSERT)) {Cmd_Insert(e); return true;}
		if (this->IsEvent(e, IDM_DELETE)) {Cmd_Delete(e); return true;}
		if (this->IsEvent(e, IDM_EDIT)) {Cmd_Edit(e); return true;}
		if (this->IsEvent(e, IDM_COPY)) {Cmd_Copy(e); return true;}
		if (this->IsEvent(e, IDM_MSEXCEL)) {Cmd_Msexcel(e); return true;}
		return false;
	}
};
