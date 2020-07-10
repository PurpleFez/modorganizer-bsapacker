cmake_minimum_required(VERSION 3.16)

project(bsa_packer_tests)
set(project_type tests)
set(enable_warnings OFF)
set(create_translations OFF)
if(DEFINED DEPENDENCIES_DIR)
	include(${DEPENDENCIES_DIR}/modorganizer_super/cmake_common/project.cmake)
else()
	include(../cmake_common/project.cmake)
endif()
add_subdirectory(tests)

find_package(Qt5Concurrent REQUIRED)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		../src
		${BOOST_DI_ROOT}/include)
target_link_directories(${PROJECT_NAME}
	PRIVATE
		lib
		src)
target_link_libraries(${PROJECT_NAME}
	Qt5::Concurrent
	DirectXTex)
requires_library(libbsarch)

# Add include from the original src:
target_include_directories(${PROJECT_NAME} PRIVATE src)


project(bsa_packer)
set(project_type plugin)
set(enable_warnings OFF)
set(create_translations ON)

if(DEFINED DEPENDENCIES_DIR)
	include(${DEPENDENCIES_DIR}/modorganizer_super/cmake_common/project.cmake)
else()
	include(../cmake_common/project.cmake)
endif()
add_subdirectory(src)

find_package(Qt5Concurrent REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ${BOOST_DI_ROOT}/include)
target_link_directories(${PROJECT_NAME} PRIVATE lib)
target_link_libraries(${PROJECT_NAME}
	Qt5::Concurrent
	DirectXTex)
requires_library(libbsarch)
target_compile_definitions(bsa_packer PRIVATE BSAPACKER_LIBRARY)

target_link_libraries(bsa_packer_tests bsa_packer)