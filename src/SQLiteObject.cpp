#include "SQLiteObject.h"
#include "SQLitePrint.h"
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
// CSQLiteRow
CSQLiteRow::CSQLiteRow(CSQLiteRow && other)
{
    m_vecItems = std::move(other.m_vecItems);
}

CSQLiteRow::CSQLiteRow(std::vector< TSharedPtrRowItem > && vecOther)
{
    m_vecItems = std::move(vecOther);
}

void CSQLiteRow::deserialize(CArchieve & ar)
{
    std::uint64_t uiSize = 0;
    ar.load(uiSize);
    for (size_t i = 0; i < uiSize; ++i)
    {
        std::uint8_t ui8Type = 0;
        ar.load(ui8Type);

        std::shared_ptr<CSQLiteItem> spItem = construct(ui8Type);

        spItem->deserialize(ar);
        m_vecItems.push_back(TSharedPtrRowItem(ui8Type, spItem));
    }
}

void CSQLiteRow::serialize(CArchieve & ar)
{
    ar.store((std::uint64_t)m_vecItems.size());
    for (auto& itPair : m_vecItems)
    {
        ar.store(itPair.first);
        itPair.second->serialize(ar);
    }
}

std::ostream& operator<< (std::ostream& stream, const CSQLiteRow& sRow)
{
    for (auto & itItems : sRow.m_vecItems)
    {
        itItems.second->Print(stream);
    }

    return stream;
}
////////////////////////////////////////////////////////////////////////////////////
// CSQLiteTable
CSQLiteTable::CSQLiteTable(const std::string& strName, std::vector<string> && vecFields, std::vector<CSQLiteRow> && vecRows) :
    CSQLiteObject(strName), m_vecFields(std::move(vecFields)), m_vecRows(std::move(vecRows))
{}

CSQLiteTable::~CSQLiteTable()
{
}

void CSQLiteTable::deserialize(CArchieve & ar)
{
    CSQLiteObject::deserialize(ar);
    ar.load(m_vecFields);
    
    std::uint64_t uiRowCount = 0;
    ar.load(uiRowCount);

    for (size_t i = 0; i < uiRowCount; ++i)
    {   
        CSQLiteRow sSQLiteRow;

        sSQLiteRow.deserialize(ar);
        m_vecRows.push_back(std::move(sSQLiteRow));
    }

}

void CSQLiteTable::serialize( CArchieve & ar)
{
    CSQLiteObject::serialize(ar);
    ar.store(m_vecFields);

    ar.store((std::uint64_t)m_vecRows.size());

    for (auto& itRow : m_vecRows)
    {
        itRow.serialize(ar);
    }
}

void CSQLiteTable::print(std::ostream& stream, size_t uiRowCount)
{
    std::ios_base::fmtflags format(stream.flags());
    stream << "========================================" << std::setw(20) << centered(m_strName) << "========================================" << std::endl;
    for (auto & itField : m_vecFields)
    {
        AdjustWeightLeftPrint(stream, itField);
    }

    stream << std::endl;
    stream << "---------------------------------------------------------------------------------------------------" << std::endl;

    int iCount = 0;
    for (auto & itRow : m_vecRows)
    {
        if (iCount == uiRowCount) break;
        stream << itRow << std::endl;
        iCount++;
    }

    stream.flags(format);

}

std::ostream& operator<< (std::ostream& stream, const CSQLiteTable& sTable)
{
    for(auto & itField : sTable.m_vecFields)
    {
        AdjustWeightLeftPrint(stream, itField);
    }

    stream << std::endl;

    for (auto & itRow : sTable.m_vecRows)
    {
        stream << itRow << std::endl;
    }

    return stream;
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



