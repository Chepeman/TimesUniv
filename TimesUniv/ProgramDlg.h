#pragma once   //_____________________________________________ ProgramDlg.h  
#include "resource.h"

class ProgramDlg: public Win::Dialog
{
public:
	ProgramDlg()
	{
		program_id=-1;
	}
	~ProgramDlg()
	{
	}
	int program_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Label lbDescr;
	Win::Textbox tbxDescr;
	Win::Label lbCareer_name;
	Win::Textbox tbxCareer_name;
	Win::Label lbDepartment;
	Win::DropDownList ddDepartment;
	Win::Button btOK;
	Win::Button btCancel;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(415);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(111);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		lbDescr.Create(NULL, L"Program Key:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 14, 87, 19, hWnd, 1000);
		tbxDescr.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 109, 10, 200, 25, hWnd, 1001);
		lbCareer_name.Create(NULL, L"Program Name:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 42, 98, 18, hWnd, 1002);
		tbxCareer_name.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 109, 38, 200, 25, hWnd, 1003);
		lbDepartment.Create(NULL, L"Department:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 70, 79, 16, hWnd, 1004);
		ddDepartment.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 109, 66, 200, 25, hWnd, 1005);
		btOK.Create(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 315, 10, 80, 28, hWnd, 1006);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 315, 40, 80, 28, hWnd, 1007);
		this->SetDefaultButton(btOK);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lbDescr.Font = fontArial014A;
		tbxDescr.Font = fontArial014A;
		lbCareer_name.Font = fontArial014A;
		tbxCareer_name.Font = fontArial014A;
		lbDepartment.Font = fontArial014A;
		ddDepartment.Font = fontArial014A;
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
