// ManageGroupsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "ManageGroupsDlg.h"
#include "afxdialogex.h"
#include "UserGroup.h"


// CManageGroupsDlg dialog

IMPLEMENT_DYNAMIC(CManageGroupsDlg, CDialogEx)

CManageGroupsDlg::CManageGroupsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MANAGEGROUPS, pParent)
	, m_Name(_T(""))
	, m_Description(_T(""))
{

}

CManageGroupsDlg::~CManageGroupsDlg()
{
}

void CManageGroupsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EGROUPNAME, m_Name);
	DDV_MaxChars(pDX, m_Name, 50);
	DDX_Text(pDX, IDC_EGROUPDES, m_Description);
	DDV_MaxChars(pDX, m_Description, 50);
}


BEGIN_MESSAGE_MAP(CManageGroupsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BSAVE, &CManageGroupsDlg::OnBnClickedBSave)
	ON_BN_CLICKED(IDC_BCANCEL, &CManageGroupsDlg::OnBnClickedBCancel)
END_MESSAGE_MAP()

BOOL CManageGroupsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strText;
	strText.LoadString(IDS_MANAGEGROUPS);

	SetWindowText(CKontrolaPristupaApp::strAppName + " - " + strText);


	strText.LoadString(IDS_GROUPNAME);
	strText += ":";
	GetDlgItem(IDC_TGROUPNAME)->SetWindowText(strText);


	strText.LoadString(IDS_DESCRIPTION);
	strText += ":";
	GetDlgItem(IDC_TGROUPDES)->SetWindowText(strText);

	strText.LoadString(IDS_SAVE);
	GetDlgItem(IDC_BSAVE)->SetWindowText(strText);

	strText.LoadString(IDS_CANCEL);
	GetDlgItem(IDC_BCANCEL)->SetWindowText(strText);
	
	CUserGroup groups;
	groups.m_strFilter.Format(_T("ID = '%d'"), selectedID);
	groups.Open();

	GetDlgItem(IDC_EGROUPNAME)->SetWindowText(groups.m_Name);
	GetDlgItem(IDC_EGROUPDES)->SetWindowText(groups.m_Description);

	groups.Close();

	return TRUE;  // return TRUE  unless you set the focus to a control
}


// CManageGroupsDlg message handlers


void CManageGroupsDlg::OnBnClickedBSave()
{
	UpdateData();
	CString strMessage;

	if (m_Name.IsEmpty())
	{
		strMessage.LoadString(IDS_EMPTYFIELDS);
		MessageBox(strMessage, CKontrolaPristupaApp::strAppName, MB_OK);
		return;
	}

	CUserGroup groups;

	try
	{
		groups.m_strFilter.Format(_T("ID = '%d'"), selectedID);
		groups.Open();
		groups.Edit();
		groups.m_Name = m_Name;
		groups.m_Description = m_Description;
		groups.Update();

		strMessage.LoadString(IDS_SAVEGROUPOK);
		MessageBox(strMessage, CKontrolaPristupaApp::strAppName, MB_OK);
	}
	catch (CDBException* ex)
	{
		strMessage.LoadString(IDS_SAVEGROUPERR);
		MessageBox(strMessage, CKontrolaPristupaApp::strAppName, MB_OK | MB_ICONERROR);

		if (groups.IsOpen())
			groups.Close();
		return;
	}

	if (groups.IsOpen())
		groups.Close();

	EndDialog(0);
}


void CManageGroupsDlg::OnBnClickedBCancel()
{
	EndDialog(0);
}