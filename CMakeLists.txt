cmake_minimum_required(VERSION 3.20)

project(
    sphincs_plus_zero
    DESCRIPTION         "Arm Cortex-M0 implementation of digital signing algorithm SPHINCS+"
    LANGUAGES           C CXX
)

set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Target definition
set(CMAKE_SYSTEM_NAME       Generic)
set(CMAKE_SYSTEM_PROCESSOR  ARM)

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


set(CMAKE_C_COMPILER            ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT} CACHE INTERNAL "C Compiler")
set(CMAKE_CXX_COMPILER          ${TOOLCHAIN_BIN_DIR}/g++${TOOLCHAIN_EXT} CACHE INTERNAL "CXX Compiler")
set(CMAKE_C_COMPILER_ID         GNU)
set(CMAKE_CXX_COMPILER_ID       GNU)
set(CMAKE_C_COMPILER_FORCED     TRUE)
set(CMAKE_CXX_COMPILER_FORCED   TRUE)

#---------------------------------------------------------------------------------------
# Set compiler/linker flags
#---------------------------------------------------------------------------------------

# Object build options
# -O0                       No optimizations, reduce compilation time and make debugging produce the expected results.
# -g                        Produce debugging information.
# -march=armv6-m            Specify ARMv6-M as the target architecture since STM32G0B1RE uses a Cortex-M0+.
# -mcpu=cortex-m0plus       Specify target processor.
# -mthumb                   Generate thumb instructions.
# -mfloat-abi=soft          Causes GCC to generate output containing library calls for floating-point operations.
# -Wall -Wextra             Print all warnings.
# -Wno-override-init        Do not warn when an initiliazed field is overriden.
# -Wshadow                  Warn whenever a local variable or type declaration shadows another variable.
# -Werror                   Make all warnings into hard errors.

set(SOURCES_DIR             "${CMAKE_SOURCE_DIR}/src")
set(EXTERNAL_SOURCES_DIR    "lib")

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${SOURCES_DIR}
)

# Linking options
# --specs=nano.specs            Link with newlib-nano.
# --specs=nosys.specs           No syscalls, provide empty implementations for the POSIX system calls.
# -nostartfiles                 Do not use standard system startup files.
# -T </path/to/linker-script>   Custom linking script for development board.


set(EXECUTABLE      ${PROJECT_NAME}.elf)
set(LINKER_SCRIPT   "STM32G0B1RE.ld")


add_executable(${EXECUTABLE}
    ${SOURCES_DIR}/main.c
    ${SOURCES_DIR}/startup.c
    ${SOURCES_DIR}/drivers/io.c
    ${SOURCES_DIR}/drivers/uart.c
    ${SOURCES_DIR}/drivers/rng.c
    ${SOURCES_DIR}/common/ring_buffer.c
    ${SOURCES_DIR}/common/utils.c
    ${SOURCES_DIR}/common/address.c
    ${SOURCES_DIR}/common/crypto.c
)

target_compile_options(
    ${EXECUTABLE}
    PRIVATE
        -march=armv6-m
        -mcpu=cortex-m0plus
        -mthumb
        -mfloat-abi=soft
        -O0
        -g
        -Werror
        -Wall
        -Wextra
        -Wno-override-init
        -DDISABLE_ENUM_STRINGS
        -DDISABLE_TRACE
        -DHASH_SHA3
)


target_link_options(
    ${EXECUTABLE}
    PRIVATE
        -specs=nano.specs
        -nostartfiles
        -T${SOURCES_DIR}/${LINKER_SCRIPT}
        -Xlinker -Map=${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.map
    )

target_link_directories(
    ${EXECUTABLE}
    PRIVATE ${EXTERNAL_SOURCES_DIR}/XKCP/armv6-m
)

target_link_libraries(
    ${EXECUTABLE}
    c
    nosys
    XKCP
)

add_custom_target(
    flash
    COMMAND openocd -f interface/stlink.cfg -f target/stm32g0x.cfg -c "program ${EXECUTABLE} verify reset exit"
    COMMENT "Flash firmware onto the connected development board"
)

# External dependencies
include(FetchContent)

FetchContent_Declare(
  printf
  GIT_REPOSITORY https://github.com/mpaland/printf
  GIT_TAG        v4.0.0 # release-4.0.0
)

FetchContent_MakeAvailable(printf)
