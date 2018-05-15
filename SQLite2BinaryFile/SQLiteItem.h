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

template <typename Type>
struct is_sqlite_value : public std::integral_constant<
	bool,
	std::is_floating_point<Type>::value
	|| std::is_integral<Type>::value
> { };

template<typename numeric_t>
class CSQLiteNumericItem : public CSQLiteItem
{
	using type_t = typename std::enable_if<is_sqlite_value<numeric_t>::value, numeric_t>::type;
	CSQLiteNumericItem(const CSQLiteNumericItem<numeric_t>&);
	CSQLiteNumericItem& operator=(const CSQLiteNumericItem<numeric_t>&);
public:
	CSQLiteNumericItem(type_t value) : m_value(value) {}
	~CSQLiteNumericItem() {}
private:
	type_t m_value;
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
