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
	void CMenuDlg::PopulateListCtrl();
	static CString eventFilter;
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
};
