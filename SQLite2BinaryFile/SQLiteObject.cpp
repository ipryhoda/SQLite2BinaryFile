#include "SQLiteObject.h"
#include <iomanip>

CSQLiteObject::CSQLiteObject(CSQLiteObject&& other)
{
	m_strName = std::move(other.m_strName);
}


void CSQLiteObject::deserialize(CArchieve & ar)
{
    ar.load(m_strName);
}

void CSQLiteObject::serialize( CArchieve & ar)
{
    ar.store(m_strName);
}

std::ostream& operator<< (std::ostream& stream, const CSQLiteObject& sObject)
{
	stream << setw(10) << left << sObject.m_strName;
	return stream;
}
////////////////////////////////////////////////////////////////////////////////////
// CSQLiteTable
CSQLiteTable::CSQLiteTable(const std::string& strName, std::vector<string> && vecFields, std::vector<std::vector< std::shared_ptr< CSQLiteItem> > > && vecRows) :
    CSQLiteObject(strName), m_vecFields(std::move(vecFields)), m_vecRows(std::move(vecRows))
{}

CSQLiteTable::~CSQLiteTable()
{
}

void CSQLiteTable::deserialize(CArchieve & ar)
{
    CSQLiteObject::deserialize(ar);
    ar.load(m_vecFields);
    
    size_t uiRowCount = 0;
    ar.load(uiRowCount);
    for (size_t i = 0; i < uiRowCount; ++i)
    {
        std::vector< std::shared_ptr< CSQLiteItem> > vecRowItems;
        for (size_t j = 0; j < m_vecFields.size(); ++j)
        {
            switch (m_vecFields[j].GetType())
            {
                case SQLITE_INTEGER:
                {
                    std::shared_ptr<CSQLiteNumericItem<int64_t> > spItem(std::make_shared<CSQLiteNumericItem<int64_t> >());
                    spItem->deserialize(ar);
                    vecRowItems.push_back(spItem);
                    break;
                }
                case SQLITE_FLOAT:
                {
                    std::shared_ptr<CSQLiteNumericItem<double> > spItem(std::make_shared<CSQLiteNumericItem<double> >());
                    spItem->deserialize(ar);
                    vecRowItems.push_back(spItem);
                    break;
                }
                case SQLITE_BLOB:
                {
                    std::shared_ptr<CSQLLiteBinaryItem > spItem(std::make_shared<CSQLLiteBinaryItem>());
                    spItem->deserialize(ar);
                    vecRowItems.push_back(spItem);
                    break;
                }
                case SQLITE_TEXT:
                {
                    std::shared_ptr<CSQLLiteStringItem<char> > spItem(std::make_shared<CSQLLiteStringItem<char>>());
                    spItem->deserialize(ar);
                    vecRowItems.push_back(spItem);
                    break;
                }
                case SQLITE_NULL:
                {
                    std::shared_ptr<CSQLLiteNullItem> spItem(std::make_shared<CSQLLiteNullItem>());
                    spItem->deserialize(ar);
                    vecRowItems.push_back(spItem);
                    break;
                }
                default:
                {
                    throw std::runtime_error("Unsupported SQL type handling");
                    break;
                }
            }
        }

        m_vecRows.push_back(std::move(vecRowItems));
    }
}

void CSQLiteTable::serialize( CArchieve & ar)
{
    CSQLiteObject::serialize(ar);
    ar.store(m_vecFields);

    ar.store(m_vecRows.size());
    for (auto& itRow : m_vecRows)
    {        
        for (auto itItem : itRow)
        {
            itItem->serialize(ar);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////
// CSQLiteDatabase
CSQLiteDatabase::CSQLiteDatabase(const std::string& sName) 	: CSQLiteObject(sName)
{
    sqlite3* pSqlite3 = nullptr;
    if (sqlite3_open_v2(sName.c_str(), &pSqlite3, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK)
    {
        throw std::runtime_error(sqlite3_errmsg(pSqlite3));
    }

    m_spSqlite3.reset(pSqlite3, sqlite3_close);
}

CSQLiteDatabase::~CSQLiteDatabase()
{}

CSQLiteResult CSQLiteDatabase::Run(const CSQLiteQuery& sQuery)
{
    CSQLiteStatement sStatement;
    int rc = sqlite3_prepare_v2(m_spSqlite3.get(), sQuery.ToString().c_str(), -1, &sStatement, nullptr);
    if (rc != SQLITE_OK)
    {
        throw std::runtime_error(sqlite3_errmsg(m_spSqlite3.get()));
    }

    return CSQLiteResult(std::move(sStatement), m_spSqlite3, sQuery.GetTableName());
}



