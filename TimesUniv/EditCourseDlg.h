#pragma once   //_____________________________________________ EditCourseDlg.h  
#include "resource.h"

class EditCourseDlg: public Win::Dialog
{
public:
	EditCourseDlg()
	{
		professor_id=-1;
		course_id=-1;
		classroom_id=-1;
		group='Z';
		period_id=-1;
		classhours=-1;
	}
	~EditCourseDlg()
	{
	}

	int professor_id, course_id, classroom_id, period_id, classhours;
	char group;
	wstring errorDescr;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Button gbox1;
	Win::Button btOk;
	Win::Button btCancel;
	Win::Label lb1;
	Win::Label lb2;
	Win::Label lb3;
	Win::Label lb4;
	Win::Textbox tbxQuota;
	Win::Label lb5;
	Win::DropDownList ddHours;
	Win::Label lb6;
	Win::DropDownList ddClassroom;
	Win::Textbox tbxError;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(734);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(331);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		gbox1.Create(WS_EX_TRANSPARENT, L"Course Information", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 40, 36, 674, 275, hWnd, 1000);
		btOk.Create(NULL, L"Accept", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 480, 276, 107, 28, hWnd, 1001);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 600, 276, 107, 28, hWnd, 1002);
		lb1.Create(NULL, L"Course Name: ", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 50, 59, 203, 34, hWnd, 1003);
		lb2.Create(NULL, L"Professor: ", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 272, 59, 203, 34, hWnd, 1004);
		lb3.Create(NULL, L"Group: ", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 498, 57, 203, 34, hWnd, 1005);
		lb4.Create(NULL, L"Quota", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 50, 119, 79, 25, hWnd, 1006);
		tbxQuota.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 139, 120, 121, 25, hWnd, 1007);
		lb5.Create(NULL, L"Class Hours", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 391, 119, 132, 25, hWnd, 1008);
		ddHours.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 538, 118, 162, 25, hWnd, 1009);
		lb6.Create(NULL, L"Classroom", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 50, 190, 128, 25, hWnd, 1010);
		ddClassroom.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 188, 189, 128, 25, hWnd, 1011);
		tbxError.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_READONLY | ES_LEFT | ES_WINNORMALCASE, 52, 269, 294, 25, hWnd, 1012);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		gbox1.Font = fontArial014A;
		btOk.Font = fontArial014A;
		btCancel.Font = fontArial014A;
		lb1.Font = fontArial014A;
		lb2.Font = fontArial014A;
		lb3.Font = fontArial014A;
		lb4.Font = fontArial014A;
		tbxQuota.Font = fontArial014A;
		lb5.Font = fontArial014A;
		ddHours.Font = fontArial014A;
		lb6.Font = fontArial014A;
		ddClassroom.Font = fontArial014A;
		tbxError.Font = fontArial014A;
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
