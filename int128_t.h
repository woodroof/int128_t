#pragma once

#include <cstdint>

struct int128_t final
{
	int128_t() = default;

	constexpr int128_t(const int64_t high_, const uint64_t low_) : high(high_), low(low_) {}

	constexpr int128_t(const int64_t v) : high(v < 0 ? 0xfffffffffffffffflu : 0), low(v) {}
	constexpr int128_t(const int32_t v) : high(v < 0 ? 0xfffffffffffffffflu : 0), low(~v) {}
	constexpr int128_t(const int16_t v) : high(v < 0 ? 0xfffffffffffffffflu : 0), low(~v) {}
	constexpr int128_t(const int8_t v) : high(v < 0 ? 0xfffffffffffffffflu : 0), low(~v) {}

	constexpr int128_t(const uint64_t v) : high(0), low(v) {}
	constexpr int128_t(const uint32_t v) : high(0), low(v) {}
	constexpr int128_t(const uint16_t v) : high(0), low(v) {}
	constexpr int128_t(const uint8_t v) : high(0), low(v) {}

	constexpr int128_t(const bool v) : high(0), low(v) {}

	//! fixme NOW explicit operator (u)intX_t
	//! fixme NOW explicit operator uint128_t

	explicit constexpr operator bool() const { return low || high; }

	int64_t high;
	uint64_t low;
};

inline constexpr bool operator<(const int128_t l, const int128_t r)
{
	return l.high < r.high || (l.high == r.high && l.low < r.low);
}

inline constexpr bool operator<=(const int128_t l, const int128_t r)
{
	return l.high < r.high || (l.high == r.high && l.low <= r.low);
}

inline constexpr bool operator>(const int128_t l, const int128_t r)
{
	return l.high > r.high || (l.high == r.high && l.low > r.low);
}

inline constexpr bool operator>=(const int128_t l, const int128_t r)
{
	return l.high > r.high || (l.high == r.high && l.low >= r.low);
}

inline constexpr bool operator==(const int128_t l, const int128_t r)
{
	return l.low == r.low && l.high == r.high;
}

inline constexpr bool operator!=(const int128_t l, const int128_t r)
{
	return l.low != r.low && l.high != r.high;
}

inline constexpr int128_t operator~(const int128_t v)
{
	return int128_t{~v.high, ~v.low};
}

inline constexpr int128_t operator&(const int128_t l, const int128_t r)
{
	return int128_t{l.high & r.high, l.low & r.low};
}

inline constexpr int128_t operator|(const int128_t l, const int128_t r)
{
	return int128_t{l.high | r.high, l.low | r.low};
}

inline constexpr int128_t operator^(const int128_t l, const int128_t r)
{
	return int128_t{l.high ^ r.high, l.low ^ r.low};
}

inline constexpr int128_t operator<<(const int128_t v, const unsigned s)
{
	if (s >= 64)
	{
		return {static_cast<int64_t>(v.low) << (s - 64), 0};
	}
	return {v.high << s | static_cast<int64_t>(v.low >> (64 - s)), v.low << s};
}

inline constexpr int128_t operator>>(const int128_t v, const unsigned s)
{
	if (s >= 64)
	{
		return {v.high >> s, static_cast<uint64_t>(v.high >> (s - 64))};
	}
	return {v.high >> s, v.high << (64 - s) | v.low >> s};
}

inline constexpr int128_t operator+(const int128_t l, const int128_t r)
{
	int128_t result{l.high + r.high, l.low + r.low};
	if (result.low < l.low)
	{
		++result.high;
	}
	return result;
}

inline constexpr int128_t operator-(const int128_t l, const int128_t r)
{
	int128_t result{l.high - r.high, l.low - r.low};
	if (result.low > l.low)
	{
		--result.high;
	}
	return result;
}

inline constexpr int128_t operator*(const int128_t l, const int128_t r)
{
	return int128_t{
			static_cast<int64_t>(static_cast<uint64_t>(l.high) * r.low + l.low * static_cast<uint64_t>(r.high) + (l.low >> 32) * (r.low >> 32)),
			(l.low & 0xffffffff) * (r.low & 0xffffffff)} +
		((int128_t{0, (l.low >> 32) * (r.low & 0xffffffff)} + int128_t{0, (r.low >> 32) * (l.low & 0xffffffff)}) << 32);
}

/*
inline constexpr int128_t operator/(const int128_t l, const int128_t r)
{
	//! \todo implement
	return l;
}

inline constexpr int128_t operator%(const int128_t l, const int128_t r)
{
	//! \todo implement
	return l;
}
*/

inline constexpr int128_t & operator++(int128_t & v)
{
	++v.low;
	if (!v.low)
	{
		++v.high;
	}
	return v;
}

inline constexpr int128_t & operator--(int128_t & v)
{
	if (!v.low)
	{
		--v.high;
	}
	--v.low;
	return v;
}

inline constexpr int128_t operator++(int128_t & v, int)
{
	int128_t r = v;
	++v;
	return r;
}

inline constexpr int128_t operator--(int128_t & v, int)
{
	int128_t r = v;
	--v;
	return r;
}

inline constexpr int128_t operator+(const int128_t v)
{
	return v;
}

inline constexpr int128_t operator-(const int128_t v)
{
	int128_t result{~v.high, ~v.low};
	++result;
	return result;
}

inline constexpr int128_t & operator&=(int128_t & l, const int128_t r)
{
	l.high &= r.high;
	l.low &= r.low;
	return l;
}

inline constexpr int128_t & operator|=(int128_t & l, const int128_t r)
{
	l.high |= r.high;
	l.low |= r.low;
	return l;
}

inline constexpr int128_t & operator^=(int128_t & l, const int128_t r)
{
	l.high ^= r.high;
	l.low ^= r.low;
	return l;
}

inline constexpr int128_t & operator<<=(int128_t & v, const unsigned s)
{
	if (s >= 64)
	{
		v.high = v.low << (s - 64);
		v.low = 0;
	}
	else
	{
		v.high = v.high << s | v.low >> (64 - s);
		v.low <<= s;
	}
	return v;
}

inline constexpr int128_t & operator>>=(int128_t & v, const unsigned s)
{
	if (s >= 64)
	{
		v.low = v.high >> (s - 64);
	}
	else
	{
		v.low = v.high << (64 - s) | v.low >> s;
	}
	v.high >>= s;
	return v;
}

inline constexpr int128_t & operator+=(int128_t & l, const int128_t r)
{
	const uint64_t low = l.low;
	l.low += r.low;
	l.high += r.high;
	if (l.low < low)
	{
		++l.high;
	}
	return l;
}

inline constexpr int128_t & operator-=(int128_t & l, const int128_t r)
{
	const uint64_t low = l.low;
	l.low -= r.low;
	l.high -= r.high;
	if (l.low > low)
	{
		--l.high;
	}
	return l;
}

inline constexpr int128_t & operator*=(int128_t & l, const int128_t r)
{
	l = l * r;
	return l;
}

/*
inline constexpr int128_t & operator/=(int128_t & l, const int128_t r)
{
	//! \todo implement
	return l;
}

inline constexpr int128_t & operator%=(int128_t & l, const int128_t r)
{
	//! \todo implement
	return l;
}
*/