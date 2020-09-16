// Events.h : Implementation of the CEvents class



// CEvents implementation

// code generated on 26. kolovoza 2020., 23:27

#include "stdafx.h"
#include "Events.h"
#include "KontrolaPristupa.h"
IMPLEMENT_DYNAMIC(CEvents, CRecordset)

CEvents::CEvents(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_DoorName = L"";
	m_DoorOpened = 0;
	m_UserName = L"";
	m_Surname = L"";
	m_GroupName = L"";
	m_DateTime;
	m_nFields = 6;
	m_nDefaultType = dynaset;
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CEvents::GetDefaultConnect()
{
	return _T("ODBC;DSN=") + ((CKontrolaPristupaApp*)AfxGetApp())->getDsn();
}

CString CEvents::GetDefaultSQL()
{
	return _T("[dbo].[EventView]");
}

void CEvents::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Text(pFX, _T("[Door Name]"), m_DoorName);
	RFX_Byte(pFX, _T("[Door Opened]"), m_DoorOpened);
	RFX_Text(pFX, _T("[User Name]"), m_UserName);
	RFX_Text(pFX, _T("[Surname]"), m_Surname);
	RFX_Text(pFX, _T("[Group Name]"), m_GroupName);
	RFX_Date(pFX, _T("[DateTime]"), m_DateTime);

}
/////////////////////////////////////////////////////////////////////////////
// CEvents diagnostics

#ifdef _DEBUG
void CEvents::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEvents::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


