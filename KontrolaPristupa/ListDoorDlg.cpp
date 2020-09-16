// ListDoorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "ListDoorDlg.h"
#include "afxdialogex.h"
#include "Door.h"
#include "ManageDoorsDlg.h"


// CListDoorDlg dialog

IMPLEMENT_DYNAMIC(CListDoorDlg, CDialogEx)

CListDoorDlg::CListDoorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LISTDOOR, pParent)
{
	theApp = (CKontrolaPristupaApp*)AfxGetApp();
}

CListDoorDlg::~CListDoorDlg()
{
}

void CListDoorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DOORS, lstCtrl);
}


BEGIN_MESSAGE_MAP(CListDoorDlg, CDialogEx)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_DOORS, &CListDoorDlg::OnLvnColumnClickDoors)
	ON_NOTIFY(NM_DBLCLK, IDC_DOORS, &CListDoorDlg::OnNMDblclkDoors)
END_MESSAGE_MAP()

BOOL CListDoorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strText;
	strText.LoadString(IDS_DOORS);

	SetWindowText(theApp->getAppName() + " - " + strText);


	CString strLabel;
	lstCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	strLabel.LoadString(IDS_ID);
	lstCtrl.InsertColumn(0, strLabel, LVCFMT_LEFT, 50);
	strLabel.LoadString(IDS_NAME);
	lstCtrl.InsertColumn(1, strLabel, LVCFMT_LEFT, 150);
	strLabel.LoadString(IDS_DESCRIPTION);
	lstCtrl.InsertColumn(2, strLabel, LVCFMT_LEFT, 150);
	strLabel.LoadString(IDS_IPADDRESS);
	lstCtrl.InsertColumn(3, strLabel, LVCFMT_LEFT, 100);

	sortData = "[ID] DESC";
	PopulateListCtrl();

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CListDoorDlg::PopulateListCtrl()
{
	CDoor doors;
	doors.m_strSort.Format(_T("%s"), sortData);
	doors.Open();

	int itemNo;
	CString strItem;

	while (!doors.IsEOF())
	{
		strItem.Format(_T("%d"), doors.m_ID);

		itemNo = lstCtrl.InsertItem(0, strItem);
		lstCtrl.SetItemText(itemNo, 1, doors.m_Name);
		lstCtrl.SetItemText(itemNo, 2, doors.m_Description);

		strItem = doors.m_IPaddress;
		lstCtrl.SetItemText(itemNo, 3, strItem);

		doors.MoveNext();
	}

	doors.Close();
}

void CListDoorDlg::IdSort()
{
	if (sortData.Compare(_T("[ID] DESC")))
		sortData = "[ID] DESC";
	else
		sortData = "[ID] ASC";
}

void CListDoorDlg::UsernameSort()
{
	if (sortData.Compare(_T("[Name] DESC")))
		sortData = "[Name] DESC";
	else
		sortData = "[Name] ASC";
}

void CListDoorDlg::RoleSort()
{
	if (sortData.Compare(_T("[Description] DESC")))
		sortData = "[Description] DESC";
	else
		sortData = "[Description] ASC";
}

void CListDoorDlg::IpSort()
{
	if (sortData.Compare(_T("[IP address] DESC")))
		sortData = "[IP address] DESC";
	else
		sortData = "[IP address] ASC";
}

// CListDoorDlg message handlers


void CListDoorDlg::OnLvnColumnClickDoors(NMHDR *pNMHDR, LRESULT *pResult)
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
	case 3:
		IpSort();
		break;
	default:
		break;
	}

	lstCtrl.DeleteAllItems();
	PopulateListCtrl();

	*pResult = 0;
}


void CListDoorDlg::OnNMDblclkDoors(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (pNMItemActivate->iItem != -1)
	{
		if (theApp->getAdmin())
		{
			if (theApp->getActiveOperator().Compare(lstCtrl.GetItemText(pNMItemActivate->iItem, 1)))
			{
				CString selectedID = lstCtrl.GetItemText(pNMItemActivate->iItem, 0);
				CManageDoorsDlg manageDoorsDlg;
				manageDoorsDlg.selectedID = _wtol(selectedID);
				manageDoorsDlg.DoModal();
				lstCtrl.DeleteAllItems();
				PopulateListCtrl();
			}
		}
	}

	*pResult = 0;
}
