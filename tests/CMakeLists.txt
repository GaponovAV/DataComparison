project (tests)

set(headers
	test_DataContainer.h
	test.h
)

set(sources
	test_DataContainer.cpp
	tests_main.cpp
)

add_library(${PROJECT_NAME} STATIC ${sources} ${headers})
