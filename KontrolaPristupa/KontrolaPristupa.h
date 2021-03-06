
// KontrolaPristupa.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CKontrolaPristupaApp:
// See KontrolaPristupa.cpp for the implementation of this class
//

class CKontrolaPristupaApp : public CWinApp
{
private:
	CString appName;
	CString activeOperator;
	BOOL admin;
	CString dsn;
	friend class CKontrolaPristupaDlg;
public:
	CKontrolaPristupaApp();
	CString getAppName();
	CString getActiveOperator();
	BOOL getAdmin();
	CString getDsn();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CKontrolaPristupaApp theApp;