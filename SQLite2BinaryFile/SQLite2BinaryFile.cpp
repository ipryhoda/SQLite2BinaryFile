// SQLite2BinaryFile.cpp : Defines the entry point for the application.
//

#include "SQLite2BinaryFile.h"
#include "SQLiteDecorator.h"
#include "SQLiteQuery.h"

#include <fstream>

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

		//CSQLiteSelectQuery sSQL("tracks", { "TrackId", "Name", "Composer", "UnitPrice" }, "");
		CSQLiteSelectQuery sSQL("employees ", { "*" }, "");

		std::shared_ptr<CSQLiteDBDecorator> spSQLite = CSQLiteDBDecorator::GetInstance(strDbPath);
		CSQLiteResult results = spSQLite->Execute(sSQL);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "ERROR: " << ex.what() << std::endl;
		iExitCode = ERROR;
	}

	return iExitCode;
}
