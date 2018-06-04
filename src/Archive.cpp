#include "Archive.h"

CBinaryFileArchive::CBinaryFileArchive(const std::string& sFilePath, MODE eMode)
{
    m_stream.exceptions(std::basic_fstream<char>::failbit | std::basic_fstream<char>::badbit);
    if (eMode == READ)
    {
        m_stream.open(sFilePath, ios::binary | ios::in);
    }
    else
    {
        m_stream.open(sFilePath, ios::binary | ios::out);
    }
}

CBinaryFileArchive::~CBinaryFileArchive()
{
    if (m_stream.is_open())
    {
        m_stream.close();
    }
}

void CBinaryFileArchive::load(std::vector<std::uint8_t>& vecBytes)
{
    std::uint64_t iSize = 0;
    m_stream.read(reinterpret_cast<char*>(&iSize), sizeof(iSize));
    if (iSize > 0)
    {
        vecBytes.resize(iSize);
        m_stream.read(reinterpret_cast<char*>(&vecBytes[0]), iSize);
    }
}

void CBinaryFileArchive::store(const std::vector<std::uint8_t>& vecBytes)
{
    const std::uint64_t iSize = vecBytes.size();
    m_stream.write(reinterpret_cast<const char*>(&iSize), sizeof(iSize));
    if (iSize > 0)
    {
        m_stream.write(reinterpret_cast<const char*>(&vecBytes[0]), vecBytes.size());
    }
}

void CBinaryFileArchive::load(std::string& sData)
{
    std::uint64_t iSize = 0;
    m_stream.read(reinterpret_cast<char*>(&iSize), sizeof(iSize));
    if (iSize > 0)
    {
        sData.resize(iSize);
        m_stream.read(reinterpret_cast<char*>(&sData[0]), iSize);
    }
}

void CBinaryFileArchive::store(const std::string& sData)
{
    const std::uint64_t iSize = sData.size();
    m_stream.write(reinterpret_cast<const char*>(&iSize), sizeof(iSize));
    if (iSize > 0)
    {
        m_stream.write(reinterpret_cast<const char*>(&sData[0]), iSize);
    }
}

void CBinaryFileArchive::load(std::uint64_t& ui64Data)
{
    m_stream.read(reinterpret_cast<char*>(&ui64Data), sizeof(ui64Data));
}

void CBinaryFileArchive::store(const std::uint64_t& ui64Data)
{
    m_stream.write(reinterpret_cast<const char*>(&ui64Data), sizeof(ui64Data));
}

void CBinaryFileArchive::load(std::int64_t& i64Data)
{
    m_stream.read(reinterpret_cast<char*>(&i64Data), sizeof(i64Data));
}

void CBinaryFileArchive::store(const std::int64_t& i64Data)
{
    m_stream.write(reinterpret_cast<const char*>(&i64Data), sizeof(i64Data));
}

void CBinaryFileArchive::load(double& dValue)
{
    m_stream.read(reinterpret_cast<char*>(&dValue), sizeof(dValue));
}

void CBinaryFileArchive::store(const double& dValue)
{
    m_stream.write(reinterpret_cast<const char*>(&dValue), sizeof(dValue));
}

void CBinaryFileArchive::load(std::uint8_t& ui8Data)
{
    m_stream.read(reinterpret_cast<char*>(&ui8Data), sizeof(ui8Data));
}

void CBinaryFileArchive::store(const std::uint8_t& ui8Data)
{
    m_stream.write(reinterpret_cast<const char*>(&ui8Data), sizeof(ui8Data));
}

void CBinaryFileArchive::load(vector<string>& vec)
{
    std::uint64_t iSize = 0;
    m_stream.read(reinterpret_cast<char*>(&iSize), sizeof(iSize));
    for (size_t i = 0; i < iSize; ++i)
    {
        string strValue;

        load(strValue);
        vec.push_back(std::move(strValue));
    }
}

void CBinaryFileArchive::store(const vector<string>& vec)
{
    const std::uint64_t iSize = vec.size();
    m_stream.write(reinterpret_cast<const char*>(&iSize), sizeof(iSize));
    if (iSize > 0)
    {
        for (auto & it : vec)
        {
            store(it);
        }
    }
}
