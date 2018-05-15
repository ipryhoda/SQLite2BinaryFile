#ifndef  _SQLLITE_ITEM_H
#define  _SQLLITE_ITEM_H

#include <cstdint>
#include <vector>

class CSQLiteItem
{
	CSQLiteItem(const CSQLiteItem&);
	CSQLiteItem& operator=(const CSQLiteItem&);
public:
	CSQLiteItem() {}
	virtual ~CSQLiteItem() {};
};

template<typename numeric_t>
class CSQLiteNumericItem : public CSQLiteItem
{
	CSQLiteNumericItem(const CSQLiteNumericItem<numeric_t>&);
	CSQLiteNumericItem& operator=(const CSQLiteNumericItem<numeric_t>&);
public:
	CSQLiteNumericItem(numeric_t value) : m_value(value) {}
	~CSQLiteNumericItem() {}
private:
	numeric_t m_value;
};

class CSQLLiteBinaryItem : public CSQLiteItem
{
	CSQLLiteBinaryItem(const CSQLLiteBinaryItem&);
	CSQLLiteBinaryItem& operator=(const CSQLLiteBinaryItem&);
public:
	CSQLLiteBinaryItem(std::uint8_t* pv, size_t iBytesCount);
	~CSQLLiteBinaryItem();
private:
	std::vector<std::uint8_t> m_vec;
};

#endif // _SQLLITE_ITEM_H
