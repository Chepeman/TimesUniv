#pragma once   //_____________________________________________ ProfDlg.h  
#include "resource.h"

class ProfDlg: public Win::Dialog
{
public:
	ProfDlg()
	{
		professor_id=-1;
	}
	~ProfDlg()
	{
	}
	int professor_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Button gbox1;
	Win::Label lbLast_name_p;
	Win::Textbox tbxLast_name_p;
	Win::Label lbLast_name_m;
	Win::Textbox tbxLast_name_m;
	Win::Label lbName;
	Win::Textbox tbxName;
	Win::Label lbEmail;
	Win::Textbox tbxEmail;
	Win::Label lbExtension;
	Win::Textbox tbxExtension;
	Win::Label lbDepartment;
	Win::DropDownList ddDepartment;
	Win::Button ckPromep;
	Win::Button ckSni;
	Win::Button btOK;
	Win::Button btCancel;
	Win::Button ckBase;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(346);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(348);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		gbox1.Create(WS_EX_TRANSPARENT, L"Data:", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 19, 11, 307, 284, hWnd, 1000);
		lbLast_name_p.Create(NULL, L"Last Name 1:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 39, 84, 17, hWnd, 1001);
		tbxLast_name_p.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 117, 33, 200, 25, hWnd, 1002);
		lbLast_name_m.Create(NULL, L"Last Name 2:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 70, 84, 16, hWnd, 1003);
		tbxLast_name_m.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 117, 63, 200, 25, hWnd, 1004);
		lbName.Create(NULL, L"Name:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 99, 84, 17, hWnd, 1005);
		tbxName.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 117, 93, 200, 25, hWnd, 1006);
		lbEmail.Create(NULL, L"Email:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 131, 84, 16, hWnd, 1007);
		tbxEmail.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 117, 123, 200, 25, hWnd, 1008);
		lbExtension.Create(NULL, L"Extension:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 160, 84, 17, hWnd, 1009);
		tbxExtension.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 117, 153, 200, 25, hWnd, 1010);
		lbDepartment.Create(NULL, L"Department:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 191, 84, 17, hWnd, 1011);
		ddDepartment.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 117, 183, 200, 25, hWnd, 1012);
		ckPromep.Create(NULL, L"Promep", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFT | BS_VCENTER, 117, 210, 200, 26, hWnd, 1013);
		ckSni.Create(NULL, L"Sni", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFT | BS_VCENTER, 117, 236, 200, 26, hWnd, 1014);
		btOK.Create(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 237, 300, 80, 28, hWnd, 1015);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 152, 300, 80, 28, hWnd, 1016);
		ckBase.Create(NULL, L"Full Time", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFT | BS_VCENTER, 117, 262, 200, 26, hWnd, 1017);
		this->SetDefaultButton(btOK);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		gbox1.Font = fontArial014A;
		lbLast_name_p.Font = fontArial014A;
		tbxLast_name_p.Font = fontArial014A;
		lbLast_name_m.Font = fontArial014A;
		tbxLast_name_m.Font = fontArial014A;
		lbName.Font = fontArial014A;
		tbxName.Font = fontArial014A;
		lbEmail.Font = fontArial014A;
		tbxEmail.Font = fontArial014A;
		lbExtension.Font = fontArial014A;
		tbxExtension.Font = fontArial014A;
		lbDepartment.Font = fontArial014A;
		ddDepartment.Font = fontArial014A;
		ckPromep.Font = fontArial014A;
		ckSni.Font = fontArial014A;
		btOK.Font = fontArial014A;
		btCancel.Font = fontArial014A;
		ckBase.Font = fontArial014A;
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
