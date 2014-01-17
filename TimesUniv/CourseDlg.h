#pragma once   //_____________________________________________ CourseDlg.h  
#include "resource.h"

class CourseDlg: public Win::Dialog
{
public:
	CourseDlg()
	{
		course_id=-1;
	}
	~CourseDlg()
	{
	}
	int course_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Button gbox2;
	Win::Button gbox1;
	Win::Label lbCourse_key;
	Win::Textbox tbxCourse_key;
	Win::Label lbDescr;
	Win::Textbox tbxDescr;
	Win::Label lbLab;
	Win::DropDownList ddLab;
	Win::Button ckNeed_tables;
	Win::Label lbWeek_hours;
	Win::Textbox tbxWeek_hours;
	Win::Button btOK;
	Win::Button btCancel;
	Win::ListView clProgram;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(882);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(519);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		gbox2.Create(WS_EX_TRANSPARENT, L"Programs:", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 445, 8, 417, 457, hWnd, 1000);
		gbox1.Create(WS_EX_TRANSPARENT, L"Data:", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 20, 8, 417, 457, hWnd, 1001);
		lbCourse_key.Create(NULL, L"Course Key:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 35, 80, 18, hWnd, 1002);
		tbxCourse_key.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 122, 28, 304, 25, hWnd, 1003);
		lbDescr.Create(NULL, L"Course Name:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 69, 92, 17, hWnd, 1004);
		tbxDescr.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 122, 59, 304, 25, hWnd, 1005);
		lbLab.Create(NULL, L"Laboratory:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 94, 73, 18, hWnd, 1006);
		ddLab.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 122, 91, 304, 25, hWnd, 1007);
		ckNeed_tables.Create(NULL, L"Need tables", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFT | BS_VCENTER, 122, 155, 304, 26, hWnd, 1008);
		lbWeek_hours.Create(NULL, L"Week Hours:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 29, 131, 84, 18, hWnd, 1009);
		tbxWeek_hours.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 122, 124, 304, 25, hWnd, 1010);
		btOK.Create(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 772, 471, 80, 28, hWnd, 1011);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 688, 471, 80, 28, hWnd, 1012);
		clProgram.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_VSCROLL | LVS_ALIGNLEFT | LVS_LIST, 454, 28, 399, 429, hWnd, 1013);
		clProgram.SetExtStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		this->SetDefaultButton(btOK);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		gbox2.Font = fontArial014A;
		gbox1.Font = fontArial014A;
		lbCourse_key.Font = fontArial014A;
		tbxCourse_key.Font = fontArial014A;
		lbDescr.Font = fontArial014A;
		tbxDescr.Font = fontArial014A;
		lbLab.Font = fontArial014A;
		ddLab.Font = fontArial014A;
		ckNeed_tables.Font = fontArial014A;
		lbWeek_hours.Font = fontArial014A;
		tbxWeek_hours.Font = fontArial014A;
		btOK.Font = fontArial014A;
		btCancel.Font = fontArial014A;
		clProgram.Font = fontArial014A;
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
