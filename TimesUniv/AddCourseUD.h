#pragma once   //_____________________________________________ AddCourseUD.h  
#include "resource.h"

class AddCourseUD: public Win::Dialog
{
public:
	AddCourseUD()
	{
		isEditing=0;
	}
	~AddCourseUD()
	{
	}
	int current_period;
	int isEditing;
	void editingCourse(void);
	int course_id,professor_id,classroom_id,classtime_id,classdays_id, career_id;
	char grupo;
	void loadByCareer(void);
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Button gbox3;
	Win::Button gbox2;
	Win::Label lb1;
	Win::DropDownList ddCourse;
	Win::Label lb2;
	Win::DropDownList ddProfessor;
	Win::Label lb3;
	Win::DropDownList ddClassroom;
	Win::DropDownList ddCareer;
	Win::Label lb5;
	Win::DropDownList ddClasstime;
	Win::DropDownList ddClassdays;
	Win::Label lb6;
	Win::Button btAccept;
	Win::Button btCancel;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(513);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(288);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		gbox3.Create(WS_EX_TRANSPARENT, L"Data:", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 22, 55, 471, 179, hWnd, 1000);
		gbox2.Create(WS_EX_TRANSPARENT, L"Career:", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 232, 9, 261, 43, hWnd, 1001);
		lb1.Create(NULL, L"Course:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 30, 85, 73, 18, hWnd, 1002);
		ddCourse.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 107, 78, 370, 25, hWnd, 1003);
		lb2.Create(NULL, L"Professor:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 30, 114, 73, 18, hWnd, 1004);
		ddProfessor.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 107, 108, 370, 25, hWnd, 1005);
		lb3.Create(NULL, L"Classroom:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 30, 143, 73, 18, hWnd, 1006);
		ddClassroom.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 107, 138, 370, 25, hWnd, 1007);
		ddCareer.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 311, 21, 173, 25, hWnd, 1008);
		lb5.Create(NULL, L"Classtime:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 30, 173, 73, 18, hWnd, 1009);
		ddClasstime.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 107, 168, 370, 25, hWnd, 1010);
		ddClassdays.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 107, 198, 370, 25, hWnd, 1011);
		lb6.Create(NULL, L"Classdays:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 30, 203, 73, 18, hWnd, 1012);
		btAccept.Create(NULL, L"Add", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 375, 240, 102, 28, hWnd, 1013);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 269, 240, 102, 28, hWnd, 1014);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		gbox3.Font = fontArial014A;
		gbox2.Font = fontArial014A;
		lb1.Font = fontArial014A;
		ddCourse.Font = fontArial014A;
		lb2.Font = fontArial014A;
		ddProfessor.Font = fontArial014A;
		lb3.Font = fontArial014A;
		ddClassroom.Font = fontArial014A;
		ddCareer.Font = fontArial014A;
		lb5.Font = fontArial014A;
		ddClasstime.Font = fontArial014A;
		ddClassdays.Font = fontArial014A;
		lb6.Font = fontArial014A;
		btAccept.Font = fontArial014A;
		btCancel.Font = fontArial014A;
	}
	//_________________________________________________
	void ddCareer_SelChange(Win::Event& e);
	void btAccept_Click(Win::Event& e);
	void btCancel_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (ddCareer.IsEvent(e, CBN_SELCHANGE)) {ddCareer_SelChange(e); return true;}
		if (btAccept.IsEvent(e, BN_CLICKED)) {btAccept_Click(e); return true;}
		if (btCancel.IsEvent(e, BN_CLICKED)) {btCancel_Click(e); return true;}
		return false;
	}
};
