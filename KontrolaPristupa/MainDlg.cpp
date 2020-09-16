// MenuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "KontrolaPristupaDlg.h"
#include "Events.h"
#include "AddUserDlg.h"
#include "AddGroupDlg.h"
#include "AddRuleDlg.h"
#include "AddOperatorDlg.h"
#include "ChangePassDlg.h"
#include "AddDoorDlg.h"
#include "ManageOperatorsDlg.h"
#include "Operator.h"
#include "ListUserDlg.h"
#include "ListGroupDlg.h"
#include "ListRuleDlg.h"
#include "ListDoorDlg.h"
#include "ListOperatorDlg.h"
#include "FilterDlg.h"

// CMainDlg dialog

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAIN_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMainDlg::~CMainDlg()
{
}


void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENTS, lstCtrl);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BREFRESH, &CMainDlg::OnBnClickedBrefresh)
	ON_COMMAND(ID_LOGOUT, &CMainDlg::OnLogout)
	ON_COMMAND(ID_USER_ADDUSER, &CMainDlg::OnAddUser)
	ON_COMMAND(ID_GROUP_ADDGROUP, &CMainDlg::OnGroupAddgroup)
	ON_COMMAND(ID_RULE_ADDRULE, &CMainDlg::OnRuleAddrule)
	ON_COMMAND(ID_OPERATOR_ADDOPERATOR, &CMainDlg::OnOperatorAddOperator)
	ON_COMMAND(ID_OPERATOR_CHANGEPASSWORD, &CMainDlg::OnOperatorChangepassword)
	ON_COMMAND(ID_DOOR_ADDDOOR, &CMainDlg::OnDoorAddDoor)
	ON_COMMAND(ID_USER_LISTUSERS, &CMainDlg::OnUserListUsers)
	ON_COMMAND(ID_GROUP_LISTGROUPS, &CMainDlg::OnGroupListGroups)
	ON_COMMAND(ID_RULE_LISTRULES, &CMainDlg::OnRuleListRules)
	ON_COMMAND(ID_DOOR_LISTDOORS, &CMainDlg::OnDoorListDoors)
	ON_COMMAND(ID_OPERATOR_LISTOPERATORS, &CMainDlg::OnOperatorListOperators)
	ON_COMMAND(ID_FILTER, &CMainDlg::OnFilter)
	ON_BN_CLICKED(IDC_BFILTEROFF, &CMainDlg::OnBnClickedBFilterOff)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_EVENTS, &CMainDlg::OnLvnColumnClickEvents)
	ON_COMMAND(ID_REPORT_PRINT, &CMainDlg::OnReportPrint)
END_MESSAGE_MAP()


BOOL CMainDlg::OnInitDialog()
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

	SetWindowText(CKontrolaPristupaApp::getAppName());
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);

	CString strText;
	strText.LoadString(IDS_REFRESH);
	GetDlgItem(IDC_BREFRESH)->SetWindowText(strText);

	strText.LoadString(IDS_FILTEROFF);
	GetDlgItem(IDC_BFILTEROFF)->SetWindowText(strText);
	
	CString strLabel;
	
	lstCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);
		
	strLabel.LoadString(IDS_DOOR);
	lstCtrl.InsertColumn(0, strLabel, LVCFMT_LEFT, 180);
	strLabel.LoadString(IDS_STATUS);
	lstCtrl.InsertColumn(1, strLabel, LVCFMT_LEFT, 100);
	strLabel.LoadString(IDS_NAME);
	lstCtrl.InsertColumn(2, strLabel, LVCFMT_LEFT, 100);
	strLabel.LoadString(IDS_SURNAME);
	lstCtrl.InsertColumn(3, strLabel, LVCFMT_LEFT, 100);
	strLabel.LoadString(IDS_GROUPNAME);
	lstCtrl.InsertColumn(4, strLabel, LVCFMT_LEFT, 100);
	strLabel.LoadString(IDS_DATETIME);
	lstCtrl.InsertColumn(5, strLabel, LVCFMT_LEFT, 160);
	
	PopulateListCtrl();


	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMainDlg::PopulateListCtrl()
{
	CEvents events;
	events.m_strFilter.Format(_T("%s"), eventFilter);
	events.m_strSort.Format(_T("%s"), sortData);
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

	if (eventFilter.Compare(_T("")))
	{
		GetDlgItem(IDC_BFILTEROFF)->ShowWindow(SW_SHOW);
	}
}

void CMainDlg::DoorSort()
{
	if (sortData.Compare(_T("[Door Name] DESC, [DateTime] ASC")))
		sortData = "[Door Name] DESC, [DateTime] ASC";
	else
		sortData = "[Door Name] ASC, [DateTime] ASC";
}

void CMainDlg::StatusSort()
{
	if (sortData.Compare(_T("[Door Opened] ASC, [DateTime] ASC")))
		sortData = "[Door Opened] ASC, [DateTime] ASC";
	else
		sortData = "[Door Opened] DESC, [DateTime] ASC";
}

void CMainDlg::UsernameSort()
{
	if (sortData.Compare(_T("[User Name] DESC, [Surname] DESC, [DateTime] ASC")))
		sortData = "[User Name] DESC, [Surname] DESC, [DateTime] ASC";
	else
		sortData = "[User Name] ASC, [Surname] ASC, [DateTime] ASC";
}

void CMainDlg::SurnameSort()
{
	if (sortData.Compare(_T("[Surname] DESC, [User Name] DESC, [DateTime] ASC")))
		sortData = "[Surname] DESC, [User Name] DESC, [DateTime] ASC";
	else
		sortData = "[Surname] ASC, [User Name] ASC, [DateTime] ASC";
}

void CMainDlg::GroupSort()
{
	if (sortData.Compare(_T("[Group Name] DESC, [DateTime] ASC")))
		sortData = "[Group Name] DESC, [DateTime] ASC";
	else
		sortData = "[Group Name] ASC, [DateTime] ASC";
}

void CMainDlg::DatetimeSort()
{
	if (sortData.Compare(_T("[DateTime] ASC")))
		sortData = "[DateTime] ASC";
	else
		sortData = "[DateTime] DESC";
}

// CMainDlg message handlers


void CMainDlg::OnLogout()
{
	EndDialog(0);

	CKontrolaPristupaDlg loginDlg;
	loginDlg.DoModal();
}


void CMainDlg::OnAddUser()
{
	CAddUserDlg addUserDlg;
	addUserDlg.DoModal();
}


void CMainDlg::OnBnClickedBrefresh()
{
	lstCtrl.DeleteAllItems();
	sortData = "";
	PopulateListCtrl();
}


void CMainDlg::OnGroupAddgroup()
{
	CAddGroupDlg addGroupDlg;
	addGroupDlg.DoModal();
}


void CMainDlg::OnRuleAddrule()
{
	CAddRuleDlg addRuleDlg;
	addRuleDlg.DoModal();
}


void CMainDlg::OnOperatorAddOperator()
{
	CAddOperatorDlg addOperatorDlg;
	addOperatorDlg.DoModal();
}


void CMainDlg::OnOperatorChangepassword()
{
	CChangePassDlg changePassDlg;
	changePassDlg.DoModal();
}


void CMainDlg::OnDoorAddDoor()
{
	CAddDoorDlg addDoorDlg;
	addDoorDlg.DoModal();
}


void CMainDlg::OnUserListUsers()
{
	CListUserDlg listUserDlg;
	listUserDlg.DoModal();
}


void CMainDlg::OnGroupListGroups()
{
	CListGroupDlg listGroupDlg;
	listGroupDlg.DoModal();
}


void CMainDlg::OnRuleListRules()
{
	CListRuleDlg listRuleDlg;
	listRuleDlg.DoModal();
}


void CMainDlg::OnDoorListDoors()
{
	CListDoorDlg listDoorDlg;
	listDoorDlg.DoModal();
}


void CMainDlg::OnOperatorListOperators()
{
	CListOperatorDlg listOperatorDlg;
	listOperatorDlg.DoModal();
}


void CMainDlg::OnFilter()
{
	CFilterDlg filterDlg(eventFilter);
	filterDlg.DoModal();

	lstCtrl.DeleteAllItems();
	PopulateListCtrl();
}


void CMainDlg::OnBnClickedBFilterOff()
{
	eventFilter = "";
	GetDlgItem(IDC_BFILTEROFF)->ShowWindow(SW_HIDE);
	lstCtrl.DeleteAllItems();
	PopulateListCtrl();
}


void CMainDlg::OnLvnColumnClickEvents(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	switch (pNMLV->iSubItem) 
	{
		case 0:
			DoorSort();
			break;
		case 1:
			StatusSort();
			break;
		case 2:
			UsernameSort();
			break;
		case 3:
			SurnameSort();
			break;
		case 4:
			GroupSort();
			break;
		case 5:
			DatetimeSort();
			break;
		default:
			break;
	}

	lstCtrl.DeleteAllItems();
	PopulateListCtrl();

	*pResult = 0;
}


void CMainDlg::OnReportPrint()
{
	Print();
}

void CMainDlg::OnBeginPrinting(CDC *pDC, CPrintInfo* pInfo)
{
}

void CMainDlg::OnPrint(CDC *pDC, CPrintInfo* pInfo)
{
	BOOL bPrintingOK;
	int horizontalWidth = pDC->GetDeviceCaps(HORZRES);
	int verticalHeight = pDC->GetDeviceCaps(VERTRES);
	CSize s = pDC->GetTextExtent(_T("A"));
	int x = horizontalWidth / 99;
	int y = s.cy * 4;
	int count = 0;
	int pageNo = 1;
	CString strItem;
	CTime currentTime = CTime::GetCurrentTime();
	CString sortPrint = sortData;

	sortPrint.Replace(_T("ASC"), _T("TEMP"));
	sortPrint.Replace(_T("DESC"), _T("ASC"));
	sortPrint.Replace(_T("TEMP"), _T("DESC"));

	if(sortPrint.IsEmpty())
		sortPrint = "[DateTime] DESC";
	
	strItem.Format(_T("Report by: %s"), CKontrolaPristupaApp::getActiveOperator());
	pDC->TextOut(x * 4, s.cy * 2, strItem); 
	strItem.Format(_T("Timestamp: %s"), currentTime.Format("%d.%m.%Y. - %T"));
	pDC->TextOut(x * 60, s.cy * 2, strItem);

	pDC->TextOut(x * 4, y, _T("No."));
	pDC->TextOut(x * 9, y, _T("Door"));
	pDC->TextOut(x * 34, y, _T("Open"));
	pDC->TextOut(x * 40, y, _T("Name"));
	pDC->TextOut(x * 52, y, _T("Surname"));
	pDC->TextOut(x * 64, y, _T("Group"));
	pDC->TextOut(x * 77, y, _T("Date & Time"));

	strItem.Format(_T("%d"), pageNo++);
	pDC->TextOut(horizontalWidth -300, verticalHeight - 300, strItem);

	y += s.cy;
	pDC->MoveTo(200, y);
	pDC->LineTo(horizontalWidth -200, y);
		

	CEvents events;
	events.m_strFilter.Format(_T("%s"), eventFilter);
	events.m_strSort.Format(_T("%s"), sortPrint);
	events.Open();
	
	while (!events.IsEOF())
	{
		y += s.cy;
		strItem.Format(_T("%d"), ++count);

		pDC->TextOut(x * 4, y, strItem);
		pDC->TextOut(x * 9, y, events.m_DoorName);
			
		if (events.m_DoorOpened == 1)
			pDC->TextOut(x * 35, y, _T("X"));

		pDC->TextOut(x * 40, y, events.m_UserName);
		pDC->TextOut(x * 52, y, events.m_Surname);
		pDC->TextOut(x * 64, y, events.m_GroupName);
		pDC->TextOut(x * 77, y, events.m_DateTime.Format(_T("%d.%m.%Y. - %T")));

		events.MoveNext();

		if (y >= verticalHeight - 600)
		{
			bPrintingOK = (pDC->EndPage() > 0);
			if (bPrintingOK)
			{
				pDC->StartPage();
				y = s.cy * 4;

				strItem.Format(_T("Report by: %s"), CKontrolaPristupaApp::getActiveOperator());
				pDC->TextOut(x * 4, s.cy * 2, strItem);
				strItem.Format(_T("Timestamp: %s"), currentTime.Format("%d.%m.%Y. - %T"));
				pDC->TextOut(x * 60, s.cy * 2, strItem);

				pDC->TextOut(x * 4, y, _T("No."));
				pDC->TextOut(x * 9, y, _T("Door"));
				pDC->TextOut(x * 34, y, _T("Open"));
				pDC->TextOut(x * 40, y, _T("Name"));
				pDC->TextOut(x * 52, y, _T("Surname"));
				pDC->TextOut(x * 64, y, _T("Group"));
				pDC->TextOut(x * 77, y, _T("Date & Time"));

				strItem.Format(_T("%d"), pageNo++);
				pDC->TextOut(horizontalWidth - 300, verticalHeight - 300, strItem);

				y += s.cy;
				pDC->MoveTo(200, y);
				pDC->LineTo(horizontalWidth - 200, y);
			}
			else
				return;
		}
	}
	events.Close();
}

void CMainDlg::OnEndPrinting(CDC *pDC, CPrintInfo* pInfo)
{
}

void CMainDlg::Print()
{
	CDC dc;
	CPrintDialog printDlg(FALSE);

	if (printDlg.DoModal() == IDCANCEL)     // Get printer settings from user
		return;

	dc.Attach(printDlg.GetPrinterDC());     // Get and attach a printer DC
	dc.m_bPrinting = TRUE;

	CString strTitle;                       // Get the application title
	strTitle.LoadString(AFX_IDS_APP_TITLE);

	DOCINFO di;                             // Initialise print document details
	::ZeroMemory(&di, sizeof(DOCINFO));
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = strTitle;

	BOOL bPrintingOK = dc.StartDoc(&di);    // Begin a new print job

											// Get the printing extents and store in the m_rectDraw field of a 
											// CPrintInfo object
	CPrintInfo Info;
	Info.m_rectDraw.SetRect(0, 0,
		dc.GetDeviceCaps(HORZRES),
		dc.GetDeviceCaps(VERTRES));

	OnBeginPrinting(&dc, &Info);            // Call your "Init printing" function
	
	dc.StartPage();                     // begin new page
	OnPrint(&dc, &Info);                // Call your "Print page" function
	bPrintingOK = (dc.EndPage() > 0);   // end page
	
	OnEndPrinting(&dc, &Info);              // Call your "Clean up" function

	if (bPrintingOK)
		dc.EndDoc();                        // end a print job
	else
		dc.AbortDoc();                      // abort job.

	dc.DeleteDC();
}
