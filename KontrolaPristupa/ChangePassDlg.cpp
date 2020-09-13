// ChangePassDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "ChangePassDlg.h"
#include "afxdialogex.h"
#include "Operator.h"


// CChangePassDlg dialog

IMPLEMENT_DYNAMIC(CChangePassDlg, CDialogEx)

CChangePassDlg::CChangePassDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHANGEPASS, pParent)
	, m_OldPassword(_T(""))
	, m_Password1(_T(""))
	, m_Password2(_T(""))
{

}

CChangePassDlg::~CChangePassDlg()
{
}

void CChangePassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EOLDPASSWORD, m_OldPassword);
	DDV_MaxChars(pDX, m_OldPassword, 50);
	DDX_Text(pDX, IDC_EPASSWORD1, m_Password1);
	DDV_MaxChars(pDX, m_Password1, 50);
	DDX_Text(pDX, IDC_EPASSWORD2, m_Password2);
	DDV_MaxChars(pDX, m_Password2, 50);
}


BEGIN_MESSAGE_MAP(CChangePassDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BCHANGEPASSWORD, &CChangePassDlg::OnBnClickedBchangepassword)
END_MESSAGE_MAP()

BOOL CChangePassDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(CKontrolaPristupaApp::getAppName());

	CString strText;
	strText.LoadString(IDS_OLDPASSWORD);
	strText += ":";
	GetDlgItem(IDC_TOLDPASSWORD)->SetWindowText(strText);

	strText.LoadString(IDS_NEWPASSWORD);
	strText += ":";
	GetDlgItem(IDC_TPASSWORD1)->SetWindowText(strText);
	GetDlgItem(IDC_TPASSWORD2)->SetWindowText(strText);
	
	strText.LoadString(IDS_CHANGE);
	GetDlgItem(IDC_BCHANGEPASS)->SetWindowText(strText);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// CChangePassDlg message handlers


void CChangePassDlg::OnBnClickedBchangepassword()
{
	UpdateData();
	CString strMessage;

	if (m_OldPassword.IsEmpty() || m_Password1.IsEmpty() || m_Password2.IsEmpty())
	{
		strMessage.LoadString(IDS_EMPTYFIELDS);
		MessageBox(strMessage, CKontrolaPristupaApp::getAppName(), MB_OK);
		return;
	}

	if (m_Password1.Compare(m_Password2))
	{
		strMessage.LoadString(IDS_PASSMISSMATCH);
		MessageBox(strMessage, CKontrolaPristupaApp::getAppName(), MB_OK);
		return;
	}

	COperator oper;
	oper.m_strFilter.Format(_T("Username = '%s'"), CKontrolaPristupaApp::getActiveOperator());
	oper.Open();

	if (oper.m_Password.Compare(m_OldPassword))
	{
		strMessage.LoadString(IDS_WRONGPASSWORD);
		MessageBox(strMessage, CKontrolaPristupaApp::getAppName(), MB_OK);
		oper.Close();
		return;
	}

	oper.Edit();
	oper.m_Password = m_Password1;
	oper.Update();
	oper.Close();

	EndDialog(0);
}
