#pragma once
#include "afxcmn.h"


// CListOperatorDlg dialog

class CListOperatorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CListOperatorDlg)

public:
	CListOperatorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CListOperatorDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTOPERATOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl lstCtrl;
};
