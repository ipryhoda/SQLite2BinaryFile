#ifndef  _SQLLITE_ITEM_H
#define  _SQLLITE_ITEM_H

#include "Archieve.h"
#include <cstdint>
#include <vector>

class CSQLiteItem : public CArchieve<char>
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

	// Overriden
	istream_t& deserialize(istream_t& stream)
	{
		stream.read(reinterpret_cast<char*>(&m_value), sizeof(m_value));
		return stream;
	}
	ostream_t& serialize(ostream_t& stream)
	{
		stream.write(reinterpret_cast<const char*>(&m_value), sizeof(m_value));
		return stream;
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
	istream_t& deserialize(istream_t& stream)
	{
		std::uint64_t iSize = 0;
		stream.read(reinterpret_cast<char*>(&iSize), sizeof(iSize));
		m_vec.resize(iSize);
		stream.read(reinterpret_cast<char*>(&m_vec[0]), iSize);

		return stream;
	}

	ostream_t& serialize(ostream_t& stream)
	{
		const std::uint64_t iSize = m_vec.size();
		stream.write(reinterpret_cast<const char*>(&iSize), sizeof(iSize));
		stream.write(reinterpret_cast<const char*>(&m_vec[0]), m_vec.size());

		return stream;
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
	// Overriden
	istream_t& deserialize(istream_t& stream)
	{
		std::uint64_t iSize = 0;
		stream.read(reinterpret_cast<char*>(&iSize), sizeof(iSize));
		m_sText.resize(iSize);
		stream.read(reinterpret_cast<char*>(&m_sText[0]), iSize);

		return stream;
	}
	ostream_t& serialize(ostream_t& stream)
	{
		const std::uint64_t iSize = m_sText.size() * sizeof(char_t);
		stream.write(reinterpret_cast<const char*>(&iSize), sizeof(iSize));
		stream.write(reinterpret_cast<const char*>(&m_sText[0]), iSize);

		return stream;
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
	// Overriden
	istream_t& deserialize(istream_t& stream)
	{
		std::uint8_t uiNull = 0;
		stream.read(reinterpret_cast<char*>(&uiNull), sizeof(uiNull));

		return stream;
	}
	ostream_t& serialize(ostream_t& stream)
	{
		const std::uint8_t uiNull = 0;
		stream.write(reinterpret_cast<const char*>(&uiNull), sizeof(uiNull));

		return stream;
	}
};

#endif // _SQLLITE_ITEM_H
