// ListUser.h : Implementation of the CListUser class



// CListUser implementation

// code generated on 11. rujna 2020., 20:09

#include "stdafx.h"
#include "ListUser.h"
IMPLEMENT_DYNAMIC(CListUser, CRecordset)

CListUser::CListUser(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Name = L"";
	m_Surname = L"";
	m_GroupName = L"";
	m_CardNo = "";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CListUser::GetDefaultConnect()
{
	return _T("DSN=KontrolaPristupa;Description=Seminarski rad NWP 2020;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2015;WSID=NDPC10;DATABASE=KontrolaPristupa");
}

CString CListUser::GetDefaultSQL()
{
	return _T("[dbo].[ListUser]");
}

void CListUser::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Surname]"), m_Surname);
	RFX_Text(pFX, _T("[GroupName]"), m_GroupName);
	RFX_Text(pFX, _T("[CardNo]"), m_CardNo);

}
/////////////////////////////////////////////////////////////////////////////
// CListUser diagnostics

#ifdef _DEBUG
void CListUser::AssertValid() const
{
	CRecordset::AssertValid();
}

void CListUser::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


