#ifndef  _SQLLITE_ITEM_H
#define  _SQLLITE_ITEM_H

#include "Archieve.h"
#include <cstdint>
#include <vector>

class CSQLiteItem
{
	CSQLiteItem(const CSQLiteItem&);
	CSQLiteItem& operator=(const CSQLiteItem&);
protected:
	CSQLiteItem();
public:
	virtual ~CSQLiteItem();
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
	CSQLiteNumericItem& operator=(const CSQLiteNumericItem<numeric_t>&) {}
public:
	CSQLiteNumericItem(type_t value) : m_value(value) {}
	~CSQLiteNumericItem() {}

	void deserialize()
	{
	}

	void serialize()
	{
	}
private:
	type_t m_value;
};

class CSQLLiteBinaryItem : public CSQLiteItem
{
	CSQLLiteBinaryItem(const CSQLLiteBinaryItem&);
	CSQLLiteBinaryItem& operator=(const CSQLLiteBinaryItem&);
public:
	CSQLLiteBinaryItem(const std::uint8_t* pv, size_t iBytesCount);
	~CSQLLiteBinaryItem();
	// Overriden
	void deserialize()
	{
	}

	void serialize()
	{
	}

private:
	std::vector<std::uint8_t> m_vec;
};

template<typename char_t>
class CSQLLiteStringItem : public CSQLiteItem
{
	CSQLLiteStringItem<char_t>(const CSQLLiteStringItem<char_t>&);
	CSQLLiteStringItem<char_t>& operator=(const CSQLLiteStringItem<char_t>&);
public:
	CSQLLiteStringItem(const std::basic_string<char_t>& sText) : m_sText(sText) {}
	~CSQLLiteStringItem() {}

	void deserialize()
	{
	}

	void serialize()
	{
	}
private:
	std::basic_string<char_t> m_sText;
};

class CSQLLiteNullItem : public CSQLiteItem
{
	CSQLLiteNullItem(const CSQLLiteNullItem&);
	CSQLLiteNullItem& operator=(const CSQLLiteNullItem&);
public:
	CSQLLiteNullItem();
	~CSQLLiteNullItem();

	void deserialize()
	{
	}

	void serialize()
	{
	}
};

#endif // _SQLLITE_ITEM_H
