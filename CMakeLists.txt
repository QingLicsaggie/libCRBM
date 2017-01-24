project(libCRBM)

cmake_minimum_required(VERSION 3.0)

ENABLE_TESTING()

cmake_policy(SET CMP0042 OLD)

set(EXECUTABLE_OUTPUT_PATH       ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH          ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_VERBOSE_MAKEFILE       OFF)


if(APPLE)
  set(CMAKE_CXX_FLAGS_DEBUG        "-g")
  set(CMAKE_CXX_FLAGS_RELEASE      "-g")
  set(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3")
else(APPLE)
  set(CMAKE_CXX_FLAGS_DEBUG        "-g -fPIC -std=c++0x")
  set(CMAKE_CXX_FLAGS_RELEASE      "-g -fPIC -std=c++0x")
  set(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3")
endif(APPLE)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED filesystem system)

add_subdirectory(src/crbm)

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/src/crbm/
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/crbm
  CONFIGURATIONS Release Debug
  PATTERN "*.cpp" EXCLUDE
  PATTERN "*.txt" EXCLUDE
  )

option(LIBCRBM_TESTS   "Compile test cases" OFF)
option(LIBCRBM_VERBOSE "Verbose mode"       OFF)

if(LIBCRBM_TESTS)
  add_subdirectory(tests)
endif(LIBCRBM_TESTS)
