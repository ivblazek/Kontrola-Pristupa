// ListGroupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "ListGroupDlg.h"
#include "afxdialogex.h"
#include "UserGroup.h"
#include "ManageGroupsDlg.h"


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
	DDX_Control(pDX, IDC_GROUPS, lstCtrl);
}


BEGIN_MESSAGE_MAP(CListGroupDlg, CDialogEx)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_GROUPS, &CListGroupDlg::OnLvnColumnClickGroups)
	ON_NOTIFY(NM_DBLCLK, IDC_GROUPS, &CListGroupDlg::OnNMDblclkGroups)
END_MESSAGE_MAP()

BOOL CListGroupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strText;
	strText.LoadString(IDS_GROUPS);

	SetWindowText(CKontrolaPristupaApp::strAppName + " - " + strText);


	CString strLabel;
	lstCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	strLabel.LoadString(IDS_ID);
	lstCtrl.InsertColumn(0, strLabel, LVCFMT_LEFT, 50);
	strLabel.LoadString(IDS_GROUPNAME);
	lstCtrl.InsertColumn(1, strLabel, LVCFMT_LEFT, 100);
	strLabel.LoadString(IDS_DESCRIPTION);
	lstCtrl.InsertColumn(2, strLabel, LVCFMT_LEFT, 300);

	sortData = "[ID] DESC";
	PopulateListCtrl();

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CListGroupDlg::PopulateListCtrl()
{
	CUserGroup groups;
	groups.m_strSort.Format(_T("%s"), sortData);
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
}

void CListGroupDlg::IdSort()
{
	if (sortData.Compare(_T("[ID] DESC")))
		sortData = "[ID] DESC";
	else
		sortData = "[ID] ASC";
}

void CListGroupDlg::UsernameSort()
{
	if (sortData.Compare(_T("[Name] DESC")))
		sortData = "[Name] DESC";
	else
		sortData = "[Name] ASC";
}

void CListGroupDlg::RoleSort()
{
	if (sortData.Compare(_T("[Description] DESC")))
		sortData = "[Description] DESC";
	else
		sortData = "[Description] ASC";
}

// CListGroupDlg message handlers


void CListGroupDlg::OnLvnColumnClickGroups(NMHDR *pNMHDR, LRESULT *pResult)
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
		RoleSort();
		break;
	default:
		break;
	}

	lstCtrl.DeleteAllItems();
	PopulateListCtrl();

	*pResult = 0;
}


void CListGroupDlg::OnNMDblclkGroups(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	if (CKontrolaPristupaApp::adminUser)
	{
		if (CKontrolaPristupaApp::activeOperator.Compare(lstCtrl.GetItemText(pNMItemActivate->iItem, 1)))
		{
			CString selectedID = lstCtrl.GetItemText(pNMItemActivate->iItem, 0);
			CManageGroupsDlg manageGroupsDlg;
			manageGroupsDlg.selectedID = _wtol(selectedID);
			manageGroupsDlg.DoModal();
			lstCtrl.DeleteAllItems();
			PopulateListCtrl();
		}
	}

	*pResult = 0;
}
