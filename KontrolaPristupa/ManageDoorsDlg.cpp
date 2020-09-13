// ManageDoorsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "ManageDoorsDlg.h"
#include "afxdialogex.h"
#include "Door.h"


// CManageDoorsDlg dialog

IMPLEMENT_DYNAMIC(CManageDoorsDlg, CDialogEx)

CManageDoorsDlg::CManageDoorsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MANAGEDOORS, pParent)
	, m_Name(_T(""))
	, m_Description(_T(""))
	, m_IPAddress(_T(""))
{

}

CManageDoorsDlg::~CManageDoorsDlg()
{
}

void CManageDoorsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ENAME, m_Name);
	DDV_MaxChars(pDX, m_Name, 50);
	DDX_Text(pDX, IDC_EDESCRIPTION, m_Description);
	DDV_MaxChars(pDX, m_Description, 50);
	DDX_Text(pDX, IDC_EIPADDRESS, m_IPAddress);
	DDV_MaxChars(pDX, m_IPAddress, 15);
}


BEGIN_MESSAGE_MAP(CManageDoorsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BSAVE, &CManageDoorsDlg::OnBnClickedBSave)
	ON_BN_CLICKED(IDC_BCANCEL, &CManageDoorsDlg::OnBnClickedBCancel)
	ON_BN_CLICKED(IDC_BDELETE, &CManageDoorsDlg::OnBnClickedBDelete)
END_MESSAGE_MAP()

BOOL CManageDoorsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strText;
	strText.LoadString(IDS_MANAGEDOORS);

	SetWindowText(CKontrolaPristupaApp::getAppName() + " - " + strText);


	strText.LoadString(IDS_NAME);
	strText += ":";
	GetDlgItem(IDC_TNAME)->SetWindowText(strText);

	strText.LoadString(IDS_DESCRIPTION);
	strText += ":";
	GetDlgItem(IDC_TDESCRIPTION)->SetWindowText(strText);

	strText.LoadString(IDS_IPADDRESS);
	strText += ":";
	GetDlgItem(IDC_TIPADDRESS)->SetWindowText(strText);

	strText.LoadString(IDS_SAVE);
	GetDlgItem(IDC_BSAVE)->SetWindowText(strText);

	strText.LoadString(IDS_CANCEL);
	GetDlgItem(IDC_BCANCEL)->SetWindowText(strText);

	strText.LoadString(IDS_DELETE);
	GetDlgItem(IDC_BDELETE)->SetWindowText(strText);

	CDoor doors;
	doors.m_strFilter.Format(_T("ID = '%d'"), selectedID);
	doors.Open();

	GetDlgItem(IDC_ENAME)->SetWindowText(doors.m_Name);
	GetDlgItem(IDC_EDESCRIPTION)->SetWindowText(doors.m_Description);
	GetDlgItem(IDC_EIPADDRESS)->SetWindowText((CString)doors.m_IPaddress);

	doors.Close();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// CManageDoorsDlg message handlers


void CManageDoorsDlg::OnBnClickedBSave()
{
	UpdateData();
	CString strMessage;

	if (m_Name.IsEmpty() || m_Description.IsEmpty() || m_IPAddress.IsEmpty())
	{
		strMessage.LoadString(IDS_EMPTYFIELDS);
		MessageBox(strMessage, CKontrolaPristupaApp::getAppName(), MB_OK);
		return;
	}

	CDoor doors;

	try
	{
		doors.m_strFilter.Format(_T("ID = '%d'"), selectedID);
		doors.Open();
		doors.Edit();
		doors.m_Name = m_Name;
		doors.m_Description = m_Description;
		doors.m_IPaddress = m_IPAddress;
		doors.Update();

		strMessage.LoadString(IDS_SAVEDOOROK);
		MessageBox(strMessage, CKontrolaPristupaApp::getAppName(), MB_OK);
	}
	catch (CDBException* ex)
	{
		strMessage.LoadString(IDS_SAVEDOORERR);
		MessageBox(strMessage, CKontrolaPristupaApp::getAppName(), MB_OK | MB_ICONERROR);

		if (doors.IsOpen())
			doors.Close();
		return;
	}

	if (doors.IsOpen())
		doors.Close();

	EndDialog(0);
}


void CManageDoorsDlg::OnBnClickedBCancel()
{
	EndDialog(0);
}


void CManageDoorsDlg::OnBnClickedBDelete()
{
	CString strMessage;
	CDoor doors;

	try
	{
		doors.m_strFilter.Format(_T("ID = '%d'"), selectedID);
		doors.Open();
		doors.Delete();

		strMessage.LoadString(IDS_DELDOOROK);
		MessageBox(strMessage, CKontrolaPristupaApp::getAppName(), MB_OK);
	}
	catch (CDBException* ex)
	{
		if (ex->m_strError.Find(_T("FK_Events_Doors")) != -1)
		{
			strMessage.LoadString(IDS_DELDOORFKEVENT);
		}
		else if (ex->m_strError.Find(_T("FK_Rules_Doors")) != -1)
		{
			strMessage.LoadString(IDS_DELDOORFKRULES);
		}
		else
			strMessage.LoadString(IDS_DELDOORERR);

		MessageBox(strMessage, CKontrolaPristupaApp::getAppName(), MB_OK | MB_ICONERROR);

		if (doors.IsOpen())
			doors.Close();
		return;
	}

	if (doors.IsOpen())
		doors.Close();

	EndDialog(0);
}
