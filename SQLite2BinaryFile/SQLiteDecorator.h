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
	static shared_ptr<CSQLiteDBDecorator> GetInstance(const string& strDbPath);
protected:
	sqlite3	 *m_pDatabase;
};


#endif // #_SQLLITE_DECORATOR_H