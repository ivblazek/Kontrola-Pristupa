#pragma once


// CAddGroupDlg dialog

class CAddGroupDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddGroupDlg)

public:
	CAddGroupDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddGroupDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDGROUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBaddgroup();
	CString m_Name;
	CString m_Description;
};
