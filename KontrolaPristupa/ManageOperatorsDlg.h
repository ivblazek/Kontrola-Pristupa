#pragma once
#include "afxwin.h"


// CManageOperatorsDlg dialog

class CManageOperatorsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManageOperatorsDlg)

public:
	CManageOperatorsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CManageOperatorsDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANAGEOPER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_Operator;
	long selectedID;
	afx_msg void OnCbnSelchangeCOperator();
	afx_msg void OnBnClickedBUnlock();
	afx_msg void OnBnClickedBResetPass();
	afx_msg void OnBnClickedBAdmin();
	afx_msg void OnBnClickedBDelete();
	afx_msg void OnBnClickedBExit();
	CComboBox operatorComboBox;
};
