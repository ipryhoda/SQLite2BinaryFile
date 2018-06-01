// SQLite2BinaryFile.cpp : Defines the entry point for the application.
//

#include "SQLite2BinaryFile.h"
#include "SQLiteObject.h"
#include "SQLiteQuery.h"
#include "SQLiteSchema.h"

#include <fstream>
#include <memory>
#include <iostream>

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
#if 0
    const std::string strDbPath("F:\\chinook.db");
    const std::string strXmlPath("F:\\schema.xml");
    const std::string strSqlDump("F:\\SQLDump.dump");
#else
    const std::string strDbPath("./SQLite/db/chinook.db");
    const std::string strXmlPath("./config/schema.xml");
    const std::string strSqlDump("./SQLDump.dump");
#endif

    int iExitCode = OK;
    try
    {
#if 0
        std::vector< std::shared_ptr<CSQLiteQuery> > vecSQLQueries{ std::make_shared<CSQLiteSelectQuery>("albums", std::initializer_list<std::string>{ "*" }, "")
            , std::make_shared<CSQLiteSelectQuery>("artists", std::initializer_list<std::string>{ "*" }, "")
            , std::make_shared<CSQLiteSelectQuery>("customers", std::initializer_list<std::string>{ "*" }, "") 
            , std::make_shared<CSQLiteSelectQuery>("employees", std::initializer_list<std::string>{ "*" }, "") 
            , std::make_shared<CSQLiteSelectQuery>("genres", std::initializer_list<std::string>{ "*" }, "") 
            , std::make_shared<CSQLiteSelectQuery>("invoices", std::initializer_list<std::string>{ "*" }, "") 
            , std::make_shared<CSQLiteSelectQuery>("invoice_items", std::initializer_list<std::string>{ "*" }, "") 
            , std::make_shared<CSQLiteSelectQuery>("media_types", std::initializer_list<std::string>{ "*" }, "") 
            , std::make_shared<CSQLiteSelectQuery>("playlists", std::initializer_list<std::string>{ "*" }, "")
            , std::make_shared<CSQLiteSelectQuery>("playlist_track", std::initializer_list<std::string>{ "*" }, "")
            , std::make_shared<CSQLiteSelectQuery>("tracks", std::initializer_list<std::string>{ "*" }, "") };
#endif

        std::vector< std::shared_ptr<CSQLiteQuery> > vecSQLQueries;
        CSQLiteSchema sSQLSchema(strXmlPath);
        sSQLSchema.Parse(vecSQLQueries);
#if 0
        std::shared_ptr<CArchieve> spArchive(new CBinaryFileArchive(strSqlDump, CBinaryFileArchive::WRITE));
        spArchive->store((std::uint64_t)vecSQLQueries.size());

        CSQLiteDatabase sSqliteDb(strDbPath);
        for (auto& it : vecSQLQueries)
        {
            std::cout << "Call query to SQLite: \"" << it->ToString() << "\"" << std::endl;
            CSQLiteResult sResult = sSqliteDb.Run(*it);
            std::cout << "Fetching data from SQLite ..." << std::endl;
            std::unique_ptr<CSQLiteTable> upTable = sResult.Get();
            std::cout << "Dumping table: \""<< it->GetTableName() << "\"" << std::endl;
            upTable->serialize(*spArchive);
        }

#else
        std::shared_ptr<CArchieve> spArchive(new CBinaryFileArchive(strSqlDump, CBinaryFileArchive::READ));
        std::vector<std::shared_ptr<CSQLiteTable> > vecTables;
        size_t iTableCount = 0;
        spArchive->load(iTableCount);
        for (size_t i = 0; i < iTableCount; ++i)
        {
            std::shared_ptr<CSQLiteTable> spTable(std::make_shared<CSQLiteTable>());
            spTable->deserialize(*spArchive);
            spTable->print(std::cout, 5);
            vecTables.push_back(spTable);
        }
#endif
    }
    catch (const std::exception& ex)
    {
        std::cerr << "ERROR: " << ex.what() << std::endl;
        iExitCode = ERROR;
    }

    return iExitCode;
}
