#pragma once   //_____________________________________________ CoordDlg.h  
#include "resource.h"

class CoordDlg: public Win::Dialog
{
public:
	CoordDlg()
	{
		coordinator_id=-1;
	}
	~CoordDlg()
	{
	}
	int coordinator_id;
	void UpdateddProf();
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Button gbox1;
	Win::Label lbProfessor;
	Win::DropDownList ddProfessor;
	Win::Label lbProgram;
	Win::DropDownList ddProgram;
	Win::Label lbUsername;
	Win::Textbox tbxUsername;
	Win::Label lbPass;
	Win::Textbox tbxPass;
	Win::Button ckIsadmin;
	Win::Button btOK;
	Win::Button btCancel;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(333);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(242);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		gbox1.Create(WS_EX_TRANSPARENT, L"Data:", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 19, 13, 294, 174, hWnd, 1000);
		lbProfessor.Create(NULL, L"Professor:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 69, 69, 16, hWnd, 1001);
		ddProfessor.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 101, 61, 200, 25, hWnd, 1002);
		lbProgram.Create(NULL, L"Program:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 39, 59, 18, hWnd, 1003);
		ddProgram.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 101, 32, 200, 25, hWnd, 1004);
		lbUsername.Create(NULL, L"Username:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 28, 98, 70, 16, hWnd, 1005);
		tbxUsername.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 101, 90, 200, 25, hWnd, 1006);
		lbPass.Create(NULL, L"Pass:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 28, 126, 37, 17, hWnd, 1007);
		tbxPass.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_PASSWORD | ES_LEFT | ES_WINNORMALCASE, 101, 120, 200, 25, hWnd, 1008);
		ckIsadmin.Create(NULL, L"Isadmin", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFT | BS_VCENTER, 101, 150, 200, 26, hWnd, 1009);
		btOK.Create(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 222, 194, 80, 28, hWnd, 1010);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 137, 194, 80, 28, hWnd, 1011);
		this->SetDefaultButton(btOK);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		gbox1.Font = fontArial014A;
		lbProfessor.Font = fontArial014A;
		ddProfessor.Font = fontArial014A;
		lbProgram.Font = fontArial014A;
		ddProgram.Font = fontArial014A;
		lbUsername.Font = fontArial014A;
		tbxUsername.Font = fontArial014A;
		lbPass.Font = fontArial014A;
		tbxPass.Font = fontArial014A;
		ckIsadmin.Font = fontArial014A;
		btOK.Font = fontArial014A;
		btCancel.Font = fontArial014A;
	}
	//_________________________________________________
	void ddProgram_SelChange(Win::Event& e);
	void btOK_Click(Win::Event& e);
	void btCancel_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (ddProgram.IsEvent(e, CBN_SELCHANGE)) {ddProgram_SelChange(e); return true;}
		if (btOK.IsEvent(e, BN_CLICKED)) {btOK_Click(e); return true;}
		if (btCancel.IsEvent(e, BN_CLICKED)) {btCancel_Click(e); return true;}
		return false;
	}
};
