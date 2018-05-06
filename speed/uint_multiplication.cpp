#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include "uint128_t.h"

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <sltbench/Bench.h>

std::vector<uint64_t> prepare_data()
{
	boost::random::mt19937 gen;
	boost::random::uniform_int_distribution<uint64_t> dist(
		std::numeric_limits<uint64_t>::min(),
		std::numeric_limits<uint64_t>::max());

	std::vector<uint64_t> result;
	result.reserve(100000 * 4);
	for (size_t i = 0; i < result.capacity(); ++i)
	{
		result.push_back(dist(gen));
	}
	return result;
}

const auto data = prepare_data();

template <typename T>
std::vector<T> prepare_args()
{
	std::vector<T> result;
	result.reserve(data.size() / 2);
	for (size_t i = 0; i < data.size() / 2; ++i)
	{
		T num = data[i * 2];
		num <<= 64;
		num += data[i * 2 + 1];
		result.push_back(num);
	}
	return result;
}

template <typename T>
std::vector<T> & get_result()
{
	static std::vector<T> result(data.size() / 4);
	return result;
}

template <typename T>
void test_function(const std::vector<T> & args, std::vector<T> & result)
{
	for (size_t i = 0, size = args.size() / 2; i < size; ++i)
	{
		result[i] = args[i * 2] * args[i * 2 + 1];
	}
}

const auto my_args = prepare_args<uint128_t>();
auto & my_result = get_result<uint128_t>();

void my_test()
{
	test_function(my_args, my_result);
}

SLTBENCH_FUNCTION(my_test);

void alt_test_function(const std::vector<uint128_t> & args, std::vector<uint128_t> & result)
{
	for (size_t i = 0, size = args.size() / 2; i < size; ++i)
	{
		result[i] = args[i * 2] * args[i * 2 + 1];
	}
}

void alt_test()
{
	alt_test_function(my_args, my_result);
}

SLTBENCH_FUNCTION(alt_test);

const auto boost_args = prepare_args<boost::multiprecision::uint128_t>();
auto & boost_result = get_result<boost::multiprecision::uint128_t>();

void boost_test()
{
	test_function(boost_args, boost_result);
}

SLTBENCH_FUNCTION(boost_test);

const auto native_args = prepare_args<__uint128_t>();
auto & native_result = get_result<__uint128_t>();

void native_test()
{
	test_function<__uint128_t>(native_args, native_result);
}

SLTBENCH_FUNCTION(native_test);

SLTBENCH_MAIN();
