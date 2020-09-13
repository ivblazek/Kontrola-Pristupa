// DoorRule.h : Implementation of the CDoorRule class



// CDoorRule implementation

// code generated on 24. kolovoza 2020., 22:52

#include "stdafx.h"
#include "DoorRule.h"
#include "KontrolaPristupa.h"
IMPLEMENT_DYNAMIC(CDoorRule, CRecordset)

CDoorRule::CDoorRule(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_DoorID = 0;
	m_UserID = 0;
	m_nFields = 2;
	m_nDefaultType = dynaset;
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CDoorRule::GetDefaultConnect()
{
	return _T("ODBC;DSN=") + CKontrolaPristupaApp::getDsn();
}

CString CDoorRule::GetDefaultSQL()
{
	return _T("[dbo].[DoorRule]");
}

void CDoorRule::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[DoorID]"), m_DoorID);
	RFX_Long(pFX, _T("[UserID]"), m_UserID);

}
/////////////////////////////////////////////////////////////////////////////
// CDoorRule diagnostics

#ifdef _DEBUG
void CDoorRule::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDoorRule::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


