#pragma once
#include "afxcmn.h"


// CListRuleDlg dialog

class CListRuleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CListRuleDlg)

public:
	CListRuleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CListRuleDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTRULE };
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
	void CListRuleDlg::PopulateListCtrl();
	void CListRuleDlg::DoorIdSort();
	void CListRuleDlg::DoorNameSort();
	void CListRuleDlg::UserIdSort();
	void CListRuleDlg::UsernameSort();
	void CListRuleDlg::SurnameSort();
	afx_msg void OnLvnColumnClickRules(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkRules(NMHDR *pNMHDR, LRESULT *pResult);
	CKontrolaPristupaApp* theApp;
};
