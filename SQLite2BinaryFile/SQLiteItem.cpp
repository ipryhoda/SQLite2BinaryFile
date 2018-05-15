#include "SQLiteItem.h"


CSQLLiteBinaryItem::CSQLLiteBinaryItem(std::uint8_t* pv, size_t iBytesCount) :  m_vec(&pv[0], &pv[iBytesCount])
{
}

CSQLLiteBinaryItem::~CSQLLiteBinaryItem()
{
}