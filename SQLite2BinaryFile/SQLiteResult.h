#ifndef  _SQLLITE_RESULT_H
#define  _SQLLITE_RESULT_H

#include "SQLiteStatement.h"
#include "SQLiteObject.h"

#include <functional>
#include <vector>
#include <memory>

class CSQLiteResult
{
	CSQLiteResult(const CSQLiteResult&);
	CSQLiteResult& operator=(const CSQLiteResult&) {}
public:
	CSQLiteResult(CSQLiteStatement&& sSQLStmt, const std::shared_ptr<sqlite3>&);
	CSQLiteResult(CSQLiteResult&& other);
	~CSQLiteResult();

	void get_Rows(std::function<void(std::shared_ptr<std::vector<CSQLiteField>>, std::vector<std::shared_ptr<CSQLiteItem> >) > notify);
protected:
	std::shared_ptr<sqlite3> m_spSqlite;
	CSQLiteStatement m_sSQLStmt;
};

#endif //_SQLLITE_RESULT_H