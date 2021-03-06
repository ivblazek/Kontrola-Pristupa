#pragma once
#include "afxcmn.h"


// CListGroupDlg dialog

class CListGroupDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CListGroupDlg)

public:
	CListGroupDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CListGroupDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTGROUP };
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
	void CListGroupDlg::PopulateListCtrl();
	void CListGroupDlg::IdSort();
	void CListGroupDlg::UsernameSort();
	void CListGroupDlg::RoleSort();
	afx_msg void OnLvnColumnClickGroups(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkGroups(NMHDR *pNMHDR, LRESULT *pResult);
	CKontrolaPristupaApp* theApp;
};
