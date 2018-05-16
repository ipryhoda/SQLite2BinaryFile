#include "SQLiteQuery.h"

CSortBy::CSortBy(const std::string& strSortBy) noexcept : m_strSortBy(strSortBy)
{}

CSortBy::~CSortBy()
{
}

bool CSortBy::is_set() const
{
	return !m_strSortBy.empty();
}

std::ostream& operator<< (std::ostream& stream, const CSortBy& sSort)
{
	stream << sSort.m_strSortBy;
	return stream;
}


CSQLiteSelectQuery::CSQLiteSelectQuery(const std::string& strTableName, const std::vector<std::string>& vecFields, const std::string& strSortBy) noexcept
	: m_strTable(strTableName), m_vecFields(vecFields), m_sSortBy(strSortBy)
{	
}

std::string CSQLiteSelectQuery::ToString() const
{
	std::basic_stringstream<char> stream;

	stream << "SELECT ";
	for (auto& it = m_vecFields.begin(); it != m_vecFields.end(); ++it)
	{
		stream << *it;
		if (*it != m_vecFields.back())
		{
			stream << ", ";
		}
	}

	stream << " FROM " << m_strTable;
	if (m_sSortBy.is_set())
	{
		stream << " GROUP BY " << m_sSortBy;
	}

	return stream.str();
}
