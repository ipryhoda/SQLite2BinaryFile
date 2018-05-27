#ifndef  _SQLLITE_ARCHIEVE_H
#define  _SQLLITE_ARCHIEVE_H

#include <vector>
#include <ostream>
#include <istream>

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

    virtual void load(double&) = 0;
    virtual void store(const double&) = 0;

    virtual void load(std::uint8_t&) = 0;
    virtual void store(const std::uint8_t&) = 0;
};

template<typename char_t>
class CBinaryFileArchive : public CArchieve
{
    CBinaryFileArchive(const CBinaryFileArchive&);
    CBinaryFileArchive& operator=(const CBinaryFileArchive&);
public:
    CBinaryFileArchive(const std::string& sFilePath) : CBinaryFileArchive<char_t>(),  m_stream(sFilePath, ios::binary) {}
    ~CBinaryFileArchive() {}

    virtual void load(std::vector<std::uint8_t>& vecBytes)
    {
        std::uint64_t iSize = 0;
        m_stream.read(reinterpret_cast<char*>(&iSize), sizeof(iSize));
        vecBytes.resize(iSize);
        m_stream.read(reinterpret_cast<char*>(&vecBytes[0]), iSize);
    }

    virtual void store(const std::vector<std::uint8_t>& vecBytes)
    {
        const std::uint64_t iSize = vecBytes.size();
        m_stream.write(reinterpret_cast<const char*>(&iSize), sizeof(iSize));
        m_stream.write(reinterpret_cast<const char*>(&vecBytes[0]), vecBytes.size());
    }

    virtual void load(std::string& sData)
    {
        std::uint64_t iSize = 0;
        m_stream.read(reinterpret_cast<char*>(&iSize), sizeof(iSize));
        sData.resize(iSize);
        m_stream.read(reinterpret_cast<char*>(&sData[0]), iSize);
    }

    virtual void store(std::string& sData)
    {
        const std::uint64_t iSize = sData.size() * sizeof(char_t);
        m_stream.write(reinterpret_cast<const char*>(&iSize), sizeof(iSize));
        m_stream.write(reinterpret_cast<const char*>(&sData[0]), iSize);
    }

    virtual void load(std::uint64_t& ui64Data)
    {
        m_stream.read(reinterpret_cast<char*>(&ui64Data), sizeof(ui64Data));
    }

    virtual void store(const std::uint64_t& ui64Data)
    {
        m_stream.write(reinterpret_cast<const char*>(&ui64Data), sizeof(ui64Data));
    }

    virtual void load(double& dValue)
    {
        m_stream.read(reinterpret_cast<char*>(&dValue), sizeof(dValue));
    }

    virtual void store(const double& dValue)
    {
        m_stream.write(reinterpret_cast<const char*>(&dValue), sizeof(dValue));
    }

    virtual void load(std::uint8_t& ui8Data)
    {
        m_stream.read(reinterpret_cast<char*>(&ui8Data), sizeof(ui8Data));
    }

    virtual void store(const std::uint8_t& ui8Data)
    {
        m_stream.write(reinterpret_cast<const char*>(&ui8Data), sizeof(ui8Data));
    }
private:
    std::ofstream m_stream;    
};

#endif // _SQLLITE_ARCHIEVE_H