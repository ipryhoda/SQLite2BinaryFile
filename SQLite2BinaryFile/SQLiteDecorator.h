#ifndef  _SQLLITE_DECORATOR_H
#define  _SQLLITE_DECORATOR_H

#include "SQLiteQuery.h"
#include "SQLiteResult.h"

#include <vector>
#include <memory>
#include <string>


using namespace std;

//SQLite Decorator Class
class CSQLiteDBDecorator
{
private:
	CSQLiteDBDecorator(const CSQLiteDBDecorator&);
	CSQLiteDBDecorator& operator=(const CSQLiteDBDecorator&) {}
public:
	CSQLiteDBDecorator(const string& strDbPath);
	~CSQLiteDBDecorator();

	CSQLiteResult Execute(const CSQLiteQuery& sSQL);
protected:
	std::shared_ptr<sqlite3> m_spSqlite3;
};


#endif // #_SQLLITE_DECORATOR_H