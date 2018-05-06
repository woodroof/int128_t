#pragma once

#include <limits>

#include "uint128_t.h"

template<>
class std::numeric_limits<uint128_t>
{
	static constexpr bool is_specialized = true;
	static constexpr bool is_signed = false;
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
	static constexpr bool is_modulo = true;
	static constexpr int digits = std::numeric_limits<uint64_t>::digits * 2;
	static constexpr int digits10 = 38;
	static constexpr int max_digits10 = 0;
	static constexpr int radix = 2;
	static constexpr int min_exponent = 0;
	static constexpr int min_exponent10 = 0;
	static constexpr int max_exponent = 0;
	static constexpr int max_exponent10 = 0;
	static constexpr bool traps = std::numeric_limits<uint64_t>::traps;
	static constexpr bool tinyness_before = false;

	static constexpr uint128_t min() { return {0}; }
	static constexpr uint128_t lowest() { return {0}; }
	static constexpr uint128_t max() { return {std::numeric_limits<uint64_t>::max(), std::numeric_limits<uint64_t>::max()}; }
	static constexpr uint128_t epsilon() { return {0}; }
	static constexpr uint128_t round_error() { return {0}; }
	static constexpr uint128_t infinity() { return {0}; }
	static constexpr uint128_t quiet_NaN() { return {0}; }
	static constexpr uint128_t signaling_NaN() { return {0}; }
	static constexpr uint128_t denorm_min() { return {0}; }
};