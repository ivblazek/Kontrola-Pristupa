#pragma once
#include "afxwin.h"


// CManageRulesDlg dialog

class CManageRulesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManageRulesDlg)

public:
	CManageRulesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CManageRulesDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANAGERULES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox userComboBox;
	CComboBox doorComboBox;
	CString m_User;
	CString m_Door;
	long selectedDoorID;
	long selectedUserID;
	afx_msg void OnBnClickedBExit();
	afx_msg void OnBnClickedBDelete();
	afx_msg void OnCbnSelchangeCUser();
	afx_msg void OnCbnSelchangeCDoor();
};
