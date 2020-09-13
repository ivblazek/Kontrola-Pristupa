// ManageUsersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "ManageUsersDlg.h"
#include "afxdialogex.h"
#include "DoorUser.h"
#include "UserGroup.h"


// CManageUsersDlg dialog

IMPLEMENT_DYNAMIC(CManageUsersDlg, CDialogEx)

CManageUsersDlg::CManageUsersDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MANAGEUSERS, pParent)
	, m_Name(_T(""))
	, m_Surname(_T(""))
	, m_GroupName(_T(""))
	, m_CardNo(_T(""))
{

}

CManageUsersDlg::~CManageUsersDlg()
{
}

void CManageUsersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ENAME, m_Name);
	DDV_MaxChars(pDX, m_Name, 50);
	DDX_Text(pDX, IDC_ESURNAME, m_Surname);
	DDV_MaxChars(pDX, m_Surname, 50);
	DDX_CBString(pDX, IDC_EGROUPNAME, m_GroupName);
	DDV_MaxChars(pDX, m_GroupName, 50);
	DDX_Control(pDX, IDC_EGROUPNAME, groupComboBox);
	DDX_Text(pDX, IDC_ECARDNO, m_CardNo);
	DDV_MaxChars(pDX, m_CardNo, 8);
}


BEGIN_MESSAGE_MAP(CManageUsersDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BSAVE, &CManageUsersDlg::OnBnClickedBSave)
	ON_BN_CLICKED(IDC_BCANCEL, &CManageUsersDlg::OnBnClickedBCancel)
	ON_BN_CLICKED(IDC_BDELETE, &CManageUsersDlg::OnBnClickedBDelete)
END_MESSAGE_MAP()

BOOL CManageUsersDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strText;
	strText.LoadString(IDS_MANAGEUSERS);

	SetWindowText(CKontrolaPristupaApp::getAppName() + " - " + strText);


	strText.LoadString(IDS_NAME);
	strText += ":";
	GetDlgItem(IDC_TNAME)->SetWindowText(strText);

	strText.LoadString(IDS_SURNAME);
	strText += ":";
	GetDlgItem(IDC_TSURNAME)->SetWindowText(strText);

	strText.LoadString(IDS_GROUPNAME);
	strText += ":";
	GetDlgItem(IDC_TGROUPNAME)->SetWindowText(strText);

	strText.LoadString(IDS_CARDNO);
	strText += ":";
	GetDlgItem(IDC_TCARDNO)->SetWindowText(strText);

	strText.LoadString(IDS_SAVE);
	GetDlgItem(IDC_BSAVE)->SetWindowText(strText);

	strText.LoadString(IDS_CANCEL);
	GetDlgItem(IDC_BCANCEL)->SetWindowText(strText);

	strText.LoadString(IDS_DELETE);
	GetDlgItem(IDC_BDELETE)->SetWindowText(strText);


	CDoorUser users;
	users.m_strFilter.Format(_T("ID = '%d'"), selectedID);
	users.Open();

	GetDlgItem(IDC_ENAME)->SetWindowText(users.m_Name);
	GetDlgItem(IDC_ESURNAME)->SetWindowText(users.m_Surname);
	GetDlgItem(IDC_ECARDNO)->SetWindowText((CString)users.m_CardNo);

	CUserGroup groups;
	groups.Open();

	while (!groups.IsEOF())
	{
		groupComboBox.AddString(groups.m_Name);
		if (groups.m_ID == users.m_GroupID)
			groupComboBox.SetCurSel(groupComboBox.GetCount() - 1);
		groups.MoveNext();
	}
	groups.Close();

	users.Close();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// CManageUsersDlg message handlers


void CManageUsersDlg::OnBnClickedBSave()
{
	UpdateData();
	CString strMessage;

	if (m_Name.IsEmpty() || m_Surname.IsEmpty() || m_GroupName.IsEmpty() || m_CardNo.IsEmpty())
	{
		strMessage.LoadString(IDS_EMPTYFIELDS);
		MessageBox(strMessage, CKontrolaPristupaApp::getAppName(), MB_OK);
		return;
	}

	if (m_CardNo.GetLength() < 8)
	{
		strMessage.LoadString(IDS_SHORTCARDNO);
		MessageBox(strMessage, CKontrolaPristupaApp::getAppName(), MB_OK);
		return;
	}

	CDoorUser users;
	CUserGroup groups;

	try
	{
		users.m_strFilter.Format(_T("ID = '%d'"), selectedID);
		users.Open();

		groups.m_strFilter.Format(_T("Name = '%s'"), m_GroupName);
		groups.Open();

		users.Edit();
		users.m_Name = m_Name;
		users.m_Surname = m_Surname;
		users.m_GroupID = groups.m_ID;
		users.m_CardNo = m_CardNo;
		users.Update();

		strMessage.LoadString(IDS_SAVEUSEROK);
		MessageBox(strMessage, CKontrolaPristupaApp::getAppName(), MB_OK);
	}
	catch (CDBException* ex)
	{
		strMessage.LoadString(IDS_SAVEUSERERR);
		MessageBox(strMessage, CKontrolaPristupaApp::getAppName(), MB_OK | MB_ICONERROR);

		if (users.IsOpen())
			users.Close();
		if (groups.IsOpen())
			groups.Close();
		return;
	}

	if (users.IsOpen())
		users.Close();
	if (groups.IsOpen())
		groups.Close();

	EndDialog(0);
}


void CManageUsersDlg::OnBnClickedBCancel()
{
	EndDialog(0);
}


void CManageUsersDlg::OnBnClickedBDelete()
{
	CString strMessage;
	CDoorUser users;

	try
	{
		users.m_strFilter.Format(_T("ID = '%d'"), selectedID);
		users.Open();
		users.Delete();

		strMessage.LoadString(IDS_DELUSEROK);
		MessageBox(strMessage, CKontrolaPristupaApp::getAppName(), MB_OK);
	}
	catch (CDBException* ex)
	{
		if (ex->m_strError.Find(_T("FK_Events_Users")) != -1)
		{
			strMessage.LoadString(IDS_DELUSERFKEVENT);
		}
		else if (ex->m_strError.Find(_T("FK_Rules_Users")) != -1)
		{
			strMessage.LoadString(IDS_DELUSERFKRULES);
		}
		else
			strMessage.LoadString(IDS_DELUSERERR);

		MessageBox(strMessage, CKontrolaPristupaApp::getAppName(), MB_OK | MB_ICONERROR);

		if (users.IsOpen())
			users.Close();
		return;
	}

	if (users.IsOpen())
		users.Close();

	EndDialog(0);
}
