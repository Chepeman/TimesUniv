#pragma once   //_____________________________________________ ScheduleDlg.h  
#include "resource.h"

struct ScheduleID //Needs to be modified, adding the quota and professor hours
{
	int professor_id;
	int course_id;
	int classroom_id;
	int classhours;
	int onetwo;
	wchar_t grupo[2];
	wstring periodDateEnd;
};
class ScheduleDlg: public Win::Dialog
{
public:
	ScheduleDlg()
	{
	}
	~ScheduleDlg()
	{
	}
	int period_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Button gbox1;
	Win::ListView lvSchedule;
	Win::Button btOk;
	Win::Button btCancel;
	
	
	vector<ScheduleID> schedule;
	void makeRandoms(void);
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(1065);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(645);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		gbox1.Create(WS_EX_TRANSPARENT, L"Schedule: ", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 51, 26, 990, 563, hWnd, 1000);
		lvSchedule.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_REPORT, 62, 46, 968, 529, hWnd, 1001);
		btOk.Create(NULL, L"O.k.", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 812, 597, 113, 28, hWnd, 1002);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 934, 596, 111, 28, hWnd, 1003);
		lvSchedule.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		this->SetDefaultButton(btOk);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		gbox1.Font = fontArial014A;
		lvSchedule.Font = fontArial014A;
		btOk.Font = fontArial014A;
		btCancel.Font = fontArial014A;
	}
	//_________________________________________________
	void btOk_Click(Win::Event& e);
	void btCancel_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (btOk.IsEvent(e, BN_CLICKED)) {btOk_Click(e); return true;}
		if (btCancel.IsEvent(e, BN_CLICKED)) {btCancel_Click(e); return true;}
		return false;
	}
};
