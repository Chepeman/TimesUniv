#pragma once   //_____________________________________________ UpDownDlg.h  
#include "resource.h"

class UpDownDlg: public Win::Dialog
{
public:
	UpDownDlg()
	{
	}
	~UpDownDlg()
	{
	}
	int cu_period;
	void loadSchedule(void);
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Button gbox1;
	Win::DropDownList ddCareer;
	Win::ListView lvModify;
	Win::Button btAddC;
	Win::Button btDeleteM;
	Win::Button btClose;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(1029);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(644);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		gbox1.Create(WS_EX_TRANSPARENT, L"UpDown", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 65, 49, 944, 575, hWnd, 1000);
		ddCareer.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 88, 76, 180, 25, hWnd, 1001);
		lvModify.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_REPORT, 88, 111, 892, 455, hWnd, 1002);
		btAddC.Create(NULL, L"Add", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 593, 578, 113, 28, hWnd, 1003);
		btDeleteM.Create(NULL, L"Delete", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 723, 577, 124, 28, hWnd, 1004);
		btClose.Create(NULL, L"Close", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 861, 580, 123, 28, hWnd, 1005);
		lvModify.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		gbox1.Font = fontArial014A;
		ddCareer.Font = fontArial014A;
		lvModify.Font = fontArial014A;
		btAddC.Font = fontArial014A;
		btDeleteM.Font = fontArial014A;
		btClose.Font = fontArial014A;
	}
	//_________________________________________________
	void ddCareer_SelChange(Win::Event& e);
	void btAddC_Click(Win::Event& e);
	void btDeleteM_Click(Win::Event& e);
	void btClose_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (ddCareer.IsEvent(e, CBN_SELCHANGE)) {ddCareer_SelChange(e); return true;}
		if (btAddC.IsEvent(e, BN_CLICKED)) {btAddC_Click(e); return true;}
		if (btDeleteM.IsEvent(e, BN_CLICKED)) {btDeleteM_Click(e); return true;}
		if (btClose.IsEvent(e, BN_CLICKED)) {btClose_Click(e); return true;}
		return false;
	}
};
