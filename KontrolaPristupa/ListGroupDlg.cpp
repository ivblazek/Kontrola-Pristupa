// ListGroupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "ListGroupDlg.h"
#include "afxdialogex.h"
#include "UserGroup.h"


// CListGroupDlg dialog

IMPLEMENT_DYNAMIC(CListGroupDlg, CDialogEx)

CListGroupDlg::CListGroupDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LISTGROUP, pParent)
{

}

CListGroupDlg::~CListGroupDlg()
{
}

void CListGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENTS, lstCtrl);
}


BEGIN_MESSAGE_MAP(CListGroupDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CListGroupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	SetWindowText(CKontrolaPristupaApp::strAppName);


	CString strLabel;
	lstCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	strLabel.LoadString(IDS_ID);
	lstCtrl.InsertColumn(0, strLabel, LVCFMT_LEFT, 50);
	strLabel.LoadString(IDS_GROUPNAME);
	lstCtrl.InsertColumn(1, strLabel, LVCFMT_LEFT, 100);
	strLabel.LoadString(IDS_DESCRIPTION);
	lstCtrl.InsertColumn(2, strLabel, LVCFMT_LEFT, 300);

	CUserGroup groups;
	groups.Open();
	
	int itemNo;
	CString strItem;
	
	while (!groups.IsEOF())
	{
		strItem.Format(_T("%d"), groups.m_ID);

		itemNo = lstCtrl.InsertItem(0, strItem);
		lstCtrl.SetItemText(itemNo, 1, groups.m_Name);
		lstCtrl.SetItemText(itemNo, 2, groups.m_Description);
		
		groups.MoveNext();
	}

	groups.Close();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// CListGroupDlg message handlers
