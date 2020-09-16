// AddUserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "AddUserDlg.h"
#include "afxdialogex.h"
#include "DoorUser.h"
#include "UserGroup.h"


// CAddUserDlg dialog

IMPLEMENT_DYNAMIC(CAddUserDlg, CDialogEx)

CAddUserDlg::CAddUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADDUSER, pParent)
	, m_Name(_T(""))
	, m_Surname(_T(""))
	, m_GroupName(_T(""))
	, m_CardNo(_T(""))
{
	theApp = (CKontrolaPristupaApp*)AfxGetApp();
}

CAddUserDlg::~CAddUserDlg()
{
}

void CAddUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ENAME, m_Name);
	DDV_MaxChars(pDX, m_Name, 50);
	DDX_Text(pDX, IDC_ESURNAME, m_Surname);
	DDV_MaxChars(pDX, m_Surname, 50);
	DDX_CBString(pDX, IDC_EGROUPNAME, m_GroupName);
	DDV_MaxChars(pDX, m_GroupName, 50);
	DDX_Text(pDX, IDC_ECARDNO, m_CardNo);
	DDV_MaxChars(pDX, m_CardNo, 8);
	DDX_Control(pDX, IDC_EGROUPNAME, groupComboBox);
}


BEGIN_MESSAGE_MAP(CAddUserDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BADDUSER, &CAddUserDlg::OnBnClickedBadduser)
END_MESSAGE_MAP()


// CAddUserDlg message handlers

BOOL CAddUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strText;
	strText.LoadString(IDS_ADDUSER);

	SetWindowText(theApp->getAppName() + " - " + strText);
	
	
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

	strText.LoadString(IDS_ADDUSER);
	GetDlgItem(IDC_BADDUSER)->SetWindowText(strText);

	CUserGroup groups;
	groups.Open();

	while (!groups.IsEOF())
	{
		groupComboBox.AddString(groups.m_Name);
		groups.MoveNext();
	}
	groups.Close();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAddUserDlg::OnBnClickedBadduser()
{
	UpdateData();
	CString strMessage;

	if (m_Name.IsEmpty() || m_Surname.IsEmpty() || m_GroupName.IsEmpty() || m_CardNo.IsEmpty())
	{
		strMessage.LoadString(IDS_EMPTYFIELDS);
		MessageBox(strMessage, theApp->getAppName(), MB_OK);
		return;
	}

	if (m_CardNo.GetLength() < 8)
	{
		strMessage.LoadString(IDS_SHORTCARDNO);
		MessageBox(strMessage, theApp->getAppName(), MB_OK);
		return;
	}		

	CDoorUser users;
	CUserGroup groups;

	try
	{		
		users.Open();

		groups.m_strFilter.Format(_T("Name = '%s'"), m_GroupName);
		groups.Open();		
		
		users.AddNew();
		users.m_Name = m_Name;
		users.m_Surname = m_Surname;
		users.m_GroupID = groups.m_ID;
		users.m_CardNo = m_CardNo;
		users.Update();

		strMessage.LoadString(IDS_ADDUSEROK);
		MessageBox(strMessage, theApp->getAppName(), MB_OK);
	}
	catch (CDBException* ex)
	{
		strMessage.LoadString(IDS_ADDUSERERR);
		MessageBox(strMessage, theApp->getAppName(), MB_OK | MB_ICONERROR);

		GetDlgItem(IDC_ENAME)->SetWindowText(_T(""));
		GetDlgItem(IDC_ESURNAME)->SetWindowText(_T(""));
		GetDlgItem(IDC_EGROUPNAME)->SetWindowText(_T(""));
		groupComboBox.SetCurSel(-1);
		GetDlgItem(IDC_ECARDNO)->SetWindowText(_T(""));
		if (users.IsOpen())
			users.Close();
		if (groups.IsOpen())
			groups.Close();
		return;
	}

	if (users.IsOpen())
		users.Close();
	if(groups.IsOpen())
		groups.Close();

	EndDialog(0);
}
