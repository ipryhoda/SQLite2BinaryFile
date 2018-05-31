#ifndef  _SQLLITE_OBJECT_H
#define  _SQLLITE_OBJECT_H

#include "SQLiteItem.h"
#include "Archive.h"
#include "SQLiteQuery.h"
#include "SQLiteResult.h"

#include <string>
#include <vector>
#include <memory>
#include <utility>

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

class CSQLiteRow
{
    CSQLiteRow(const CSQLiteRow&);
    CSQLiteRow& operator=(const CSQLiteRow&);

public:
    typedef std::pair<std::uint8_t, std::shared_ptr< CSQLiteItem> > TSharedPtrRowItem;
    CSQLiteRow(std::vector< TSharedPtrRowItem > &&);
    CSQLiteRow(CSQLiteRow &&);
    CSQLiteRow() {}

    void deserialize(CArchieve & ar);
    void serialize(CArchieve & ar);
    friend std::ostream& operator<< (std::ostream& stream, const CSQLiteRow& sRow);
private:
    std::vector< TSharedPtrRowItem > m_vecItems;
};

class CSQLiteTable : public CSQLiteObject
{
	CSQLiteTable(const CSQLiteTable&);
	CSQLiteTable& operator=(const CSQLiteTable&);
public:
	CSQLiteTable(const std::string& sName, std::vector<string> && vecFields, std::vector<CSQLiteRow> && vecRows);
    CSQLiteTable() {}
	~CSQLiteTable();

    void deserialize(CArchieve & ar);
    void serialize(CArchieve & ar);
    void print(std::ostream& stream, size_t uiRowCount = -1);
    friend std::ostream& operator<< (std::ostream& stream, const CSQLiteTable& sTable);
private:
    std::vector<std::string> m_vecFields;
    std::vector<CSQLiteRow>  m_vecRows;
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
