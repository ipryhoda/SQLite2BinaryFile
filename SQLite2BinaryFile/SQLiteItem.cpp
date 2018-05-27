#include "SQLiteItem.h"

CSQLiteItem::CSQLiteItem() 
{
}

CSQLiteItem::~CSQLiteItem()
{
}

CSQLLiteBinaryItem::CSQLLiteBinaryItem(const std::uint8_t* pv, size_t iBytesCount) :  m_vec(&pv[0], &pv[iBytesCount])
{
}

CSQLLiteBinaryItem::~CSQLLiteBinaryItem()
{
}

CSQLLiteNullItem::CSQLLiteNullItem()
{
}

CSQLLiteNullItem::~CSQLLiteNullItem()
{
}