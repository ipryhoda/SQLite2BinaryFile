#ifndef  _SQLLITE_OBJECT_H
#define  _SQLLITE_OBJECT_H

#include "SQLiteItem.h"
#include "Archive.h"
#include "SQLiteQuery.h"
#include "SQLiteResult.h"

#include <string>
#include <vector>
#include <memory>

class CSQLiteObject
{
    CSQLiteObject(const CSQLiteObject&);
    CSQLiteObject& operator=(const CSQLiteObject&) {}
public:
    CSQLiteObject(const std::string& sName) : m_strName(sName) {}
    CSQLiteObject(CSQLiteObject&& other);
    CSQLiteObject() {}
	virtual ~CSQLiteObject() {}

    void deserialize(CArchieve & ar);
    void serialize(CArchieve & ar);
	friend std::ostream& operator<< (std::ostream& stream, const CSQLiteObject& sField);
protected:
	std::string m_strName;
};

class CSQLiteTable : public CSQLiteObject
{
	CSQLiteTable(const CSQLiteTable&);
	CSQLiteTable& operator=(const CSQLiteTable&);
public:
	CSQLiteTable(const std::string& sName, std::vector<string> && vecFields, std::vector< std::vector< std::shared_ptr< CSQLiteItem> > > && vecRows);
    CSQLiteTable() {}
	~CSQLiteTable();

    void deserialize(CArchieve & ar);
    void serialize(CArchieve & ar);
private:
    std::vector< std::vector< std::shared_ptr< CSQLiteItem> > >  m_vecRows;
    std::vector<std::string> m_vecFields;
};

class CSQLiteDatabase : public CSQLiteObject
{
	CSQLiteDatabase(const CSQLiteDatabase&);
	CSQLiteDatabase& operator=(const CSQLiteDatabase&);
public:
	CSQLiteDatabase(const std::string& sName);
	~CSQLiteDatabase();

    CSQLiteResult Run(const CSQLiteQuery& sQuery);
private:
    std::shared_ptr<sqlite3> m_spSqlite3;
};

#endif // _SQLLITE_OBJECT_H
