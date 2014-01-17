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
	Win::Button gbox2;
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
	Win::ListView clDays;
	Win::Button gbox3;
	Win::ListView clHours;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(747);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(324);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		gbox2.Create(WS_EX_TRANSPARENT, L"Avaliable Days:", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 334, 11, 193, 258, hWnd, 1000);
		gbox1.Create(WS_EX_TRANSPARENT, L"Data:", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 19, 11, 307, 257, hWnd, 1001);
		lbLast_name_p.Create(NULL, L"Last Name 1:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 39, 84, 17, hWnd, 1002);
		tbxLast_name_p.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 117, 33, 200, 25, hWnd, 1003);
		lbLast_name_m.Create(NULL, L"Last Name 2:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 70, 84, 16, hWnd, 1004);
		tbxLast_name_m.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 117, 63, 200, 25, hWnd, 1005);
		lbName.Create(NULL, L"Name:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 99, 84, 17, hWnd, 1006);
		tbxName.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 117, 93, 200, 25, hWnd, 1007);
		lbEmail.Create(NULL, L"Email:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 131, 84, 16, hWnd, 1008);
		tbxEmail.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 117, 123, 200, 25, hWnd, 1009);
		lbExtension.Create(NULL, L"Extension:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 160, 84, 17, hWnd, 1010);
		tbxExtension.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 117, 153, 200, 25, hWnd, 1011);
		lbDepartment.Create(NULL, L"Department:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 191, 84, 17, hWnd, 1012);
		ddDepartment.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 117, 183, 200, 25, hWnd, 1013);
		ckPromep.Create(NULL, L"Promep", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFT | BS_VCENTER, 117, 210, 200, 26, hWnd, 1014);
		ckSni.Create(NULL, L"Sni", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFT | BS_VCENTER, 117, 236, 200, 26, hWnd, 1015);
		btOK.Create(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 638, 276, 80, 28, hWnd, 1016);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 553, 276, 80, 28, hWnd, 1017);
		clDays.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_LIST, 343, 31, 174, 229, hWnd, 1018);
		gbox3.Create(WS_EX_TRANSPARENT, L"Avaliable Hours:", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 534, 11, 193, 258, hWnd, 1019);
		clHours.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_LIST, 543, 31, 174, 229, hWnd, 1020);
		clDays.SetExtStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		clHours.SetExtStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		this->SetDefaultButton(btOK);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		gbox2.Font = fontArial014A;
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
		clDays.Font = fontArial014A;
		gbox3.Font = fontArial014A;
		clHours.Font = fontArial014A;
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
