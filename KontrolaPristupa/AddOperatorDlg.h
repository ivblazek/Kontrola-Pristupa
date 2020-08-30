#pragma once


// CAddOperatorDlg dialog

class CAddOperatorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddOperatorDlg)

public:
	CAddOperatorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddOperatorDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDOPERATOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_Username;
	CString m_Password1;
	CString m_Password2;
	BOOL m_Admin;
	afx_msg void OnBnClickedBAddOper();
};
