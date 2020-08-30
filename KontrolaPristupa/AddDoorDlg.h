#pragma once


// CAddDoorDlg dialog

class CAddDoorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddDoorDlg)

public:
	CAddDoorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddDoorDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDDOOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_Name;
	CString m_Description;
	CString m_IPAddress;
	afx_msg void OnBnClickedBAddDoor();
};
