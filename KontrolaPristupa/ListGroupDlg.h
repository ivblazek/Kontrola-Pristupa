#pragma once
#include "afxcmn.h"


// CListGroupDlg dialog

class CListGroupDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CListGroupDlg)

public:
	CListGroupDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CListGroupDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTGROUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl lstCtrl;
};
