#include "SQLiteDecorator.h"
#include "SQLiteStatement.h"

CSQLiteDBDecorator::CSQLiteDBDecorator(const string& strDbPath) : m_spSqlite3(nullptr)
{
	sqlite3* pSqlite3 = nullptr;
	if (sqlite3_open_v2(strDbPath.c_str(), &pSqlite3, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK)
	{
		throw std::runtime_error(sqlite3_errmsg(pSqlite3));
	}

	m_spSqlite3.reset(pSqlite3, sqlite3_close);
}

CSQLiteDBDecorator::~CSQLiteDBDecorator()
{	
}

CSQLiteResult CSQLiteDBDecorator::Execute(const CSQLiteQuery& sSQL)
{
	CSQLiteStatement sStatement;
	int rc = sqlite3_prepare_v2(m_spSqlite3.get(), sSQL.ToString().c_str(), -1, &sStatement, nullptr);
	if (rc != SQLITE_OK)
	{
		throw std::runtime_error(sqlite3_errmsg(m_spSqlite3.get()));
	}

	return std::move(CSQLiteResult(std::move(sStatement), m_spSqlite3));
}