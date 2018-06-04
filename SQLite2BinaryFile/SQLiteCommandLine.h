#ifndef  _SQLLITE_COMMAND_LINE_H
#define  _SQLLITE_COMMAND_LINE_H

#include <string>
#include <vector>

class CCommandLine
{
    CCommandLine(const CCommandLine&);
    CCommandLine& operator=(const CCommandLine&);
public:
    CCommandLine(const std::vector<std::string> vecOptions);
    ~CCommandLine();

};

#endif // _SQLLITE_COMMAND_LINE_H