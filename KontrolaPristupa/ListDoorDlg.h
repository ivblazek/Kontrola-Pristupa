#pragma once
#include "afxcmn.h"


// CListDoorDlg dialog

class CListDoorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CListDoorDlg)

public:
	CListDoorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CListDoorDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTDOOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl lstCtrl;
	CString sortData;
	void CListDoorDlg::PopulateListCtrl();
	void CListDoorDlg::IdSort();
	void CListDoorDlg::UsernameSort();
	void CListDoorDlg::RoleSort();
	void CListDoorDlg::IpSort();
	afx_msg void OnLvnColumnClickDoors(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkDoors(NMHDR *pNMHDR, LRESULT *pResult);
};
