#include "SQLiteDecorator.h"

/////////////////////////////////////////////////////////////////////////////////////
// CSQLiteStatement
class CSQLiteStatement
{
public:
	CSQLiteStatement() : _pStmt(nullptr)
	{}
	~CSQLiteStatement()
	{
		if (_pStmt != nullptr)
		{
			sqlite3_finalize(_pStmt);
		}
	}

	sqlite3_stmt** operator&()
	{
		return &_pStmt;
	}

	operator sqlite3_stmt*() const
	{
		return _pStmt;
	}

private:
	sqlite3_stmt * _pStmt;
};


/////////////////////////////////////////////////////////////////////////////////////
// CSQLiteDB
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

void  CSQLiteDBDecorator::ExcuteSelect(const std::string& strQuery)
{
	CSQLiteStatement sStatement;
	int rc = sqlite3_prepare_v2(m_pDatabase, strQuery.c_str(), -1, &sStatement, nullptr);
	if (rc != SQLITE_OK) 
	{
		throw std::runtime_error(sqlite3_errmsg(m_pDatabase));
	}

	while ((rc = sqlite3_step(sStatement)) == SQLITE_ROW)
	{
		
	}

	if (rc != SQLITE_DONE) 
	{
		throw std::runtime_error(sqlite3_errmsg(m_pDatabase));
	}
}
