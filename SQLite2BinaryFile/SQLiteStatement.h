#ifndef  _SQLLITE_STATEMENT_H
#define  _SQLLITE_STATEMENT_H

//SQLite Header and library
#include "SQLite\sqlite3.h"

class CSQLiteStatement
{
	CSQLiteStatement(const CSQLiteStatement&) {}
	CSQLiteStatement& operator=(const CSQLiteStatement&) {}
public:
	CSQLiteStatement() : _pStmt(nullptr)
	{}

	CSQLiteStatement(CSQLiteStatement&& other)
	{
		_pStmt = other._pStmt;
		other._pStmt = nullptr;
	}

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

#endif //_SQLLITE_STATEMENT_H