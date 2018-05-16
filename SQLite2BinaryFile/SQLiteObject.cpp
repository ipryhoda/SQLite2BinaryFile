#include "SQLiteObject.h"
#include "SQLiteDecorator.h"
#include "SQLiteResult.h"
#include <iomanip>

CSQLiteObject::CSQLiteObject(CSQLiteObject&& other)
{
	m_sName = std::move(other.m_sName);
}

std::ostream& operator<< (std::ostream& stream, const CSQLiteObject& sObject)
{
	stream << setw(10) << left << sObject.m_sName;
	return stream;
}

CSQLiteField::CSQLiteField(CSQLiteField&& other) : CSQLiteObject(std::move(other))
{
	m_iType = std::move(other.m_iType);
}

std::ostream& operator<< (std::ostream& stream, const CSQLiteField& sField)
{
	stream << static_cast<const CSQLiteObject&>(sField) << left << ":" << left << sField.m_iType << "\t";
	return stream;
}

CSQLiteTable::CSQLiteTable(const std::string& sName, std::unique_ptr<CSQLiteResult>&& upSQLiteResult) : CSQLiteObject(sName), 
m_upSQLiteResult(std::move(upSQLiteResult))
{}

CSQLiteTable::~CSQLiteTable()
{}


CSQLiteDatabase::CSQLiteDatabase(const std::string& sName, const std::vector<shared_ptr<CSQLiteQuery> >& vecQueries) 
	: CSQLiteObject(sName), m_spSQLLiteDB(std::make_shared<CSQLiteDBDecorator>(sName)), m_vecQueries(vecQueries)
{}

CSQLiteDatabase::~CSQLiteDatabase()
{}


