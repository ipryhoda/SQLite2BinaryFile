# CMakeList.txt : CMake project for SQLite2BinaryFile, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.7)

# Add source to this project's executable.
add_executable (SQLite2BinaryFile "SQLite2BinaryFile.cpp" "SQLite2BinaryFile.h" 
                                "SQLiteQuery.cpp" "SQLiteQuery.h"
                                "SQLiteItem.cpp" "SQLiteItem.h"
                                "SQLiteObject.cpp" "SQLiteObject.h"
                                "SQLiteResult.cpp" "SQLiteResult.h"
                                "SQLiteSchema.cpp" "SQLiteSchema.h"
                                "Archive.cpp" "Archive.h"
                                "SQLite/sqlite3.c" "SQLite/sqlite3.h"
								"rapidxml/rapidxml.hpp" "rapidxml/rapidxml_iterators.hpp" "rapidxml/rapidxml_print.hpp" "rapidxml/rapidxml_utils.hpp")
add_definitions(-DFOO)

# TODO: Add tests and install targets if needed.
