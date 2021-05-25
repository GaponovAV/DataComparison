#include "test_DataContainer.h"

#include <iostream>
#include <math.h>

namespace {

#define ASSERT(flag)                                                             \
    if (!(flag)) {                                                               \
        std::cout << "ASSERT: " << __FUNCTION__ << " " <<__LINE__ << std::endl;  \
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
