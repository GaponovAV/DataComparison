#pragma once

#include "DataContainer.h"
#include "DistributionHelper.h"

template <typename T, typename Alloc = std::allocator<T>>
class DataSetContainer
{
public:
	DataSetContainer(const size_t& size = 0, bool isRand = false)
	    : m_params(rand_distribution_helper::createDefaultParams<T>())
	    , m_dataR1(std::vector<T, Alloc>(size))
	    , m_dataR2(std::vector<T, Alloc>(size))
	{
		if (!isRand || size == 0) {
			return;
		}

		m_dataR1 = rand_distribution_helper::generateByParams({
		                                                          generateDevice()
		                                                        , generateGen()
		                                                        , generateDistribution()
		                                                        , size
		});
		m_dataR1 = rand_distribution_helper::generateByParams({
		                                                          generateDevice()
		                                                        , generateGen()
		                                                        , generateDistribution()
		                                                        , size
		});
	};
	DataSetContainer(const std::vector<T, Alloc> &dataR1, const std::vector<T, Alloc> &dataR2)
	    : m_params(rand_distribution_helper::createDefaultParams<T>())
	    , m_dataR1(dataR1)
	    , m_dataR2(dataR2)
	{
	}

	void generateDevice() {
		m_params.rDevice = rand_distribution_helper::randDevice();
	};
	void generateGen() {
		m_params.gen = rand_distribution_helper::randGen();
	}
	void generateDistribution(const T& begin, const T& end) {
		m_params.dist = std::normal_distribution<T>(begin, end);
	}

	DataSetContainer<T, Alloc> dataR1() const {
		return m_dataR1;
	}

	DataSetContainer<T, Alloc> dataR2() const {
		return m_dataR2;
	}

private:
	rand_distribution_helper::Params<T> m_params;
	DataContainer<T, Alloc> m_dataR1;
	DataContainer<T, Alloc> m_dataR2;
};
