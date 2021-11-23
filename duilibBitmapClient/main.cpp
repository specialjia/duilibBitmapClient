// duilibBitmapClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//



#include <Windows.h>
#include "CMainDlg.h"




int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    CPaintManagerUI::SetInstance(hInstance);
    CPaintManagerUI::SetResourcePath(_T("../DuiLib_Skin"));
    CMainDlg duiMain;
    duiMain.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    duiMain.CenterWindow();
    duiMain.ShowModal();
    return 0;

}

