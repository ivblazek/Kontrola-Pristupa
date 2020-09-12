#pragma once


// CMainDlg dialog

class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMainDlg();

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
	static CString eventFilter;
	CString sortData;
	void CMainDlg::PopulateListCtrl();
	void CMainDlg::DoorSort();
	void CMainDlg::StatusSort();
	void CMainDlg::UsernameSort();
	void CMainDlg::SurnameSort();
	void CMainDlg::GroupSort();
	void CMainDlg::DatetimeSort();
	void CMainDlg::OnBeginPrinting(CDC *pDC, CPrintInfo* pInfo);
	void CMainDlg::OnPrint(CDC *pDC, CPrintInfo* pInfo);
	void CMainDlg::OnEndPrinting(CDC *pDC, CPrintInfo* pInfo);
	void CMainDlg::Print();
	afx_msg void OnBnClickedBrefresh();
	afx_msg void OnLogout();
	afx_msg void OnAddUser();
	afx_msg void OnGroupAddgroup();
	afx_msg void OnRuleAddrule();
	afx_msg void OnOperatorAddOperator();
	afx_msg void OnOperatorChangepassword();
	afx_msg void OnDoorAddDoor();
	afx_msg void OnOperatorManage();
	afx_msg void OnUserListUsers();
	afx_msg void OnGroupListGroups();
	afx_msg void OnRuleListRules();
	afx_msg void OnDoorListDoors();
	afx_msg void OnOperatorListOperators();
	afx_msg void OnFilter();
	afx_msg void OnBnClickedBFilterOff();
	afx_msg void OnLvnColumnClickEvents(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnReportPrint();
};
