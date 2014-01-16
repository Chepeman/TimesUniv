#include "stdafx.h"  //_____________________________________________ UpDownDlg.cpp
#include "UpDownDlg.h"

void UpDownDlg::Window_Open(Win::Event& e)
{

	//________________________________________________________ ddCareer

	//________________________________________________________ lvModify
	lvModify.Cols.Add(0, LVCFMT_LEFT, 100, L"Day");
	lvModify.Cols.Add(1, LVCFMT_RIGHT, 200, L"Activity");
}



void UpDownDlg::btAddC_Click(Win::Event& e)
{

}

void UpDownDlg::btDeleteM_Click(Win::Event& e)
{

}

void UpDownDlg::btClose_Click(Win::Event& e)
{

}

