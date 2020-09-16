// UserGroup.h : Implementation of the CUserGroup class



// CUserGroup implementation

// code generated on 24. kolovoza 2020., 22:49

#include "stdafx.h"
#include "UserGroup.h"
#include "KontrolaPristupa.h"
IMPLEMENT_DYNAMIC(CUserGroup, CRecordset)

CUserGroup::CUserGroup(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Name = L"";
	m_Description = L"";
	m_nFields = 3;
	m_nDefaultType = dynaset;
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CUserGroup::GetDefaultConnect()
{
	return _T("ODBC;DSN=") + ((CKontrolaPristupaApp*)AfxGetApp())->getDsn();
}

CString CUserGroup::GetDefaultSQL()
{
	return _T("[dbo].[UserGroup]");
}

void CUserGroup::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Description]"), m_Description);

}
/////////////////////////////////////////////////////////////////////////////
// CUserGroup diagnostics

#ifdef _DEBUG
void CUserGroup::AssertValid() const
{
	CRecordset::AssertValid();
}

void CUserGroup::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


