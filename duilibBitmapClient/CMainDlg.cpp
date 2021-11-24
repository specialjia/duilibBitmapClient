﻿#define  _CRT_SECURE_NO_WARNINGS
#include "CMainDlg.h"

#include "Utils.h"

typedef int (WINAPI* load_pdf)(char*);
typedef bool (WINAPI* needs_password)();
typedef bool (WINAPI* set_password)(const char* password, int& nPage);
typedef bool (WINAPI* pdf_to_image)(const char* export_filename, int from, int to, int zoom);
typedef bool (WINAPI* pdf_to_image2)(const char* export_filename, int pageIndex, HBITMAP& hbi, int zoom);
typedef void(WINAPI* unload)();
class AutoDeleteLib
{
public:
    AutoDeleteLib()
    {
        m_hmodule = nullptr;
        m_hmodule = LoadLibraryA("E:\\code\\duilibBitmapClient\\lib\\pdfpage.dll");
    }
    ~AutoDeleteLib()
    {
        if(m_hmodule!=nullptr)
        FreeLibrary(m_hmodule);
    }
    HMODULE   getModule() { return m_hmodule ? m_hmodule : 0; }
    operator HMODULE() { return m_hmodule; }
	
private:
    HMODULE m_hmodule;
};

class AutoDeleteDC {
    HDC hdc = nullptr;

public:
    explicit AutoDeleteDC(HDC hdc) {
        this->hdc = hdc;
    }
    ~AutoDeleteDC() {
        DeleteDC(hdc);
    }
    operator HDC() const {
        return hdc;
    }
};

bool ifNeedPassWord()
{
    AutoDeleteLib myModule;
    HMODULE hmodule = myModule.getModule();
    needs_password needpass = (needs_password)GetProcAddress(hmodule, "_needs_password@0");
    return needpass();
}

bool setPassWord(char* password,int nPage)
{
    AutoDeleteLib myModule;
    HMODULE hmodule = myModule.getModule();
    set_password setPassword = (set_password)GetProcAddress(hmodule, "_set_password@8");
    return setPassword(password, nPage);
}

bool pdf2Image(const char* export_filename, int from, int to, int zoom)
{
    AutoDeleteLib myModule;
    HMODULE hmodule = myModule.getModule();
    pdf_to_image pdfToImage = (pdf_to_image)GetProcAddress(myModule, "_pdf_to_image@16");
    return pdfToImage(export_filename, from, to, zoom);
}

size_t getImageFromPdf(char* path,const char* export_filename, int pageIndex, HBITMAP& hbi, int zoom)
{
    AutoDeleteLib myModule;
    HMODULE hmodule = myModule.getModule();

    load_pdf new_instance = (load_pdf)GetProcAddress(hmodule, "_load_pdf@4");
	size_t page = new_instance(path);
     
    pdf_to_image2 pdfToImage2 = (pdf_to_image2)GetProcAddress(hmodule, "_pdf_to_image2@16");
    pdfToImage2(export_filename, pageIndex, hbi, zoom);

    unload unLoad = (unload)GetProcAddress(hmodule, "_unload@0");
    unLoad();
    return page;
}

struct Rect
{
    int x;
    int y;
    int dx;
    int dy;
};
// render the bitmap into the target rectangle (streching and skewing as requird)
bool BlitHBITMAP(HBITMAP hbmp, HDC hdc, Rect target) {
    HDC bmpDC = CreateCompatibleDC(hdc);
    if (!bmpDC) {
        return false;
    }

    BITMAP bi{};
    GetObject(hbmp, sizeof(BITMAP), &bi);
    int dx = bi.bmWidth;
    int dy = bi.bmHeight;

    HGDIOBJ oldBmp = SelectObject(bmpDC, hbmp);
    if (!oldBmp) {
        DeleteDC(bmpDC);
        return false;
    }
    SetStretchBltMode(hdc, HALFTONE);
    int x = target.x;
    int y = target.y;
    int tdx = target.dx;
    int tdy = target.dy;
    bool ok = StretchBlt(hdc, x, y, tdx, tdy, bmpDC, 0, 0, dx, dy, SRCCOPY);
    SelectObject(bmpDC, oldBmp);
    DeleteDC(bmpDC);
    return ok;
}

void printPdf(HBITMAP& bitmap)
{
    const DEVMODEW* pdev;
    DEVMODEW d = { 0 };
    _tcscpy(d.dmDeviceName, L"Microsoft Print to PDF");
    d.dmSpecVersion = 1025;
    d.dmDriverVersion = 1539;
    d.dmSize = 220;
    d.dmDriverExtra = 5200;
    d.dmFields = 77571;
    d.dmOrientation = 1;
    d.dmPaperSize = 9;
    d.dmPaperLength = 2970;
    d.dmPaperWidth = 2100;
    d.dmScale = 100;
    d.dmCopies = 1;
    d.dmDefaultSource = 15;
    d.dmPrintQuality = 600;
    d.dmPosition.x = 589825;
    d.dmPosition.y = 127628570;
    d.dmDisplayOrientation = 65636;
    d.dmDisplayFixedOutput = 39321615;
    d.dmColor = 2;
    d.dmDuplex = 1;
    d.dmYResolution = 600;
    d.dmTTOption = 3;
    d.dmCollate = 0;
    _tcscpy(d.dmFormName, L"A4");
    d.dmDisplayFlags = 1;
    d.dmNup = 1;
    d.dmICMMethod = 1;
    d.dmICMIntent = 2;
    d.dmMediaType = 1;
    d.dmDitherType = 4294967295;
    d.dmReserved1 = 877873479;



    pdev = &d;
    AutoDeleteDC hdc(CreateDC(nullptr, L"Microsoft Print to PDF", nullptr, pdev));
    DOCINFOW di{};
    di.cbSize = sizeof(DOCINFO);
    di.lpszDocName = L"E:\\algrithom.pdf";
    if (StartDoc(hdc, &di) <= 0) {
        DUI__Trace(L"startdoc err");
    }
    StartPage(hdc);
    Rect rc;
    rc.x = 110;
    rc.y = 0;
    rc.dx = 4741;
    rc.dy = 7016;
    BlitHBITMAP(bitmap, hdc, rc);
    EndPage(hdc);
    // AbortDoc(hdc); //会取消打印
    EndDoc(hdc);


}

CMainDlg::CMainDlg()
{
    m_pageCount = 0;
}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::__InitWindow()
{
    DragAcceptFiles(m_hWnd, true);
	m_pic = (CPictureUI*)m_pm.FindControl(L"pic_image");
    assert(m_pic);
    m_list = (CListUI*)m_pm.FindControl(L"list_file");
    assert(m_list);
    m_text = (CTextUI*)m_pm.FindControl(L"lb_page");
    assert(m_text);
    m_btnPre = (CButtonUI*)m_pm.FindControl(L"btn_pre");
    assert(m_btnPre);
    m_btnNext = (CButtonUI*)m_pm.FindControl(L"btn_next");

   


}

LRESULT CMainDlg::HandleMessage(UINT msg, WPARAM param, LPARAM long_ptr)
{
    if (WM_DROPFILES == msg) {
        return OnDropFile(msg, param, long_ptr);
    }

    return __super::HandleMessage(msg, param, long_ptr);
}

void CMainDlg::Notify(TNotifyUI& msg)
{
    if (msg.sType == DUI_MSGTYPE_CLICK)
    {
        CDuiString strClass = msg.pSender->GetClass();
        if(!strClass.CompareNoCase(L"ButtonUI"))
        {
            CDuiString strName = msg.pSender->GetName();
            DUITRACE(strName);
            if(!strName.CompareNoCase(L"btn_pre"))
            {
                PrePage();
            }
            else if(!strName.CompareNoCase(L"btn_next"))
            {
                NextPage();
            }
        }
        else
        {
            CControlUI* cui = msg.pSender->GetParent();
            CDuiString path = cui->GetName();
            PreviewPdf(path);
        }
    }
}


LRESULT CMainDlg::OnDropFile(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDROP hDrop = (HDROP)wParam;

    TCHAR path[1024];

    int index = 0;

    while (true) {
        memset(path, 0, 1024);
        if (0 == DragQueryFile(hDrop, index++, path, 1024)) {
            break;
        }

        m_vFilePath.emplace_back(path);
        AddFile(path);
    }

    DragFinish(hDrop);

    return 0;
}

void CMainDlg::AddFile(CString path)
{
	if (path.Right(3).CompareNoCase(L"pdf"))
	{
		return;
	}
	HBITMAP bitmap;
	getImageFromPdf((char*)Utils::w2u(path.GetBuffer()).c_str(), nullptr, 1, bitmap, 100);
	auto pic = new CPictureUI;
	pic->LoadHBitmap(bitmap);
	pic->SetFixedWidth(92);
	pic->SetFixedHeight(112);

	auto lab = new CLabelUI;
	lab->SetAutoCalcHeight(true);
	lab->SetAutoCalcWidth(true);
	lab->SetText(Utils::GetFileName(path));

    auto v = new CVerticalLayoutUI;
	v->Add(pic);
	v->Add(lab);
    v->SetName(path);
    v->SetEnabled(true);
    
    

	v->SetChildAlign(DT_CENTER);
	v->SetFixedHeight(140);

	m_list->AddAt(v, m_list->GetCount());
	m_list->SetAutoCalcHeight(true);
    PreviewPdf(path.GetBuffer());
}

void CMainDlg::PreviewPdf(CDuiString path)
{
    HBITMAP bitmap;
    m_pageCount = getImageFromPdf((char*)Utils::w2u(path.GetData()).c_str(), NULL, 1, bitmap, 100);
    m_pic->LoadHBitmap(bitmap);
    m_pic->NeedUpdate();

    CDuiString str;
    str.Format(L"1/%d", m_pageCount);
    m_text->SetText(str);
    m_curPage = 1;
    m_strCurPath = path;

}

void CMainDlg::NextPage()
{
    if (m_curPage == m_pageCount) return;

    HBITMAP bitmap;
    m_pageCount = getImageFromPdf((char*)Utils::w2u(m_strCurPath.GetData()).c_str(), NULL, ++m_curPage, bitmap, 100);
    m_pic->LoadHBitmap(bitmap);
    m_pic->NeedUpdate();
    CDuiString str;
    str.Format(L"%d/%d", m_curPage, m_pageCount);
    m_text->SetText(str);
}

void CMainDlg::PrePage()
{
    if (m_curPage == 1) return;

    HBITMAP bitmap;
    m_pageCount = getImageFromPdf((char*)Utils::w2u(m_strCurPath.GetData()).c_str(), NULL, --m_curPage, bitmap, 100);
    m_pic->LoadHBitmap(bitmap);
    m_pic->NeedUpdate();
    CDuiString str;
    str.Format(L"%d/%d", m_curPage, m_pageCount);
    m_text->SetText(str);
}

vector<CString> CMainDlg::GetPrinterList()
{
    std::vector<CString> plist;
    //函数体
    DWORD            dwFlags = PRINTER_ENUM_FAVORITE | PRINTER_ENUM_LOCAL;
    LPPRINTER_INFO_2 pPrinters;
    DWORD            cbPrinters;
    DWORD            cReturned, i;
    char             buf[256];

    EnumPrinters(dwFlags, NULL, 2, NULL, 0, &cbPrinters,
        &cReturned);

    if (!(pPrinters = (LPPRINTER_INFO_2)LocalAlloc(LPTR, cbPrinters + 4)))
    {

    }

    if (!EnumPrinters(dwFlags, NULL, 2, (LPBYTE)pPrinters,
        cbPrinters, &cbPrinters, &cReturned))
    {

    }

    if (cReturned > 0)
    {

        for (i = 0; i < cReturned; i++)
        {
            //   
            // for each printer in the PRINTER_INFO_2 array: build a string that   
            //   looks like "DEVICE_NAME;PORT;DRIVER_NAME"   
            //   
            plist.push_back((pPrinters + i)->pPrinterName);

            // strcpy(buf, (pPrinters + i)->pPrinterName);
            // strcat(buf, ";");
            // strcat(buf, (pPrinters + i)->pPortName);
            // strcat(buf, ";");
            // strcat(buf, (pPrinters + i)->pDriverName);

        }
    }



    return plist;
}
