#pragma once

#include "../lib/headers/DataContainer.h"

#include <optional>
#include <istream>
#include <memory>

namespace test_structs {

struct test_Data
{
	std::optional<std::vector<double>> m_doubleVector;
	std::optional<std::vector<char>> m_charVector;
	std::optional<std::vector<int>> m_intVector;

	static test_Data create(const std::vector<double> &doubleVector
	                      , const std::vector<char> &charVector
	                      , const std::vector<int> &intVector);
	static test_Data create(const std::vector<double> &vector);
	static test_Data create(const std::vector<char> &vector);
	static test_Data create(const std::vector<int> &vector);
};

}

namespace test_function {

template<typename ...Args>
test_structs::test_Data init(Args&&... args);

}

namespace test_class {
class Test {
public:
	void test_operators();;
	void test_base();
	void test_constructor();
	void runAll();

	static void init(const std::istream& stream);
	static std::shared_ptr<Test> init();

private:
	test_structs::test_Data m_data;
};

}
