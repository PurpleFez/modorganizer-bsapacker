set(DirectXTex_INCLUDE_DIR ${DirectXTex_DIR}/include)
set(DirectXTex_LIBRARY_DIR ${DirectXTex_DIR}/lib)
set(DirectXTex_VERSION ${PC_modorganizer_VERSION})

mark_as_advanced(DirectXTex_FOUND DirectXTex_DIR DirectXTex_INCLUDE_DIR DirectXTex_LIBRARY_DIR DirectXTex_VERSION)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(DirectXTex
    REQUIRED_VARS DirectXTex_DIR DirectXTex_INCLUDE_DIR DirectXTex_LIBRARY_DIR
    VERSION_VAR DirectXTex_VERSION
)

if(DirectXTex_FOUND)
    set(DirectXTex_INCLUDE_DIRS ${modorganizer_INCLUDE_DIR})
endif()
