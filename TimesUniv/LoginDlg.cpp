#include "stdafx.h"  //_____________________________________________ LoginDlg.cpp
#include "LoginDlg.h"

void LoginDlg::Window_Open(Win::Event& e)
{
	tbxUser.SetText(L"");
	tbxPass.SetText(L"");
	//________________________________________________________ imgUG
	//imgUG.FileName=L"C:\\Users\\BrYt3 KaTz3\\Dropbox\\Marikillas\\TimesUniv\\TimesUniv\\UG.png";
	imgUG.FileName=L"C:\\Users\\JCarlos\\Dropbox\\Marikillas\\TimesUniv\\TimesUniv\\UG.png";
	this->Text=L"Welcome";
	this->AlwaysOnTop(true);
}
void LoginDlg::btLogin_Click(Win::Event& e)
{
	if (tryCount >= 3)
	{
		this->MessageBox(L"Numero maximo de intentos alcanzado",L"Login",MB_OK | MB_ICONERROR);
		this->EndDialog(FALSE);
		return;
	}
	if (tbxUser.Text.length() <= 1) return;
	if (tbxPass.Text.length() <= 1) return;
	Sql::SqlConnection conn;
	int count=0;
	wstring sqlCmd;
	wstring username=tbxUser.GetText();
	wstring password=tbxPass.GetText();
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		//conn.OpenSession(hWnd, CONNECTION_STRING);
		Sys::Format(sqlCmd,L"SELECT count(*) FROM coordinator WHERE username='%s' AND pass='%s'",username.c_str(),password.c_str());
		count = conn.GetInt(sqlCmd);
		if (count == 1)
		{
			this->EndDialog(TRUE);
			return;
		}
		else
		{
			tryCount++;
			tbxPass.SetText(L"");
			this->MessageBox(L"Usuario o password incorrectos, intente de nuevo",L"Login",MB_OK | MB_ICONERROR);
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}
void LoginDlg::btClose_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}
