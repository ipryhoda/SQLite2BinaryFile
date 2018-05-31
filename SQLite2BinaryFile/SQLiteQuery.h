#ifndef  _SQLLITE_QUERY_H
#define  _SQLLITE_QUERY_H

#include "Archive.h"

#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <functional>

using namespace std;

class CSQLiteQuery
{	
	CSQLiteQuery(const CSQLiteQuery&);
	CSQLiteQuery& operator=(const CSQLiteQuery&) {}
protected:
    CSQLiteQuery(const std::string& strName);
    std::string m_strTable;
public:
    std::string GetTableName() const;
	virtual ~CSQLiteQuery() {};
	virtual std::string ToString() const = 0;
};

class CSortBy
{
	CSortBy(const CSortBy&);
	CSortBy& operator=(const CSortBy&);
public:
	CSortBy(const std::string& strSortBy) noexcept;
	~CSortBy();

	bool is_set() const;
	friend std::ostream& operator<< (std::ostream& stream, const CSortBy& sSort);
private:
	std::string m_strSortBy;
};

class CSQLiteSelectQuery : public CSQLiteQuery
{
	CSQLiteSelectQuery(const CSQLiteSelectQuery&);
	CSQLiteSelectQuery& operator=(const CSQLiteSelectQuery&) {}
public:
	CSQLiteSelectQuery(const std::string& sTableName, 
		const std::vector<std::string>& vecFields, 
		const std::string& strSortBy) noexcept;
	~CSQLiteSelectQuery() {}

	virtual std::string ToString() const;
protected:
	std::vector<std::string> m_vecFields;
	CSortBy m_sSortBy;
	bool m_bFlagSet;
};

#endif // _SQLLITE_QUERY_H
