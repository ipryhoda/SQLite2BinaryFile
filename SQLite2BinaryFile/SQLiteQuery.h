#ifndef  _SQLLITE_QUERY_H
#define  _SQLLITE_QUERY_H

#include <string>
#include <vector>
#include <sstream>

template<class char_t> 
class CSQLiteQuery
{
	CSQLiteQuery(const CSQLiteQuery<char_t>&);
	CSQLiteQuery<char_t>& operator=(const CSQLiteQuery<char_t>&) {}
public:
	virtual ~CSQLiteQuery() = 0;
	virtual void ToString() = 0;
};

template<class char_t>
class CSQLiteSelectQuery : public CSQLiteQuery<char_t>
{
	typedef std::basic_string<char_t> string_t;
	string_t m_sQuery;

	CSQLiteSelectQuery(const CSQLiteSelectQuery<char_t>&);
	CSQLiteSelectQuery<char_t>& operator=(const CSQLiteSelectQuery<char_t>&) {}
public:
	CSQLiteSelectQuery(const string_t& sTableName, std::vector<string_t>& vecFields, const string_t& sSortBy)
	{
		std::stringstream<char_t> stream;

		stream << "select ";
		for (auto& it = vecFields.begin(); it != vecFields.end(); ++it)
		{
			stream << it;
			if (it != vecFields.back())
			{
				stream << ", ";
			}
		}

		stream << " from " << sTableName;
		if (!sSortBy.empty())
		{
			stream << " group by " << sSortBy;
		}

		m_sQuery = stream.str();
	}

	~CSQLiteSelectQuery() {}

	virtual void ToString()
	{
		return m_sQuery;
	}
};

#endif // _SQLLITE_QUERY_H
