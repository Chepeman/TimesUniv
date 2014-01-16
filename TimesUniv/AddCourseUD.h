#pragma once   //_____________________________________________ AddCourseUD.h  
#include "resource.h"

class AddCourseUD: public Win::Dialog
{
public:
	AddCourseUD()
	{
	}
	~AddCourseUD()
	{
	}
	int current_period;
	void loadByCareer(void);
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Button gbox1;
	Win::Label lb1;
	Win::DropDownList ddCourse;
	Win::Label lb2;
	Win::DropDownList ddProfessor;
	Win::Label lb3;
	Win::DropDownList ddClassroom;
	Win::Label lb4;
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
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(868);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(543);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		gbox1.Create(WS_EX_TRANSPARENT, L"Add New Course", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 73, 65, 775, 458, hWnd, 1000);
		lb1.Create(NULL, L"Course", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 110, 99, 115, 25, hWnd, 1001);
		ddCourse.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 241, 97, 220, 25, hWnd, 1002);
		lb2.Create(NULL, L"Professor", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 108, 149, 120, 25, hWnd, 1003);
		ddProfessor.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 241, 148, 228, 25, hWnd, 1004);
		lb3.Create(NULL, L"Classroom", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 108, 198, 122, 25, hWnd, 1005);
		ddClassroom.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 242, 197, 227, 25, hWnd, 1006);
		lb4.Create(NULL, L"Career", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 511, 94, 135, 25, hWnd, 1007);
		ddCareer.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 664, 94, 173, 25, hWnd, 1008);
		lb5.Create(NULL, L"Classtime", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 110, 254, 126, 25, hWnd, 1009);
		ddClasstime.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 241, 251, 230, 25, hWnd, 1010);
		ddClassdays.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 239, 299, 237, 25, hWnd, 1011);
		lb6.Create(NULL, L"Classdays", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 107, 298, 126, 25, hWnd, 1012);
		btAccept.Create(NULL, L"Add", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 555, 463, 121, 28, hWnd, 1013);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 691, 461, 132, 28, hWnd, 1014);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		gbox1.Font = fontArial014A;
		lb1.Font = fontArial014A;
		ddCourse.Font = fontArial014A;
		lb2.Font = fontArial014A;
		ddProfessor.Font = fontArial014A;
		lb3.Font = fontArial014A;
		ddClassroom.Font = fontArial014A;
		lb4.Font = fontArial014A;
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
