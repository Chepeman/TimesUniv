#pragma once   //_____________________________________________ DeptDlg.h  
#include "resource.h"

class DeptDlg: public Win::Dialog
{
public:
	DeptDlg()
	{
		department_id=-1;
	}
	~DeptDlg()
	{
	}
	int department_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Label lbDescr;
	Win::Textbox tbxDescr;
	Win::Button btOK;
	Win::Button btCancel;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(360);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(91);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		lbDescr.Create(NULL, L"Department Name:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 16, 15, 122, 19, hWnd, 1000);
		tbxDescr.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 140, 12, 200, 25, hWnd, 1001);
		btOK.Create(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 259, 43, 80, 28, hWnd, 1002);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 176, 43, 80, 28, hWnd, 1003);
		this->SetDefaultButton(btOK);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lbDescr.Font = fontArial014A;
		tbxDescr.Font = fontArial014A;
		btOK.Font = fontArial014A;
		btCancel.Font = fontArial014A;
	}
	//_________________________________________________
	void btOK_Click(Win::Event& e);
	void btCancel_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (btOK.IsEvent(e, BN_CLICKED)) {btOK_Click(e); return true;}
		if (btCancel.IsEvent(e, BN_CLICKED)) {btCancel_Click(e); return true;}
		return false;
	}
};
