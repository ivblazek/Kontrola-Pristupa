// ListUser.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "ListUserDlg.h"
#include "afxdialogex.h"
#include "ListUser.h"


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
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_EVENTS, &CListUserDlg::OnLvnColumnClickEvents)
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

	sortData = "[ID] DESC";
	PopulateListCtrl();	

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CListUserDlg::PopulateListCtrl()
{
	CListUser users;
	users.m_strSort.Format(_T("%s"), sortData);
	users.Open();

	int itemNo;
	CString strItem;

	while (!users.IsEOF())
	{
		strItem.Format(_T("%d"), users.m_ID);

		itemNo = lstCtrl.InsertItem(0, strItem);
		lstCtrl.SetItemText(itemNo, 1, users.m_Name);
		lstCtrl.SetItemText(itemNo, 2, users.m_Surname);
		lstCtrl.SetItemText(itemNo, 3, users.m_GroupName);

		strItem = users.m_CardNo;
		lstCtrl.SetItemText(itemNo, 4, strItem);
		users.MoveNext();
	}

	users.Close();
}

void CListUserDlg::IdSort()
{
	if (sortData.Compare(_T("[ID] DESC")))
		sortData = "[ID] DESC";
	else
		sortData = "[ID] ASC";
}

void CListUserDlg::UsernameSort()
{
	if (sortData.Compare(_T("[Name] DESC, [Surname] DESC")))
		sortData = "[Name] DESC, [Surname] DESC";
	else
		sortData = "[Name] ASC, [Surname] ASC";
}

void CListUserDlg::SurnameSort()
{
	if (sortData.Compare(_T("[Surname] DESC, [Name] DESC")))
		sortData = "[Surname] DESC, [Name] DESC";
	else
		sortData = "[Surname] ASC, [Name] ASC";
}

void CListUserDlg::GroupSort()
{
	if (sortData.Compare(_T("[GroupName] DESC, [Surname] DESC, [Name] DESC")))
		sortData = "[GroupName] DESC, [Surname] DESC, [Name] DESC";
	else
		sortData = "[GroupName] ASC, [Surname] ASC, [Name] ASC";
}

void CListUserDlg::CardSort()
{
	if (sortData.Compare(_T("[CardNo] DESC")))
		sortData = "[CardNo] DESC";
	else
		sortData = "[CardNo] ASC";
}

// CListUserDlg message handlers


void CListUserDlg::OnLvnColumnClickEvents(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	switch (pNMLV->iSubItem)
	{
	case 0:
		IdSort();
		break;
	case 1:
		UsernameSort();
		break;
	case 2:
		SurnameSort();
		break;
	case 3:
		GroupSort();
		break;
	case 4:
		CardSort();
		break;
	default:
		break;
	}

	lstCtrl.DeleteAllItems();
	PopulateListCtrl();

	*pResult = 0;
}
