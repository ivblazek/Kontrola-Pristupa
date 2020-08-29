// AddGroupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "AddGroupDlg.h"
#include "afxdialogex.h"
#include "UserGroup.h"


// CAddGroupDlg dialog

IMPLEMENT_DYNAMIC(CAddGroupDlg, CDialogEx)

CAddGroupDlg::CAddGroupDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADDGROUP, pParent)
	, m_Name(_T(""))
	, m_Description(_T(""))
{
	strAppName.LoadString(IDS_APPNAME);
}

CAddGroupDlg::~CAddGroupDlg()
{
}

void CAddGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EGROUPNAME, m_Name);
	DDV_MaxChars(pDX, m_Name, 50);
	DDX_Text(pDX, IDC_EGROUPDES, m_Description);
	DDV_MaxChars(pDX, m_Description, 50);
}


BEGIN_MESSAGE_MAP(CAddGroupDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BADDGROUP, &CAddGroupDlg::OnBnClickedBaddgroup)
END_MESSAGE_MAP()

BOOL CAddGroupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(strAppName);
	
	CString strText;
	strText.LoadString(IDS_GROUPNAME);
	strText += ":";
	GetDlgItem(IDC_TGROUPNAME)->SetWindowText(strText);


	strText.LoadString(IDS_DESCRIPTION);
	strText += ":";
	GetDlgItem(IDC_TGROUPDES)->SetWindowText(strText);

	strText.LoadString(IDS_ADDGROUP);
	GetDlgItem(IDC_BADDGROUP)->SetWindowText(strText);

	

	return TRUE;  // return TRUE  unless you set the focus to a control
}


// CAddGroupDlg message handlers


void CAddGroupDlg::OnBnClickedBaddgroup()
{
	UpdateData();
	CString strMessage;

	if (m_Name.IsEmpty() )
	{
		strMessage.LoadString(IDS_EMPTYFIELDS);
		MessageBox(strMessage, strAppName, MB_OK);
		return;
	}

	CUserGroup groups;
	groups.Open();

	groups.AddNew();
	groups.m_Name = m_Name;
	groups.m_Description = m_Description;
	groups.Update();
	
	groups.Close();

	EndDialog(0);
}