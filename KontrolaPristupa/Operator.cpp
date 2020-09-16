// Operator.h : Implementation of the COperator class



// COperator implementation

// code generated on 24. kolovoza 2020., 22:47

#include "stdafx.h"
#include "Operator.h"
#include "KontrolaPristupa.h"
IMPLEMENT_DYNAMIC(COperator, CRecordset)

COperator::COperator(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Username = L"";
	m_Password = L"";
	m_IsAdmin = 0;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString COperator::GetDefaultConnect()
{
	return _T("ODBC;DSN=") + ((CKontrolaPristupaApp*)AfxGetApp())->getDsn();
}

CString COperator::GetDefaultSQL()
{
	return _T("[dbo].[Operator]");
}

void COperator::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Username]"), m_Username);
	RFX_Text(pFX, _T("[Password]"), m_Password);
	RFX_Byte(pFX, _T("[IsAdmin]"), m_IsAdmin);

}
/////////////////////////////////////////////////////////////////////////////
// COperator diagnostics

#ifdef _DEBUG
void COperator::AssertValid() const
{
	CRecordset::AssertValid();
}

void COperator::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


