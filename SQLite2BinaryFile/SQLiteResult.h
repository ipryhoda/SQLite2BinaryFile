#ifndef  _SQLLITE_RESULT_H
#define  _SQLLITE_RESULT_H

#include "SQLiteStatement.h"
#include "SQLiteObject.h"

#include <functional>
#include <vector>

class CSQLiteResult
{
	CSQLiteResult(const CSQLiteResult&);
	CSQLiteResult& operator=(const CSQLiteResult&) {}
public:
	CSQLiteResult(CSQLiteStatement&& sSQLStmt);
	CSQLiteResult(CSQLiteResult&& other);
	~CSQLiteResult();

	void get_Fields();
	void get_Rows(std::function<void(std::vector<CSQLiteItem>)> notify);
protected:
	CSQLiteStatement m_sSQLStmt;
};

#endif //_SQLLITE_RESULT_H