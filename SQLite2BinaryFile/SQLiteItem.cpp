#include "SQLiteItem.h"
#include "SQLite\sqlite3.h"
////////////////////////////////////////////////////////////////////////////////////
// CSQLiteItem
CSQLiteItem::CSQLiteItem() 
{
}

CSQLiteItem::~CSQLiteItem()
{
}

////////////////////////////////////////////////////////////////////////////////////
// CSQLLiteBinaryItem
CSQLLiteBinaryItem::CSQLLiteBinaryItem(const std::uint8_t* pv, size_t iBytesCount) :  m_vec(&pv[0], &pv[iBytesCount])
{
}

CSQLLiteBinaryItem::~CSQLLiteBinaryItem()
{
}

void CSQLLiteBinaryItem::deserialize(CArchieve & ar)
{
    ar.load(m_vec);
}

void CSQLLiteBinaryItem::serialize(CArchieve & ar)
{
    ar.store(m_vec);
}

void CSQLLiteBinaryItem::Print(std::ostream& stream)
{
}
////////////////////////////////////////////////////////////////////////////////////
// CSQLLiteStringItem


////////////////////////////////////////////////////////////////////////////////////
// CSQLLiteNullItem
CSQLLiteNullItem::CSQLLiteNullItem()
{
}

CSQLLiteNullItem::~CSQLLiteNullItem()
{
}

void CSQLLiteNullItem::deserialize(CArchieve & ar)
{
    std::uint64_t ui8Value = 0;
    ar.load(ui8Value);
}

void CSQLLiteNullItem::serialize(CArchieve & ar)
{
    ar.store(static_cast<std::uint64_t>(0));
}

void CSQLLiteNullItem::Print(std::ostream& stream)
{
    AdjustWeightLeftPrint(stream, "NULL");
}

std::shared_ptr<CSQLiteItem> construct(std::uint8_t ui8Type)
{
    switch (ui8Type)
    {
    case SQLITE_INTEGER:
    {
        return std::make_shared< CSQLiteNumericItem<int64_t> >();
    }
    case SQLITE_FLOAT:
    {
        return std::make_shared< CSQLiteNumericItem<double> >();
    }
    case SQLITE_BLOB:
    {
        return std::make_shared< CSQLLiteBinaryItem >();
    }
    case SQLITE_TEXT:
    {
        return std::make_shared< CSQLLiteStringItem<char> >();
    }
    case SQLITE_NULL:
    {
        return std::make_shared< CSQLLiteNullItem >();
    }
    default:
        throw std::runtime_error("Unsupported SQL type handling");
        break;
    }

    return std::shared_ptr<CSQLiteItem>(nullptr);
}

std::ostream& operator<< (std::ostream& stream, const CSQLiteItem& sSQLitem)
{
    return stream;
}