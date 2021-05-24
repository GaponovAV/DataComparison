project (tests)

set(headers
	test_DataContainer.h
)
set(sources
	tests_main.cpp
)
add_library(${PROJECT_NAME} ${sources} ${headers})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE coreLib)
