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

	SetWindowText(CKontrolaPristupaApp::getAppName() + " - " + strText);


	CString strLabel;
	lstCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	strLabel.LoadString(IDS_ID);
	lstCtrl.InsertColumn(0, strLabel, LVCFMT_LEFT, 50);
	strLabel.LoadString(IDS_USERNAME);
	lstCtrl.InsertColumn(1, strLabel, LVCFMT_LEFT, 100);
	strLabel.LoadString(IDS_ROLE);
	lstCtrl.InsertColumn(2, strLabel, LVCFMT_LEFT, 100);

	sortData = "[ID] DESC";
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
		if (CKontrolaPristupaApp::getAdmin())
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
	if (sortData.Compare(_T("[ID] DESC")))
		sortData = "[ID] DESC";
	else
		sortData = "[ID] ASC";
}

void CListOperatorDlg::UsernameSort()
{
	if (sortData.Compare(_T("[Username] DESC")))
		sortData = "[Username] DESC";
	else
		sortData = "[Username] ASC";
}

void CListOperatorDlg::RoleSort()
{
	if (sortData.Compare(_T("[IsAdmin] DESC")))
		sortData = "[IsAdmin] DESC";
	else
		sortData = "[IsAdmin] ASC";
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
		if (CKontrolaPristupaApp::getAdmin())
		{
			if (CKontrolaPristupaApp::getActiveOperator().Compare(lstCtrl.GetItemText(pNMItemActivate->iItem, 1)))
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
