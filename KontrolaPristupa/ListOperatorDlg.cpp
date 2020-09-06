// ListOperatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "ListOperatorDlg.h"
#include "afxdialogex.h"
#include "Operator.h"

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
	DDX_Control(pDX, IDC_EVENTS, lstCtrl);
}


BEGIN_MESSAGE_MAP(CListOperatorDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CListOperatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	SetWindowText(CKontrolaPristupaApp::strAppName);


	CString strLabel;
	lstCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	strLabel.LoadString(IDS_ID);
	lstCtrl.InsertColumn(0, strLabel, LVCFMT_LEFT, 50);
	strLabel.LoadString(IDS_USERNAME);
	lstCtrl.InsertColumn(1, strLabel, LVCFMT_LEFT, 100);
	strLabel.LoadString(IDS_ROLE);
	lstCtrl.InsertColumn(2, strLabel, LVCFMT_LEFT, 100);


	COperator opers;
	opers.Open();

	int itemNo;
	CString strItem;

	while (!opers.IsEOF())
	{
		strItem.Format(_T("%d"), opers.m_ID);

		itemNo = lstCtrl.InsertItem(0, strItem);
		lstCtrl.SetItemText(itemNo, 1, opers.m_Username);
		if (opers.m_IsAdmin == 1)
			strItem = "Admin";
		else
			strItem = "User";
		lstCtrl.SetItemText(itemNo, 2, strItem);

		opers.MoveNext();
	}

	opers.Close();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// CListOperatorDlg message handlers
