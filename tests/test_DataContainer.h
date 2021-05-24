#pragma once

#include "../lib/headers/DataContainer.h"

#include <optional>

namespace test_structs {

struct test_Data
{
	std::optional<std::vector<double>> m_doubleVector;
	std::optional<std::vector<char>> m_charVector;
	std::optional<std::vector<int>> m_intVector;

	static test_Data create(const std::vector<double> &doubleVector
	                      , const std::vector<char> &charVector
	                      , const std::vector<int> &intVector) {
		auto testData = test_Data();
		testData.m_doubleVector = doubleVector;
		testData.m_charVector = charVector;
		testData.m_intVector = intVector;

		return testData;
	};
	static test_Data create(const std::vector<double> &vector) {
		auto testData = test_Data();
		testData.m_doubleVector = vector;
		return testData;
	};
	static test_Data create(const std::vector<char> &vector) {
		auto testData = test_Data();
		testData.m_charVector = vector;
		return testData;
	};
	static test_Data create(const std::vector<int> &vector) {
		auto testData = test_Data();
		testData.m_intVector = vector;
		return testData;
	};
	
};

}

namespace test_function {

template<typename ...Args>
test_structs::test_Data init(const Args&... args) {
	const auto testDataResult = test_structs::test_Data::create(args...);
}

}

namespace test_class {
class Test {
	void test_operators();
	void test_base();
	void test_constructor();
};
}
