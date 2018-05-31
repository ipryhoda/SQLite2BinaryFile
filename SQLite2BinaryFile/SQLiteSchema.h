#ifndef  _SQLLITE_SCHEMA_H
#define  _SQLLITE_SCHEMA_H

//SQLite Header and library
#include "rapidxml/rapidxml.hpp"

#include <string>
#include <vector>

class CSQLiteQuery;
class CSQLiteSchema
{
    CSQLiteSchema(const CSQLiteSchema&);
    CSQLiteSchema& operator=(const CSQLiteSchema&);
public:
    CSQLiteSchema(const std::string& sXmlFile);
    ~CSQLiteSchema();

    void Parse(std::vector<std::shared_ptr<CSQLiteQuery>>&);

private:
    std::string m_strXmlFile;
};


#endif //_SQLLITE_SCHEMA_H