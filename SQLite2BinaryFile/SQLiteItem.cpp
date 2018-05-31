#include "SQLiteItem.h"

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