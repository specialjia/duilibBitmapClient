#pragma once
#include <afxdisp.h>
#include "UIlib.h"
#include "CDocument0.h"
#include "CDocuments.h"
#include "CApplication.h"

namespace  KF
{

	class DocView
	{
	public:
		static void pdfView();
		static void createDoc();

	};

}

 

#define wdCharacter 1
#define wdLine 5
#define wdCell 12
#define wdExtend 1
#define wdMove 0
 

#include "CSelection.h"
#include "CRange.h"
class CWordOperate
{
public:
	CWordOperate();
	virtual ~CWordOperate();
private:
	CApplication m_wdApp;
	CDocuments m_wdDocs;
	CDocument0  m_wdDoc;
	CSelection m_wdSel;
	CRange     m_wdRange;


public:
	//操作
	//**********************创建新文档*******************************************
	BOOL CreateApp();                    //创建一个新的WORD应用程序
	BOOL CreateDocuments();                //创建一个新的Word文档集合
	BOOL CreateDocument();                //创建一个新的Word文档
	BOOL Create();                        //创建新的WORD应用程序并创建一个新的文档
	void ShowApp();                        //显示WORD文档
	void HideApp();                        //隐藏word文档

	//**********************打开文档*********************************************
	BOOL OpenDocument(CString fileName);//打开已经存在的文档。
	BOOL Open(CString fileName);        //创建新的WORD应用程序并打开一个已经存在的文档。
	BOOL SetActiveDocument(short i);    //设置当前激活的文档。

	//**********************保存文档*********************************************
	BOOL SaveDocument();                //文档是以打开形式，保存。
	BOOL SaveDocumentAs(CString fileName);//文档以创建形式，保存。
	BOOL CloseDocument();
	void CloseApp();

	//**********************文本书写操作*****************************************
	void WriteText(CString szText);        //当前光标处写文本
	void WriteNewLineText(CString szText, int nLineCount = 1); //换N行写字
	void WriteEndLine(CString szText);    //文档结尾处写文本
	void WholeStory();                    //全选文档内容
	void Copy();                        //复制文本内容到剪贴板
	void InsertFile(CString fileName);    //将本地的文件全部内容写入到当前文档的光标处。
	//----------------------add by zxx--------------------------------------
	//***********************光标操作********************************************
	//上下按行选择
	void SelectMoveDown(short lineCount, short unit);//有选择操作的移动
	void NoneSelectMoveDown(short lineCount, short unit);//仅仅移动光标，不选中
	void SelectMoveUp(short lineCount, short unit);//有选择操作的移动
	void NoneSelectMoveUp(short lineCount, short unit);//仅仅移动光标，不选中
	//左右按列选择
	void SelectMoveLeft(short charCount, short unit);//有选择操作的移动
	void NoneSelectMoveLeft(short charCount, short unit);//
	void SelectMoveRight(short charCount, short unit);//有选择操作的移动
	void NoneSelectMoveRight(short charCount, short unit);//


	void MoveToFirst();
	void MoveToNextPage();
	void TypeParagraph();
	void PasteAndFormat();
	void Paste();
	void TypeBackspace(int count);
};