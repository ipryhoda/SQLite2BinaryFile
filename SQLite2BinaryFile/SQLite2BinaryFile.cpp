// SQLite2BinaryFile.cpp : Defines the entry point for the application.
//

#include "SQLite2BinaryFile.h"
#include "SQLiteQuery.h"

#include <fstream>
#include <memory>

enum EXIT_CODE
{
	OK,
	ERROR
};

int main()
{
	const std::string strDbPath("C:\\SQLite\\db\\chinook.db");
	int iExitCode = OK;
	try
	{

		std::vector< std::shared_ptr< CSQLiteSelectQuery> > spSQLQueries{ 
			std::make_shared<CSQLiteSelectQuery>("employees", std::initializer_list<std::string>{ "*" }, "") };
#if 0
		//CSQLiteSelectQuery sSQL("tracks", { "TrackId", "Name", "Composer", "UnitPrice" }, "");
		CSQLiteSelectQuery sSQL("employees ", { "*" }, "");


		CSQLiteResult results = spSQLite->Execute(sSQL);
		bool bCallOnce = false;
		results.get_Rows([&](std::shared_ptr<std::vector<CSQLiteField>> spFields, std::vector<std::shared_ptr<CSQLiteItem> > vecRows)
		{
			if (!bCallOnce)
			{
				for (auto& it : *spFields.get())
				{
					std::cout << it;
				}
				bCallOnce = true;
			}
		});
#endif
	}
	catch (const std::exception& ex)
	{
		std::cerr << "ERROR: " << ex.what() << std::endl;
		iExitCode = ERROR;
	}

	return iExitCode;
}
