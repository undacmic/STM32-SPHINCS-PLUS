cmake_minimum_required(VERSION 3.20)

project(
    sphincs_plus_zero
    DESCRIPTION         "Unit tests definitions for Arm Cortex-M0 implementation of digital signing algorithm SPHINCS+"
)

set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#---------------------------------------------------------------------------------------
# Set toolchain paths
#---------------------------------------------------------------------------------------
set(TOOLCHAIN arm-none-eabi)
if(NOT DEFINED TOOLCHAIN_PREFIX)
    if(CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)
        set(TOOLCHAIN_PREFIX "/usr")
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Darwin)
        set(TOOLCHAIN_PREFIX "/usr/local")
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Windows)
        message(STATUS "Please specify the TOOLCHAIN_PREFIX !\n For example: -DTOOLCHAIN_PREFIX=\"C:/Program Files/GNU Tools ARM Embedded\" ")
    else()
        set(TOOLCHAIN_PREFIX "/usr")
        message(STATUS "No TOOLCHAIN_PREFIX specified, using default: " ${TOOLCHAIN_PREFIX})
    endif()
endif()
set(TOOLCHAIN_BIN_DIR ${TOOLCHAIN_PREFIX}/bin)
set(TOOLCHAIN_INC_DIR ${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/include)
set(TOOLCHAIN_LIB_DIR ${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/lib)

# Set system depended extensions
if(WIN32)
    set(TOOLCHAIN_EXT ".exe" )
else()
    set(TOOLCHAIN_EXT "" )
endif()


set(CMAKE_C_COMPILER            ${TOOLCHAIN_BIN_DIR}/g++${TOOLCHAIN_EXT} CACHE INTERNAL "C Compiler")
set(CMAKE_CXX_COMPILER          ${TOOLCHAIN_BIN_DIR}/g++${TOOLCHAIN_EXT} CACHE INTERNAL "CXX Compiler")
set(CMAKE_C_COMPILER_ID         GNU)
set(CMAKE_CXX_COMPILER_ID       GNU)
set(CMAKE_C_COMPILER_FORCED     TRUE)
set(CMAKE_CXX_COMPILER_FORCED   TRUE)


# External dependencies

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2 # release-1.15.2
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

set(CMAKE_SOURCE_DIR ..)
set(EXTERNAL_SOURCES_DIR ${CMAKE_SOURCE_DIR}/../lib)
set(SPHINCS_SOURCES
    ${CMAKE_SOURCE_DIR}/common/utils.c
    ${CMAKE_SOURCE_DIR}/common/address.c
    ${CMAKE_SOURCE_DIR}/common/crypto.c
)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ../..
)

add_compile_options(
    -fprofile-arcs
    -ftest-coverage
    -Wall
    -Wextra
    -Werror
    -DTEST_SETUP
    -DHASH_SHA3
)

add_link_options(
    -fprofile-arcs
    -ftest-coverage
    -Wall
    -Wextra
    -Werror
    -DTEST_SETUP
    -DHASH_SHA3
)

add_library(sphincs STATIC ${SPHINCS_SOURCES})

add_executable(
    sphincs_test
    ${CMAKE_SOURCE_DIR}/test/main.cpp
    ${CMAKE_SOURCE_DIR}/test/test_utils.cpp
    ${CMAKE_SOURCE_DIR}/test/test_address.cpp
    ${CMAKE_SOURCE_DIR}/test/test_crypto.cpp
    ${SPHINCS_SOURCES}
)

target_link_directories(
    sphincs_test
    PRIVATE ${EXTERNAL_SOURCES_DIR}/XKCP/generic64
)
target_link_libraries(
    sphincs_test
    PRIVATE
        GTest::gtest
        XKCP
)

include(GoogleTest)
gtest_discover_tests(sphincs_test)

include(CTest)
add_test(NAME coverage COMMAND sphincs_test)