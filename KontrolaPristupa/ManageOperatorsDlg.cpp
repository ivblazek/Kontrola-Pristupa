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
	theApp = (CKontrolaPristupaApp*)AfxGetApp();
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

	SetWindowText(theApp->getAppName() + " - " + strText);

	
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
	oper.m_strFilter.Format(_T("NOT Username = '%s'"), theApp->getActiveOperator());
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
	CString strMessage;
	COperator oper;
	CBlockedAccount blockAcc;

	try
	{
		oper.m_strFilter.Format(_T("Username = '%s'"), m_Operator);
		oper.Open();

		blockAcc.m_strFilter.Format(_T("OperatorID = '%d'"), oper.m_ID);
		blockAcc.Open();

		if (!blockAcc.IsEOF())
			blockAcc.Delete();

		GetDlgItem(IDC_BUNLOCK)->EnableWindow(FALSE);

		strMessage.LoadString(IDS_USERUNLOCKEDOK);
		MessageBox(strMessage, theApp->getAppName(), MB_OK);
	}
	catch (CDBException* ex)
	{
		strMessage.LoadString(IDS_USERUNLOCKEDERR);
		MessageBox(strMessage, theApp->getAppName(), MB_OK | MB_ICONERROR);

		if (oper.IsOpen())
			oper.Close();
		if (blockAcc.IsOpen())
			blockAcc.Close();
		return;
	}

	if (oper.IsOpen())
		oper.Close();
	if (blockAcc.IsOpen())
		blockAcc.Close();
}


void CManageOperatorsDlg::OnBnClickedBResetPass()
{
	CString strMessage;
	COperator oper;

	try
	{
		oper.m_strFilter.Format(_T("Username = '%s'"), m_Operator);
		oper.Open();
		oper.Edit();
		oper.m_Password = "defaultpassword123";
		oper.Update();

		strMessage.LoadString(IDS_PASSRESETOK);
		MessageBox(strMessage, theApp->getAppName(), MB_OK);
	}
	catch (CDBException* ex)
	{
		strMessage.LoadString(IDS_PASSRESETERR);
		MessageBox(strMessage, theApp->getAppName(), MB_OK | MB_ICONERROR);

		if (oper.IsOpen())
			oper.Close();
		return;
	}

	if (oper.IsOpen())
		oper.Close();
}


void CManageOperatorsDlg::OnBnClickedBAdmin()
{
	CString strMessage;
	CString strText;
	COperator oper;

	try
	{
		oper.m_strFilter.Format(_T("Username = '%s'"), m_Operator);
		oper.Open();
		oper.Edit();

		if (oper.m_IsAdmin == 1)
		{
			oper.m_IsAdmin = 0;
			oper.Update();
			strText.LoadString(IDS_ADDADMIN);
			GetDlgItem(IDC_BADMIN)->SetWindowText(strText);
			strMessage.LoadString(IDS_REMOVEADMINOK);
		}
		else
		{
			oper.m_IsAdmin = 1;
			oper.Update();
			strText.LoadString(IDS_REMOVEADMIN);
			GetDlgItem(IDC_BADMIN)->SetWindowText(strText);
			strMessage.LoadString(IDS_ADDADMINOK);
		}		

		MessageBox(strMessage, theApp->getAppName(), MB_OK);
	}
	catch (CDBException* ex)
	{
		strMessage.LoadString(IDS_ADMINCHANGEERR);
		MessageBox(strMessage, theApp->getAppName(), MB_OK | MB_ICONERROR);

		if (oper.IsOpen())
			oper.Close();
		return;
	}

	if (oper.IsOpen())
		oper.Close();
}


void CManageOperatorsDlg::OnBnClickedBDelete()
{
	CString strMessage;
	COperator oper;
	
	try
	{
		oper.m_strFilter.Format(_T("Username = '%s'"), m_Operator);
		oper.Open();
		oper.Delete();
		
		strMessage.LoadString(IDS_DELOPEROK);
		MessageBox(strMessage, theApp->getAppName(), MB_OK);
	}
	catch (CDBException* ex)
	{
		if (ex->m_strError.Find(_T("FK_Blocked_Operator")) != -1)
		{
			strMessage.LoadString(IDS_DELOPERFKBLOCKED);
		}
		else
			strMessage.LoadString(IDS_DELOPERERR);
		
		MessageBox(strMessage, theApp->getAppName(), MB_OK | MB_ICONERROR);

		if (oper.IsOpen())
			oper.Close();
		return;
	}

	if (oper.IsOpen())
		oper.Close();

	EndDialog(0);
}


void CManageOperatorsDlg::OnBnClickedBExit()
{
	EndDialog(0);
}
