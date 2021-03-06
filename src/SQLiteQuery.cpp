#include "SQLiteQuery.h"

CSQLiteQuery::CSQLiteQuery(const std::string& strName) : m_strTable(strName) {}

std::string CSQLiteQuery::GetTableName() const
{
    return m_strTable;
}

////////////////////////////////////////////////////////////////////////////////////
// CSortBy
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
	: CSQLiteQuery(strTableName), m_vecFields(vecFields), m_sSortBy(strSortBy), m_bFlagSet(false)
{
}

#if 0
void CSQLiteSelectQuery::Run(std::shared_ptr<CSQLiteDBDecorator>& spSQLiteDB)
{
	CSQLiteResult results = spSQLiteDB->Execute(*this);
	bool bCallOnce = false;
	results.get_Rows([&bCallOnce](std::shared_ptr<std::vector<CSQLiteField>> spFields,
		std::vector<std::shared_ptr<CSQLiteItem> > vecRows)
	{
		if (!bCallOnce)
		{
			for (auto& it : *spFields.get())
			{
			}

			bCallOnce = true;
		}
	});
}
#endif

std::string CSQLiteSelectQuery::ToString() const
{
	std::basic_stringstream<char> stream;

	stream << "SELECT ";
	for (std::vector<std::string>::const_iterator it = m_vecFields.begin(); it != m_vecFields.end(); ++it)
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
