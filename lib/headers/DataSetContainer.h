#pragma once

#include <iostream>
#include <cassert>
#include <optional>

#include "DataContainer.h"
#include "DistributionHelper.h"

template <typename T>
class DataSetContainer
{
public:
	DataSetContainer(const size_t& size = 0, bool isRand = false)
	    : m_params(rand_distribution_helper::createDefaultParams<T>())
	    , m_dataR1(std::vector<T>(size))
	    , m_dataR2(std::vector<T>(size))
	{
		if (!isRand || size == 0) {
			return;
		}

		m_dataR1 = rand_distribution_helper::generateByParams(createParams(size));
		m_dataR1 = rand_distribution_helper::generateByParams(createParams(size));
	};
	DataSetContainer(const std::vector<T> &dataR1, const std::vector<T> &dataR2)
	    : m_dataR1(dataR1)
	    , m_dataR2(dataR2)
	{
		assert(m_dataR1.size() == m_dataR2.size());
	}
	DataSetContainer(const DataContainer<T> &dataR1, const DataContainer<T> &dataR2)
	    : m_dataR1(dataR1)
	    , m_dataR2(dataR2)
	{
		assert(m_dataR1.size() == m_dataR2.size());
	}

	void generateGen(std::optional<rand_distribution_helper::Params<T>> &opParams) {
		if (opParams) {
			opParams.value().gen = rand_distribution_helper::randGen();
			return;
		}
		m_params.gen = rand_distribution_helper::randGen();
	}
	void generateDistribution(std::optional<rand_distribution_helper::Params<T>> &opParams, const T& begin, const T& end) {
		if (opParams) {
			opParams.value().dist = std::normal_distribution<T>(begin, end);
			return;
		}
		m_params.dist = std::normal_distribution<T>(begin, end);
	}

	DataContainer<T> dataR1() const {
		return m_dataR1;
	}
	DataContainer<T> dataR2() const {
		return m_dataR2;
	}
	void setDataR1(const DataContainer<T> &newDataR1) {
		m_dataR1 = newDataR1;
		calculateAllFTPN();
	}
	void setDataR2(const DataContainer<T> &newDataR2) {
		m_dataR2 = newDataR2;
		calculateAllFTPN();
	}

	template<typename Container>
	void append(bool isFirst, const Container& value) {
		if (isFirst) {
			m_dataR1 << value;
		} else {
			m_dataR2 << value;
		}
	}
	template<typename Container>
	void append(const Container& value) {
		m_dataR1 << value;
		m_dataR2 << value;
	}

	uint calculateTP() const
	{
		return true_positive;
	}
	uint calculateTN() const
	{
		return true_negative;
	}
	uint calculateFP() const
	{
		return false_positive;
	}
	uint calculateFN() const
	{
		return false_negative;
	}
	double calculateTPR() const
	{
		double tpr = true_positive / (true_positive + false_negative);
		return tpr;
	}
	double calculateFPR() const
	{
		double FPR = false_positive / (false_positive + true_negative);
		return FPR;
	}
	double calculatePPV() const
	{
		double ppv = true_positive/(true_positive+false_negative);
		return ppv;
	}
	double calculateNPV() const
	{
		double npv = true_negative/(true_negative+false_negative);
		return npv;
	}
	double calculateFDR() const
	{
		double fdr = false_positive/(false_positive+true_negative);
		return fdr;
	}
	double calculateFOR() const
	{
		double foR = false_negative/(false_negative+true_negative);
		return foR;
	}
	double calculateACC() const
	{
		double acc = (true_positive + true_negative)/(true_positive+true_negative+ false_positive + false_negative);
		return acc;
	}
	double calculateF1() const
	{
		double acc = (2 * true_positive)/(2*true_positive + false_positive + false_negative);
		return acc;
	}
	double calculateCorrelation () const
	{
		uint sum1 = std::accumulate(m_dataR1.begin(), m_dataR1.end(), 0);
		uint sum2 = std::accumulate(m_dataR2.begin(), m_dataR2.end(), 0);
		double aver1 = sum1 / m_dataR1.size();
		double aver2 = sum2 / m_dataR2.size();
		double upside = 0;
		double downside1 = 0;
		double downside2 = 0;
		for (int i = 0; i < m_dataR2.size(); ++i)
		{
			upside += (m_dataR1.at(i) - aver1)*(m_dataR2.at(i) - aver2);
			downside1 += std::pow(m_dataR1.at(i) - aver1, 2);
			downside2 += std::pow(m_dataR2.at(i) - aver2, 2);
		}
		downside1 = std::sqrt(downside1);
		downside2 = std::sqrt(downside2);
		double downside = downside1 * downside2;
		return upside / downside;
	}
	double calculateEuclideanDistance() const
	{
		double sum = 0;
		for (int i = 0; i < m_dataR2.size(); ++i)
		{
			sum += std::pow(m_dataR1.at(i) - m_dataR2.at(i), 2);
		}
		return std::sqrt(sum);
	}
	void calculateAllFTPN()
	{
		uint true_positive_in(0), true_negative_in(0), false_positive_in(0),
		        false_negative_in(0);
		
		for (int j = 0; j < m_dataR1.size(); ++j)
		{
			for (int i = 0; i < m_dataR2.size(); ++i)
			{
				bool isEqual = m_dataR1.at(i) == m_dataR2.at(j);
				if (m_dataR1.at(i) == 0)
				{
					if (isEqual)
						true_positive_in++;
					else
						false_negative_in++;
				}
				else
				{
					if (isEqual)
						true_negative_in++;
					else
						false_positive_in++;
				}
			}
		}
		
		true_positive = true_positive_in;
		true_negative = true_negative_in;
		false_positive = false_positive_in;
		false_negative = false_negative_in;
		assert(isEmpty());
	}
	
	bool isEmpty() const
	{
		if (true_positive == 0 || true_negative == 0 || false_positive == 0 || false_negative == 0)
		{
			return true;
		}
		return false;
	}

private:
	rand_distribution_helper::Params<T> createParams(const size_t &size) {
		auto opParams = std::make_optional<rand_distribution_helper::Params<T>>();
		generateDistribution(opParams, 0, size);
		opParams.value().size = size;
		return opParams.value_or(rand_distribution_helper::createDefaultParams<T>());
	}

	rand_distribution_helper::Params<T> m_params;
	DataContainer<T> m_dataR1;
	DataContainer<T> m_dataR2;

	uint true_positive = 0;
	uint true_negative = 0;
	uint false_positive = 0;
	uint false_negative = 0;
};
