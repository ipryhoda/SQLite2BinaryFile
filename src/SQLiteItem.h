#ifndef  _SQLLITE_ITEM_H
#define  _SQLLITE_ITEM_H

#include "SQLitePrint.h"
#include "Archive.h"
#include <cstdint>
#include <vector>
#include <memory>
#include <string>

class CSQLiteItem
{
	CSQLiteItem(const CSQLiteItem&);
	CSQLiteItem& operator=(const CSQLiteItem&);
protected:
	CSQLiteItem();
public:
	virtual ~CSQLiteItem();
    virtual  void deserialize(CArchieve & ar) = 0;
    virtual void serialize(CArchieve & ar) = 0;
    virtual void Print(std::ostream& stream) = 0;
};

template <typename Type>
struct is_sqlite_value : public std::integral_constant<	bool, std::is_floating_point<Type>::value || std::is_integral<Type>::value> { };
template<typename numeric_t>
class CSQLiteNumericItem : public CSQLiteItem
{
	using type_t = typename std::enable_if<is_sqlite_value<numeric_t>::value, numeric_t>::type;
	CSQLiteNumericItem(const CSQLiteNumericItem<numeric_t>&);
	CSQLiteNumericItem& operator=(const CSQLiteNumericItem<numeric_t>&) {}
public:
	CSQLiteNumericItem(type_t value) : m_value(value) {}
    CSQLiteNumericItem() {}
	~CSQLiteNumericItem() {}

    void deserialize(CArchieve & ar)
    {
        ar.load(m_value);
    }

    void serialize(CArchieve & ar)
    {
        ar.store(m_value);
    }

    void Print(std::ostream& stream)
    {
        AdjustWeightLeftPrint(stream, std::to_string((type_t)m_value));
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
    CSQLLiteBinaryItem() {}
	~CSQLLiteBinaryItem();

    void deserialize(CArchieve & ar);
    void serialize(CArchieve & ar);
    void Print(std::ostream& stream);
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
    CSQLLiteStringItem() {}
	~CSQLLiteStringItem() {}

    void deserialize(CArchieve & ar)
    {
        ar.load(m_sText);
    }
    void serialize(CArchieve & ar)
    {
        ar.store(m_sText);
    }

    void Print(std::ostream& stream)
    {
        AdjustWeightLeftPrint(stream, m_sText);
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

    void deserialize(CArchieve & ar);
    void serialize(CArchieve & ar);
    void Print(std::ostream& stream);
};


std::ostream& operator<< (std::ostream& stream, const CSQLiteItem& sSQLitem);
std::shared_ptr<CSQLiteItem> construct(std::uint8_t ui8Type);

#endif // _SQLLITE_ITEM_H
