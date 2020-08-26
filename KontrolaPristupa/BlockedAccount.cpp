// BlockedAccount.h : Implementation of the CBlockedAccount class



// CBlockedAccount implementation

// code generated on 26. kolovoza 2020., 19:31

#include "stdafx.h"
#include "BlockedAccount.h"
IMPLEMENT_DYNAMIC(CBlockedAccount, CRecordset)

CBlockedAccount::CBlockedAccount(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_OperatorID = 0;
	m_PassAttempts = 0;
	m_nFields = 2;
	m_nDefaultType = dynaset;
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CBlockedAccount::GetDefaultConnect()
{
	return _T("DSN=KontrolaPristupa;Description=Seminarski rad NWP 2020;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2015;WSID=NDPC10;DATABASE=KontrolaPristupa");
}

CString CBlockedAccount::GetDefaultSQL()
{
	return _T("[dbo].[BlockedAccount]");
}

void CBlockedAccount::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[OperatorID]"), m_OperatorID);
	RFX_Long(pFX, _T("[PassAttempts]"), m_PassAttempts);

}
/////////////////////////////////////////////////////////////////////////////
// CBlockedAccount diagnostics

#ifdef _DEBUG
void CBlockedAccount::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBlockedAccount::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


