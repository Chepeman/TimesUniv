#include "stdafx.h"  //_____________________________________________ ScheduleDlg.cpp
#include "ScheduleDlg.h"

void ScheduleDlg::Window_Open(Win::Event& e)
{
	//________________________________________________________ lvSchedule
	lvSchedule.Cols.Add(0, LVCFMT_LEFT, 100, L"Day");
	lvSchedule.Cols.Add(1, LVCFMT_RIGHT, 200, L"Activity");
	lvSchedule.Items.Add(0, L"Monday");
	lvSchedule.Items[0][1].Text = L"Math Class";
}



void ScheduleDlg::btOk_Click(Win::Event& e)
{
}

void ScheduleDlg::btClose_Click(Win::Event& e)
{
}

