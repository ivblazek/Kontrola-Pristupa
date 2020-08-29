#pragma once


// CMenuDlg dialog

class CMenuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMenuDlg)

public:
	CMenuDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMenuDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	CListCtrl lstCtrl;
	DECLARE_MESSAGE_MAP()
	
public:
	CString strAppName;
	void CMenuDlg::PopulateListCtrl();
	afx_msg void OnBnClickedBrefresh();
	afx_msg void OnLogout();
	afx_msg void OnAddUser();
	afx_msg void OnGroupAddgroup();
	afx_msg void OnRuleAddrule();
};
