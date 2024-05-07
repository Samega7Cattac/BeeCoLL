# Shows a configuration message for this folder
message(STATUS "\tConfiguring Dependencies")

include(FetchContent)

FetchContent_Declare(
    serial
    GIT_REPOSITORY "https://github.com/oncontroltech/serial.git"
    GIT_TAG main
)

FetchContent_MakeAvailable(serial)
FetchContent_GetProperties(serial)

add_dependencies(${LIBRARY_TARGET_NAME} serial)

target_link_directories(${LIBRARY_TARGET_NAME}
    PRIVATE
        ${serial_BINARY_DIR}
)

target_include_directories(${LIBRARY_TARGET_NAME}
    PRIVATE
        ${serial_SOURCE_DIR}/include
)

target_link_libraries(${LIBRARY_TARGET_NAME}
    PRIVATE
        serial
)
