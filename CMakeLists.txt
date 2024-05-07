cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20
    CACHE STRING "Cpp standard.")

project(BeeCoLL)

set(LIBRARY_TARGET_NAME "beecoll"
    CACHE STRING "Library target name.")

set(STATIC_LIBRARY OFF
    CACHE BOOL "Build static library.")

# Set to "ON" to debug makefile commands
set (CMAKE_VERBOSE_MAKEFILE ON
     CACHE BOOL "Show makefiles commands on build")

if (STATIC_LIBRARY EQUAL ON)
    message(STATUS "Build: Static")
    add_library(${LIBRARY_TARGET_NAME} STATIC)
else()
    message(STATUS "Build: Shared")
    add_library(${LIBRARY_TARGET_NAME} SHARED)
    target_compile_options(${LIBRARY_TARGET_NAME}
        PRIVATE
            -fPIC)
endif()

message(STATUS "Configuration type: ${CMAKE_BUILD_TYPE}")

# Add extra flags to the compiler
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions("DEBUG")
    target_compile_options(${LIBRARY_TARGET_NAME}
        PRIVATE
            # Increased reliability of backtraces
            -fasynchronous-unwind-tables
            # Store compiler flags in debugging information
            -grecord-gcc-switches
    )

elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${LIBRARY_TARGET_NAME}
        PRIVATE
            # Optimizations
            -O3
            # Run-time buffer overflow detection
            -D_FORTIFY_SOURCE=2
    )
    
    # Check and enable LTO support if possible
    include(CheckIPOSupported)
    check_ipo_supported(RESULT supported OUTPUT error)
    if (supported)
        message(STATUS "IPO / LTO support: enabled")
        set_property(TARGET ${LIBRARY_TARGET_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    else()
        message(STATUS "IPO / LTO support: disabled (<${error}>)")
    endif()
endif()

# Add extra flags to the compiler
target_compile_options(${LIBRARY_TARGET_NAME}
    PRIVATE
        # -Werror
        -Wall
        -Wextra
        -Wpedantic
        # Run-time bounds checking for C++ strings and containers
        -D_GLIBCXX_ASSERTIONS
        # Enable table-based thread cancellation
        -fexceptions
        # No text relocations for shared libraries
        -fpic
        # Increased reliability of stack overflow detection
        -fstack-clash-protection
        # Stack smashing protector
        -fstack-protector-strong
        # Detect and reject underlinking
        -Wl,-z,defs
        # Disable lazy binding
        -Wl,-z,now
        # Read-only segments after relocation
        -Wl,-z,relro
)

if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "64Bit")
    target_compile_options(${LIBRARY_TARGET_NAME}
        PRIVATE
            # Control flow integrity protection
            -fcf-protection
    )
endif ()

# Add include directories for build and install
target_include_directories(${LIBRARY_TARGET_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

add_subdirectory(deps)
add_subdirectory(include/beecoll)
add_subdirectory(src)

###
# INSTALL
###

include(GNUInstallDirs)

install(
    TARGETS ${LIBRARY_TARGET_NAME}
    EXPORT "${LIBRARY_TARGET_NAME}Config"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT "${LIBRARY_TARGET_NAME}Config"
    FILE "${LIBRARY_TARGET_NAME}Config.cmake"
    NAMESPACE beecoll::
    DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake
)

# uninstall target
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY
    )

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
