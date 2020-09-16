
// KontrolaPristupaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "KontrolaPristupaDlg.h"
#include "afxdialogex.h"
#include "Operator.h"
#include "BlockedAccount.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKontrolaPristupaDlg dialog



CKontrolaPristupaDlg::CKontrolaPristupaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_KONTROLAPRISTUPA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	theApp = (CKontrolaPristupaApp*)AfxGetApp();
	theApp->appName.LoadString(IDS_APPNAME);
}

void CKontrolaPristupaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKontrolaPristupaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BLOGIN, &CKontrolaPristupaDlg::OnBnClickedBLogin)
END_MESSAGE_MAP()


// CKontrolaPristupaDlg message handlers

BOOL CKontrolaPristupaDlg::OnInitDialog()
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	SetWindowText(theApp->getAppName());

	CString strText;
	strText.LoadString(IDS_USERNAME);
	strText += ":";
	GetDlgItem(IDC_TUSERNAME)->SetWindowText(strText);

	
	strText.LoadString(IDS_PASSWORD);
	strText += ":";
	GetDlgItem(IDC_TPASSWORD)->SetWindowText(strText);

	
	strText.LoadString(IDS_LOGIN);
	GetDlgItem(IDC_BLOGIN)->SetWindowText(strText);

	if (theApp->getActiveOperator().Compare(_T("")))
	{
		GetDlgItem(IDC_EUSERNAME)->SetWindowText(theApp->getActiveOperator());
	}

	try
	{
		CDatabase * db = new CDatabase();
		db->Open(theApp->getDsn());
		db->Close();
	}
	catch(CDBException* ex)
	{
		strText.LoadString(IDS_DBCONNERR);
		MessageBox(strText, theApp->getAppName(), MB_OK | MB_ICONERROR);
		EndDialog(0);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKontrolaPristupaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKontrolaPristupaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKontrolaPristupaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKontrolaPristupaDlg::OnBnClickedBLogin()
{
	CString strMessage;
	CString strUsername;
	GetDlgItem(IDC_EUSERNAME)->GetWindowTextW(strUsername);
		
	if (strUsername.IsEmpty())
	{
		strMessage.LoadString(IDS_NOOPERATOR);
	}
	else
	{
		COperator oper;
		oper.m_strFilter.Format(_T("Username = '%s'"), strUsername);
		oper.Open();

		if (!oper.IsEOF())
		{
			CBlockedAccount blockAcc;
			blockAcc.m_strFilter.Format(_T("OperatorID = '%d'"), oper.m_ID);
			blockAcc.Open();

			if (blockAcc.IsEOF() || blockAcc.m_PassAttempts < 3)
			{
				CString password;
				GetDlgItem(IDC_EPASSWORD)->GetWindowTextW(password);
				if (!password.Compare(oper.m_Password))
				{
					theApp->activeOperator = oper.m_Username;
					theApp->admin = oper.m_IsAdmin;

					if (!blockAcc.IsEOF())
						blockAcc.Delete();
					
					oper.Close();
					EndDialog(0);

					CMainDlg menuDlg;
					menuDlg.DoModal();
					
					return;
				}
				else
				{
					strMessage.LoadString(IDS_WRONGPASSWORD);
					GetDlgItem(IDC_EPASSWORD)->SetWindowText(_T(""));
					if (!blockAcc.IsEOF())
					{
						blockAcc.Edit();
						blockAcc.m_PassAttempts ++;
						blockAcc.Update();
					}
					else
					{
						blockAcc.AddNew();
						blockAcc.m_OperatorID = oper.m_ID;
						blockAcc.m_PassAttempts = 1;
						blockAcc.Update();
					}
				}				
			}
			else
			{
				strMessage.LoadString(IDS_BLOCKEDACC);
				GetDlgItem(IDC_EUSERNAME)->SetWindowText(_T(""));
				GetDlgItem(IDC_EPASSWORD)->SetWindowText(_T(""));
			}
		}
		else
		{
			strMessage.LoadString(IDS_NOOPERATOR);
			GetDlgItem(IDC_EUSERNAME)->SetWindowText(_T(""));
			GetDlgItem(IDC_EPASSWORD)->SetWindowText(_T(""));
		}

		MessageBox(strMessage, theApp->getAppName(), MB_OK);
		oper.Close();
	}
}
