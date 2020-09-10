cmake_minimum_required(VERSION 3.16)

project(bsa_packer_tests)
set(project_type tests)
set(enable_warnings OFF)
set(create_translations OFF)

if(DEFINED DEPENDENCIES_DIR)
    include(${DEPENDENCIES_DIR}/modorganizer_super/cmake_common/project.cmake)
	include(${DEPENDENCIES_DIR}/modorganizer_super/cmake_common/src.cmake)
else()
    include(../../cmake_common/project.cmake)
	include(../../cmake_common/src.cmake)
endif()

target_include_directories(bsa_packer_tests PRIVATE ${BOOST_DI_ROOT}/include ../src)
target_link_directories(bsa_packer_tests PRIVATE ../lib ../src)
target_link_libraries(bsa_packer_tests
	DirectXTex
	bsa_packer)
requires_library(libbsarch)