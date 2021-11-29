#pragma once
// #include <Windows.h>
 #include "UIlib.h"

using namespace DuiLib;


class CMainDlg : public WindowImplBase
{
    CPictureUI* m_pic;
    CListUI* m_list;
    CTextUI* m_textPagePro;
    CButtonUI* m_btnPre;
    CButtonUI* m_btnNext;
    CComboUI* m_comboPrinter;
    CButtonUI* m_btnPrint;
    void Print();

    CComboUI* m_comboRange;
    bool IsAllRange();

    CEditUI* m_editRange;
    vector<size_t> GetPageRange();

    void AddPrinterToCombo(CDuiString printerName);


    vector<CDuiString> m_vFilePath;
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
    void AddFile(CDuiString path);
    void PreviewPdf(CDuiString path);
    void NextPage();
    void PrePage();

  



public:
    
    vector<CDuiString> GetPrinterList();

};