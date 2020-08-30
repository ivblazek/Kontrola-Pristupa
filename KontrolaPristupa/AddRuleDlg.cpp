// AddRuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "AddRuleDlg.h"
#include "afxdialogex.h"
#include "Door.h"
#include "DoorUser.h"
#include "DoorRule.h"
#include "UserGroup.h"


// CAddRuleDlg dialog

IMPLEMENT_DYNAMIC(CAddRuleDlg, CDialogEx)

CAddRuleDlg::CAddRuleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADDRULE, pParent)
	, m_User(_T(""))
	, m_Door(_T(""))
{

}

CAddRuleDlg::~CAddRuleDlg()
{
}

void CAddRuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_CUSER, m_User);
	DDV_MaxChars(pDX, m_User, 50);
	DDX_CBString(pDX, IDC_CDOOR, m_Door);
	DDV_MaxChars(pDX, m_Door, 50);
	DDX_Control(pDX, IDC_CUSER, userComboBox);
	DDX_Control(pDX, IDC_CDOOR, doorComboBox);
}


BEGIN_MESSAGE_MAP(CAddRuleDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BADDRULE, &CAddRuleDlg::OnBnClickedBAddRule)
	ON_CBN_SELCHANGE(IDC_CUSER, &CAddRuleDlg::OnCbnSelchangeCUser)
END_MESSAGE_MAP()

BOOL CAddRuleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(CKontrolaPristupaApp::strAppName);

	CString strText;
	strText.LoadString(IDS_USER);
	strText += ":";
	GetDlgItem(IDC_TUSER)->SetWindowText(strText);


	strText.LoadString(IDS_DOOR);
	strText += ":";
	GetDlgItem(IDC_TDOOR)->SetWindowText(strText);

	strText.LoadString(IDS_ADDRULE);
	GetDlgItem(IDC_BADDRULE)->SetWindowText(strText);

	CDoorUser users;
	users.Open();

	CUserGroup groups;
	
	while (!users.IsEOF())
	{
		groups.m_strFilter.Format(_T("ID = '%d'"), users.m_GroupID);
		groups.Open();
		strText.Format(_T("%d - %s %s, %s"), users.m_ID, users.m_Name, users.m_Surname, groups.m_Name);
		groups.Close();
		userComboBox.AddString(strText);
		users.MoveNext();
	}
	groups.Close();
	users.Close();	

	return TRUE;  // return TRUE  unless you set the focus to a control
}


// CAddRuleDlg message handlers


void CAddRuleDlg::OnBnClickedBAddRule()
{
	UpdateData();
	CString strMessage;

	if (m_User.IsEmpty() || m_Door.IsEmpty())
	{
		strMessage.LoadString(IDS_EMPTYFIELDS);
		MessageBox(strMessage, CKontrolaPristupaApp::strAppName, MB_OK);
		return;
	}

	CDoorRule rules;
	rules.Open();

	rules.AddNew();
	rules.m_DoorID = _wtol(m_Door.Mid(0, m_Door.Find('-') - 1));
	rules.m_UserID = _wtol(m_User.Mid(0, m_User.Find('-') - 1));
	rules.Update();

	rules.Close();

	EndDialog(0);
}


void CAddRuleDlg::OnCbnSelchangeCUser()
{
	UpdateData();
	doorComboBox.ResetContent();

	CString strText;
	CString filter;
	filter = m_User.Mid(0, m_User.Find('-') - 1);

	CDoor doors;
	doors.Open();
	while (!doors.IsEOF())
	{
		CDoorRule rules;
		rules.m_strFilter.Format(_T("UserID = '%s' AND DoorID = '%d'"), filter, doors.m_ID);
		rules.Open();
		if(rules.IsEOF())
		{
			strText.Format(_T("%d - %s, %s"), doors.m_ID, doors.m_Name, doors.m_Description);
			doorComboBox.AddString(strText);
		}
		rules.Close();
		doors.MoveNext();
	}
	doors.Close();
}

