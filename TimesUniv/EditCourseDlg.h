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
	Win::Button gbox4;
	Win::Button gbox3;
	Win::Button gbox2;
	Win::Button btOk;
	Win::Button btCancel;
	Win::Label lb5;
	Win::Textbox tbxQuota;
	Win::Label lb4;
	Win::DropDownList ddHours;
	Win::Label lb3;
	Win::DropDownList ddClassroom;
	Win::Textbox tbxError;
	Win::Textbox tbxCourse;
	Win::Textbox tbxProfessor;
	Win::Textbox tbxGroup;
	Win::Label lb1;
	Win::Label lb2;
	Win::Label lb6;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(585);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(335);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		gbox4.Create(WS_EX_TRANSPARENT, L"Editable data:", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 21, 180, 544, 103, hWnd, 1000);
		gbox3.Create(WS_EX_TRANSPARENT, L"Data:", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 21, 72, 544, 104, hWnd, 1001);
		gbox2.Create(WS_EX_TRANSPARENT, L"Error description:", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 21, 10, 544, 58, hWnd, 1002);
		btOk.Create(NULL, L"Accept", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 465, 287, 88, 28, hWnd, 1003);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 369, 287, 88, 28, hWnd, 1004);
		lb5.Create(NULL, L"Quota:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 31, 257, 45, 25, hWnd, 1005);
		tbxQuota.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 124, 252, 121, 25, hWnd, 1006);
		lb4.Create(NULL, L"Class Hours:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 31, 228, 85, 25, hWnd, 1007);
		ddHours.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 124, 223, 430, 25, hWnd, 1008);
		lb3.Create(NULL, L"Classroom:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 31, 199, 72, 25, hWnd, 1009);
		ddClassroom.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 124, 194, 430, 25, hWnd, 1010);
		tbxError.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_READONLY | ES_LEFT | ES_WINNORMALCASE, 32, 30, 522, 25, hWnd, 1011);
		tbxCourse.Create(WS_EX_CLIENTEDGE, L"Course Name: ", WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_READONLY | ES_LEFT | ES_WINNORMALCASE, 124, 86, 430, 25, hWnd, 1012);
		tbxProfessor.Create(WS_EX_CLIENTEDGE, L"Professor: ", WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_READONLY | ES_LEFT | ES_WINNORMALCASE, 124, 115, 430, 25, hWnd, 1013);
		tbxGroup.Create(WS_EX_CLIENTEDGE, L"Group:", WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_READONLY | ES_LEFT | ES_WINNORMALCASE, 124, 144, 430, 25, hWnd, 1014);
		lb1.Create(NULL, L"Course name:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 31, 92, 92, 25, hWnd, 1015);
		lb2.Create(NULL, L"Professor:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 31, 121, 70, 25, hWnd, 1016);
		lb6.Create(NULL, L"Group:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 31, 150, 46, 18, hWnd, 1017);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		gbox4.Font = fontArial014A;
		gbox3.Font = fontArial014A;
		gbox2.Font = fontArial014A;
		btOk.Font = fontArial014A;
		btCancel.Font = fontArial014A;
		lb5.Font = fontArial014A;
		tbxQuota.Font = fontArial014A;
		lb4.Font = fontArial014A;
		ddHours.Font = fontArial014A;
		lb3.Font = fontArial014A;
		ddClassroom.Font = fontArial014A;
		tbxError.Font = fontArial014A;
		tbxCourse.Font = fontArial014A;
		tbxProfessor.Font = fontArial014A;
		tbxGroup.Font = fontArial014A;
		lb1.Font = fontArial014A;
		lb2.Font = fontArial014A;
		lb6.Font = fontArial014A;
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
