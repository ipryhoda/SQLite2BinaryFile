#ifndef  _SQLLITE_OBJECT_H
#define  _SQLLITE_OBJECT_H

#include "SQLiteItem.h"
#include "Archieve.h"
#include <string>
#include <vector>

class CSQLiteObject
{	
	CSQLiteObject(const CSQLiteObject&);
	CSQLiteObject& operator=(const CSQLiteObject&) {}
public:
	CSQLiteObject(const std::string& sName) : m_sName(sName) {}
	virtual ~CSQLiteObject() {}
protected:
	std::string m_sName;
};

class CSQLiteField : public CSQLiteObject
{
	CSQLiteField(const CSQLiteField&);
	CSQLiteField& operator=(const CSQLiteField&) {}
public:
	CSQLiteField(const std::string& sName, int iType) : CSQLiteObject(sName), m_iType(iType) {}
	~CSQLiteField() {}
private:
	int m_iType;
};

#if 0
class CSQLiteTable : public CSQLiteObject
{
	CSQLiteTable(const CSQLiteTable&);
	CSQLiteTable& operator=(const CSQLiteTable&) {}
public:
	CSQLiteTable(const std::string& sName, std::vector<CSQLiteField>& vecFields) 
		: CSQLiteObject(sName), m_vecFields(vecFields) {}
	~CSQLiteTable() {}
private:
	std::vector<CSQLiteField> m_vecFields;	
};

#endif

#endif // _SQLLITE_OBJECT_H
