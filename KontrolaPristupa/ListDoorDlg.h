#pragma once
#include "afxcmn.h"


// CListDoorDlg dialog

class CListDoorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CListDoorDlg)

public:
	CListDoorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CListDoorDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTDOOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl lstCtrl;
};
