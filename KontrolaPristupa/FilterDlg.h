#pragma once
#include "atltime.h"


// CFilterDlg dialog

class CFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFilterDlg)

public:
	CFilterDlg(CString& eventFilter, CWnd* pParent = NULL);   // standard constructor
	virtual ~CFilterDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox doorComboBox;
	CComboBox statusComboBox;
	CComboBox nameComboBox;
	CComboBox groupComboBox;
	afx_msg void OnBnClickedApply();
	CString m_door;
	CString m_status;
	CString m_name;
	CString m_group;
	afx_msg void OnCbnSelchangeCnamef();
	afx_msg void OnCbnSelchangeCgroupf();
	BOOL dateCheckBox;
	BOOL timeCheckBox;
	CTime dateStart;
	CTime dateEnd;
	CTime timeStart;
	CTime timeEnd;
	CString& eventFilter;
};
