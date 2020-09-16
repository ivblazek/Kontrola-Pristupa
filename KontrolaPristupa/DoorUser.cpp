// DoorUser.h : Implementation of the CDoorUser class



// CDoorUser implementation

// code generated on 24. kolovoza 2020., 22:48

#include "stdafx.h"
#include "DoorUser.h"
#include "KontrolaPristupa.h"
IMPLEMENT_DYNAMIC(CDoorUser, CRecordset)

CDoorUser::CDoorUser(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Name = L"";
	m_Surname = L"";
	m_GroupID = 0;
	m_CardNo = "";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CDoorUser::GetDefaultConnect()
{
	return _T("ODBC;DSN=") + ((CKontrolaPristupaApp*)AfxGetApp())->getDsn();
}

CString CDoorUser::GetDefaultSQL()
{
	return _T("[dbo].[DoorUser]");
}

void CDoorUser::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Surname]"), m_Surname);
	RFX_Long(pFX, _T("[GroupID]"), m_GroupID);
	RFX_Text(pFX, _T("[CardNo]"), m_CardNo);

}
/////////////////////////////////////////////////////////////////////////////
// CDoorUser diagnostics

#ifdef _DEBUG
void CDoorUser::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDoorUser::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


