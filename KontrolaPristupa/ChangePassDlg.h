#pragma once


// CChangePassDlg dialog

class CChangePassDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangePassDlg)

public:
	CChangePassDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CChangePassDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHANGEPASS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_OldPassword;
	CString m_Password1;
	CString m_Password2;
	afx_msg void OnBnClickedBchangepassword();
};
