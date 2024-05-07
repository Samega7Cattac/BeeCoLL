# Shows a configuration message for this folder
message(STATUS "\tConfiguring Dependencies")

include(FetchContent)

FetchContent_Declare(
    serial
    GIT_REPOSITORY "https://github.com/oncontroltech/serial.git"
    GIT_TAG main
)

add_dependencies(${LIBRARY_TARGET_NAME} serial)

FetchContent_MakeAvailable(serial)

target_link_libraries(${LIBRARY_TARGET_NAME}
    PRIVATE
        serial)

target_link_directories(${LIBRARY_TARGET_NAME}
    PRIVATE
        serial)

target_include_directories(${LIBRARY_TARGET_NAME}
    PRIVATE
        serial)
