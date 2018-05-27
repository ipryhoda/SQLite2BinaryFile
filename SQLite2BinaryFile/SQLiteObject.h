#ifndef  _SQLLITE_OBJECT_H
#define  _SQLLITE_OBJECT_H

#include "SQLiteItem.h"
#include "Archieve.h"
#include "SQLiteQuery.h"

#include <string>
#include <vector>
#include <memory>

class CSQLiteObject
{	
	CSQLiteObject(const CSQLiteObject&);
	CSQLiteObject& operator=(const CSQLiteObject&) {}
public:
	CSQLiteObject(const std::string& sName) : m_sName(sName) {}
	CSQLiteObject(CSQLiteObject&& other);
	virtual ~CSQLiteObject() {}

	void deserialize()
	{
	}

	void serialize()
	{
	}

	friend std::ostream& operator<< (std::ostream& stream, const CSQLiteObject& sField);
protected:
	std::string m_sName;
};

class CSQLiteField : public CSQLiteObject
{
	CSQLiteField(const CSQLiteField&);
	CSQLiteField& operator=(const CSQLiteField&);
public:
	CSQLiteField(const std::string& sName, int iType) : CSQLiteObject(sName), m_iType(iType) {}
	CSQLiteField(CSQLiteField&& other);
	~CSQLiteField() {}

	void deserialize()
	{
	}
	void serialize()
	{
	}

	friend std::ostream& operator<< (std::ostream& stream, const CSQLiteField& sField);
private:
	int m_iType;
};

#if 0
class CSQLiteResult;
class CSQLiteTable : public CSQLiteObject
{
	CSQLiteTable(const CSQLiteTable&);
	CSQLiteTable& operator=(const CSQLiteTable&);
public:
	CSQLiteTable(const std::string& sName, std::unique_ptr<CSQLiteResult>&& upSQLiteResult);
	~CSQLiteTable();
private:
	std::unique_ptr<CSQLiteResult> m_upSQLiteResult;
};
#endif

class CSQLiteDBDecorator;
class CSQLiteDatabase : public CSQLiteObject
{
	CSQLiteDatabase(const CSQLiteDatabase&);
	CSQLiteDatabase& operator=(const CSQLiteDatabase&);
public:
	CSQLiteDatabase(const std::string& sName, const std::vector<shared_ptr<CSQLiteQuery> >& vecQueries);
	~CSQLiteDatabase();

	void deserialize()
	{
	}

	void serialize()
	{
	}

private:
	std::vector<shared_ptr<CSQLiteQuery> > m_vecQueries;
	std::shared_ptr<CSQLiteDBDecorator> m_spSQLLiteDB;
};

#endif // _SQLLITE_OBJECT_H
