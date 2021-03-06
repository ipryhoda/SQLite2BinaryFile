// SQLite2BinaryFile.cpp : Defines the entry point for the application.
//

#include "SQLite2BinaryFile.h"
#include "SQLiteCommandLine.h"
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
    std::cout << "sqlite2file -action serialize|verify -saveset <binary file> [-xmlfile <xml path>] [-show <records count>] [<db source file>]" << std::endl << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "Serialize sqlite db ('./SQLite/db/chinook.db') into binary file ('./saveset.sav'):" << std::endl << std::endl;
    std::cout << "sqlite2file -action serialize -saveset './saveset.sav' -xmlfile './config/schema.xml' './SQLite/db/chinook.db'" << std::endl;
    std::cout << "Verify binary file ('./saveset.sav') and show up to 20 entries:" << std::endl << std::endl;
    std::cout << "sqlite2file -action verify -saveset './saveset.sav' -show 20" << std::endl;
    std::cout << std::endl;
}


void sqlite2file_main(int argc, char *argv[])
{
    std::vector<std::string> vecArguments;
    if (argc < 1)
    {
        throw std::runtime_error("not enought arugments");
    }

    for (int i = 1; i < argc; ++i)
    {
        vecArguments.push_back(argv[i]);
        if (IsHelp(argv[i]))
        {
            PrintUsage();
            return;
        }
    }

    CSQLiteCommandLine sCmd(vecArguments);
    sCmd.Parse();

    if (sCmd.GetAction().compare(STR_SERIALIZE) == 0)
    {
        std::vector< std::shared_ptr<CSQLiteQuery> > vecSQLQueries;
        CSQLiteSchema sSQLSchema(sCmd.GetSchema());
        sSQLSchema.Parse(vecSQLQueries);

        std::shared_ptr<CArchieve> spArchive(new CBinaryFileArchive(sCmd.GetSaveset(), CBinaryFileArchive::WRITE));
        spArchive->store((std::uint64_t)vecSQLQueries.size());

        CSQLiteDatabase sSqliteDb(sCmd.GetSource());
        for (auto& it : vecSQLQueries)
        {
            std::cout << "Call query to SQLite: \"" << it->ToString() << "\"" << std::endl;
            CSQLiteResult sResult = sSqliteDb.Run(*it);
            std::cout << "Fetching data from SQLite ..." << std::endl;
            std::unique_ptr<CSQLiteTable> upTable = sResult.Get();
            std::cout << "Dumping table: \"" << it->GetTableName() << "\"" << std::endl;
            upTable->serialize(*spArchive);
        }
    }
    else if (sCmd.GetAction().compare(STR_VERIFY) == 0)
    {
        std::shared_ptr<CArchieve> spArchive(new CBinaryFileArchive(sCmd.GetSaveset(), CBinaryFileArchive::READ));
        std::vector<std::shared_ptr<CSQLiteTable> > vecTables;
        std::uint64_t ui64TableCount = 0;
        spArchive->load(ui64TableCount);
        for (std::uint64_t i = 0; i < ui64TableCount; ++i)
        {
            std::shared_ptr<CSQLiteTable> spTable(std::make_shared<CSQLiteTable>());
            spTable->deserialize(*spArchive);
            spTable->print(std::cout, sCmd.GetShowCount());
            vecTables.push_back(spTable);
        }
    }
    else
    {
        throw command_line_parse_error("Invalid operation type");
    }
}

int main(int argc, char *argv[])
{
    int iExitCode = OK;
    try
    {
        sqlite2file_main(argc, argv);
    }
    catch (const command_line_parse_error& ex)
    {
        std::cerr << "ERROR: " << ex.what() << std::endl << std::endl;
        std::cerr << "Use -help option for details." << std::endl;
        iExitCode = ERROR;        
    }
    catch (const std::exception& ex)
    {
        std::cerr << "ERROR: " << ex.what() << std::endl;
        iExitCode = ERROR;
    }

    return iExitCode;
}
