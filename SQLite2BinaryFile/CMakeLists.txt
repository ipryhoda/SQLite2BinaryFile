# CMakeList.txt : CMake project for SQLite2BinaryFile, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.7)

# Add source to this project's executable.
add_executable (sqlite2file "SQLite2BinaryFile.cpp" "SQLite2BinaryFile.h" 
                                "SQLiteQuery.cpp" "SQLiteQuery.h"
                                "SQLiteItem.cpp" "SQLiteItem.h"
                                "SQLiteObject.cpp" "SQLiteObject.h"
                                "SQLiteResult.cpp" "SQLiteResult.h"
                                "SQLiteSchema.cpp" "SQLiteSchema.h"
                                "SQLiteCommandLine.cpp" "SQLiteCommandLine.h"
                                "Archive.cpp" "Archive.h"
                                "SQLite/sqlite3.c" "SQLite/sqlite3.h"
"rapidxml/rapidxml.hpp" "rapidxml/rapidxml_iterators.hpp" "rapidxml/rapidxml_print.hpp" "rapidxml/rapidxml_utils.hpp")

if (WIN32)
add_definitions(-DFOO)
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread" )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl" )
endif()


# TODO: Add tests and install targets if needed.
