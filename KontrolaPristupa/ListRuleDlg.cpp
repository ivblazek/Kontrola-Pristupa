// ListRule.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "ListRuleDlg.h"
#include "afxdialogex.h"
#include "DoorRule.h"
#include "Door.h"
#include "DoorUser.h"


// CListRuleDlg dialog

IMPLEMENT_DYNAMIC(CListRuleDlg, CDialogEx)

CListRuleDlg::CListRuleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LISTRULE, pParent)
{

}

CListRuleDlg::~CListRuleDlg()
{
}

void CListRuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENTS, lstCtrl);
}


BEGIN_MESSAGE_MAP(CListRuleDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CListRuleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	SetWindowText(CKontrolaPristupaApp::strAppName);


	CString strLabel;
	lstCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	strLabel.LoadString(IDS_DOORID);
	lstCtrl.InsertColumn(0, strLabel, LVCFMT_LEFT, 50);
	strLabel.LoadString(IDS_DOORNAME);
	lstCtrl.InsertColumn(1, strLabel, LVCFMT_LEFT, 150);
	strLabel.LoadString(IDS_USERID);
	lstCtrl.InsertColumn(2, strLabel, LVCFMT_LEFT, 50);
	strLabel.LoadString(IDS_NAME);
	lstCtrl.InsertColumn(3, strLabel, LVCFMT_LEFT, 100);
	strLabel.LoadString(IDS_SURNAME);
	lstCtrl.InsertColumn(4, strLabel, LVCFMT_LEFT, 100);

	CDoorRule rules;
	rules.Open();

	int itemNo;
	CString strItem;
	CDoor doors;
	CDoorUser users;

	while (!rules.IsEOF())
	{
		doors.m_strFilter.Format(_T("ID = '%d'"), rules.m_DoorID);
		users.m_strFilter.Format(_T("ID = '%d'"), rules.m_UserID);
		doors.Open();
		users.Open();

		strItem.Format(_T("%d"), rules.m_DoorID);
		
		itemNo = lstCtrl.InsertItem(0, strItem);
		lstCtrl.SetItemText(itemNo, 1, doors.m_Name);

		strItem.Format(_T("%d"), rules.m_UserID);

		lstCtrl.SetItemText(itemNo, 2, strItem);
		lstCtrl.SetItemText(itemNo, 3, users.m_Name);
		lstCtrl.SetItemText(itemNo, 4, users.m_Surname);

		doors.Close();
		users.Close();
		rules.MoveNext();
	}

	rules.Close();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// CListRuleDlg message handlers
