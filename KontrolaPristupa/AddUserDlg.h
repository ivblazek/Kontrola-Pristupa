#pragma once
#include "afxwin.h"


// CAddUserDlg dialog

class CAddUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddUserDlg)

public:
	CAddUserDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddUserDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDUSER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	CString m_Name;
	CString m_Surname;
	CString m_GroupName;
	CString m_CardNo;
	afx_msg void OnBnClickedBadduser();
	CComboBox groupComboBox;
};
