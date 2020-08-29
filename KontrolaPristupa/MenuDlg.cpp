// MenuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "MenuDlg.h"
#include "afxdialogex.h"
#include "KontrolaPristupaDlg.h"
#include "Events.h"

// CMenuDlg dialog

IMPLEMENT_DYNAMIC(CMenuDlg, CDialogEx)

CMenuDlg::CMenuDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAIN_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	strAppName.LoadString(IDS_APPNAME);
}

CMenuDlg::~CMenuDlg()
{
}

void CMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENTS, lstCtrl);
}


BEGIN_MESSAGE_MAP(CMenuDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BREFRESH, &CMenuDlg::OnBnClickedBrefresh)
	ON_COMMAND(ID_LOGOUT, &CMenuDlg::OnLogout)
END_MESSAGE_MAP()


BOOL CMenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetWindowText(strAppName);
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);

	CString strText;
	strText.LoadString(IDS_REFRESH);
	GetDlgItem(IDC_BREFRESH)->SetWindowText(strText);
	
	CString strLabel;
	
	lstCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);
		
	strLabel.LoadString(IDS_LDOORNAME);
	lstCtrl.InsertColumn(0, strLabel, LVCFMT_LEFT, 180);
	strLabel.LoadString(IDS_LDOOROPENED);
	lstCtrl.InsertColumn(1, strLabel, LVCFMT_LEFT, 100);
	strLabel.LoadString(IDS_LNAME);
	lstCtrl.InsertColumn(2, strLabel, LVCFMT_LEFT, 100);
	strLabel.LoadString(IDS_LSURNAME);
	lstCtrl.InsertColumn(3, strLabel, LVCFMT_LEFT, 100);
	strLabel.LoadString(IDS_LGROUPNAME);
	lstCtrl.InsertColumn(4, strLabel, LVCFMT_LEFT, 100);
	strLabel.LoadString(IDS_LDATETIME);
	lstCtrl.InsertColumn(5, strLabel, LVCFMT_LEFT, 160);
	
	PopulateListCtrl();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMenuDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CMenuDlg::PopulateListCtrl()
{
	CEvents events;
	events.Open();

	int itemNo;
	CString strItem;

	while (!events.IsEOF())
	{
		itemNo = lstCtrl.InsertItem(0, events.m_DoorName);
		if (events.m_DoorOpened == 1)
			strItem = "Opened";
		else
			strItem = "Not Opened";
		lstCtrl.SetItemText(itemNo, 1, strItem);
		lstCtrl.SetItemText(itemNo, 2, events.m_UserName);
		lstCtrl.SetItemText(itemNo, 3, events.m_Surname);
		lstCtrl.SetItemText(itemNo, 4, events.m_GroupName);
		lstCtrl.SetItemText(itemNo, 5, events.m_DateTime.Format(_T("%d.%m.%Y. - %T")));
		events.MoveNext();
	}
	events.Close();
}

void CMenuDlg::OnLogout()
{
	EndDialog(0);

	CKontrolaPristupaDlg loginDlg;
	loginDlg.DoModal();
}


// CMenuDlg message handlers

void CMenuDlg::OnBnClickedBrefresh()
{
	lstCtrl.DeleteAllItems();
	PopulateListCtrl();
}