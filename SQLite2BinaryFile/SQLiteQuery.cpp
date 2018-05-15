#include "SQLiteQuery.h"

CSQLiteSelectQuery::CSQLiteSelectQuery(const std::string& sTableName, const std::vector<std::string>& vecFields, const std::string& sSortBy)
{
	std::basic_stringstream<char> stream;

	stream << "SELECT ";
	for (auto& it = vecFields.begin(); it != vecFields.end(); ++it)
	{
		stream << *it;
		if (*it != vecFields.back())
		{
			stream << ", ";
		}
	}

	stream << " FROM " << sTableName;
	if (!sSortBy.empty())
	{
		stream << " GROUP BY " << sSortBy;
	}

	m_sQuery = stream.str();
}

std::string CSQLiteSelectQuery::ToString() const
{
	return m_sQuery;
}
