
// KontrolaPristupaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KontrolaPristupa.h"
#include "KontrolaPristupaDlg.h"
#include "afxdialogex.h"
#include "Operator.h"
#include "BlockedAccount.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

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
	strAppName.LoadString(IDS_APPNAME);
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
	
	SetWindowText(strAppName);

	CString strTextUsername;
	strTextUsername.LoadString(IDS_USERNAME);
	strTextUsername += ":";
	GetDlgItem(IDC_TUSERNAME)->SetWindowText(strTextUsername);

	CString strTextPassword;
	strTextPassword.LoadString(IDS_PASSWORD);
	strTextPassword += ":";
	GetDlgItem(IDC_TPASSWORD)->SetWindowText(strTextPassword);

	CString strButtonLogin;
	strButtonLogin.LoadString(IDS_LOGIN);
	GetDlgItem(IDC_BLOGIN)->SetWindowText(strButtonLogin);

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
					if (!blockAcc.IsEOF())
						blockAcc.Delete();

					//TODO: go to next window
					EndDialog(0);
					return;
				}
				else
				{
					strMessage.LoadString(IDS_WRONGPASSWORD);

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
			}
		}
		else
		{
			strMessage.LoadString(IDS_NOOPERATOR);
		}

		MessageBox(strMessage, strAppName, MB_OK);
	}
}

