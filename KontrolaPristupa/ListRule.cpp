// ListRule.h : Implementation of the CListRule class



// CListRule implementation

// code generated on 11. rujna 2020., 20:18

#include "stdafx.h"
#include "ListRule.h"
#include "KontrolaPristupa.h"
IMPLEMENT_DYNAMIC(CListRule, CRecordset)

CListRule::CListRule(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_DoorID = 0;
	m_UserID = 0;
	m_DoorName = L"";
	m_Name = L"";
	m_Surname = L"";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CListRule::GetDefaultConnect()
{
	return _T("ODBC;DSN=") + CKontrolaPristupaApp::getDsn();
}

CString CListRule::GetDefaultSQL()
{
	return _T("[dbo].[ListRule]");
}

void CListRule::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[DoorID]"), m_DoorID);
	RFX_Long(pFX, _T("[UserID]"), m_UserID);
	RFX_Text(pFX, _T("[DoorName]"), m_DoorName);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Surname]"), m_Surname);

}
/////////////////////////////////////////////////////////////////////////////
// CListRule diagnostics

#ifdef _DEBUG
void CListRule::AssertValid() const
{
	CRecordset::AssertValid();
}

void CListRule::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


