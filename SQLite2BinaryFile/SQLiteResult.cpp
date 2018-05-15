#include "SQLiteResult.h"

CSQLiteResult::CSQLiteResult(CSQLiteStatement&& sSQLStmt) : m_sSQLStmt(std::move(sSQLStmt))
{}

CSQLiteResult::CSQLiteResult(CSQLiteResult&& other) : m_sSQLStmt(std::move(other.m_sSQLStmt))
{
}

CSQLiteResult::~CSQLiteResult()
{}

void CSQLiteResult::get_Fields()
{
	return;
}

void CSQLiteResult::get_Rows(std::function<void(std::vector<CSQLiteItem>)> notify)
{
	int rc = SQLITE_OK;
	while ((rc = sqlite3_step(m_sSQLStmt)) == SQLITE_ROW)
	{
	}

	if (rc != SQLITE_DONE)
	{
		//throw std::runtime_error(sqlite3_errmsg(m_pDatabase));
	}
	return;
}
