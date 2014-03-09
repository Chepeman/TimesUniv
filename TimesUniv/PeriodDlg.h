#pragma once   //_____________________________________________ PeriodDlg.h  
#include "resource.h"

class PeriodDlg: public Win::Dialog
{
public:
	PeriodDlg()
	{
	}
	~PeriodDlg()
	{
	}
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Button gbox1;
	Win::Label lbDescr;
	Win::Textbox tbxDescr;
	Win::Label lbBegin_date;
	Win::DateTimeBox dtboxBegin_date;
	Win::Label lbEnd_date;
	Win::DateTimeBox dtboxEnd_date;
	Win::Button btOK;
	Win::Button btCancel;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(470);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(178);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		gbox1.Create(WS_EX_TRANSPARENT, L"Data:", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 18, 12, 432, 113, hWnd, 1000);
		lbDescr.Create(NULL, L"Period Description:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 34, 39, 123, 16, hWnd, 1001);
		tbxDescr.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 160, 32, 277, 25, hWnd, 1002);
		lbBegin_date.Create(NULL, L"Begin Date:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 34, 67, 75, 19, hWnd, 1003);
		dtboxBegin_date.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | DTS_RIGHTALIGN, 160, 61, 277, 25, hWnd, 1004);
		lbEnd_date.Create(NULL, L"End Date:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 34, 96, 67, 17, hWnd, 1005);
		dtboxEnd_date.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | DTS_RIGHTALIGN, 160, 90, 277, 25, hWnd, 1006);
		btOK.Create(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 358, 130, 80, 28, hWnd, 1007);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 273, 130, 80, 28, hWnd, 1008);
		this->SetDefaultButton(btOK);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		gbox1.Font = fontArial014A;
		lbDescr.Font = fontArial014A;
		tbxDescr.Font = fontArial014A;
		lbBegin_date.Font = fontArial014A;
		dtboxBegin_date.Font = fontArial014A;
		lbEnd_date.Font = fontArial014A;
		dtboxEnd_date.Font = fontArial014A;
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
