// AddOperatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "AddOperatorDlg.h"
#include "afxdialogex.h"
#include "Operator.h"


// CAddOperatorDlg dialog

IMPLEMENT_DYNAMIC(CAddOperatorDlg, CDialogEx)

CAddOperatorDlg::CAddOperatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADDOPERATOR, pParent)
	, m_Username(_T(""))
	, m_Password1(_T(""))
	, m_Password2(_T(""))
	, m_Admin(FALSE)
{
	theApp = (CKontrolaPristupaApp*)AfxGetApp();
}

CAddOperatorDlg::~CAddOperatorDlg()
{
}

void CAddOperatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EUSERNAME, m_Username);
	DDV_MaxChars(pDX, m_Username, 50);
	DDX_Text(pDX, IDC_EPASSWORD1, m_Password1);
	DDV_MaxChars(pDX, m_Password1, 50);
	DDX_Text(pDX, IDC_EPASSWORD2, m_Password2);
	DDV_MaxChars(pDX, m_Password2, 50);
	DDX_Check(pDX, IDC_ADMIN, m_Admin);
}


BEGIN_MESSAGE_MAP(CAddOperatorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BADDOPER, &CAddOperatorDlg::OnBnClickedBAddOper)
END_MESSAGE_MAP()

BOOL CAddOperatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strText;
	strText.LoadString(IDS_ADDOPERATOR);

	SetWindowText(theApp->getAppName() + " - " + strText);


	strText.LoadString(IDS_USERNAME);
	strText += ":";
	GetDlgItem(IDC_TUSERNAME)->SetWindowText(strText);

	strText.LoadString(IDS_PASSWORD);
	strText += ":";
	GetDlgItem(IDC_TPASSWORD1)->SetWindowText(strText);
	GetDlgItem(IDC_TPASSWORD2)->SetWindowText(strText);

	strText.LoadString(IDS_ADMIN);
	GetDlgItem(IDC_ADMIN)->SetWindowText(strText);

	strText.LoadString(IDS_ADDOPERATOR);
	GetDlgItem(IDC_BADDOPER)->SetWindowText(strText);

	COperator oper;
	oper.m_strFilter.Format(_T("Username = '%s'"), theApp->getActiveOperator());
	oper.Open();

	if (oper.m_IsAdmin == 1)
	{
		strText.LoadString(IDS_REMOVEADMIN);
		GetDlgItem(IDC_ADMIN)->EnableWindow(TRUE);
	}
	oper.Close();
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// CAddOperatorDlg message handlers


void CAddOperatorDlg::OnBnClickedBAddOper()
{
	UpdateData();
	CString strMessage;

	if (m_Username.IsEmpty() || m_Password1.IsEmpty() || m_Password2.IsEmpty())
	{
		strMessage.LoadString(IDS_EMPTYFIELDS);
		MessageBox(strMessage, theApp->getAppName(), MB_OK);
		return;
	}

	if (m_Password1.Compare(m_Password2))
	{
		strMessage.LoadString(IDS_PASSMISSMATCH);
		MessageBox(strMessage, theApp->getAppName(), MB_OK);
		return;
	}

	COperator opers;
	
	try
	{
		opers.Open();
		opers.AddNew();
		opers.m_Username = m_Username;
		opers.m_Password = m_Password1;
		opers.m_IsAdmin = m_Admin;
		opers.Update();

		strMessage.LoadString(IDS_ADDOPEROK);
		MessageBox(strMessage, theApp->getAppName(), MB_OK);
	}
	catch (CDBException* ex)
	{
		strMessage.LoadString(IDS_ADDOPERERR);
		MessageBox(strMessage, theApp->getAppName(), MB_OK | MB_ICONERROR);

		GetDlgItem(IDC_EUSERNAME)->SetWindowText(_T(""));
		GetDlgItem(IDC_EPASSWORD1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EPASSWORD2)->SetWindowText(_T(""));
		((CButton*)GetDlgItem(IDC_ADMIN))->SetCheck(FALSE);
		if (opers.IsOpen())
			opers.Close();
		return;
	}

	if (opers.IsOpen())
		opers.Close();
	
	EndDialog(0);
}