#include "test.h"

#include <iostream>
#include "test_DataContainer.h"

namespace tests {
int test_main(int argc, const char* argv[])
{
	auto test = test_class::Test::init();
	test->test_operators();
	return 0;
}
}
