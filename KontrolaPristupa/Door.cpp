// Door.h : Implementation of the CDoor class



// CDoor implementation

// code generated on 24. kolovoza 2020., 22:50

#include "stdafx.h"
#include "Door.h"
#include "KontrolaPristupa.h"
IMPLEMENT_DYNAMIC(CDoor, CRecordset)

CDoor::CDoor(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Name = L"";
	m_Description = L"";
	m_IPaddress = "";
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CDoor::GetDefaultConnect()
{
	return _T("ODBC;DSN=") + ((CKontrolaPristupaApp*)AfxGetApp())->getDsn();
}

CString CDoor::GetDefaultSQL()
{
	return _T("[dbo].[Door]");
}

void CDoor::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Text(pFX, _T("[IP address]"), m_IPaddress);

}
/////////////////////////////////////////////////////////////////////////////
// CDoor diagnostics

#ifdef _DEBUG
void CDoor::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDoor::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


