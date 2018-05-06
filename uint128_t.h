#pragma once

#include <cstdint>

struct uint128_t final
{
	uint128_t() = default;

	constexpr uint128_t(const uint64_t high_, const uint64_t low_) : high(high_), low(low_) {}

	constexpr uint128_t(const uint64_t v) : high(0), low(v) {}
	constexpr uint128_t(const uint32_t v) : high(0), low(v) {}
	constexpr uint128_t(const uint16_t v) : high(0), low(v) {}
	constexpr uint128_t(const uint8_t v) : high(0), low(v) {}

	//! fixme NOW explicit от intX_t + explicit operator intX_t
	//! fixme NOW explicit operator int128_t

	constexpr uint128_t(const bool v) : high(0), low(v) {}

	explicit constexpr operator uint64_t() const { return low; }
	explicit constexpr operator uint32_t() const { return static_cast<uint32_t>(low); }
	explicit constexpr operator uint16_t() const { return static_cast<uint16_t>(low); }
	explicit constexpr operator uint8_t() const { return static_cast<uint8_t>(low); }

	explicit constexpr operator bool() const { return low || high; }

	uint64_t high;
	uint64_t low;
};

inline constexpr bool operator<(const uint128_t l, const uint128_t r)
{
	return l.high < r.high || (l.high == r.high && l.low < r.low);
}

inline constexpr bool operator<=(const uint128_t l, const uint128_t r)
{
	return l.high < r.high || (l.high == r.high && l.low <= r.low);
}

inline constexpr bool operator>(const uint128_t l, const uint128_t r)
{
	return l.high > r.high || (l.high == r.high && l.low > r.low);
}

inline constexpr bool operator>=(const uint128_t l, const uint128_t r)
{
	return l.high > r.high || (l.high == r.high && l.low >= r.low);
}

inline constexpr bool operator==(const uint128_t l, const uint128_t r)
{
	return l.low == r.low && l.high == r.high;
}

inline constexpr bool operator!=(const uint128_t l, const uint128_t r)
{
	return l.low != r.low || l.high != r.high;
}

inline constexpr uint128_t operator~(const uint128_t v)
{
	return uint128_t{~v.high, ~v.low};
}

inline constexpr uint128_t operator&(const uint128_t l, const uint128_t r)
{
	return uint128_t{l.high & r.high, l.low & r.low};
}

inline constexpr uint128_t operator|(const uint128_t l, const uint128_t r)
{
	return uint128_t{l.high | r.high, l.low | r.low};
}

inline constexpr uint128_t operator^(const uint128_t l, const uint128_t r)
{
	return uint128_t{l.high ^ r.high, l.low ^ r.low};
}

inline constexpr uint128_t operator<<(const uint128_t v, const unsigned s)
{
	if (s >= 64)
	{
		return {v.low << (s - 64), 0};
	}
	return {v.high << s | v.low >> (64 - s), v.low << s};
}

inline constexpr uint128_t operator>>(const uint128_t v, const unsigned s)
{
	if (s >= 64)
	{
		return {0, v.high >> (s - 64)};
	}
	return {v.high >> s, v.high << (64 - s) | v.low >> s};
}

inline constexpr uint128_t operator+(const uint128_t l, const uint128_t r)
{
	uint128_t result{l.high + r.high, l.low + r.low};
	if (result.low < l.low)
	{
		++result.high;
	}
	return result;
}

inline constexpr uint128_t operator-(const uint128_t l, const uint128_t r)
{
	uint128_t result{l.high - r.high, l.low - r.low};
	if (result.low > l.low)
	{
		--result.high;
	}
	return result;
}

inline constexpr uint128_t operator*(const uint128_t l, const uint128_t r)
{
	return uint128_t{l.high * r.low + l.low * r.high + (l.low >> 32) * (r.low >> 32), (l.low & 0xffffffff) * (r.low & 0xffffffff)} +
		((uint128_t{0, (l.low >> 32) * (r.low & 0xffffffff)} + uint128_t{0, (r.low >> 32) * (l.low & 0xffffffff)}) << 32);
}

/*
inline constexpr uint128_t operator/(const uint128_t l, const uint128_t r)
{
	//! \todo implement
	return {};
}

inline constexpr uint128_t operator%(const uint128_t l, const uint128_t r)
{
	//! \todo implement
	return {};
}
*/

inline constexpr uint128_t & operator++(uint128_t & v)
{
	++v.low;
	if (!v.low)
	{
		++v.high;
	}
	return v;
}

inline constexpr uint128_t & operator--(uint128_t & v)
{
	if (!v.low)
	{
		--v.high;
	}
	--v.low;
	return v;
}

inline constexpr uint128_t operator++(uint128_t & v, int)
{
	uint128_t r = v;
	++v;
	return r;
}

inline constexpr uint128_t operator--(uint128_t & v, int)
{
	uint128_t r = v;
	--v;
	return r;
}

inline constexpr uint128_t operator+(const uint128_t v)
{
	return v;
}

inline constexpr uint128_t operator-(const uint128_t v)
{
	//! fixme NOW а что должно быть?
	return v;
}

inline constexpr uint128_t & operator&=(uint128_t & l, const uint128_t r)
{
	l.high &= r.high;
	l.low &= r.low;
	return l;
}

inline constexpr uint128_t & operator|=(uint128_t & l, const uint128_t r)
{
	l.high |= r.high;
	l.low |= r.low;
	return l;
}

inline constexpr uint128_t & operator^=(uint128_t & l, const uint128_t r)
{
	l.high ^= r.high;
	l.low ^= r.low;
	return l;
}

inline constexpr uint128_t & operator<<=(uint128_t & v, const unsigned s)
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

inline constexpr uint128_t & operator>>=(uint128_t & v, const unsigned s)
{
	if (s >= 64)
	{
		v.low = v.high >> (s - 64);
		v.high = 0;
	}
	else
	{
		v.low = v.high << (64 - s) | v.low >> s;
		v.high >>= s;
	}
	return v;
}

inline constexpr uint128_t & operator+=(uint128_t & l, const uint128_t r)
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

inline constexpr uint128_t & operator-=(uint128_t & l, const uint128_t r)
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

inline constexpr uint128_t & operator*=(uint128_t & l, const uint128_t r)
{
	l = l * r;
	return l;
}

/*
inline constexpr uint128_t & operator/=(uint128_t & l, const uint128_t r)
{
	//! \todo implement
	return l;
}

inline constexpr uint128_t & operator%=(uint128_t & l, const uint128_t r)
{
	//! \todo implement
	return l;
}
*/