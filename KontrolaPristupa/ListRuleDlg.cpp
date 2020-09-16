// ListRule.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "ListRuleDlg.h"
#include "afxdialogex.h"
#include "ListRule.h"
#include "ManageRulesDlg.h"


// CListRuleDlg dialog

IMPLEMENT_DYNAMIC(CListRuleDlg, CDialogEx)

CListRuleDlg::CListRuleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LISTRULE, pParent)
{
	theApp = (CKontrolaPristupaApp*)AfxGetApp();
}

CListRuleDlg::~CListRuleDlg()
{
}

void CListRuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RULES, lstCtrl);
}


BEGIN_MESSAGE_MAP(CListRuleDlg, CDialogEx)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_RULES, &CListRuleDlg::OnLvnColumnClickRules)
	ON_NOTIFY(NM_DBLCLK, IDC_RULES, &CListRuleDlg::OnNMDblclkRules)
END_MESSAGE_MAP()

BOOL CListRuleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strText;
	strText.LoadString(IDS_RULES);

	SetWindowText(theApp->getAppName() + " - " + strText);


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

	sortData = "[DoorID] DESC, [UserID] DESC";
	sortAsc = TRUE;
	sortBy = 1;

	PopulateListCtrl();

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CListRuleDlg::PopulateListCtrl()
{
	CListRule rules;
	rules.m_strSort.Format(_T("%s"), sortData);
	rules.Open();

	int itemNo;
	CString strItem;

	while (!rules.IsEOF())
	{
		strItem.Format(_T("%d"), rules.m_DoorID);
		itemNo = lstCtrl.InsertItem(0, strItem);
		lstCtrl.SetItemText(itemNo, 1, rules.m_DoorName);

		strItem.Format(_T("%d"), rules.m_UserID);
		lstCtrl.SetItemText(itemNo, 2, strItem);
		lstCtrl.SetItemText(itemNo, 3, rules.m_Name);
		lstCtrl.SetItemText(itemNo, 4, rules.m_Surname);

		rules.MoveNext();
	}

	rules.Close();
}

void CListRuleDlg::DoorIdSort()
{
	if (sortBy != 1)
		sortAsc = FALSE;

	if (sortAsc)
	{
		sortData = "[DoorID] ASC, [UserID] DESC";
		sortAsc = FALSE;
	}
	else
	{
		sortData = "[DoorID] DESC, [UserID] DESC";
		sortAsc = TRUE;
	}

	sortBy = 1;
}

void CListRuleDlg::DoorNameSort()
{
	if (sortBy != 2)
		sortAsc = FALSE;

	if (sortAsc)
	{
		sortData = "[DoorName] ASC, [UserID] DESC";
		sortAsc = FALSE;
	}
	else
	{
		sortData = "[DoorName] DESC, [UserID] DESC";
		sortAsc = TRUE;
	}

	sortBy = 2;
}

void CListRuleDlg::UserIdSort()
{
	if (sortBy != 3)
		sortAsc = FALSE;

	if (sortAsc)
	{
		sortData = "[UserID] ASC, [DoorID] DESC";
		sortAsc = FALSE;
	}
	else
	{
		sortData = "[UserID] DESC, [DoorID] DESC";
		sortAsc = TRUE;
	}

	sortBy = 3;
}

void CListRuleDlg::UsernameSort()
{
	if (sortBy != 4)
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

	sortBy = 4;
}

void CListRuleDlg::SurnameSort()
{
	if (sortBy != 5)
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

	sortBy = 5;
}

// CListRuleDlg message handlers


void CListRuleDlg::OnLvnColumnClickRules(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	switch (pNMLV->iSubItem)
	{
	case 0:
		DoorIdSort();
		break;
	case 1:
		DoorNameSort();
		break;
	case 2:
		UserIdSort();
		break;
	case 3:
		UsernameSort();
		break;
	case 4:
		SurnameSort();
		break;
	default:
		break;
	}

	lstCtrl.DeleteAllItems();
	PopulateListCtrl();

	*pResult = 0;
}


void CListRuleDlg::OnNMDblclkRules(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (pNMItemActivate->iItem != -1)
	{
		if (theApp->getAdmin())
		{
			if (theApp->getActiveOperator().Compare(lstCtrl.GetItemText(pNMItemActivate->iItem, 1)))
			{
				CString selectedID = lstCtrl.GetItemText(pNMItemActivate->iItem, 0);
				CManageRulesDlg manageRulesDlg;
				manageRulesDlg.selectedDoorID = _wtol(selectedID);
				selectedID = lstCtrl.GetItemText(pNMItemActivate->iItem, 2);
				manageRulesDlg.selectedUserID = _wtol(selectedID);
				manageRulesDlg.DoModal();
				lstCtrl.DeleteAllItems();
				PopulateListCtrl();
			}
		}
	}	

	*pResult = 0;
}
