project (core)

set(headers
	headers/core.h
)

set(sources
	sources/core.cpp
)

add_library(${PROJECT_NAME} ${sources} ${headers})

target_include_directories( ${PROJECT_NAME}
	PUBLIC ${PROJECT_SOURCE_DIR}/headera
)

target_link_libraries(${PROJECT_NAME} PRIVATE coreLib tests)
