#pragma once

#include <random>
#include <cmath>

namespace rand_distribution_helper {

template <typename T>
struct Params
{	
	std::random_device rDevice;
	std::mt19937 gen;
	std::normal_distribution<T> dist;
	size_t size;
};

std::random_device randDevice();
std::mt19937 randGen();

template <typename T>
std::normal_distribution<T> generateDistribution(const T& begin, const T& end);

template<typename T>
std::vector<T> generateRandVector(const T& begin, const T&end, const size_t &size);

template<typename T>
std::vector<T> generateByParams(Params<T> &&params);

template <typename T>
Params<T> createDefaultParams();

}
