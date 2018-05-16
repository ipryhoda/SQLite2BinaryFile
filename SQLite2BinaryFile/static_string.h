
#ifndef _STATIC_STRING_H
#define _STATIC_STRING_H

template<typename char_t> struct TStaticString
{
	const char_t *psz;
	size_t stLength;
};

#define _STATIC_STRING( char_t, Name, Val ) \
	const TStaticString<char_t> Name = { Val, ( sizeof( Val ) / sizeof( char_t ) ) - 1 };

#define STATIC_STRINGA( Name, Val ) _STATIC_STRING( char, Name, Val )
#define STATIC_STRINGW( Name, Val ) _STATIC_STRING( wchar_t, Name, L##Val )
#define STATIC_STRING( char_t, Name, Val ) _STATIC_STRING( char_t, Name, ( std::conditional<std::is_same<char_t, wchar_t>::value, L##Val, Val> ) )

template<typename char_t>
void init(TStaticString<char_t> &statstrThis)
{
	statstrThis.psz = nullptr, statstrThis.stLength = 0;
}

namespace NStaticString {

#ifdef _DEBUG
	template<typename char_t>
	bool is_empty(const TStaticString<char_t> &statstrThis)
	{
		return statstrThis.psz == nullptr && statstrThis.stLength == 0;
	}
#endif // _DEBUG

} // NStaticString

template<typename char_t>
void assign(
	TStaticString<char_t> &statstrThis
	, const char_t *psz
	, size_t stLength
)
{
	assert(NStaticString::is_empty(statstrThis));

	statstrThis.psz = psz, statstrThis.stLength = stLength;
}

template<typename char_t>
void assign(
	TStaticString<char_t> &statstrThis
	, const TStaticString<char_t> &statstrValue
)
{
	assign(statstrThis, statstrValue.psz, statstrValue.stLength);
}

template<typename char_t>
void move(
	TStaticString<char_t> &statstrTo
	, TStaticString<char_t> &statstrFrom
)
{
	assert(NStaticString::is_empty(statstrTo));

	statstrTo.psz = statstrFrom.psz, statstrFrom.psz = nullptr;
	statstrTo.stLength = statstrFrom.stLength, statstrFrom.stLength = 0;
}

template<typename char_t>
void copy(
	TStaticString<char_t> &statstrTo
	, const TStaticString<char_t> &statstrFrom
)
{
	assert(NStaticString::is_empty(statstrTo));

	statstrTo.psz = statstrFrom.psz;
	statstrTo.stLength = statstrFrom.stLength;
}

template<typename char_t>
void clear(TStaticString<char_t> &statstrThis)
{
	statstrThis.psz = nullptr, statstrThis.stLength = 0;
}

#endif // _STATIC_STRING_H
