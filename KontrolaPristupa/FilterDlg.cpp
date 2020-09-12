// FilterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "FilterDlg.h"
#include "afxdialogex.h"
#include "MainDlg.h"
#include "Door.h"
#include "DoorUser.h"
#include "UserGroup.h"


// CFilterDlg dialog

IMPLEMENT_DYNAMIC(CFilterDlg, CDialogEx)

CFilterDlg::CFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FILTER, pParent)
	, m_door(_T(""))
	, m_status(_T(""))
	, m_name(_T(""))
	, m_group(_T(""))
	, dateCheckBox(FALSE)
	, timeCheckBox(FALSE)
	, dateStart(CTime::GetCurrentTime())
	, dateEnd(CTime::GetCurrentTime())
	, timeStart(CTime::GetCurrentTime())
	, timeEnd(CTime::GetCurrentTime())
{

}

CFilterDlg::~CFilterDlg()
{
}

void CFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CDOORF, doorComboBox);
	DDX_Control(pDX, IDC_CSTATUSF, statusComboBox);
	DDX_Control(pDX, IDC_CNAMEF, nameComboBox);
	DDX_Control(pDX, IDC_CGROUPF, groupComboBox);
	DDX_CBString(pDX, IDC_CDOORF, m_door);
	DDX_CBString(pDX, IDC_CSTATUSF, m_status);
	DDX_CBString(pDX, IDC_CNAMEF, m_name);
	DDX_CBString(pDX, IDC_CGROUPF, m_group);
	DDX_Check(pDX, IDC_CHECKDATE, dateCheckBox);
	DDX_Check(pDX, IDC_CHECKTIME, timeCheckBox);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, dateStart);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, dateEnd);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, timeStart);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER4, timeEnd);
}


BEGIN_MESSAGE_MAP(CFilterDlg, CDialogEx)
	ON_BN_CLICKED(IDC_APPLY, &CFilterDlg::OnBnClickedApply)
	ON_CBN_SELCHANGE(IDC_CNAMEF, &CFilterDlg::OnCbnSelchangeCnamef)
	ON_CBN_SELCHANGE(IDC_CGROUPF, &CFilterDlg::OnCbnSelchangeCgroupf)
END_MESSAGE_MAP()

BOOL CFilterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(CKontrolaPristupaApp::strAppName);

	CString strText;

	strText.LoadString(IDS_DOOR);
	strText += ":";
	GetDlgItem(IDC_TDOOR)->SetWindowText(strText);
	
	strText.LoadString(IDS_STATUS);
	strText += ":";
	GetDlgItem(IDC_TSTATUS)->SetWindowText(strText);

	strText.LoadString(IDS_USER);
	strText += ":";
	GetDlgItem(IDC_TNAME)->SetWindowText(strText);

	strText.LoadString(IDS_GROUP);
	strText += ":";
	GetDlgItem(IDC_TGROUP)->SetWindowText(strText);

	strText.LoadString(IDS_DATE);
	strText += ":";
	GetDlgItem(IDC_TDATE)->SetWindowText(strText);

	strText.LoadString(IDS_TIME);
	strText += ":";
	GetDlgItem(IDC_TTIME)->SetWindowText(strText);

	strText.LoadString(IDS_FILTERDATE);
	GetDlgItem(IDC_CHECKDATE)->SetWindowText(strText);

	strText.LoadString(IDS_FILTERTIME);
	GetDlgItem(IDC_CHECKTIME)->SetWindowText(strText);

	strText.LoadString(IDS_APPLY);
	GetDlgItem(IDC_APPLY)->SetWindowText(strText);
	
	CDoor doors;
	doors.Open();
	while (!doors.IsEOF())
	{
		strText.Format(_T("%s"), doors.m_Name);
		doorComboBox.AddString(strText);
		doors.MoveNext();
	}
	doors.Close();

	strText.LoadString(IDS_OPENED);
	statusComboBox.AddString(strText);
	strText.LoadString(IDS_NOTOPENED);
	statusComboBox.AddString(strText);

	CDoorUser users;
	users.Open();
	while (!users.IsEOF())
	{
		strText.Format(_T("%s %s"), users.m_Name, users.m_Surname);
		nameComboBox.AddString(strText);
		users.MoveNext();
	}
	users.Close();
	
	CUserGroup groups;
	groups.Open();
	while (!groups.IsEOF())
	{
		strText.Format(_T("%s"), groups.m_Name);
		groupComboBox.AddString(strText);
		groups.MoveNext();
	}
	groups.Close();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// CFilterDlg message handlers


void CFilterDlg::OnBnClickedApply()
{
	UpdateData();
	CString strText;

	if (CMainDlg::eventFilter.Compare(_T("1 = 1")))
		CMainDlg::eventFilter = _T("1 = 1");

	if (!m_door.IsEmpty())
	{
		strText.Format(_T(" AND [Door Name] = '%s'"), m_door);
		CMainDlg::eventFilter += strText;
	}

	if (!m_status.IsEmpty())
	{
		BYTE status = 0;
		strText.LoadString(IDS_OPENED);
		if (!m_status.Compare(strText))
			status = 1;
		strText.Format(_T(" AND [Door Opened] = %d"), status);
		CMainDlg::eventFilter += strText;
	}

	if (!m_name.IsEmpty())
	{
		CString filter;

		filter = m_name.Mid(0, m_name.Find(' '));
		strText.Format(_T(" AND [User Name] = '%s'"), filter);
		CMainDlg::eventFilter += strText;

		filter = m_name.Right(m_name.Find(' ') + 1);
		strText.Format(_T(" AND [Surname] = '%s'"), filter);
		CMainDlg::eventFilter += strText;
	}

	if (!m_group.IsEmpty())
	{
		strText.Format(_T(" AND [Group Name] = '%s'"), m_group);
		CMainDlg::eventFilter += strText;
	}
	
	if (dateCheckBox && timeCheckBox)
	{
		strText.Format(_T(" AND [DateTime] >= '%s %s'"), dateStart.Format(_T("%Y-%m-%d")), timeStart.Format(_T("%H:%M:%S")));
		CMainDlg::eventFilter += strText;

		strText.Format(_T(" AND [DateTime] <= '%s %s'"), dateEnd.Format(_T("%Y-%m-%d")), timeEnd.Format(_T("%H:%M:%S")));
		CMainDlg::eventFilter += strText;
	}
	else
	{
		if (dateCheckBox)
		{
			strText.Format(_T(" AND [DateTime] >= '%s'"), dateStart.Format(_T("%Y-%m-%d")));
			CMainDlg::eventFilter += strText;

			strText.Format(_T(" AND [DateTime] <= '%s'"), dateEnd.Format(_T("%Y-%m-%d")));
			CMainDlg::eventFilter += strText;
		}

		if (timeCheckBox)
		{
			strText.Format(_T(" AND CONVERT(VARCHAR(8), [DateTime], 108) >= '%s'"), timeStart.Format(_T("%H:%M:%S")));
			CMainDlg::eventFilter += strText;

			strText.Format(_T(" AND CONVERT(VARCHAR(8), [DateTime], 108) <= '%s'"), timeEnd.Format(_T("%H:%M:%S")));
			CMainDlg::eventFilter += strText;
		}
	}	
	
	EndDialog(0);
}


void CFilterDlg::OnCbnSelchangeCnamef()
{
	UpdateData();
	if (m_group.Compare(_T("")))
	{
		CString strMessage;
		strMessage.LoadString(IDS_USERGROUPERR);
		MessageBox(strMessage, CKontrolaPristupaApp::strAppName, MB_OK);
		groupComboBox.SetCurSel(-1);
	}
}


void CFilterDlg::OnCbnSelchangeCgroupf()
{
	UpdateData();
	if (m_name.Compare(_T("")))
	{
		CString strMessage;
		strMessage.LoadString(IDS_USERGROUPERR);
		MessageBox(strMessage, CKontrolaPristupaApp::strAppName, MB_OK);
		nameComboBox.SetCurSel(-1);
	}
}
