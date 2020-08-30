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
	strAppName.LoadString(IDS_APPNAME);
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

	SetWindowText(strAppName);

	CString strText;
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
		MessageBox(strMessage, strAppName, MB_OK);
		return;
	}

	if (m_Password1.Compare(m_Password2))
	{
		strMessage.LoadString(IDS_PASSMATCH);
		MessageBox(strMessage, strAppName, MB_OK);
		return;
	}

	COperator oper;
	oper.Open();

	oper.AddNew();
	oper.m_Username = m_Username;
	oper.m_Password = m_Password1;
	oper.m_IsAdmin = m_Admin;
	oper.Update();

	oper.Close();

	EndDialog(0);
}