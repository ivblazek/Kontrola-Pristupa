#pragma once
#include "afxcmn.h"


// CListRuleDlg dialog

class CListRuleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CListRuleDlg)

public:
	CListRuleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CListRuleDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTRULE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl lstCtrl;
};
