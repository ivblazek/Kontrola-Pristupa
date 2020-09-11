// MenuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "MenuDlg.h"
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

// CMenuDlg dialog

IMPLEMENT_DYNAMIC(CMenuDlg, CDialogEx)

CMenuDlg::CMenuDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAIN_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMenuDlg::~CMenuDlg()
{
}

CString CMenuDlg::eventFilter = _T("1 = 1");

void CMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENTS, lstCtrl);
}


BEGIN_MESSAGE_MAP(CMenuDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BREFRESH, &CMenuDlg::OnBnClickedBrefresh)
	ON_COMMAND(ID_LOGOUT, &CMenuDlg::OnLogout)
	ON_COMMAND(ID_USER_ADDUSER, &CMenuDlg::OnAddUser)
	ON_COMMAND(ID_GROUP_ADDGROUP, &CMenuDlg::OnGroupAddgroup)
	ON_COMMAND(ID_RULE_ADDRULE, &CMenuDlg::OnRuleAddrule)
	ON_COMMAND(ID_OPERATOR_ADDOPERATOR, &CMenuDlg::OnOperatorAddOperator)
	ON_COMMAND(ID_OPERATOR_CHANGEPASSWORD, &CMenuDlg::OnOperatorChangepassword)
	ON_COMMAND(ID_DOOR_ADDDOOR, &CMenuDlg::OnDoorAddDoor)
	ON_COMMAND(ID_OPERATOR_MANAGE, &CMenuDlg::OnOperatorManage)
	ON_COMMAND(ID_USER_LISTUSERS, &CMenuDlg::OnUserListUsers)
	ON_COMMAND(ID_GROUP_LISTGROUPS, &CMenuDlg::OnGroupListGroups)
	ON_COMMAND(ID_RULE_LISTRULES, &CMenuDlg::OnRuleListRules)
	ON_COMMAND(ID_DOOR_LISTDOORS, &CMenuDlg::OnDoorListDoors)
	ON_COMMAND(ID_OPERATOR_LISTOPERATORS, &CMenuDlg::OnOperatorListOperators)
	ON_COMMAND(ID_FILTER, &CMenuDlg::OnFilter)
	ON_BN_CLICKED(IDC_BFILTEROFF, &CMenuDlg::OnBnClickedBFilterOff)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_EVENTS, &CMenuDlg::OnLvnColumnClickEvents)
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

	SetWindowText(CKontrolaPristupaApp::strAppName);
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

	if (eventFilter.Compare(_T("1 = 1")))
	{
		GetDlgItem(IDC_BFILTEROFF)->ShowWindow(SW_SHOW);
	}
}

void CMenuDlg::DoorSort()
{
	if (sortData.Compare(_T("[Door Name] DESC, [DateTime] ASC")))
		sortData = "[Door Name] DESC, [DateTime] ASC";
	else
		sortData = "[Door Name] ASC, [DateTime] ASC";
}

void CMenuDlg::StatusSort()
{
	if (sortData.Compare(_T("[Door Opened] ASC, [DateTime] ASC")))
		sortData = "[Door Opened] ASC, [DateTime] ASC";
	else
		sortData = "[Door Opened] DESC, [DateTime] ASC";
}

void CMenuDlg::UsernameSort()
{
	if (sortData.Compare(_T("[User Name] DESC, [Surname] DESC, [DateTime] ASC")))
		sortData = "[User Name] DESC, [Surname] DESC, [DateTime] ASC";
	else
		sortData = "[User Name] ASC, [Surname] ASC, [DateTime] ASC";
}

void CMenuDlg::SurnameSort()
{
	if (sortData.Compare(_T("[Surname] DESC, [User Name] DESC, [DateTime] ASC")))
		sortData = "[Surname] DESC, [User Name] DESC, [DateTime] ASC";
	else
		sortData = "[Surname] ASC, [User Name] ASC, [DateTime] ASC";
}

void CMenuDlg::GroupSort()
{
	if (sortData.Compare(_T("[Group Name] DESC, [DateTime] ASC")))
		sortData = "[Group Name] DESC, [DateTime] ASC";
	else
		sortData = "[Group Name] ASC, [DateTime] ASC";
}

void CMenuDlg::DatetimeSort()
{
	if (sortData.Compare(_T("[DateTime] ASC")))
		sortData = "[DateTime] ASC";
	else
		sortData = "[DateTime] DESC";
}

// CMenuDlg message handlers


void CMenuDlg::OnLogout()
{
	EndDialog(0);

	CKontrolaPristupaDlg loginDlg;
	loginDlg.DoModal();
}


void CMenuDlg::OnAddUser()
{
	CAddUserDlg addUserDlg;
	addUserDlg.DoModal();
}


void CMenuDlg::OnBnClickedBrefresh()
{
	lstCtrl.DeleteAllItems();
	sortData = "";
	PopulateListCtrl();
}


void CMenuDlg::OnGroupAddgroup()
{
	CAddGroupDlg addGroupDlg;
	addGroupDlg.DoModal();
}


void CMenuDlg::OnRuleAddrule()
{
	CAddRuleDlg addRuleDlg;
	addRuleDlg.DoModal();
}


void CMenuDlg::OnOperatorAddOperator()
{
	CAddOperatorDlg addOperatorDlg;
	addOperatorDlg.DoModal();
}


void CMenuDlg::OnOperatorChangepassword()
{
	CChangePassDlg changePassDlg;
	changePassDlg.DoModal();
}


void CMenuDlg::OnDoorAddDoor()
{
	CAddDoorDlg addDoorDlg;
	addDoorDlg.DoModal();
}


void CMenuDlg::OnOperatorManage()
{
	COperator oper;
	oper.m_strFilter.Format(_T("Username = '%s'"), CKontrolaPristupaApp::activeOperator);
	oper.Open();
	if (oper.m_IsAdmin == 0)
	{
		CString strText;
		strText.LoadString(IDS_ADMINONLY);
		MessageBox(strText, CKontrolaPristupaApp::strAppName, MB_OK);
		return;
	}
		
	CManageOperatorsDlg manageOperatorsDlg;
	manageOperatorsDlg.DoModal();
}


void CMenuDlg::OnUserListUsers()
{
	CListUserDlg listUserDlg;
	listUserDlg.DoModal();
}


void CMenuDlg::OnGroupListGroups()
{
	CListGroupDlg listGroupDlg;
	listGroupDlg.DoModal();
}


void CMenuDlg::OnRuleListRules()
{
	CListRuleDlg listRuleDlg;
	listRuleDlg.DoModal();
}


void CMenuDlg::OnDoorListDoors()
{
	CListDoorDlg listDoorDlg;
	listDoorDlg.DoModal();
}


void CMenuDlg::OnOperatorListOperators()
{
	CListOperatorDlg listOperatorDlg;
	listOperatorDlg.DoModal();
}


void CMenuDlg::OnFilter()
{
	CFilterDlg filterDlg;
	filterDlg.DoModal();

	lstCtrl.DeleteAllItems();
	PopulateListCtrl();
}


void CMenuDlg::OnBnClickedBFilterOff()
{
	eventFilter = "1 = 1";
	GetDlgItem(IDC_BFILTEROFF)->ShowWindow(SW_HIDE);
	lstCtrl.DeleteAllItems();
	PopulateListCtrl();
}


void CMenuDlg::OnLvnColumnClickEvents(NMHDR *pNMHDR, LRESULT *pResult)
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
