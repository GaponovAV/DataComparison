project (coreLib)

set(sources
	sources/lib.cpp
	sources/DistributionHelper.cpp
)

set(headers
	headers/DataContainer.h
	headers/DataSetContainer.h
	headers/DistributionHelper.h
)

add_library(${PROJECT_NAME} STATIC ${headers} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/headers)
