#pragma once
#include "UIlib.h"

using namespace DuiLib;


class CMainDlg : public WindowImplBase
{
    CPictureUI* m_pic;
    CListUI* m_list;
    CTextUI* m_text;
    CButtonUI* m_btnPre;
    CButtonUI* m_btnNext;


    vector<CString> m_vFilePath;
    size_t m_pageCount;
    size_t m_curPage;
    CDuiString m_strCurPath;
public:
    CMainDlg();
    ~CMainDlg();
    virtual LPCTSTR    GetWindowClassName() const { return _T("DUIMainFrame"); }
    virtual CDuiString GetSkinFile() { return _T("MainDlg.xml"); }
    virtual CDuiString GetSkinFolder() { return _T(""); }
    virtual void __InitWindow() override;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
    virtual void Notify(TNotifyUI& msg) override;

    LRESULT OnDropFile(UINT uMsg, WPARAM wParam, LPARAM lParam);
    void AddFile(CString path);
    void PreviewPdf(CDuiString path);
    void NextPage();
    void PrePage();



public:
    
    vector<CString> GetPrinterList();

};