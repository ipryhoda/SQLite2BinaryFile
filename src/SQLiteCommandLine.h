#ifndef  _SQLLITE_COMMAND_LINE_H
#define  _SQLLITE_COMMAND_LINE_H

#include <string>
#include <vector>
#include <map>

#define STR_ACTION      "action"
#define STR_XML_FILE    "xmlfile"
#define STR_SAVESET     "saveset"
#define STR_SHOW        "show"
#define STR_SERIALIZE   "serialize"
#define STR_VERIFY      "verify"
#define STR_SOURCE      "source"
#define STR_HELP        "help"

bool IsHelp(const std::string& strArg);

class command_line_parse_error : public std::runtime_error
{
public:
    command_line_parse_error(const std::string& sMsg) : std::runtime_error(sMsg)  {}
    ~command_line_parse_error() {}
};

class CSQLiteCommandLine
{
    CSQLiteCommandLine(const CSQLiteCommandLine&);
    CSQLiteCommandLine& operator=(const CSQLiteCommandLine&);
public:

    CSQLiteCommandLine(const std::vector<std::string>& vecOptions);
    ~CSQLiteCommandLine();

    void Parse();

    std::string GetAction() const;

    std::string GetSaveset() const;
    std::string GetSource() const;
    std::string GetSchema() const;
    size_t GetShowCount() const;
private:
    std::map<std::string, std::string> m_handled;
    std::vector<std::string> m_vecOptions;
};

#endif // _SQLLITE_COMMAND_LINE_H