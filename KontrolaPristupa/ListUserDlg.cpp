// ListUser.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "ListUserDlg.h"
#include "afxdialogex.h"
#include "ListUser.h"
#include "ManageUsersDlg.h"


// CListUserDlg dialog

IMPLEMENT_DYNAMIC(CListUserDlg, CDialogEx)

CListUserDlg::CListUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LISTUSER, pParent)
{
	theApp = (CKontrolaPristupaApp*)AfxGetApp();
}

CListUserDlg::~CListUserDlg()
{
}

void CListUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USERS, lstCtrl);
}


BEGIN_MESSAGE_MAP(CListUserDlg, CDialogEx)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_USERS, &CListUserDlg::OnLvnColumnClickUsers)
	ON_NOTIFY(NM_DBLCLK, IDC_USERS, &CListUserDlg::OnNMDblclkUsers)
END_MESSAGE_MAP()

BOOL CListUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	CString strText;
	strText.LoadString(IDS_USERS);

	SetWindowText(theApp->getAppName() + " - " + strText);
	

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
	sortAsc = TRUE;
	sortBy = 1;

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
	if (sortBy != 1)
		sortAsc = FALSE;

	if (sortAsc)
	{
		sortData = "[ID] ASC";
		sortAsc = FALSE;
	}
	else
	{
		sortData = "[ID] DESC";
		sortAsc = TRUE;
	}

	sortBy = 1;
}

void CListUserDlg::UsernameSort()
{
	if (sortBy != 2)
		sortAsc = FALSE;

	if (sortAsc)
	{
		sortData = "[Name] ASC, [Surname] ASC";
		sortAsc = FALSE;
	}
	else
	{
		sortData = "[Name] DESC, [Surname] DESC";
		sortAsc = TRUE;
	}

	sortBy = 2;
}

void CListUserDlg::SurnameSort()
{
	if (sortBy != 2)
		sortAsc = FALSE;

	if (sortAsc)
	{
		sortData = "[Surname] ASC, [Name] ASC";
		sortAsc = FALSE;
	}
	else
	{
		sortData = "[Surname] DESC, [Name] DESC";
		sortAsc = TRUE;
	}

	sortBy = 2;
}

void CListUserDlg::GroupSort()
{
	if (sortBy != 3)
		sortAsc = FALSE;

	if (sortAsc)
	{
		sortData = "[GroupName] ASC, [Surname] ASC, [Name] ASC";
		sortAsc = FALSE;
	}
	else
	{
		sortData = "[GroupName] DESC, [Surname] DESC, [Name] DESC";
		sortAsc = TRUE;
	}

	sortBy = 3;
}

void CListUserDlg::CardSort()
{
	if (sortBy != 3)
		sortAsc = FALSE;

	if (sortAsc)
	{
		sortData = "[CardNo] ASC";
		sortAsc = FALSE;
	}
	else
	{
		sortData = "[CardNo] DESC";
		sortAsc = TRUE;
	}

	sortBy = 3;
}

// CListUserDlg message handlers


void CListUserDlg::OnLvnColumnClickUsers(NMHDR *pNMHDR, LRESULT *pResult)
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


void CListUserDlg::OnNMDblclkUsers(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	if (pNMItemActivate->iItem != -1)
	{
		if (theApp->getAdmin())
		{
			if (theApp->getActiveOperator().Compare(lstCtrl.GetItemText(pNMItemActivate->iItem, 1)))
			{
				CString selectedID = lstCtrl.GetItemText(pNMItemActivate->iItem, 0);
				CManageUsersDlg manageUsersDlg;
				manageUsersDlg.selectedID = _wtol(selectedID);
				manageUsersDlg.DoModal();
				lstCtrl.DeleteAllItems();
				PopulateListCtrl();
			}
		}
	}	

	*pResult = 0;
}
