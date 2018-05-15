#ifndef  _SQLLITE_QUERY_H
#define  _SQLLITE_QUERY_H

#include <string>
#include <vector>
#include <sstream>

class CSQLiteQuery
{	
	CSQLiteQuery(const CSQLiteQuery&);
	CSQLiteQuery& operator=(const CSQLiteQuery&) {}
protected:
	CSQLiteQuery() {}
public:
	virtual ~CSQLiteQuery() {};
	virtual std::string ToString() const = 0;
};

class CSQLiteSelectQuery : public CSQLiteQuery
{
	std::string m_sQuery;

	CSQLiteSelectQuery(const CSQLiteSelectQuery&);
	CSQLiteSelectQuery& operator=(const CSQLiteSelectQuery&) {}
public:
	CSQLiteSelectQuery(const std::string& sTableName, const std::vector<std::string>& vecFields, const std::string& sSortBy);

	~CSQLiteSelectQuery() {}

	virtual std::string ToString() const;
};

#endif // _SQLLITE_QUERY_H
