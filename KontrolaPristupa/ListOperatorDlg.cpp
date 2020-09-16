// ListOperatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "ListOperatorDlg.h"
#include "afxdialogex.h"
#include "Operator.h"
#include "ManageOperatorsDlg.h"

// CListOperatorDlg dialog

IMPLEMENT_DYNAMIC(CListOperatorDlg, CDialogEx)

CListOperatorDlg::CListOperatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LISTOPERATOR, pParent)
{
	theApp = (CKontrolaPristupaApp*)AfxGetApp();
}

CListOperatorDlg::~CListOperatorDlg()
{
}

void CListOperatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OPERATORS, lstCtrl);
}


BEGIN_MESSAGE_MAP(CListOperatorDlg, CDialogEx)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_OPERATORS, &CListOperatorDlg::OnLvnColumnClickOperators)
	ON_NOTIFY(NM_DBLCLK, IDC_OPERATORS, &CListOperatorDlg::OnNMDblclkOperators)
END_MESSAGE_MAP()

BOOL CListOperatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strText;
	strText.LoadString(IDS_OPERATORS);

	SetWindowText(theApp->getAppName() + " - " + strText);


	CString strLabel;
	lstCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	strLabel.LoadString(IDS_ID);
	lstCtrl.InsertColumn(0, strLabel, LVCFMT_LEFT, 50);
	strLabel.LoadString(IDS_USERNAME);
	lstCtrl.InsertColumn(1, strLabel, LVCFMT_LEFT, 100);
	strLabel.LoadString(IDS_ROLE);
	lstCtrl.InsertColumn(2, strLabel, LVCFMT_LEFT, 100);

	sortData = "[ID] DESC";
	sortAsc = TRUE;
	sortBy = 1;

	PopulateListCtrl();

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CListOperatorDlg::PopulateListCtrl()
{
	COperator opers;
	opers.m_strSort.Format(_T("%s"), sortData);
	opers.Open();

	int itemNo;
	CString strItem;

	while (!opers.IsEOF())
	{
		strItem.Format(_T("%d"), opers.m_ID);

		itemNo = lstCtrl.InsertItem(0, strItem);
		lstCtrl.SetItemText(itemNo, 1, opers.m_Username);
		if (theApp->getAdmin())
		{
			if (opers.m_IsAdmin == 1)
				strItem = "Admin";
			else
				strItem = "User";
			lstCtrl.SetItemText(itemNo, 2, strItem);
		}

		opers.MoveNext();
	}

	opers.Close();
}

void CListOperatorDlg::IdSort()
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

void CListOperatorDlg::UsernameSort()
{
	if (sortBy != 2)
		sortAsc = FALSE;

	if (sortAsc)
	{
		sortData = "[Username] ASC";
		sortAsc = FALSE;
	}
	else
	{
		sortData = "[Username] DESC";
		sortAsc = TRUE;
	}

	sortBy = 2;
}

void CListOperatorDlg::RoleSort()
{
	if (sortBy != 3)
		sortAsc = FALSE;

	if (sortAsc)
	{
		sortData = "[IsAdmin] ASC";
		sortAsc = FALSE;
	}
	else
	{
		sortData = "[IsAdmin] DESC";
		sortAsc = TRUE;
	}

	sortBy = 3;
}

// CListOperatorDlg message handlers


void CListOperatorDlg::OnLvnColumnClickOperators(NMHDR *pNMHDR, LRESULT *pResult)
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


void CListOperatorDlg::OnNMDblclkOperators(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (pNMItemActivate->iItem != -1)
	{
		if (theApp->getAdmin())
		{
			if (theApp->getActiveOperator().Compare(lstCtrl.GetItemText(pNMItemActivate->iItem, 1)))
			{
				CString selectedID = lstCtrl.GetItemText(pNMItemActivate->iItem, 0);
				CManageOperatorsDlg manageOperatorsDlg;
				manageOperatorsDlg.selectedID = _wtol(selectedID);
				manageOperatorsDlg.DoModal();
				lstCtrl.DeleteAllItems();
				PopulateListCtrl();
			}
		}
	}	

	*pResult = 0;
}
