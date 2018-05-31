#include "SQLiteResult.h"
#include "SQLiteObject.h"

CSQLiteResult::CSQLiteResult(CSQLiteStatement&& sSQLStmt, const std::shared_ptr<sqlite3>& sp, const std::string& strTableName)
    : m_sSQLStmt(std::move(sSQLStmt)), m_spSqlite(sp), m_strTableName(strTableName)
{}

CSQLiteResult::CSQLiteResult(CSQLiteResult&& other) : m_sSQLStmt(std::move(other.m_sSQLStmt))
{}

CSQLiteResult::~CSQLiteResult()
{}


std::unique_ptr<CSQLiteTable> CSQLiteResult::Get()
{
    std::vector< std::vector<std::shared_ptr< CSQLiteItem> > >  vecRows;
    std::vector< std::string> vecFields;

    bool bFirstCall = false;
	int rc = SQLITE_OK;

	while ((rc = sqlite3_step(m_sSQLStmt)) == SQLITE_ROW)
	{
		std::vector<std::shared_ptr<CSQLiteItem> > vecItems;
		for (int i = 0; i < sqlite3_column_count(m_sSQLStmt); ++i)
		{
			int iColumnType = ::sqlite3_column_type(m_sSQLStmt, i);
			if(!bFirstCall)
			{ 
                vecFields.push_back(::sqlite3_column_name(m_sSQLStmt, i));
			}		

			switch (iColumnType)
			{
				case SQLITE_INTEGER:
				{
					vecItems.push_back(std::make_shared<CSQLiteNumericItem<int64_t>>(sqlite3_column_int(m_sSQLStmt, i)));
					break;
				}
				case SQLITE_FLOAT:
				{
					vecItems.push_back(std::make_shared<CSQLiteNumericItem<double>>(sqlite3_column_double(m_sSQLStmt, i)));
					break;
				}
				case SQLITE_BLOB:
				{
					const std::uint8_t* ui8Blob = reinterpret_cast<const std::uint8_t*>(::sqlite3_column_blob(m_sSQLStmt, i));
					vecItems.push_back(std::make_shared<CSQLLiteBinaryItem>(ui8Blob, sqlite3_column_bytes(m_sSQLStmt, i)));
					break;
				}
				case SQLITE_TEXT:
				{
					std::string sText(reinterpret_cast<const char*>(::sqlite3_column_text(m_sSQLStmt, i)));
					vecItems.push_back(std::make_shared<CSQLLiteStringItem<char> >(sText));
					break;
				}
				case SQLITE_NULL:
					vecItems.push_back(std::make_shared<CSQLLiteNullItem>());
					break;
				default:
					throw std::runtime_error("Unsupported SQL type handling");
					break;
			}            
		}

        vecRows.push_back(std::move(vecItems));
		bFirstCall = true;
	}

	if (rc != SQLITE_DONE)
	{
		throw std::runtime_error(sqlite3_errmsg(m_spSqlite.get()));
	}
	return std::make_unique<CSQLiteTable>(m_strTableName, std::move(vecFields), std::move(vecRows));
}