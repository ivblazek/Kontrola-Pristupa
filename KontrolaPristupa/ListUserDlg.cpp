// ListUser.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "ListUserDlg.h"
#include "afxdialogex.h"
#include "DoorUser.h"
#include "UserGroup.h"


// CListUserDlg dialog

IMPLEMENT_DYNAMIC(CListUserDlg, CDialogEx)

CListUserDlg::CListUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LISTUSER, pParent)
{

}

CListUserDlg::~CListUserDlg()
{
}

void CListUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENTS, lstCtrl);
}


BEGIN_MESSAGE_MAP(CListUserDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CListUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	

	SetWindowText(CKontrolaPristupaApp::strAppName);
	

	CString strLabel;
	lstCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	strLabel.LoadString(IDS_ID);
	lstCtrl.InsertColumn(0, strLabel, LVCFMT_LEFT, 50);
	strLabel.LoadString(IDS_NAME);
	lstCtrl.InsertColumn(1, strLabel, LVCFMT_LEFT, 100);
	strLabel.LoadString(IDS_SURNAME);
	lstCtrl.InsertColumn(2, strLabel, LVCFMT_LEFT, 100);
	strLabel.LoadString(IDS_GROUPNAME);
	lstCtrl.InsertColumn(3, strLabel, LVCFMT_LEFT, 100);
	strLabel.LoadString(IDS_CARDNO);
	lstCtrl.InsertColumn(4, strLabel, LVCFMT_LEFT, 100);


	CDoorUser users;
	users.Open();

	int itemNo;
	CString strItem;
	CUserGroup groups;

	while (!users.IsEOF())
	{
		strItem.Format(_T("%d"), users.m_ID);

		itemNo = lstCtrl.InsertItem(0, strItem);
		lstCtrl.SetItemText(itemNo, 1, users.m_Name);
		lstCtrl.SetItemText(itemNo, 2, users.m_Surname);
		
		groups.m_strFilter.Format(_T("ID = '%d'"), users.m_GroupID);
		groups.Open();
		lstCtrl.SetItemText(itemNo, 3, groups.m_Name);
		groups.Close();

		strItem = users.m_CardNo;
		lstCtrl.SetItemText(itemNo, 4, strItem);
		users.MoveNext();
	}

	users.Close();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// CListUserDlg message handlers
