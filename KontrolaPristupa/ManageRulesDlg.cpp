// ManageRulesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "ManageRulesDlg.h"
#include "afxdialogex.h"
#include "Door.h"
#include "DoorUser.h"
#include "UserGroup.h"
#include "DoorRule.h"


// CManageRulesDlg dialog

IMPLEMENT_DYNAMIC(CManageRulesDlg, CDialogEx)

CManageRulesDlg::CManageRulesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MANAGERULES, pParent)
	, m_User(_T(""))
	, m_Door(_T(""))
{

}

CManageRulesDlg::~CManageRulesDlg()
{
}

void CManageRulesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_CUSER, m_User);
	DDV_MaxChars(pDX, m_User, 100);
	DDX_CBString(pDX, IDC_CDOOR, m_Door);
	DDV_MaxChars(pDX, m_Door, 100);
	DDX_Control(pDX, IDC_CUSER, userComboBox);
	DDX_Control(pDX, IDC_CDOOR, doorComboBox);
}


BEGIN_MESSAGE_MAP(CManageRulesDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BEXIT, &CManageRulesDlg::OnBnClickedBExit)
	ON_BN_CLICKED(IDC_BDELETE, &CManageRulesDlg::OnBnClickedBDelete)
	ON_CBN_SELCHANGE(IDC_CUSER, &CManageRulesDlg::OnCbnSelchangeCUser)
	ON_CBN_SELCHANGE(IDC_CDOOR, &CManageRulesDlg::OnCbnSelchangeCDoor)
END_MESSAGE_MAP()

BOOL CManageRulesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strText;
	strText.LoadString(IDS_MANAGERULES);

	SetWindowText(CKontrolaPristupaApp::getAppName() + " - " + strText);
	
	strText.LoadString(IDS_USER);
	strText += ":";
	GetDlgItem(IDC_TUSER)->SetWindowText(strText);

	strText.LoadString(IDS_DOOR);
	strText += ":";
	GetDlgItem(IDC_TDOOR)->SetWindowText(strText);

	strText.LoadString(IDS_EXIT);
	GetDlgItem(IDC_BEXIT)->SetWindowText(strText);

	strText.LoadString(IDS_DELETE);
	GetDlgItem(IDC_BDELETE)->SetWindowText(strText);
	
	CDoorUser users;
	users.Open();
	
	while (!users.IsEOF())
	{
		CDoorRule rules;
		rules.m_strFilter.Format(_T("UserID = '%d' AND DoorID = '%d'"), users.m_ID, selectedDoorID);
		rules.Open();

		CUserGroup groups;
		while (!rules.IsEOF())
		{
			groups.m_strFilter.Format(_T("ID = '%d'"), users.m_GroupID);
			groups.Open();
			strText.Format(_T("%d - %s %s, %s"), users.m_ID, users.m_Name, users.m_Surname, groups.m_Name);
			groups.Close();
			userComboBox.AddString(strText);
			if (selectedUserID == users.m_ID)
				userComboBox.SetCurSel(userComboBox.GetCount() - 1);
			rules.MoveNext();
		}
		rules.Close();
		users.MoveNext();
	}

	users.Close();


	CDoor doors;
	doors.Open();

	while (!doors.IsEOF())
	{
		CDoorRule rules;
		rules.m_strFilter.Format(_T("UserID = '%d' AND DoorID = '%d'"), selectedUserID, doors.m_ID);
		rules.Open();
		while (!rules.IsEOF())
		{
			strText.Format(_T("%d - %s, %s"), doors.m_ID, doors.m_Name, doors.m_Description);
			doorComboBox.AddString(strText);
			if (selectedDoorID == doors.m_ID)
				doorComboBox.SetCurSel(doorComboBox.GetCount() - 1);
			rules.MoveNext();
		}
		rules.Close();
		doors.MoveNext();
	}

	doors.Close();

	return TRUE;  // return TRUE  unless you set the focus to a control
}


// CManageRulesDlg message handlers


void CManageRulesDlg::OnBnClickedBExit()
{
	EndDialog(0);
}


void CManageRulesDlg::OnBnClickedBDelete()
{
	UpdateData();
	CString strMessage;
	CString m_UserID;
	CString m_DoorID;

	if (m_User.IsEmpty() || m_Door.IsEmpty())
	{
		strMessage.LoadString(IDS_EMPTYFIELDS);
		MessageBox(strMessage, CKontrolaPristupaApp::getAppName(), MB_OK);
		return;
	}

	m_UserID = m_User.Mid(0, m_User.Find('-') - 1);
	m_DoorID = m_Door.Mid(0, m_Door.Find('-') - 1);

	CDoorRule rules;

	try
	{
		rules.m_strFilter.Format(_T("UserID = '%s' AND DoorID = '%s'"), m_UserID, m_DoorID);
		rules.Open();

		rules.Delete();

		strMessage.LoadString(IDS_DELETERULEOK);
		MessageBox(strMessage, CKontrolaPristupaApp::getAppName(), MB_OK);
	}
	catch (CDBException* ex)
	{
		strMessage.LoadString(IDS_DELETERULEERR);
		MessageBox(strMessage, CKontrolaPristupaApp::getAppName(), MB_OK | MB_ICONERROR);

		if (rules.IsOpen())
			rules.Close();
		return;
	}

	if (rules.IsOpen())
		rules.Close();

	EndDialog(0);
}


void CManageRulesDlg::OnCbnSelchangeCUser()
{
	UpdateData();
	doorComboBox.ResetContent();

	CString strText;
	CString m_UserID = m_User.Mid(0, m_User.Find('-') - 1);
	CString m_DoorID = m_Door.Mid(0, m_User.Find('-') - 1);

	CDoor doors;
	doors.Open();
	while (!doors.IsEOF())
	{
		CDoorRule rules;
		rules.m_strFilter.Format(_T("UserID = '%s' AND DoorID = '%d'"), m_UserID, doors.m_ID);
		rules.Open();
		while (!rules.IsEOF())
		{
			strText.Format(_T("%d - %s, %s"), doors.m_ID, doors.m_Name, doors.m_Description);
			doorComboBox.AddString(strText);
			if (_wtol(m_DoorID) == doors.m_ID)
				doorComboBox.SetCurSel(doorComboBox.GetCount() - 1);
			rules.MoveNext();
		}
		rules.Close();
		doors.MoveNext();
	}
	doors.Close();
}


void CManageRulesDlg::OnCbnSelchangeCDoor()
{
	UpdateData();
	userComboBox.ResetContent();

	CString strText;
	CString m_UserID = m_User.Mid(0, m_User.Find('-') - 1);
	CString m_DoorID = m_Door.Mid(0, m_User.Find('-') - 1);

	CDoorUser users;
	users.Open();

	while (!users.IsEOF())
	{
		CDoorRule rules;
		rules.m_strFilter.Format(_T("UserID = '%d' AND DoorID = '%s'"), users.m_ID, m_DoorID);
		rules.Open();

		CUserGroup groups;
		while (!rules.IsEOF())
		{
			groups.m_strFilter.Format(_T("ID = '%d'"), users.m_GroupID);
			groups.Open();
			strText.Format(_T("%d - %s %s, %s"), users.m_ID, users.m_Name, users.m_Surname, groups.m_Name);
			groups.Close();
			userComboBox.AddString(strText);
			if (_wtol(m_UserID) == users.m_ID)
				userComboBox.SetCurSel(userComboBox.GetCount() - 1);
			rules.MoveNext();
		}
		rules.Close();
		users.MoveNext();
	}

	users.Close();
}
