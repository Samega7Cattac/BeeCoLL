cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20
    CACHE STRING "Cpp standard.")

project(BeeCoLL)

set(LIBRARY_TARGET_NAME "beecoll"
    CACHE STRING "Library target name.")

set(STATIC_LIBRARY OFF
    CACHE BOOL "Build static library.")

if (STATIC_LIBRARY EQUAL ON)
    message(STATUS "Build: Static")
    add_library(${LIBRARY_TARGET_NAME} STATIC)
else()
    message(STATUS "Build: Shared")
    add_library(${LIBRARY_TARGET_NAME} SHARED)
endif()

add_subdirectory(src)


# Delete later
set(TEST_EXECUTABLE_TARGET_NAME "test")
add_executable(${TEST_EXECUTABLE_TARGET_NAME} main.cpp)
target_link_libraries(${TEST_EXECUTABLE_TARGET_NAME}
    PUBLIC ${LIBRARY_TARGET_NAME})
target_include_directories(${TEST_EXECUTABLE_TARGET_NAME}
    PRIVATE
        ./src/)

install(
    TARGETS ${LIBRARY_TARGET_NAME}
    EXPORT "${LIBRARY_TARGET_NAME}Config"
    DESTINATION lib
    INCLUDES DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

install(EXPORT "${LIBRARY_TARGET_NAME}Config"
        FILE "${LIBRARY_TARGET_NAME}Config.cmake"
        NAMESPACE beecoll::
        DESTINATION cmake)

install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
    DESTINATION include/beecoll
    FILES_MATCHING
    PATTERN "*.hh")