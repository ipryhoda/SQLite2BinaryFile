#ifndef  _SQLLITE_ARCHIEVE_H
#define  _SQLLITE_ARCHIEVE_H

#include <ostream>
#include <istream>

using namespace std;

template<typename char_t>
class CArchieve
{
	CArchieve(const CArchieve&);
	CArchieve& operator=(const CArchieve&);
protected:
	CArchieve() {}
public:
	typedef basic_istream<char_t> istream_t;
	typedef basic_ostream<char_t> ostream_t;
	virtual ~CArchieve() {}
	virtual istream_t& deserialize(istream_t& stream) = 0;
	virtual ostream_t& serialize(ostream_t& stream) = 0;
};

#endif // _SQLLITE_ARCHIEVE_H