#pragma once   //_____________________________________________ LoginDlg.h  
#include "resource.h"

class LoginDlg: public Win::Dialog
{
public:
	LoginDlg()
	{
		tryCount=0;
	}
	~LoginDlg()
	{
	}
	int tryCount;
public:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Image imgUG;
	Win::Textbox tbxUser;
	Win::Textbox tbxPass;
	Win::Label lb1;
	Win::Label lb2;
	Win::Button btLogin;
	Win::Button btClose;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(361);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(464);
		dlgTemplate.style = WS_CAPTION | WS_MINIMIZEBOX | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		imgUG.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_VISIBLE, 21, 15, 320, 371, hWnd, 1000);
		tbxUser.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 95, 389, 142, 25, hWnd, 1001);
		tbxPass.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_PASSWORD | ES_LEFT | ES_WINNORMALCASE, 95, 416, 142, 25, hWnd, 1002);
		lb1.Create(NULL, L"Username:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 24, 395, 71, 17, hWnd, 1003);
		lb2.Create(NULL, L"Password:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 26, 424, 68, 16, hWnd, 1004);
		btLogin.Create(NULL, L"Login", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 244, 389, 93, 28, hWnd, 1005);
		btClose.Create(NULL, L"Close", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 244, 416, 93, 28, hWnd, 1006);
		this->SetDefaultButton(btLogin);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		tbxUser.Font = fontArial014A;
		tbxPass.Font = fontArial014A;
		lb1.Font = fontArial014A;
		lb2.Font = fontArial014A;
		btLogin.Font = fontArial014A;
		btClose.Font = fontArial014A;
	}
	//_________________________________________________
	void btLogin_Click(Win::Event& e);
	void btClose_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (btLogin.IsEvent(e, BN_CLICKED)) {btLogin_Click(e); return true;}
		if (btClose.IsEvent(e, BN_CLICKED)) {btClose_Click(e); return true;}
		return false;
	}
};
