// AddDoorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "AddDoorDlg.h"
#include "afxdialogex.h"
#include "Door.h"


// CAddDoorDlg dialog

IMPLEMENT_DYNAMIC(CAddDoorDlg, CDialogEx)

CAddDoorDlg::CAddDoorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADDDOOR, pParent)
	, m_Name(_T(""))
	, m_Description(_T(""))
	, m_IPAddress(_T(""))
{

}

CAddDoorDlg::~CAddDoorDlg()
{
}

void CAddDoorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ENAME, m_Name);
	DDV_MaxChars(pDX, m_Name, 50);
	DDX_Text(pDX, IDC_EDESCRIPTION, m_Description);
	DDV_MaxChars(pDX, m_Description, 50);
	DDX_Text(pDX, IDC_EIPADDRESS, m_IPAddress);
	DDV_MaxChars(pDX, m_IPAddress, 15);
}


BEGIN_MESSAGE_MAP(CAddDoorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BADDDOOR, &CAddDoorDlg::OnBnClickedBAddDoor)
END_MESSAGE_MAP()

BOOL CAddDoorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strText;
	strText.LoadString(IDS_ADDDOOR);

	SetWindowText(CKontrolaPristupaApp::strAppName + " - " + strText);
	

	strText.LoadString(IDS_NAME);
	strText += ":";
	GetDlgItem(IDC_TNAME)->SetWindowText(strText);

	strText.LoadString(IDS_DESCRIPTION);
	strText += ":";
	GetDlgItem(IDC_TDESCRIPTION)->SetWindowText(strText);

	strText.LoadString(IDS_IPADDRESS);
	strText += ":";
	GetDlgItem(IDC_TIPADDRESS)->SetWindowText(strText);

	strText.LoadString(IDS_ADDDOOR);
	GetDlgItem(IDC_BADDDOOR)->SetWindowText(strText);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// CAddDoorDlg message handlers


void CAddDoorDlg::OnBnClickedBAddDoor()
{
	UpdateData();
	CString strMessage;

	if (m_Name.IsEmpty() || m_Description.IsEmpty() || m_IPAddress.IsEmpty())
	{
		strMessage.LoadString(IDS_EMPTYFIELDS);
		MessageBox(strMessage, CKontrolaPristupaApp::strAppName, MB_OK);
		return;
	}
	
	CDoor doors;

	try
	{		
		doors.Open();

		doors.AddNew();
		doors.m_Name = m_Name;
		doors.m_Description = m_Description;
		doors.m_IPaddress = m_IPAddress;
		doors.Update();

		strMessage.LoadString(IDS_ADDDOOROK);
		MessageBox(strMessage, CKontrolaPristupaApp::strAppName, MB_OK);
	}
	catch (CDBException* ex)
	{
		strMessage.LoadString(IDS_ADDDOORERR);
		MessageBox(strMessage, CKontrolaPristupaApp::strAppName, MB_OK | MB_ICONERROR);

		GetDlgItem(IDC_ENAME)->SetWindowTextW(_T(""));
		GetDlgItem(IDC_EDESCRIPTION)->SetWindowTextW(_T(""));
		GetDlgItem(IDC_EIPADDRESS)->SetWindowTextW(_T(""));
		if (doors.IsOpen())
			doors.Close();
		return;
	}
	
	if (doors.IsOpen())
		doors.Close();

	EndDialog(0);
}
