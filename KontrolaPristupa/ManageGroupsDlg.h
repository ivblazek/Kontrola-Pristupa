#pragma once


// CManageGroupsDlg dialog

class CManageGroupsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManageGroupsDlg)

public:
	CManageGroupsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CManageGroupsDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANAGEGROUPS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_Name;
	CString m_Description;
	long selectedID;
	afx_msg void OnBnClickedBSave();
	afx_msg void OnBnClickedBCancel();
	afx_msg void OnBnClickedBDelete();
	CKontrolaPristupaApp* theApp;
};
