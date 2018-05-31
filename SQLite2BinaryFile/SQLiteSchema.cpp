#include "SQLiteSchema.h"
#include "SQLiteQuery.h"

#include <fstream>

CSQLiteSchema::CSQLiteSchema(const std::string& sXmlFile) : m_strXmlFile(sXmlFile)
{
}

CSQLiteSchema::~CSQLiteSchema()
{
}

void CSQLiteSchema::Parse(std::vector<std::shared_ptr<CSQLiteQuery>>& vecSQLQueries)
{
    std::ifstream xmlstream(m_strXmlFile);
    std::vector<char> vecBuffer((std::istreambuf_iterator<char>(xmlstream)), std::istreambuf_iterator<char>());
    vecBuffer.push_back('\0');

    rapidxml::xml_document<> xmldoc;
    rapidxml::xml_node<> * root_node;

    xmldoc.parse<0>(&vecBuffer[0]);
    root_node = xmldoc.first_node("requests");
    for (rapidxml::xml_node<> * pTable = root_node->first_node("table"); pTable; pTable = pTable->next_sibling())
    {
        const auto& pTableName = pTable->first_attribute("name");
        if (pTableName == nullptr)
        {
            throw std::runtime_error("Invalid format of the xml file - missed attribute 'name' for 'table' tag");
        }

        std::vector<std::string> vecFields;
        for (rapidxml::xml_node<> * pField = pTable->first_node("field"); pField; pField = pField->next_sibling())
        {
            const auto& pFieldName = pField->first_attribute("name");
            if (pFieldName)
            {
                vecFields.push_back(pFieldName->value());
            }
            else
            {
                throw std::runtime_error("Invalid format of the xml file - missed attribute 'name' for 'field' tag");
            }
        }

        std::string sSortBy;
        rapidxml::xml_node<> * pSortBy = pTable->first_node("sortby");
        if (pSortBy != nullptr)
        {
            const auto& pFieldName = pSortBy->first_attribute("name");
            if (pFieldName)
            {
                sSortBy = pFieldName->value();
            }
            else
            {
                throw std::runtime_error("Invalid format of the xml file - missed attribute 'name' for 'sortby' tag");
            }
        }

        vecSQLQueries.push_back(std::make_shared<CSQLiteSelectQuery>(pTableName->value(), vecFields, sSortBy));
    }

    return;
}