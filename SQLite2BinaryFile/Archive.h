#ifndef  _SQLLITE_ARCHIEVE_H
#define  _SQLLITE_ARCHIEVE_H

#include <vector>
#include <fstream>

using namespace std;

class CArchieve
{
	CArchieve(const CArchieve&);
	CArchieve& operator=(const CArchieve&);
protected:
	CArchieve() {}
public:
	virtual ~CArchieve() {}
	virtual void load(std::vector<std::uint8_t>&) = 0;
	virtual void store(const std::vector<std::uint8_t>&) = 0;

    virtual void load(std::string&) = 0;
    virtual void store(const std::string&) = 0;

    virtual void load(std::uint64_t&) = 0;
    virtual void store(const std::uint64_t&) = 0;

    virtual void load(std::int64_t&) = 0;
    virtual void store(const std::int64_t&) = 0;

    virtual void load(double&) = 0;
    virtual void store(const double&) = 0;

    virtual void load(std::uint8_t&) = 0;
    virtual void store(const std::uint8_t&) = 0;

    virtual void load(vector<string>&) = 0;
    virtual void store(const vector<string>&) = 0;
};

class CBinaryFileArchive : public CArchieve
{
    CBinaryFileArchive(const CBinaryFileArchive&);
    CBinaryFileArchive& operator=(const CBinaryFileArchive&);
public:
    typedef enum
    {
        READ,
        WRITE
    } MODE;

    CBinaryFileArchive(const std::string& sFilePath, MODE eMode);
    ~CBinaryFileArchive();

    virtual void load(std::vector<std::uint8_t>& vecBytes);
    virtual void store(const std::vector<std::uint8_t>& vecBytes);
    virtual void load(std::string& sData);
    virtual void store(const std::string& sData);
    virtual void load(std::uint64_t& ui64Data);
    virtual void store(const std::uint64_t& ui64Data);
    virtual void load(std::int64_t&);
    virtual void store(const std::int64_t&);
    virtual void load(double& dValue);
    virtual void store(const double& dValue);
    virtual void load(std::uint8_t& ui8Data);
    virtual void store(const std::uint8_t& ui8Data);
    virtual void load(vector<string>&);
    virtual void store(const vector<string>&);
private:
    std::basic_fstream<char> m_stream;
};

#endif // _SQLLITE_ARCHIEVE_H