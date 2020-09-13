#pragma once


// CManageDoorsDlg dialog

class CManageDoorsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManageDoorsDlg)

public:
	CManageDoorsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CManageDoorsDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANAGEDOOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_Name;
	CString m_Description;
	CString m_IPAddress;
	long selectedID;
	afx_msg void OnBnClickedBSave();
	afx_msg void OnBnClickedBCancel();
};
