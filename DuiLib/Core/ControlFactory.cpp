#include "StdAfx.h"
#include "ControlFactory.h"

namespace DuiLib 
{
	CControlFactory::CControlFactory()
	{
		INNER_REGISTER_DUICONTROL(CControlUI);
		INNER_REGISTER_DUICONTROL(CContainerUI);
		INNER_REGISTER_DUICONTROL(CButtonUI);
		INNER_REGISTER_DUICONTROL(CButtonLayoutUI);
		INNER_REGISTER_DUICONTROL(CComboUI);
		INNER_REGISTER_DUICONTROL(CDateTimeUI);
		INNER_REGISTER_DUICONTROL(CEditUI);
		INNER_REGISTER_DUICONTROL(CActiveXUI);
		INNER_REGISTER_DUICONTROL(CFlashUI);
		INNER_REGISTER_DUICONTROL(CGifAnimUI);
		INNER_REGISTER_DUICONTROL(CGroupBoxUI);
		INNER_REGISTER_DUICONTROL(CIPAddressUI);
		INNER_REGISTER_DUICONTROL(CIPAddressExUI);
		INNER_REGISTER_DUICONTROL(CLabelUI);
		INNER_REGISTER_DUICONTROL(CLabelLayoutUI);
		INNER_REGISTER_DUICONTROL(CListUI);
		INNER_REGISTER_DUICONTROL(CListHeaderUI);
		INNER_REGISTER_DUICONTROL(CListHeaderItemUI);
		INNER_REGISTER_DUICONTROL(CListLabelElementUI);
		INNER_REGISTER_DUICONTROL(CListTextElementUI);
		INNER_REGISTER_DUICONTROL(CListContainerElementUI);
		INNER_REGISTER_DUICONTROL(CListExUI);
		INNER_REGISTER_DUICONTROL(CMenuUI);
		INNER_REGISTER_DUICONTROL(CMenuElementUI);
		INNER_REGISTER_DUICONTROL(COptionUI);
		INNER_REGISTER_DUICONTROL(COptionLayoutUI);
		INNER_REGISTER_DUICONTROL(CCheckBoxUI);
		INNER_REGISTER_DUICONTROL(CProgressUI);
		INNER_REGISTER_DUICONTROL(CRichEditUI);
		INNER_REGISTER_DUICONTROL(CScrollBarUI);
		INNER_REGISTER_DUICONTROL(CSliderUI);
		INNER_REGISTER_DUICONTROL(CTextUI);
		INNER_REGISTER_DUICONTROL(CTreeNodeUI);
		INNER_REGISTER_DUICONTROL(CTreeViewUI);
		INNER_REGISTER_DUICONTROL(CWebBrowserUI);
		INNER_REGISTER_DUICONTROL(CAnimationTabLayoutUI);
		INNER_REGISTER_DUICONTROL(CChildLayoutUI);
		INNER_REGISTER_DUICONTROL(CHorizontalLayoutUI);
		INNER_REGISTER_DUICONTROL(CTabLayoutUI);
		INNER_REGISTER_DUICONTROL(CTileLayoutUI);
		INNER_REGISTER_DUICONTROL(CVerticalLayoutUI);
		INNER_REGISTER_DUICONTROL(CDynamicLayoutUI);
		INNER_REGISTER_DUICONTROL(CRollTextUI);
		INNER_REGISTER_DUICONTROL(CColorPaletteUI);
		INNER_REGISTER_DUICONTROL(CHotKeyUI);
		INNER_REGISTER_DUICONTROL(CFadeButtonUI);
		INNER_REGISTER_DUICONTROL(CRingUI);

		INNER_REGISTER_DUICONTROL(CTabCtrlUI);

		INNER_REGISTER_DUICONTROL(CChildWindowUI);

		INNER_REGISTER_DUICONTROL(CMsgWndUI);
		INNER_REGISTER_DUICONTROL(CComboExUI);
		INNER_REGISTER_DUICONTROL(CIconButtonUI);
		INNER_REGISTER_DUICONTROL(CDateTimeExUI);
		INNER_REGISTER_DUICONTROL(CImageBoxExUI);
		INNER_REGISTER_DUICONTROL(CRollTextExUI);
		INNER_REGISTER_DUICONTROL(CPictureUI);
		INNER_REGISTER_DUICONTROL(CPictureBoxUI);
		INNER_REGISTER_DUICONTROL(CGridHeaderUI);
		INNER_REGISTER_DUICONTROL(CGridBodyUI);
		INNER_REGISTER_DUICONTROL(CGridRowUI);
		INNER_REGISTER_DUICONTROL(CGridCellUI);
		INNER_REGISTER_DUICONTROL(CGridUI);
		INNER_REGISTER_DUICONTROL(CTreeUI);
		INNER_REGISTER_DUICONTROL(CTreeItemUI);
		INNER_REGISTER_DUICONTROL(CTableLayoutUI);
		INNER_REGISTER_DUICONTROL(CTRUI);
		INNER_REGISTER_DUICONTROL(CTDUI);
	}

	CControlFactory::~CControlFactory()
	{
	}

	CControlUI* CControlFactory::CreateControl(CDuiString strClassName)
	{
		strClassName.MakeLower();
		MAP_DUI_CTRATECLASS::iterator iter = m_mapControl.find(strClassName);
		if ( iter == m_mapControl.end()) {
			return NULL;
		}
		else {
			return (CControlUI*) (iter->second());
		}
	}

	void CControlFactory::RegistControl(CDuiString strClassName, CreateClass pFunc)
	{
		strClassName.MakeLower();
		m_mapControl.insert(MAP_DUI_CTRATECLASS::value_type(strClassName, pFunc));
	}

	CControlFactory* CControlFactory::GetInstance()  
	{
		static CControlFactory* pInstance = new CControlFactory;
		return pInstance;
	}

	void CControlFactory::Release()
	{
		delete this;
	}
}