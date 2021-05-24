project (core)

set(sources
	sources/core.cpp
)

add_library(${PROJECT_NAME} ${sources})

target_include_directories( ${PROJECT_NAME}
	PUBLIC ${PROJECT_SOURCE_DIR}/headera
)
