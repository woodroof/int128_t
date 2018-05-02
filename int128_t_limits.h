#pragma once

#include "int128_t.h"

template<>
class std::numeric_limits<int128_t>
{
	static constexpr bool is_specialized = true;
	static constexpr bool is_signed = true;
	static constexpr bool is_integer = true;
	static constexpr bool is_exact = true;
	static constexpr bool has_infinity = false;
	static constexpr bool has_quiet_NaN = false;
	static constexpr bool has_signaling_NaN = false;
	static constexpr std::float_denorm_style has_denorm = std::denorm_absent;
	static constexpr bool has_denorm_loss = false;
	static constexpr std::float_round_style round_style = std::round_toward_zero;
	static constexpr bool is_iec559 = false;
	static constexpr bool is_bounded = true;
	static constexpr bool is_modulo = std::numeric_limits<int64_t>::is_modulo;
	static constexpr int digits = std::numeric_limits<uint64_t>::digits + std::numeric_limits<int64_t>::digits;
	static constexpr int digits10 = 38;
	static constexpr int max_digits10 = 0;
	static constexpr int radix = 2;
	static constexpr int min_exponent = 0;
	static constexpr int min_exponent10 = 0;
	static constexpr int max_exponent = 0;
	static constexpr int max_exponent10 = 0;
	static constexpr bool traps = std::numeric_limits<int64_t>::traps || std::numeric_limits<uint64_t>::traps;
	static constexpr bool tinyness_before = false;

	static constexpr int128_t min() { return {std::numeric_limits<int64_t>::min(), 0}; }
	static constexpr int128_t lowest() { return {std::numeric_limits<int64_t>::lowest(), 0}; }
	static constexpr int128_t max() { return {std::numeric_limits<int64_t>::max(), std::numeric_limits<uint64_t>::max()}; }
	static constexpr int128_t epsilon() { return {0}; }
	static constexpr int128_t round_error() { return {0}; }
	static constexpr int128_t infinity() { return {0}; }
	static constexpr int128_t quiet_NaN() { return {0}; }
	static constexpr int128_t signaling_NaN() { return {0}; }
	static constexpr int128_t denorm_min() { return {0}; }
};