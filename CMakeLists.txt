cmake_minimum_required(VERSION 2.8.12)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP> $<$<CXX_COMPILER_ID:MSVC>:$<$<CONFIG:RELEASE>:/O2>> $<$<CXX_COMPILER_ID:MSVC>:$<$<CONFIG:RELWITHDEBINFO>:/O2>>)

set(PROJ_NAME bsa_packer)

project(${PROJ_NAME})

set(DEPENDENCIES_DIR CACHE PATH "")

# hint to find qt in dependencies path
list(APPEND CMAKE_PREFIX_PATH ${QT_ROOT}/lib/cmake)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)


# pasted

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5 COMPONENTS Core Concurrent Widgets REQUIRED)

find_package(Qt5LinguistTools)
qt5_create_translation(${PROJ_NAME}_translations_qm ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/${PROJ_NAME}_en.ts)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED)

# MO projects
set(default_project_path "${DEPENDENCIES_DIR}/modorganizer_super")
get_filename_component(${default_project_path} ${default_project_path} REALPATH)

set(project_path "${default_project_path}" CACHE PATH "path to the other mo projects")
set(lib_path "${default_project_path}/../../install/libs")

add_library(${PROJ_NAME} SHARED
	include/bsapacker/IArchiveAutoService.h
	include/bsapacker/IArchiveBuilder.h
	include/bsapacker/IArchiveBuilderFactory.h
	include/bsapacker/IArchiveBuilderHelper.h
	include/bsapacker/IArchiveExtensionService.h
	include/bsapacker/IDummyPluginLogic.h
	include/bsapacker/IDummyPluginService.h
	include/bsapacker/IDummyPluginServiceFactory.h
	include/bsapacker/IEmitsValueChanged.h
	include/bsapacker/IFileWriterService.h
	include/bsapacker/IHideLooseAssetService.h
	include/bsapacker/IModDtoFactory.h
	include/bsapacker/IPackerDialog.h
	include/bsapacker/IPackerDialogFactory.h
	include/bsapacker/ISettingsService.h

	include/bsapacker/GeneralArchiveBuilder.h
	include/bsapacker/ModDtoFactory.h
	include/bsapacker/NullArchiveBuilder.h
	include/bsapacker/TextureArchiveBuilder.h
	include/bsapacker/TexturelessArchiveBuilder.h

	src/NexusId.h
	src/BsaPackerWorker.h
	src/BsaPackerWorker.cpp

	src/ArchiveAutoService.cpp
	src/ArchiveBuildDirector.cpp
	src/ArchiveBuilderFactory.cpp
	src/ArchiveBuilderHelper.cpp
	src/ArchiveExtensionService.cpp
	src/BsaPacker.cpp
	src/BSArchive.cpp
	src/BSArchiveAuto.cpp
	src/BSArchiveEntries.cpp
	src/DummyPluginLogic.cpp
	src/DummyPluginServiceFactory.cpp
	src/Fallout3DummyPluginService.cpp
	src/Fallout4DummyPluginService.cpp
	src/FileWriterService.cpp
	src/GeneralArchiveBuilder.cpp
	src/HideLooseAssetService.cpp
	src/ModContext.cpp
	src/ModDto.cpp
	src/ModDtoFactory.cpp
	src/NewVegasDummyPluginService.cpp
	src/NullArchiveBuilder.cpp
	src/NullDummyPluginService.cpp
	src/NullModDto.cpp
	src/OblivionDummyPluginService.cpp
	src/PackerDialog.cpp
	src/PackerDialogFactory.cpp
	src/SettingsService.cpp
	src/SkyrimDummyPluginService.cpp
	src/SkyrimSEDummyPluginService.cpp
	src/TextureArchiveBuilder.cpp
	src/TexturelessArchiveBuilder.cpp

	${${PROJ_NAME}_translations_qm}
)

add_library(BsaPacker::${PROJ_NAME} ALIAS ${PROJ_NAME})

target_compile_features(${PROJ_NAME} PRIVATE cxx_auto_type)

target_compile_options(${PROJ_NAME} PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

target_include_directories(${PROJ_NAME}
	PUBLIC
	    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	PRIVATE
	    ${BOOST_DI_ROOT}/include
	    ${BOOST_DI_ROOT}/extension/include
	    ${LIBBSARCH_ROOT}
	    ${Boost_INCLUDE_DIRS}
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${default_project_path}/uibase/src
)

target_link_directories(${PROJ_NAME}
	PUBLIC
	    ${lib_path}
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/lib>
		${Boost_LIBRARY_DIRS}
    PRIVATE
        ${LIBBSARCH_ROOT})

message("Default path is: ${default_project_path}")
message("Project path is: ${project_path}")
message("Lib path is: ${lib_path}")
message("packer path is ${CMAKE_SOURCE_DIR}/include/bsapacker")

target_link_libraries(${PROJ_NAME}
	PUBLIC
	    Qt5::Widgets
		Qt5::Concurrent
		Qt5::Gui
		${Boost_LIBRARIES}
		uibase
		libbsarch
		DirectXTex
)

if (MSVC)
  set_target_properties(${PROJ_NAME} PROPERTIES COMPILE_FLAGS "/std:c++latest")
endif()
if (MSVC AND CMAKE_SIZEOF_VOID_P EQUAL 4)
  # 32 bits
  set_target_properties(${PROJ_NAME} PROPERTIES LINK_FLAGS "/LARGEADDRESSAWARE")
endif()

if (NOT "${OPTIMIZE_COMPILE_FLAGS}" STREQUAL "")
  set_target_properties(${PROJ_NAME} PROPERTIES COMPILE_FLAGS_RELWITHDEBINFO ${OPTIMIZE_COMPILE_FLAGS})
endif()
if (NOT "${OPTIMIZE_LINK_FLAGS}" STREQUAL "")
  set_target_properties(${PROJ_NAME} PROPERTIES LINK_FLAGS_RELWITHDEBINFO ${OPTIMIZE_LINK_FLAGS})
endif()

###############
## Installation

install(TARGETS ${PROJ_NAME}
	EXPORT ${PROJ_NAME}-targets
	ARCHIVE DESTINATION libs
	RUNTIME DESTINATION bin/plugins)
install(FILES $<TARGET_PDB_FILE:${PROJ_NAME}>
	DESTINATION pdb)
#install(EXPORT ${PROJ_NAME}-targets
#	FILE BsaPackerTargets.cmake
#	NAMESPACE BsaPacker::
#	DESTINATION libs)

#add_subdirectory(tests)
