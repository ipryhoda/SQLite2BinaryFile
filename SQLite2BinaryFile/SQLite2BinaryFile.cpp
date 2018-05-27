// SQLite2BinaryFile.cpp : Defines the entry point for the application.
//

#include "SQLite2BinaryFile.h"
#include "SQLiteObject.h"
#include "SQLiteQuery.h"

#include <fstream>
#include <memory>

enum EXIT_CODE
{
	OK,
	ERROR
};

void PrintUsage()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "SQLite2BinaryFile.exe -x <xml path> [-s <sqlite db path> | -f <binary file> [-t <table> -r <records count>]]" << std::endl;
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    const std::string strDbPath("C:\\SQLite\\db\\chinook.db");
    const std::string strSqlDump("D:\\SQLDump.dump");
    int iExitCode = OK;
    try
    {

        std::vector< std::shared_ptr< CSQLiteQuery> > vecSQLQueries{
            std::make_shared<CSQLiteSelectQuery>("employees", std::initializer_list<std::string>{ "*" }, "") };

        CSQLiteDatabase sSqliteDb(strDbPath, vecSQLQueries);

        sSqliteDb.serialize();

    }
    catch (const std::exception& ex)
    {
        std::cerr << "ERROR: " << ex.what() << std::endl;
        iExitCode = ERROR;
    }

    return iExitCode;
}