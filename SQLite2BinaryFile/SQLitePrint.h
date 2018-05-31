#ifndef  _SQLLITE_PRINT_H
#define  _SQLLITE_PRINT_H

#include <ostream>
#include <iomanip>
#include <string>

inline std::ostream& AdjustWeightLeftPrint(std::ostream& stream, const std::string& sValue, std::uint8_t uiWeight = 12)
{
    std::string sToPrint = sValue;
    if (sToPrint.size() >= uiWeight)
    {
        sToPrint = sToPrint.substr(0, uiWeight - 4).append("...");
    }

    stream << std::setw(uiWeight) << std::left << sToPrint;
    return stream;
}

struct centered
{
public:
    centered(const std::string str) : _str(str) {}
    ~centered() {}
    std::string _str;
};

inline std::ostream& operator<< (std::ostream& stream, const centered& str)
{
    std::streamsize w = stream.width();
    if (w > (std::streamsize)str._str.length())
    {
        std::streamsize left = (w + str._str.length()) / 2;
        stream.width(left);
        stream << str._str;
        stream.width(w - left);
        stream << "";
    }
    else
    {
        stream << str._str;
    }

    return stream;
}

#endif //_SQLLITE_PRINT_H