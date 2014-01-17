#pragma once   //_____________________________________________ TimeDlg.h  
#include "resource.h"

class TimeDlg: public Win::Dialog
{
public:
	TimeDlg()
	{
		classtime_id=-1;
	}
	~TimeDlg()
	{
	}
	int classtime_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Button gbox1;
	Win::Label lbBegin_time;
	Win::Label lbEnd_time;
	Win::Button btOK;
	Win::Button btCancel;
	Win::Textbox tbxBeginTime;
	Win::Textbox tbxEndTime;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(336);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(143);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		gbox1.Create(WS_EX_TRANSPARENT, L"Data:", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 16, 8, 300, 82, hWnd, 1000);
		lbBegin_time.Create(NULL, L"Begin Time:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 27, 33, 78, 18, hWnd, 1001);
		lbEnd_time.Create(NULL, L"End Time:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 27, 63, 66, 18, hWnd, 1002);
		btOK.Create(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 225, 95, 80, 28, hWnd, 1003);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 139, 95, 80, 28, hWnd, 1004);
		tbxBeginTime.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 105, 26, 200, 25, hWnd, 1005);
		tbxEndTime.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 105, 56, 200, 25, hWnd, 1006);
		this->SetDefaultButton(btOK);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		gbox1.Font = fontArial014A;
		lbBegin_time.Font = fontArial014A;
		lbEnd_time.Font = fontArial014A;
		btOK.Font = fontArial014A;
		btCancel.Font = fontArial014A;
		tbxBeginTime.Font = fontArial014A;
		tbxEndTime.Font = fontArial014A;
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
