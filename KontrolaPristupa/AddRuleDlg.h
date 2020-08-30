#pragma once
#include "afxwin.h"


// CAddRuleDlg dialog

class CAddRuleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddRuleDlg)

public:
	CAddRuleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddRuleDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDRULE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBAddRule();
	afx_msg void OnCbnSelchangeCUser();
	CString m_User;
	CString m_Door;
	CComboBox userComboBox;
	CComboBox doorComboBox;
};
