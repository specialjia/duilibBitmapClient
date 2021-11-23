#ifndef __UICONTROL_H__
#define __UICONTROL_H__

#pragma once

namespace DuiLib {

	/////////////////////////////////////////////////////////////////////////////////////
	//

	typedef CControlUI* (CALLBACK* FINDCONTROLPROC)(CControlUI*, LPVOID);

	class UILIB_API CControlUI : public CUIAnimation
	{
		DECLARE_DUICONTROL(CControlUI)
	public:
		CControlUI();
		virtual ~CControlUI();

	public:
		virtual CDuiString GetName() const;
		virtual void SetName(LPCTSTR pstrName);
		virtual LPCTSTR GetClass() const;
		virtual LPVOID GetInterface(LPCTSTR pstrName);
		virtual UINT GetControlFlags() const;

		virtual bool Activate();
		virtual CPaintManagerUI* GetManager() const;
		virtual void SetManager(CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true);
		virtual CControlUI* GetParent() const;
	    void setInstance(HINSTANCE instance = NULL) {m_instance = instance;};
		
		// ��ʱ��
		bool SetTimer(UINT nTimerID, UINT nElapse);
		void KillTimer(UINT nTimerID);

		// �ı����
		virtual CDuiString GetText() const;
		virtual void SetText(LPCTSTR pstrText);

		virtual int  GetTextN();			//add by liqs99
		virtual void SetTextN(int n);		//add by liqs99

		virtual void SetTextV(LPCTSTR lpszFormat, ...);

		virtual bool IsResourceText() const;
		virtual void SetResourceText(bool bResource);

		virtual int  GetResourceID() const;			//add by liqs99
		virtual void SetResourceID(int resid);		//add by liqs99
		virtual CLangPackageUI *GetLangPackage();
		virtual void SetSkinFile(LPCTSTR lpstrSkinFile);
		virtual CDuiString GetSkinFile();

		virtual bool IsDragEnabled() const;
		virtual void SetDragEnable(bool bDrag);

		virtual bool IsDropEnabled() const;
		virtual void SetDropEnable(bool bDrop);

		// ͼ�����
		LPCTSTR GetGradient();
		virtual void SetGradient(LPCTSTR pStrImage);
		DWORD GetBkColor() const;
		void SetBkColor(DWORD dwBackColor);
		DWORD GetBkColor2() const;
		void SetBkColor2(DWORD dwBackColor);
		DWORD GetBkColor3() const;
		void SetBkColor3(DWORD dwBackColor);
		void SetHotBkColor(DWORD dwColor);
		DWORD GetHotBkColor() const;
		void SetFocusBkColor(DWORD dwColor);
		DWORD GetFocusBkColor() const;
		DWORD GetForeColor() const;
		void SetForeColor(DWORD dwForeColor);
		LPCTSTR GetBkImage();
		virtual void SetBkImage(LPCTSTR pStrImage);
		LPCTSTR GetForeImage() const;
		void SetForeImage(LPCTSTR pStrImage);

		DWORD GetFocusBorderColor() const;
		void SetFocusBorderColor(DWORD dwBorderColor);
		DWORD GetHotBorderColor() const; //add by liqs99
		void SetHotBorderColor(DWORD dwBorderColor); //add by liqs99
		DWORD GetDisableBorderColor() const;
		void SetDisableBorderColor(DWORD dwBorderColor);
		bool IsColorHSL() const;
		void SetColorHSL(bool bColorHSL);
		SIZE GetBorderRound() const;
		void SetBorderRound(SIZE cxyRound);
		bool DrawImage(HDC hDC, LPCTSTR pStrImage, LPCTSTR pStrModify = NULL);

		//�߿����
		int GetBorderSize() const;
		void SetBorderSize(int nSize);
		DWORD GetBorderColor() const;
		void SetBorderColor(DWORD dwBorderColor);
		void SetBorderSize(RECT rc);
		int GetLeftBorderSize() const;
		void SetLeftBorderSize(int nSize);
		int GetTopBorderSize() const;
		void SetTopBorderSize(int nSize);
		int GetRightBorderSize() const;
		void SetRightBorderSize(int nSize);
		int GetBottomBorderSize() const;
		void SetBottomBorderSize(int nSize);
		int GetBorderStyle() const;
		void SetBorderStyle(int nStyle);

		// λ�����
		virtual RECT GetRelativePos() const; // ���(���ؼ�)λ��
		virtual RECT GetClientPos() const; // �ͻ����򣨳�ȥscrollbar��inset��
		virtual const RECT& GetPos() const;
		virtual void SetPos(RECT rc, bool bNeedInvalidate = true);
		virtual void Move(SIZE szOffset, bool bNeedInvalidate = true);
		virtual bool CalcPos(CControlUI *pChildControl, RECT &rcChild); //�ӿؼ�����ѯ�ʸ��ؼ����㽫����ҷ������rect��
		virtual int GetWidth() const;
		virtual int GetHeight() const;
		virtual int GetX() const;
		virtual int GetY() const;
		virtual RECT GetPadding() const;
		virtual void SetPadding(RECT rcPadding); // ������߾࣬���ϲ㴰�ڻ���
		virtual SIZE GetFixedXY() const;         // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
		virtual void SetFixedXY(SIZE szXY);      // ��floatΪtrueʱ��Ч
		virtual int GetFixedWidth() const;       // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
		virtual void SetFixedWidth(int cx);      // Ԥ��Ĳο�ֵ
		virtual int GetFixedHeight() const;      // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
		virtual void SetFixedHeight(int cy);     // Ԥ��Ĳο�ֵ
		virtual int GetFixedWidthPercent() const;
		virtual void SetFixedWidthPercent(int cx);
		virtual int GetFixedHeightPercent() const;
		virtual void SetFixedHeightPercent(int cy);
		virtual int GetMinWidth() const;
		virtual void SetMinWidth(int cx);
		virtual int GetMaxWidth() const;
		virtual void SetMaxWidth(int cx);
		virtual int GetMinHeight() const;
		virtual void SetMinHeight(int cy);
		virtual int GetMaxHeight() const;
		virtual void SetMaxHeight(int cy);
		virtual TPercentInfo GetFloatPercent() const;
		virtual void SetFloatPercent(TPercentInfo piFloatPercent);
		virtual void SetFloatAlign(UINT uAlign);
		virtual UINT GetFloatAlign() const;

		virtual void SetFloatPosition(POINT ptPosition);
		virtual POINT GetFloatPosition() const;

		virtual bool IsAutoCalcWidth() const;
		virtual void SetAutoCalcWidth(bool bAutoCalcWidth);
		virtual bool IsAutoCalcHeight() const;
		virtual void SetAutoCalcHeight(bool bAutoCalcHeight);

		// �����ʾ
		virtual CDuiString GetToolTip() const;
		virtual void SetToolTip(LPCTSTR pstrText);
		virtual void SetToolTipWidth(int nWidth);
		virtual int	  GetToolTipWidth(void);	// ����ToolTip���������
		
		// ���
		virtual WORD GetCursor();
		virtual void SetCursor(WORD wCursor);

		// ��ݼ�
		virtual TCHAR GetShortcut() const;
		virtual void SetShortcut(TCHAR ch);

		// �˵�
		virtual bool IsContextMenuUsed() const;
		virtual void SetContextMenuUsed(bool bMenuUsed);

		// �û�����
		virtual CDuiString GetUserData(); // �������������û�ʹ��
		virtual void SetUserData(LPCTSTR pstrText); // �������������û�ʹ��
		virtual UINT_PTR GetTag() const; // �������������û�ʹ��
		virtual void SetTag(UINT_PTR pTag); // �������������û�ʹ��

		// һЩ��Ҫ������
		virtual bool IsVisible() const;
		virtual void SetVisible(bool bVisible = true);
		virtual void SetInternVisible(bool bVisible = true); // �����ڲ����ã���ЩUIӵ�д��ھ������Ҫ��д�˺���
		virtual bool IsEnabled() const;
		virtual void SetEnabled(bool bEnable = true);
		virtual bool IsMouseEnabled() const;
		virtual void SetMouseEnabled(bool bEnable = true);
		virtual bool IsKeyboardEnabled() const;
		virtual void SetKeyboardEnabled(bool bEnable = true);
		virtual bool IsFocused() const;
		virtual void SetFocus();
		virtual bool IsFloat() const;
		virtual void SetFloat(bool bFloat = true);

		virtual bool IsHot() const;
		virtual void SetHot(bool bHot = true);

		virtual CControlUI* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);

		void Invalidate();
		bool IsUpdateNeeded() const;
		void NeedUpdate();
		void NeedParentUpdate();
		DWORD GetAdjustColor(DWORD dwColor);

		virtual void Init();
		virtual void DoInit();

		virtual void Event(TEventUI& event);
		virtual void DoEvent(TEventUI& event);

		// �Զ���(δ������)����
		void AddCustomAttribute(LPCTSTR pstrName, LPCTSTR pstrAttr);
		LPCTSTR GetCustomAttribute(LPCTSTR pstrName) const;
		bool RemoveCustomAttribute(LPCTSTR pstrName);
		void RemoveAllCustomAttribute();

		virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		CControlUI* ApplyAttributeList(LPCTSTR pstrList);

		virtual SIZE EstimateSize(SIZE szAvailable);
		virtual bool Paint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl = NULL); // ����Ҫ��Ҫ��������
		virtual bool DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
		virtual void PaintBkColor(HDC hDC);
		virtual void PaintBkImage(HDC hDC);
		virtual void PaintStatusImage(HDC hDC);
		virtual void PaintForeColor(HDC hDC);
		virtual void PaintForeImage(HDC hDC);
		virtual void PaintText(HDC hDC);
		virtual void PaintBorder(HDC hDC);

		//����ʱ���ܿؼ�������С������
		virtual void DoPostPaint(HDC hDC, const RECT& rcPaint);

		//���ⴰ�ڲ���
		void SetVirtualWnd(LPCTSTR pstrValue);
		CDuiString GetVirtualWnd() const;

		//����ؼ��Ƿ�����������ӦĬ�ϰ����¼�
		virtual bool OnEnableResponseDefaultKeyEvent(WPARAM wParam) { return true; }
	public:
		CEventSource OnInit;
		CEventSource OnDestroy;
		CEventSource OnSize;
		CEventSource OnEvent;
		CEventSource OnNotify;
		CEventSource OnPaint;

	protected:
		CPaintManagerUI* m_pManager;
		CControlUI* m_pParent;
		CDuiString m_sVirtualWnd;
		CDuiString m_sName;
		bool m_bUpdateNeeded;
		bool m_bMenuUsed;
		RECT m_rcItem;
		RECT m_rcPadding;
		SIZE m_cXY;
		SIZE m_cxyFixed;
		SIZE m_cxyFixedPercent;
		SIZE m_cxyMin;
		SIZE m_cxyMax;
		bool m_bVisible;
		bool m_bInternVisible;
		bool m_bPaneVisible;
		bool m_bEnabled;
		bool m_bMouseEnabled;
		bool m_bKeyboardEnabled ;
		bool m_bFocused;
		bool m_bFloat;
		UINT m_uButtonState;
		TPercentInfo m_piFloatPercent;
		UINT m_uFloatAlign;
		POINT m_ptFloatPosition;	//���Զ�λʱ, ���ؼ����Ͻǵİٷֱ�λ��
		bool m_bSetPos; // ��ֹSetPosѭ������

		bool	m_bAutoCalcWidth;	//�����ӿؼ������ı��ȵ��Զ��������
		bool	m_bAutoCalcHeight;	//�����ӿؼ������ı��ȵ��Զ�����߶�

		bool m_bDragEnabled;
		bool m_bDropEnabled;

		bool m_bResourceText;
		int  m_nResourceID;
		CDuiString m_sSkinFile;	//�������ĸ��ļ��� add by liqs99

		CDuiString m_sText;
		CDuiString m_sToolTip;
		TCHAR m_chShortcut;
		CDuiString m_sUserData;
		UINT_PTR m_pTag;

		CDuiString m_sGradient;
		DWORD m_dwBackColor;
		DWORD m_dwBackColor2;
		DWORD m_dwBackColor3;
		DWORD m_dwHotBkColor;
		DWORD m_dwFocusBkColor;
		DWORD m_dwForeColor;
		CDuiString m_sBkImage;
		CDuiString m_sForeImage;
		DWORD m_dwBorderColor;
		DWORD m_dwFocusBorderColor;
		DWORD m_dwHotBorderColor;		//�������ʱ�߿���ɫ
		DWORD m_dwDisableBorderColor;	//���û�ֻ��ʱ�߿���ɫ
		bool m_bColorHSL;
		int m_nBorderSize;
		int m_nBorderStyle;
		int m_nTooltipWidth;
		WORD m_wCursor;
		SIZE m_cxyBorderRound;
		RECT m_rcPaint;
		RECT m_rcBorderSize;
	    HINSTANCE m_instance;

		CStdStringPtrMap m_mCustomAttrHash;

	public:
		virtual void SetPaneVisible(bool bVisible = true);
		virtual bool IsPaneVisible() const;
		virtual void SetAnimation(DuiAnim emAnim);
		virtual DuiAnim GetAnimation() const;
		virtual void SetFrameCount(int framecount);
		virtual int GetFrameCount() const;
		virtual void SetFrameDelay(int nDelay);
		virtual int GetFrameDelay() const;
		virtual void OnAnimationStart(int nAnimationID, BOOL bFirstLoop);
		virtual void OnAnimationStep(int nTotalFrame, int nCurFrame, int nAnimationID);
		virtual void OnAnimationStop(int nAnimationID);

	protected:
		DuiAnim m_animation;	//��������
		int m_nFrameCount;		//������֡��
		int m_nFrameDelay;		//����֡��ʱ
		SIZE m_szAnimationTotal;		//�ܵĶ�������
		SIZE m_szAnimationCurrect;		//��ǰ��������

	public:
		void *m_asOnInit;		//�¼�����ʱ�����ýű��ĺ���ָ��
		void *m_asOnEvent;		
		void *m_asOnNotify;	
		void *m_asOnDestroy;	
		void *m_asOnSize;
		void *m_asOnPaint;
		void *m_asOnPaintBkColor;
		void *m_asOnPaintBkImage;
		void *m_asOnPaintStatusImage;
		void *m_asOnPaintForeColor;
		void *m_asOnPaintForeImage;
		void *m_asOnPaintText;
		void *m_asOnPaintBorder;

		void __AddRef();
		void __ReleaseRef();
	private:
		int __refCount;

	public:
		void SetExtraParent(CControlUI *pControl);
		CControlUI *GetExtraParent() const;
	protected:
		CControlUI *m_pExtraParent;
	};

} // namespace DuiLib

#endif // __UICONTROL_H__