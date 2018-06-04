#ifndef  _SQLLITE_RESULT_H
#define  _SQLLITE_RESULT_H

#include "SQLiteStatement.h"

#include <vector>
#include <memory>

class CSQLiteTable;
class CSQLiteResult
{
	CSQLiteResult(const CSQLiteResult&);
	CSQLiteResult& operator=(const CSQLiteResult&) {}
public:
	CSQLiteResult(CSQLiteStatement&& sSQLStmt, const std::shared_ptr<sqlite3>&, const std::string& sTableName);
	CSQLiteResult(CSQLiteResult&& other);
	~CSQLiteResult();

	std::unique_ptr<CSQLiteTable> Get();

protected:
	std::shared_ptr<sqlite3> m_spSqlite;
	CSQLiteStatement m_sSQLStmt;
    std::string m_strTableName;
};

#endif //_SQLLITE_RESULT_H