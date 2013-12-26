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
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(399);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(90);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		lbBegin_time.Create(NULL, L"Begin Time:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 17, 78, 18, hWnd, 1000);
		lbEnd_time.Create(NULL, L"End Time:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 49, 66, 18, hWnd, 1001);
		btOK.Create(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 299, 10, 80, 28, hWnd, 1002);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 299, 42, 80, 28, hWnd, 1003);
		tbxBeginTime.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 88, 10, 200, 25, hWnd, 1004);
		tbxEndTime.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 88, 41, 200, 25, hWnd, 1005);
		this->SetDefaultButton(btOK);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
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
