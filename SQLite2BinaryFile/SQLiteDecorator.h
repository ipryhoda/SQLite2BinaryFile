#ifndef  _SQLLITE_DECORATOR_H
#define  _SQLLITE_DECORATOR_H

#include "SQLiteQuery.h"
#include <memory>
#include <string>

//SQLite Header and library
#include "SQLite\sqlite3.h"

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

	static shared_ptr<CSQLiteDBDecorator> GetInstance(const string& strDbPath);
protected:
	void ExcuteSelect(const std::string& strQuery);

	sqlite3	 *m_pDatabase;
};


#endif // #_SQLLITE_DECORATOR_H