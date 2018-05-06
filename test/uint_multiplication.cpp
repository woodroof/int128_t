#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include "uint128_t.h"

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <gtest/gtest.h>

boost::multiprecision::uint128_t construct(uint64_t high, uint64_t low)
{
	boost::multiprecision::uint128_t num = high;
	num <<= 64;
	num += low;
	return num;
}

//! \fixme NOW нормальная распечатка в случае фейла
TEST(Multiplication, ShouldAddRandomUint128)
{
	boost::random::mt19937 gen;
	boost::random::uniform_int_distribution<uint64_t> dist(
		std::numeric_limits<uint64_t>::min(),
		std::numeric_limits<uint64_t>::max());

	std::vector<uint64_t> data;
	data.reserve(100000 * 4);
	for (size_t i = 0; i < data.capacity(); ++i)
	{
		data.push_back(dist(gen));
	}

	for (size_t i = 0; i < data.size() / 4; ++i)
	{
		const auto my_result = uint128_t{data[i * 4], data[i * 4 + 1]} * uint128_t{data[i * 4 + 2], data[i * 4 + 3]};
		const auto boost_result = construct(data[i * 4], data[i * 4 + 1]) * construct(data[i * 4 + 2], data[i * 4 + 3]);
		EXPECT_EQ(my_result.low, boost_result & 0xfffffffffffffffflu);
		EXPECT_EQ(my_result.high, static_cast<uint64_t>(boost_result >> 64));
	}
}

int main(int argc, char ** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
