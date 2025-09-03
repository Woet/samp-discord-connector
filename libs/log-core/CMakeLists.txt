cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0091 NEW)
project(samp-log-core VERSION 0.4)

if (NOT LOGCORE_VERSION) # allow version override
	set(LOGCORE_VERSION ${PROJECT_VERSION})
endif()

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/libs/cmake")

set(CMAKE_CXX_STANDARD 11) #required for fmt library

if (MSVC)
	set(CMAKE_BUILD_TYPE "" CACHE STRING "" FORCE)
elseif(UNIX)
	# hide non-exported symbols
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
	set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS OFF)

	# link runtime statically
	set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
	add_link_options(
		"-static-libgcc"
		"-static-libstdc++"
	)
endif()

set(LOGCORE_LIBS_DIR "${PROJECT_SOURCE_DIR}/libs")

# -- CONAN
include(cmake/conan.cmake)
function(add_conan_lib pkg_name conan_pkg)
	conan_check(REQUIRED)

	conan_cmake_run(
		REQUIRES ${conan_pkg}
		ARCH x86
		BASIC_SETUP CMAKE_TARGETS
		BUILD missing
	)

	set_target_properties(${pkg_name} PROPERTIES IMPORTED_GLOBAL TRUE)
endfunction()

if(NOT DEFINED CONAN_HAS_FMT)
	add_conan_lib(CONAN_PKG::fmt fmt/7.1.3)
endif()

add_conan_lib(CONAN_PKG::yaml-cpp yaml-cpp/0.7.0)

set(LOGCORE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE INTERNAL "")
add_subdirectory(src)
