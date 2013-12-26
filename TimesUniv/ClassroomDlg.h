#pragma once   //_____________________________________________ ClassroomDlg.h  
#include "resource.h"

class ClassroomDlg: public Win::Dialog
{
public:
	ClassroomDlg()
	{
		classroom_id=-1;
	}
	~ClassroomDlg()
	{
	}
	int classroom_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Label lbDescr;
	Win::Textbox tbxDescr;
	Win::Label lbContact_count;
	Win::Textbox tbxContact_count;
	Win::Label lbSeat_count;
	Win::Textbox tbxSeat_count;
	Win::Button ckHas_projector;
	Win::Button ckHas_tables;
	Win::Button btOK;
	Win::Button btCancel;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(417);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(175);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		lbDescr.Create(NULL, L"Description:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 11, 14, 78, 18, hWnd, 1000);
		tbxDescr.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 107, 10, 200, 25, hWnd, 1001);
		lbContact_count.Create(NULL, L"Contact Count:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 47, 95, 17, hWnd, 1002);
		tbxContact_count.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 107, 41, 200, 25, hWnd, 1003);
		lbSeat_count.Create(NULL, L"Seat Count:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 79, 76, 17, hWnd, 1004);
		tbxSeat_count.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 107, 72, 200, 25, hWnd, 1005);
		ckHas_projector.Create(NULL, L"Has projector", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFT | BS_VCENTER, 107, 103, 200, 26, hWnd, 1006);
		ckHas_tables.Create(NULL, L"Has tables", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFT | BS_VCENTER, 107, 129, 200, 26, hWnd, 1007);
		btOK.Create(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 317, 10, 80, 28, hWnd, 1008);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 317, 43, 80, 28, hWnd, 1009);
		this->SetDefaultButton(btOK);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lbDescr.Font = fontArial014A;
		tbxDescr.Font = fontArial014A;
		lbContact_count.Font = fontArial014A;
		tbxContact_count.Font = fontArial014A;
		lbSeat_count.Font = fontArial014A;
		tbxSeat_count.Font = fontArial014A;
		ckHas_projector.Font = fontArial014A;
		ckHas_tables.Font = fontArial014A;
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
