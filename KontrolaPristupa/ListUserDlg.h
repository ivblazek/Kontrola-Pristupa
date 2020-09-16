#pragma once
#include "afxcmn.h"


// CListUserDlg dialog

class CListUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CListUserDlg)

public:
	CListUserDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CListUserDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERLIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl lstCtrl;
	CString sortData;
	int sortBy;
	BOOL sortAsc;
	void CListUserDlg::PopulateListCtrl();
	void CListUserDlg::IdSort();
	void CListUserDlg::UsernameSort();
	void CListUserDlg::SurnameSort();
	void CListUserDlg::GroupSort();
	void CListUserDlg::CardSort();
	afx_msg void OnLvnColumnClickUsers(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkUsers(NMHDR *pNMHDR, LRESULT *pResult);
	CKontrolaPristupaApp* theApp;
};
