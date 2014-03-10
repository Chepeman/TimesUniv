#pragma once   //_____________________________________________ UpDownDlg.h  
#include "resource.h"
#include "AddCourseUD.h"

struct Asignation2 //Needs to be modified, adding the quota and professor hours
{
	int classroom;
	int hour;
	int professor;
	int course;
	int classtime;
	int days;
	wchar_t group[2];

};

class UpDownDlg: public Win::Dialog
{
public:
	UpDownDlg()
	{
	}
	~UpDownDlg()
	{
	}
	vector<struct Asignation2> asign;
	int cu_period;
	int career_id,isEditing;
	void loadSchedule(void);
	void editSchedule(void);
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Button gbox1;
	Win::DropDownList ddCareer;
	Win::ListView lvModify;
	Win::Button btAddC;
	Win::Button btDeleteM;
	Win::Button btEdit;
	Win::Label lb1;
	Win::Button bt4;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(981);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(615);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		gbox1.Create(WS_EX_TRANSPARENT, L"Schedule:", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 17, 9, 944, 552, hWnd, 1000);
		ddCareer.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 772, 25, 180, 25, hWnd, 1001);
		lvModify.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_REPORT, 30, 54, 922, 496, hWnd, 1002);
		btAddC.Create(NULL, L"Add", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 863, 567, 92, 28, hWnd, 1003);
		btDeleteM.Create(NULL, L"Delete", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 765, 567, 92, 28, hWnd, 1004);
		btEdit.Create(NULL, L"Edit", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 667, 567, 92, 28, hWnd, 1005);
		lb1.Create(NULL, L"Career:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 717, 32, 52, 16, hWnd, 1006);
		bt4.Create(NULL, L"Close", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 569, 567, 92, 28, hWnd, 1007);
		lvModify.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		gbox1.Font = fontArial014A;
		ddCareer.Font = fontArial014A;
		lvModify.Font = fontArial014A;
		btAddC.Font = fontArial014A;
		btDeleteM.Font = fontArial014A;
		btEdit.Font = fontArial014A;
		lb1.Font = fontArial014A;
		bt4.Font = fontArial014A;
	}
	//_________________________________________________
	void ddCareer_SelChange(Win::Event& e);
	void btAddC_Click(Win::Event& e);
	void btDeleteM_Click(Win::Event& e);
	void btEdit_Click(Win::Event& e);
	void bt4_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (ddCareer.IsEvent(e, CBN_SELCHANGE)) {ddCareer_SelChange(e); return true;}
		if (btAddC.IsEvent(e, BN_CLICKED)) {btAddC_Click(e); return true;}
		if (btDeleteM.IsEvent(e, BN_CLICKED)) {btDeleteM_Click(e); return true;}
		if (btEdit.IsEvent(e, BN_CLICKED)) {btEdit_Click(e); return true;}
		if (bt4.IsEvent(e, BN_CLICKED)) {bt4_Click(e); return true;}
		return false;
	}
};
