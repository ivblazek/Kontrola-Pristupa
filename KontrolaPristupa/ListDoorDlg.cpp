// ListDoorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "ListDoorDlg.h"
#include "afxdialogex.h"
#include "Door.h"


// CListDoorDlg dialog

IMPLEMENT_DYNAMIC(CListDoorDlg, CDialogEx)

CListDoorDlg::CListDoorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LISTDOOR, pParent)
{

}

CListDoorDlg::~CListDoorDlg()
{
}

void CListDoorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENTS, lstCtrl);
}


BEGIN_MESSAGE_MAP(CListDoorDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CListDoorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	SetWindowText(CKontrolaPristupaApp::strAppName);


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

	CDoor doors;
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// CListDoorDlg message handlers
