#include "DocView.h"

#include "CBorders.h"
#include "CCell.h"
#include "CFont0.h"
#include "CParagraphs.h"

#include "CTable0.h"
#include "CTables0.h"

void KF::DocView::pdfView()
{
	if (CoInitialize(NULL) != S_OK)
	{
		AfxMessageBox(_T("初始化COM支持库失败!"));
		return;
	}
	CApplication m_wdApp;
	CDocuments m_wdDocs;
	CDocument0  m_wdDoc;
	COleException pe;
	if (!m_wdApp.CreateDispatch(_T("Word.Application"), &pe))
	{
		AfxMessageBox(_T("Application创建失败，请确保安装了word 2000或以上版本!"), MB_OK | MB_ICONWARNING);
		pe.ReportError();
		throw& pe;
		return;
	}
	m_wdDocs.AttachDispatch(m_wdApp.get_Documents());
	COleVariant vTrue((short)TRUE),
		vFalse((short)FALSE),
		vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR),
		vZ((short)0);
	COleVariant     vFileName(_T("E:\\123.doc"));

	//得到document变量
	m_wdDoc.AttachDispatch(m_wdDocs.Open(
		vFileName,        // FileName
		vTrue,            // Confirm Conversion.
		vFalse,            // ReadOnly.
		vFalse,            // AddToRecentFiles.
		vOptional,        // PasswordDocument.
		vOptional,        // PasswordTemplate.
		vOptional,        // Revert.
		vOptional,        // WritePasswordDocument.
		vOptional,        // WritePasswordTemplate.
		vOptional,        // Format. // Last argument for Word 97
		vOptional,        // Encoding // New for Word 2000/2002
		vOptional,        // Visible
		//如下4个是word2003需要的参数。本版本是word2000。
		vOptional,    // OpenAndRepair
		vZ,            // DocumentDirection wdDocumentDirection LeftToRight
		vOptional,    // NoEncodingDialog
		vOptional

	)                // Close Open parameters
	);                    // Close AttachDispatch
	m_wdDoc.PrintPreview();
	// m_wdDoc.ViewCode();
	CString csName = m_wdDoc.get_Name();
	_tprintf(csName);

	_tprintf(_T("WORD will exit."));
	m_wdDoc.Close(vFalse, vOptional, vOptional);
	m_wdDoc.ReleaseDispatch();
	m_wdDocs.ReleaseDispatch();

	//调用Quit退出WORD应用程序。不调用的话WORD还在运行
	m_wdApp.Quit(new CComVariant(FALSE), new CComVariant(), new CComVariant());
	m_wdApp.ReleaseDispatch();   //释放对象指针。切记，必须调
	CoUninitialize();
	

}

void KF::DocView::createDoc()
{
	if (CoInitialize(NULL) != S_OK)
	{
		AfxMessageBox(_T("初始化COM支持库失败!"));
		return;
	}
	CApplication word_app;
	if (!word_app.CreateDispatch(_T("Word.Application")))
		//if (!word_app.CreateDispatch(_T("KWPS.Application"), NULL))
	{
		AfxMessageBox(_T("本机没有安装word产品！"));
		return;
	}
	word_app.put_Visible(TRUE);//设置word可见

								//2.新建文档
	COleVariant vTrue((short)TRUE), vFalse((short)FALSE), VOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	CDocuments docs;
	CDocument0 doc;
	docs = word_app.get_Documents();
	
	doc = docs.Add(new CComVariant(_T("")), new CComVariant(false), new CComVariant(0), new CComVariant());
	 
	//3.开始向word写入数据
	CSelection sel = word_app.get_Selection();

	CParagraphs wordParagraphs = sel.get_ParagraphFormat();
	wordParagraphs.put_Alignment(0);//0 左 1剧中 2右

	CFont0 font = sel.get_Font();
	font.put_Bold(1);
	font.put_Size(22);
	font.put_Name(_T("宋体"));//设置字体属性
	sel.TypeText(TEXT("hello MSWORD.OLB\n\n"));

	CTables0 tables = doc.get_Tables();
	CTable0 table1 = tables.Add(sel.get_Range(), 5, 2, new CComVariant(), new CComVariant());//创建5行2列的表格
	CBorders borders1 = table1.get_Borders();
	borders1.put_InsideLineStyle(1);
	borders1.put_OutsideLineStyle(1);//设置表格边框，默认没有边框

	//设置单元格宽度
	CCell CellTemp;
	for (int i = 0; i < 5; i++)
	{
		CellTemp = table1.Cell(i + 1, 1);
		CellTemp.put_Width(100);//宽度
	}
	for (int i = 0; i < 5; i++)
	{
		CellTemp = table1.Cell(i + 1, 2);
		CellTemp.put_Width(315);
	}
	//写单元格内容
	CellTemp = table1.Cell(1, 1);
	CellTemp.Select();
	wordParagraphs.put_Alignment(1);//设置文字居中
	CFont0 fontTemp = sel.get_Font();
	fontTemp.put_Bold(1);
	fontTemp.put_Size(10);
	sel.TypeText(_T("1111"));
	sel.MoveDown(COleVariant((short)5), COleVariant(short(1)), COleVariant(short(0)));
	wordParagraphs.put_Alignment(1);//设置文字居中
	fontTemp.put_Bold(1);
	fontTemp.put_Size(10);
	sel.TypeText(_T("2222"));
	sel.MoveDown(COleVariant((short)5), COleVariant(short(1)), COleVariant(short(0)));
	wordParagraphs.put_Alignment(1);//设置文字居中
	fontTemp.put_Bold(1);
	fontTemp.put_Size(10);
	sel.TypeText(_T("3333"));
	sel.MoveDown(COleVariant((short)5), COleVariant(short(1)), COleVariant(short(0)));
	wordParagraphs.put_Alignment(1);//设置文字居中
	fontTemp.put_Bold(1);
	fontTemp.put_Size(10);
	sel.TypeText(_T("4444"));
	sel.MoveDown(COleVariant((short)5), COleVariant(short(1)), COleVariant(short(0)));
	wordParagraphs.put_Alignment(1);//设置文字居中
	fontTemp.put_Bold(1);
	fontTemp.put_Size(10);
	sel.TypeText(_T("5555"));
	sel.MoveDown(COleVariant((short)5), COleVariant(short(1)), COleVariant(short(0)));

	CellTemp = table1.Cell(1, 2);
	CellTemp.Select();
	wordParagraphs.put_Alignment(0);//设置文字居中
	fontTemp = sel.get_Font();
	fontTemp.put_Bold(0);
	fontTemp.put_Size(10);
	sel.TypeText(_T("一一一"));
	sel.MoveDown(COleVariant((short)5), COleVariant(short(1)), COleVariant(short(0)));
	wordParagraphs.put_Alignment(0);//设置文字居中
	fontTemp.put_Bold(0);
	fontTemp.put_Size(10);
	sel.TypeText(_T("二二二"));
	sel.MoveDown(COleVariant((short)5), COleVariant(short(1)), COleVariant(short(0)));
	wordParagraphs.put_Alignment(0);//设置文字居中
	fontTemp.put_Bold(0);
	fontTemp.put_Size(10);
	sel.TypeText(_T("三三三"));
	sel.MoveDown(COleVariant((short)5), COleVariant(short(1)), COleVariant(short(0)));
	wordParagraphs.put_Alignment(0);//设置文字居中
	fontTemp.put_Bold(0);
	fontTemp.put_Size(10);
	sel.TypeText(_T("一一\n二二\n三三"));
	sel.MoveDown(COleVariant((short)5), COleVariant(short(1)), COleVariant(short(0)));
	wordParagraphs.put_Alignment(0);//设置文字居中
	fontTemp.put_Bold(0);
	fontTemp.put_Size(10);
	sel.TypeText(_T("五五五"));
	sel.MoveDown(COleVariant((short)5), COleVariant(short(1)), COleVariant(short(0)));

	sel.MoveDown(COleVariant((short)5), COleVariant(short(1)), COleVariant(short(0)));
	fontTemp.put_Size(10);
	sel.TypeText(TEXT("不知道写啥就hello world吧\n"));
	//sel.TypeParagraph();    // 新起一段

	CTable0 table2 = tables.Add(sel.get_Range(), 4, 5, new CComVariant(), new CComVariant());//创建4行2列的表格
	CBorders borders2 = table2.get_Borders();
	borders2.put_InsideLineStyle(1);
	borders2.put_OutsideLineStyle(1);//设置表格边框，默认没有边框

	//设置单元格宽度
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			CellTemp = table2.Cell(i + 1, j + 1);
			if (j == 0)
			{
				CellTemp.put_Width(140);
			}
			else if (j == 1)
			{
				CellTemp.put_Width(80);
			}
			else if (j == 2)
			{
				CellTemp.put_Width(70);
			}
			else if (j == 3)
			{
				CellTemp.put_Width(60);
			}
			else if (j == 4)
			{
				CellTemp.put_Width(60);
			}
		}
	}
	//第一行标题
	CellTemp = table2.Cell(1, 1);
	CellTemp.Select();
	CString strTitleTemp;
	strTitleTemp = _T("AAA");
	wordParagraphs.put_Alignment(0);//设置文字居左
	fontTemp.put_Bold(1);
	fontTemp.put_Size(10);
	sel.TypeText(strTitleTemp);
	CellTemp = table2.Cell(1, 2);
	CellTemp.Select();
	strTitleTemp = _T("BBB");
	sel.TypeText(strTitleTemp);
	CellTemp = table2.Cell(1, 3);
	CellTemp.Select();
	strTitleTemp = _T("CCC");
	sel.TypeText(strTitleTemp);
	CellTemp = table2.Cell(1, 4);
	CellTemp.Select();
	strTitleTemp = _T("DDD");
	sel.TypeText(strTitleTemp);
	CellTemp = table2.Cell(1, 5);
	CellTemp.Select();
	strTitleTemp = _T("EEE");
	sel.TypeText(strTitleTemp);

	//第一列数据
	CString strTemp;
	CellTemp = table2.Cell(2, 1);
	CellTemp.Select();
	for (int i = 0; i < 4 - 1; i++)
	{
		wordParagraphs.put_Alignment(0);//设置文字居左
		fontTemp.put_Bold(0);
		fontTemp.put_Size(10);
		strTemp.Format(_T("第一列%d"), i + 1);
		sel.TypeText(strTemp);
		sel.MoveDown(COleVariant((short)5), COleVariant(short(1)), COleVariant(short(0)));
	}
	//第二列数据
	CellTemp = table2.Cell(2, 2);
	CellTemp.Select();
	for (int i = 0; i < 4 - 1; i++)
	{
		wordParagraphs.put_Alignment(0);//设置文字居左
		fontTemp.put_Bold(0);
		fontTemp.put_Size(10);
		strTemp.Format(_T("第二列%d"), i + 1);
		sel.TypeText(strTemp);
		sel.MoveDown(COleVariant((short)5), COleVariant(short(1)), COleVariant(short(0)));
	}
	//第三列数据
	CellTemp = table2.Cell(2, 3);
	CellTemp.Select();
	for (int i = 0; i < 4 - 1; i++)
	{
		wordParagraphs.put_Alignment(0);//设置文字居左
		fontTemp.put_Bold(0);
		fontTemp.put_Size(10);
		strTemp.Format(_T("第三列%d"), i + 1);
		sel.TypeText(strTemp);
		sel.MoveDown(COleVariant((short)5), COleVariant(short(1)), COleVariant(short(0)));
	}
	//第四列数据
	CellTemp = table2.Cell(2, 4);
	CellTemp.Select();
	for (int i = 0; i < 4 - 1; i++)
	{
		wordParagraphs.put_Alignment(0);//设置文字居左
		fontTemp.put_Bold(0);
		fontTemp.put_Size(10);
		strTemp.Format(_T("第四列%d"), i + 1);
		sel.TypeText(strTemp);
		sel.MoveDown(COleVariant((short)5), COleVariant(short(1)), COleVariant(short(0)));
	}
	//第五列数据
	CellTemp = table2.Cell(2, 5);
	CellTemp.Select();
	for (int i = 0; i < 4 - 1; i++)
	{
		wordParagraphs.put_Alignment(0);//设置文字居左
		fontTemp.put_Bold(0);
		fontTemp.put_Size(10);
		strTemp.Format(_T("第五列%d"), i + 1);
		if (i % 2)
		{
			fontTemp.put_Color(65280);
		}
		else
		{
			fontTemp.put_Color(255);
		}
		sel.TypeText(strTemp);
		sel.MoveDown(COleVariant((short)5), COleVariant(short(1)), COleVariant(short(0)));
	}

	//4.保存并退出
	doc.SaveAs(COleVariant(_T("E:\\123.doc")), VOpt, VOpt, VOpt, VOpt, VOpt, VOpt, VOpt, VOpt,
		VOpt, VOpt, VOpt, VOpt, VOpt, VOpt, VOpt);
	doc.PrintPreview();

	//doc.WebPagePreview();
	//doc.ViewPropertyBrowser();
	COleVariant covOptional((LONG)DISP_E_PARAMNOTFOUND, VT_ERROR), covTrue((SHORT)TRUE), covFalse((SHORT)FALSE);
	//COleVariant vTrue((SHORT)TRUE), vFalse((SHORT)FALSE), vOpt((SHORT)DISP_E_PARAMNOTFOUND, VT_ERROR);
	doc.PrintOut(covTrue, // Background.
		covOptional, // Append.
		COleVariant((long)0),// Range.
		covOptional, // OutputFileName.
		COleVariant(covOptional), // From.
		COleVariant(covOptional), // To.
		covOptional, // Item.
		COleVariant((long)1), // Copies.
		covOptional, // Pages.
		covOptional, // PageType.
		covFalse, // PrintToFile.
		covOptional, // Collate.
		covOptional, // ActivePrinterMacGX.
		covOptional, // ManualDuplexPrint.
		covOptional, // PrintZoomColumn Neweee with Word 2002
		covOptional, // PrintZoomRow ditto
		covOptional, // PrintZoomPaperWidth ditto
		covOptional);
	Sleep(10 * 1000);
	doc.Close(vFalse, VOpt, VOpt);
	word_app.Quit(VOpt, VOpt, VOpt);
	CoUninitialize();

}


CWordOperate::CWordOperate()
{
	if (CoInitialize(NULL) != S_OK)
	{
		AfxMessageBox(_T("初始化COM支持库失败!"));
		return;
	}
}


CWordOperate::~CWordOperate()
{
	CoUninitialize();
}

//操作
BOOL CWordOperate::CreateApp()
{
	COleException pe;
	if (!m_wdApp.CreateDispatch(_T("Word.Application"), &pe))
	{
		AfxMessageBox(_T("Application创建失败，请确保安装了word 2000或以上版本!"), MB_OK | MB_ICONWARNING);
		pe.ReportError();
		throw& pe;
		return FALSE;
	}
	return TRUE;
}

BOOL CWordOperate::CreateDocuments()
{
	if (FALSE == CreateApp())
	{
		return FALSE;
	}
	m_wdDocs.AttachDispatch(m_wdApp.get_Documents());
	if (!m_wdDocs.m_lpDispatch)
	{
		AfxMessageBox(_T("Documents创建失败!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	return TRUE;
}

BOOL CWordOperate::CreateDocument()
{
	if (!m_wdDocs.m_lpDispatch)
	{
		AfxMessageBox(_T("Documents为空!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}

	COleVariant varTrue(short(1), VT_BOOL), vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	CComVariant Template(_T(""));    //没有使用WORD的文档模板
	CComVariant NewTemplate(false), DocumentType(0), Visible;

	m_wdDocs.Add(&Template, &NewTemplate, &DocumentType, &Visible);

	//得到document变量
	m_wdDoc = m_wdApp.get_Documents();
	if (!m_wdDoc.m_lpDispatch)
	{
		AfxMessageBox(_T("Document获取失败!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	//得到selection变量
	m_wdSel = m_wdApp.get_Selection();
	if (!m_wdSel.m_lpDispatch)
	{
		AfxMessageBox(_T("Select获取失败!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	//得到Range变量
	m_wdRange = m_wdDoc.Range(vOptional, vOptional);
	if (!m_wdRange.m_lpDispatch)
	{
		AfxMessageBox(_T("Range获取失败!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}

	return TRUE;
}

BOOL CWordOperate::Create()
{
	if (FALSE == CreateDocuments())
	{
		return FALSE;
	}
	return CreateDocument();
}

void CWordOperate::ShowApp()
{
	m_wdApp.put_Visible(TRUE);
}

void CWordOperate::HideApp()
{
	m_wdApp.put_Visible(FALSE);
}

BOOL CWordOperate::OpenDocument(CString fileName)
{
	if (!m_wdDocs.m_lpDispatch)
	{
		AfxMessageBox(_T("Documents为空!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}

	COleVariant vTrue((short)TRUE),
		vFalse((short)FALSE),
		vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR),
		vZ((short)0);
	COleVariant     vFileName(fileName);

	LPDISPATCH dis = m_wdDocs.Open(
		vFileName,        // FileName
		vTrue,            // Confirm Conversion.
		vFalse,            // ReadOnly.
		vFalse,            // AddToRecentFiles.
		vOptional,        // PasswordDocument.
		vOptional,        // PasswordTemplate.
		vOptional,        // Revert.
		vOptional,        // WritePasswordDocument.
		vOptional,        // WritePasswordTemplate.
		vOptional,        // Format. // Last argument for Word 97
		vOptional,        // Encoding // New for Word 2000/2002
		vOptional,        // Visible
		//如下4个是word2003需要的参数。本版本是word2000。
		vOptional,    // OpenAndRepair
		vZ,            // DocumentDirection wdDocumentDirection LeftToRight
		vOptional,    // NoEncodingDialog
		vOptional   // Close Open parameters

	);
	//得到document变量
	m_wdDoc.AttachDispatch(dis );                    // Close AttachDispatch

	if (!m_wdDoc.m_lpDispatch)
	{
		AfxMessageBox(_T("Document获取失败!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	//得到selection变量
	m_wdSel = m_wdApp.get_Selection();
	if (!m_wdSel.m_lpDispatch)
	{
		AfxMessageBox(_T("Select获取失败!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	//得到全部DOC的Range变量
	m_wdRange = m_wdDoc.Range(vOptional, vOptional);
	if (!m_wdRange.m_lpDispatch)
	{
		AfxMessageBox(_T("Range获取失败!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	return TRUE;
}

BOOL CWordOperate::Open(CString fileName)
{
	if (FALSE == CreateDocuments())
	{
		return FALSE;
	}
	// HideApp();
	return OpenDocument(fileName);
}

BOOL CWordOperate::SetActiveDocument(short i)
{
	COleVariant     vIndex(i), vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	m_wdDoc.AttachDispatch(m_wdDocs.Item(vIndex));
	m_wdDoc.Activate();
	if (!m_wdDoc.m_lpDispatch)
	{
		AfxMessageBox(_T("Document获取失败!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	//得到selection变量
	m_wdSel = m_wdApp.get_Selection();
	if (!m_wdSel.m_lpDispatch)
	{
		AfxMessageBox(_T("Select获取失败!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	//得到全部DOC的Range变量
	m_wdRange = m_wdDoc.Range(vOptional, vOptional);
	if (!m_wdRange.m_lpDispatch)
	{
		AfxMessageBox(_T("Range获取失败!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	HideApp();
	return TRUE;
}

BOOL CWordOperate::SaveDocument()
{
	if (!m_wdDoc.m_lpDispatch)
	{
		AfxMessageBox(_T("Document获取失败!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	m_wdDoc.Save();
	return TRUE;
}

BOOL CWordOperate::SaveDocumentAs(CString fileName)
{
	if (!m_wdDoc.m_lpDispatch)
	{
		AfxMessageBox(_T("Document获取失败!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	COleVariant vTrue((short)TRUE),
		vFalse((short)FALSE),
		vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vFileName(fileName);

	m_wdDoc.SaveAs(
		vFileName,    //VARIANT* FileName
		vOptional,    //VARIANT* FileFormat
		vOptional,    //VARIANT* LockComments
		vOptional,    //VARIANT* Password
		vOptional,    //VARIANT* AddToRecentFiles
		vOptional,    //VARIANT* WritePassword
		vOptional,    //VARIANT* ReadOnlyRecommended
		vOptional,    //VARIANT* EmbedTrueTypeFonts
		vOptional,    //VARIANT* SaveNativePictureFormat
		vOptional,    //VARIANT* SaveFormsData
		vOptional,    //VARIANT* SaveAsAOCELetter
		vOptional,    //VARIANT* ReadOnlyRecommended
		vOptional,    //VARIANT* EmbedTrueTypeFonts
		vOptional,    //VARIANT* SaveNativePictureFormat
		vOptional,    //VARIANT* SaveFormsData
		vOptional    //VARIANT* SaveAsAOCELetter
	);
	return    TRUE;
}

BOOL CWordOperate::CloseDocument()
{
	COleVariant vTrue((short)TRUE),
		vFalse((short)FALSE),
		vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	m_wdDoc.Close(vFalse,    // SaveChanges.
		vTrue,            // OriginalFormat.
		vFalse            // RouteDocument.
	);
	//AfxMessageBox("c1");
	// m_wdDoc.AttachDispatch(m_wdApp.get_ActiveDocument());
	if (!m_wdDoc.m_lpDispatch)
	{
		AfxMessageBox(_T("Document获取失败!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	//	AfxMessageBox("c2");
		//得到selection变量
	// m_wdSel = m_wdApp.get_Selection();
	if (!m_wdSel.m_lpDispatch)
	{
		AfxMessageBox(_T("Select获取失败!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	//	AfxMessageBox("c3");
		//得到全部DOC的Range变量
	// m_wdRange = m_wdDoc.Range(vOptional, vOptional);
	if (!m_wdRange.m_lpDispatch)
	{
		AfxMessageBox(_T("Range获取失败!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	//	AfxMessageBox("c4");
	return TRUE;
}

void CWordOperate::CloseApp()
{
	COleVariant vTrue((short)TRUE),
		vFalse((short)FALSE),
		vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	// m_wdDoc.Save();
	m_wdApp.Quit(vFalse,    // SaveChanges.
		vTrue,            // OriginalFormat.
		vFalse            // RouteDocument.
	);
	//释放内存申请资源

	m_wdRange.ReleaseDispatch();
	m_wdSel.ReleaseDispatch();
	m_wdDoc.ReleaseDispatch();
	m_wdDocs.ReleaseDispatch();
	m_wdApp.ReleaseDispatch();
}

void CWordOperate::WriteText(CString szText)
{
	m_wdSel.TypeText(szText);
}

void CWordOperate::WriteNewLineText(CString szText, int nLineCount /**//* = 1 */)
{
	int i;
	if (nLineCount <= 0)
	{
		nLineCount = 0;
	}
	for (i = 0; i < nLineCount; i++)
	{
		m_wdSel.TypeParagraph();
	}
	WriteText(szText);
}

void CWordOperate::WriteEndLine(CString szText)
{
	m_wdRange.InsertAfter(szText);
}

void CWordOperate::WholeStory()
{
	m_wdRange.WholeStory();
}

void CWordOperate::Copy()
{
	m_wdSel.Copy();
	//m_wdSel.CopyFormat();
}

void CWordOperate::TypeParagraph()
{
	m_wdSel.TypeParagraph();
}

void CWordOperate::PasteAndFormat()
{
	m_wdSel.PasteAndFormat(0);
}

void CWordOperate::Paste()
{
	m_wdSel.Paste();
	//m_wdSel.PasteFormat();
}

void CWordOperate::TypeBackspace(int count)
{
	for (int i = 0; i < count; i++)
		m_wdSel.TypeBackspace();
}

void CWordOperate::InsertFile(CString fileName)
{
	COleVariant     vFileName(fileName),
		vTrue((short)TRUE),
		vFalse((short)FALSE),
		vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR),
		vNull(_T(""));
	/**//*
	void InsertFile(LPCTSTR FileName, VARIANT* Range, VARIANT* ConfirmConversions, VARIANT* Link, VARIANT* Attachment);
	*/
	m_wdSel.InsertFile(
		fileName,
		vNull,
		vFalse,
		vFalse,
		vFalse
	);
}

void CWordOperate::SelectMoveDown(short lineCount, short unit)//有选择操作的移动
{
	m_wdSel.MoveDown(COleVariant(unit), COleVariant((short)lineCount), COleVariant((short)wdExtend));
}

void CWordOperate::NoneSelectMoveDown(short lineCount, short unit)//仅仅移动光标，不选中
{
	m_wdSel.MoveDown(COleVariant(unit), COleVariant((short)lineCount), COleVariant((short)wdMove));
}

void CWordOperate::SelectMoveUp(short lineCount, short unit)//有选择操作的移动
{
	m_wdSel.MoveUp(COleVariant(unit), COleVariant((short)lineCount), COleVariant((short)wdExtend));
}

void CWordOperate::NoneSelectMoveUp(short lineCount, short unit)//仅仅移动光标，不选中
{
	m_wdSel.MoveUp(COleVariant(unit), COleVariant((short)lineCount), COleVariant((short)wdMove));
}

void CWordOperate::SelectMoveLeft(short charCount, short unit)//有选择操作的移动
{
	m_wdSel.MoveLeft(COleVariant(unit), COleVariant((short)charCount), COleVariant((short)wdExtend));
}

void CWordOperate::NoneSelectMoveLeft(short charCount, short unit)//
{
	m_wdSel.MoveLeft(COleVariant(unit), COleVariant((short)charCount), COleVariant((short)wdMove));
}
void CWordOperate::SelectMoveRight(short charCount, short unit)//有选择操作的移动
{
	m_wdSel.MoveRight(COleVariant(unit), COleVariant((short)charCount), COleVariant((short)wdExtend));
}
void CWordOperate::NoneSelectMoveRight(short charCount, short unit)//
{
	m_wdSel.MoveRight(COleVariant(unit), COleVariant((short)charCount), COleVariant((short)wdMove));
}
void CWordOperate::MoveToFirst()
{
	m_wdSel.GoTo(COleVariant((short)1), COleVariant((short)2), COleVariant((short)0), COleVariant(_T("1")));
}

void CWordOperate::MoveToNextPage()
{
	m_wdSel.GoTo(COleVariant((short)1), COleVariant((short)2), COleVariant((short)1), COleVariant(_T("")));
}
