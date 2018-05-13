#ifndef  _SQLLITE_OBJECT_H
#define  _SQLLITE_OBJECT_H

#include "SQLiteItem.h"
#include "Archieve.h"
#include <string>
#include <vector>

template<class char_t>
class CSQLiteObject
{	
	CSQLiteObject(const CSQLiteObject<char_t>&);
	CSQLiteObject<char_t>& operator=(const CSQLiteObject<char_t>&) {}
public:
	CSQLiteTable(const std::basic_string<char_t>& sName) : m_sName(sName) {}
	virtual ~CSQLiteObject() {}
protected:
	std::basic_string<char_t> m_sName;
};

class CSQLiteField : CSQLiteObject<char_t>
{
	CSQLiteField(const CSQLiteField&);
	CSQLiteField& operator=(const CSQLiteField&) {}
public:
	CSQLiteField(const std::basic_string<char_t>& sName) : CSQLiteTable(sName) {}
	~CSQLiteField() {}
};

class CSQLiteRow
{
	CSQLiteRow(const CSQLiteRow&);
	CSQLiteRow& operator=(const CSQLiteRow&) {}
public:
	~CSQLiteRow() {}

protected:
	std::vector<ISQLiteItem> m_vecItems;
};

template<class char_t>
class CSQLiteTable : public CSQLiteObject<char_t>
{
	CSQLiteTable(const CSQLiteTable&);
	CSQLiteTable<char_t>& operator=(const CSQLiteTable&) {}
public:
	CSQLiteTable(const std::basic_string<char_t>& sName, std::vector<std::shared_ptr<CSQLiteField>> vecFields) : CSQLiteTable(sName), m_vecFields(vecFields) {}
	~CSQLiteTable() {}
private:
	std::vector<std::shared_ptr<CSQLiteField>> m_vecFields;	
};


#endif // _SQLLITE_OBJECT_H
