#include "test_DataContainer.h"

#include <iostream>
#include <math.h>
#include <cassert>

#include "../lib/headers/DataSetContainer.h"

namespace {

#define ASSERT(flag)                                                             \
    if (!(flag)) {                                                               \
        std::cout << "ASSERT: " << __FUNCTION__ << " " <<__LINE__ << std::endl;  \
        assert(false);                                                           \
    } else {                                                                     \
        std::cout << "PASSED: " << __FUNCTION__ << std::endl;                    \
    }

#define VERIFY(flag)                                                             \
    if ((flag)) {                                                               \
        std::cout << "ASSERT: " << __FUNCTION__ << " " <<__LINE__ << std::endl;  \
        assert(false);                                                           \
    } else {                                                                     \
        std::cout << "PASSED: " << __FUNCTION__ << std::endl;                    \
    }

#define COMPARE(one, next, msg)                                         \
    if (one != next) {                                                  \
        ASSERT(false);                                                  \
        std::cout << "FAILED! " << msg << std::endl;                    \
    } else {                                                            \
        std::cout << "PASSED: " << __FUNCTION__ << msg << std::endl;    \
    }

template <typename T>
void test_operator_helper(const std::vector<T> &inputData)
{
	DataContainer<T> data(inputData);
	COMPARE(data, inputData, "constructor from vector");

	DataContainer<T> test_operator;
	ASSERT(test_operator.size() == 0);
	test_operator << inputData;
	COMPARE(test_operator, inputData, "operator << (append) vector");

	DataContainer<T> test_data(data);
	COMPARE(test_data, inputData, "Copy constructor");
}

template <typename T>
void test_calculateTP(const DataSetContainer<T> & container)
{
	VERIFY(container.calculateTP() == 0);
}

template <typename T>
void test_calculateTN(const DataSetContainer<T> & container)
{
	VERIFY(container.calculateTN() == 0);
}

template <typename T>
void test_calculateFP(const DataSetContainer<T> & container)
{
	VERIFY(container.calculateFP() == 0);
}

template <typename T>
void test_calculateFN(const DataSetContainer<T> & container)
{
	VERIFY(container.calculateFN() == 0);
}

template <typename T>
void test_calculateTPR(const DataSetContainer<T> & container)
{
	VERIFY(container.calculateTPR() == 0);
}

template <typename T>
void test_calculateFPR(const DataSetContainer<T> & container)
{
	VERIFY(container.calculateFPR() == 0);
}

template <typename T>
void test_calculatePPV(const DataSetContainer<T> & container)
{
	VERIFY(container.calculatePPV() == 0);
}

template <typename T>
void test_calculateNPV(const DataSetContainer<T> & container)
{
	VERIFY(container.calculateNPV() == 0);
}

template <typename T>
void test_calculateFDR(const DataSetContainer<T> & container)
{
	VERIFY(container.calculateFDR() == 0);
}

template <typename T>
void test_calculateFOR(const DataSetContainer<T> & container)
{
	VERIFY(container.calculateFOR() == 0);
}

template <typename T>
void test_calculateACC(const DataSetContainer<T> & container)
{
	VERIFY(container.calculateACC() == 0);
}

template <typename T>
void test_calculateF1(const DataSetContainer<T> & container)
{
	VERIFY(container.calculateF1() == 0);
}

template <typename T>
void test_calculateCorrelation(const DataSetContainer<T> & container)
{
	VERIFY(container.calculateCorrelation() == 0);
}

template <typename T>
void test_calculateEuclideanDistance(const DataSetContainer<T> & container)
{
	VERIFY(container.calculateEuclideanDistance() == 0);
}

template <typename T>
void test_all_calculation(const DataSetContainer<T> & container)
{
	ASSERT(container.dataR1().size() == 0);
	ASSERT(container.dataR2().size() == 0);
	ASSERT(container.isEmpty());
	test_calculateTP(container);
	test_calculateTN(container);
	test_calculateFP(container);
	test_calculateFN(container);
	test_calculateTPR(container);
	test_calculateFPR(container);
	test_calculatePPV(container);
	test_calculateNPV(container);
	test_calculateFDR(container);
	test_calculateFOR(container);
	test_calculateACC(container);
	test_calculateF1(container);
	test_calculateCorrelation(container);
	test_calculateEuclideanDistance(container);
}

}

namespace test_structs {

test_Data test_Data::create(const std::vector<double> &doubleVector, const std::vector<char> &charVector, const std::vector<int> &intVector) {
	auto testData = test_Data();
	testData.m_doubleVector = doubleVector;
	testData.m_charVector = charVector;
	testData.m_intVector = intVector;
	
	return testData;
}

test_Data test_Data::create(const std::vector<double> &vector) {
	auto testData = test_Data();
	testData.m_doubleVector = vector;
	return testData;
}

test_Data test_Data::create(const std::vector<char> &vector) {
	auto testData = test_Data();
	testData.m_charVector = vector;
	return testData;
}

test_Data test_Data::create(const std::vector<int> &vector) {
	auto testData = test_Data();
	testData.m_intVector = vector;
	return testData;
}

}

namespace test_function {

template<typename ...Args>
test_structs::test_Data init(Args&&... args)
{
	return test_structs::test_Data::create(args...);
}

}

namespace test_class {

void Test::test_operators() {
	ASSERT(m_data.m_doubleVector && m_data.m_charVector && m_data.m_intVector);

	if (m_data.m_doubleVector) {
		test_operator_helper<double>(m_data.m_doubleVector.value());
	}
	
	if (m_data.m_charVector) {
		test_operator_helper<char>(m_data.m_charVector.value());
	}
	
	if (m_data.m_intVector) {
		test_operator_helper<int>(m_data.m_intVector.value());
	}
}

void Test::test_base()
{
	
}

void Test::test_constructor()
{
	
}

void Test::runAll()
{
	auto dataSet = DataSetContainer<double>(m_data.m_doubleVector.value()
	                                      , m_data.m_doubleVector.value());
	test_all_calculation(dataSet);
}

void Test::init(const std::istream &stream)
{
	
}

std::shared_ptr<Test> Test::init() {
	const auto vectorSize = 10;
	std::vector<int> intVector(vectorSize);
	std::vector<char> charVector(vectorSize);
	std::vector<double> doubleVector(vectorSize);
	
	for (auto index = 0; index < vectorSize; ++index) {
		intVector[index] = index;
		charVector[index] = index +'0';
		doubleVector[index] = pow(index / vectorSize, 2);
	}
	
	const auto testData = test_function::init(doubleVector, charVector, intVector);
	
	auto test = std::make_shared<Test>();
	test->m_data = testData;
	return test;
}

}
