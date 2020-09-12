// ManageOperatorsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "ManageOperatorsDlg.h"
#include "afxdialogex.h"
#include "Operator.h"
#include "BlockedAccount.h"


// CManageOperatorsDlg dialog

IMPLEMENT_DYNAMIC(CManageOperatorsDlg, CDialogEx)

CManageOperatorsDlg::CManageOperatorsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MANAGEOPER, pParent)
	, m_Operator(_T(""))
{
	
}

CManageOperatorsDlg::~CManageOperatorsDlg()
{
}

void CManageOperatorsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COPERATOR, m_Operator);
	DDV_MaxChars(pDX, m_Operator, 50);
	DDX_Control(pDX, IDC_COPERATOR, operatorComboBox);
}


BEGIN_MESSAGE_MAP(CManageOperatorsDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COPERATOR, &CManageOperatorsDlg::OnCbnSelchangeCOperator)
	ON_BN_CLICKED(IDC_BUNLOCK, &CManageOperatorsDlg::OnBnClickedBUnlock)
	ON_BN_CLICKED(IDC_BRESETPASS, &CManageOperatorsDlg::OnBnClickedBResetPass)
	ON_BN_CLICKED(IDC_BADMIN, &CManageOperatorsDlg::OnBnClickedBAdmin)
	ON_BN_CLICKED(IDC_BDELETE, &CManageOperatorsDlg::OnBnClickedBDelete)
	ON_BN_CLICKED(IDC_BEXIT, &CManageOperatorsDlg::OnBnClickedBExit)
END_MESSAGE_MAP()

BOOL CManageOperatorsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strText;
	strText.LoadString(IDS_MANAGEOPERATORS);

	SetWindowText(CKontrolaPristupaApp::strAppName + " - " + strText);

	
	strText.LoadString(IDS_OPERATOR);
	strText += ":";
	GetDlgItem(IDC_TOPERATOR)->SetWindowText(strText);

	strText.LoadString(IDS_UNLOCK);
	GetDlgItem(IDC_BUNLOCK)->SetWindowText(strText);

	strText.LoadString(IDS_RESETPASS);
	GetDlgItem(IDC_BRESETPASS)->SetWindowText(strText);

	strText.LoadString(IDS_ADDADMIN);
	GetDlgItem(IDC_BADMIN)->SetWindowText(strText);

	strText.LoadString(IDS_DELETE);
	GetDlgItem(IDC_BDELETE)->SetWindowText(strText);

	strText.LoadString(IDS_EXIT);
	GetDlgItem(IDC_BEXIT)->SetWindowText(strText);

	COperator oper;
	oper.m_strFilter.Format(_T("NOT Username = '%s'"), CKontrolaPristupaApp::activeOperator);
	oper.Open();

	while (!oper.IsEOF())
	{		
		operatorComboBox.AddString(oper.m_Username);
		if (selectedID == oper.m_ID)
		{
			operatorComboBox.SetCurSel(operatorComboBox.GetCount() - 1);
			OnCbnSelchangeCOperator();
		}
			
		oper.MoveNext();
	}
	oper.Close();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// CManageOperatorsDlg message handlers


void CManageOperatorsDlg::OnCbnSelchangeCOperator()
{
	UpdateData();
	CString strText;

	COperator oper;
	oper.m_strFilter.Format(_T("Username = '%s'"), m_Operator);
	oper.Open();
		
	CBlockedAccount blockAcc;
	blockAcc.m_strFilter.Format(_T("OperatorID = '%d'"), oper.m_ID);
	blockAcc.Open();

	if (!blockAcc.IsEOF())
		GetDlgItem(IDC_BUNLOCK)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_BUNLOCK)->EnableWindow(FALSE);

	blockAcc.Close();

	oper.Close();

	GetDlgItem(IDC_BRESETPASS)->EnableWindow(TRUE);

	GetDlgItem(IDC_BADMIN)->EnableWindow(TRUE);
	if (oper.m_IsAdmin == 1)
	{
		strText.LoadString(IDS_REMOVEADMIN);
		GetDlgItem(IDC_BADMIN)->SetWindowText(strText);
	}
	else
	{
		strText.LoadString(IDS_ADDADMIN);
		GetDlgItem(IDC_BADMIN)->SetWindowText(strText);
	}

	GetDlgItem(IDC_BDELETE)->EnableWindow(TRUE);
}


void CManageOperatorsDlg::OnBnClickedBUnlock()
{
	COperator oper;
	oper.m_strFilter.Format(_T("Username = '%s'"), m_Operator);
	oper.Open();

	CBlockedAccount blockAcc;
	blockAcc.m_strFilter.Format(_T("OperatorID = '%d'"), oper.m_ID);
	blockAcc.Open();
	if (!blockAcc.IsEOF())
		blockAcc.Delete();
	blockAcc.Close();

	GetDlgItem(IDC_BUNLOCK)->EnableWindow(FALSE);
}


void CManageOperatorsDlg::OnBnClickedBResetPass()
{
	COperator oper;
	oper.m_strFilter.Format(_T("Username = '%s'"), m_Operator);
	oper.Open();
	oper.Edit();
	oper.m_Password = "defaultpassword123";
	oper.Update();
	oper.Close();
}


void CManageOperatorsDlg::OnBnClickedBAdmin()
{
	CString strText;
	COperator oper;
	oper.m_strFilter.Format(_T("Username = '%s'"), m_Operator);
	oper.Open();
	oper.Edit();
	if (oper.m_IsAdmin == 1)
	{
		oper.m_IsAdmin = 0;
		strText.LoadString(IDS_ADDADMIN);
		GetDlgItem(IDC_BADMIN)->SetWindowText(strText);
	}
	else
	{
		oper.m_IsAdmin = 1;
		strText.LoadString(IDS_REMOVEADMIN);
		GetDlgItem(IDC_BADMIN)->SetWindowText(strText);
	}
	
	oper.Update();
	oper.Close();	
}


void CManageOperatorsDlg::OnBnClickedBDelete()
{
	COperator oper;
	oper.m_strFilter.Format(_T("Username = '%s'"), m_Operator);
	oper.Open();
	oper.Delete();
	oper.Close();
	operatorComboBox.DeleteString(operatorComboBox.SelectString(0, m_Operator));

	GetDlgItem(IDC_BUNLOCK)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BRESETPASS)->EnableWindow(FALSE);
	GetDlgItem(IDC_BADMIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BDELETE)->EnableWindow(FALSE);
}


void CManageOperatorsDlg::OnBnClickedBExit()
{
	EndDialog(0);
}
