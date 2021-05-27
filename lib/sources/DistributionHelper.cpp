#include "DistributionHelper.h"

namespace rand_distribution_helper {

std::random_device randDevice()
{
	return std::random_device{};
}


std::mt19937 randGen()
{
	auto rDevice = randDevice();
	return std::mt19937{rDevice()};
}

template<typename T>
std::normal_distribution<T> generateDistribution(const T &begin, const T &end)
{
	return std::normal_distribution<T>(begin, end);
}

template<typename T>
std::vector<T> generateRandVector(const T &begin, const T &end, const size_t &size)
{
	auto rDist = generateDistribution(begin, end);
	auto rGen = randGen();
	auto result = std::vector<T>(size);
	for (auto it = result.cbegin(); it != result.cend(); ++it) {
		*it = std::round(rDist(rGen));
	}
	return result;
}

template<typename T>
std::vector<T> generateByParams(Params<T> &&params)
{
	auto result = std::vector<T>(params.size);
	for (auto it = result.cbegin(); it != result.cend(); ++it) {
		*it = std::round(params.dist(params.gen));
	}
	return result;
}

template<typename T>
Params<T> createDefaultParams()
{
	Params<T> params;
	params.dist = std::normal_distribution<T>(0, 10);
	params.gen = randGen();
	params.rDevice = randDevice();
	params.size = 0;

	return params;
}

}
