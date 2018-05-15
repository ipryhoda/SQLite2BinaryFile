#include "SQLiteDecorator.h"
#include "SQLiteStatement.h"

CSQLiteDBDecorator::CSQLiteDBDecorator(const string& strDbPath) : m_pDatabase(nullptr)
{
	if (sqlite3_open_v2(strDbPath.c_str(), &m_pDatabase, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK)
	{
		throw std::runtime_error(sqlite3_errmsg(m_pDatabase));
	}
}


CSQLiteDBDecorator::~CSQLiteDBDecorator()
{
	sqlite3_close(m_pDatabase);
}

shared_ptr<CSQLiteDBDecorator> CSQLiteDBDecorator::GetInstance(const std::string& strDbPath)
{
	static std::shared_ptr<CSQLiteDBDecorator> spSQLite(new CSQLiteDBDecorator(strDbPath));
	return spSQLite;
}

CSQLiteResult CSQLiteDBDecorator::Execute(const CSQLiteQuery& sSQL)
{
	CSQLiteStatement sStatement;
	int rc = sqlite3_prepare_v2(m_pDatabase, sSQL.ToString().c_str(), -1, &sStatement, nullptr);
	if (rc != SQLITE_OK)
	{
		throw std::runtime_error(sqlite3_errmsg(m_pDatabase));
	}

	return std::move(CSQLiteResult(std::move(sStatement)));
}