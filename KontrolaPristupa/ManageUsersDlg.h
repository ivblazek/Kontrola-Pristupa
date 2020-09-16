#pragma once
#include "afxwin.h"


// CManageUsersDlg dialog

class CManageUsersDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManageUsersDlg)

public:
	CManageUsersDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CManageUsersDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANAGEUSERS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_Name;
	CString m_Surname;
	CString m_GroupName;
	CComboBox groupComboBox;
	CString m_CardNo;
	long selectedID;
	afx_msg void OnBnClickedBSave();
	afx_msg void OnBnClickedBCancel();
	afx_msg void OnBnClickedBDelete();
	CKontrolaPristupaApp* theApp;
};
