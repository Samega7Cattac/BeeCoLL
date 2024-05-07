message(STATUS "Configuring Zigbee Frames")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        Frame.cpp
)

add_subdirectory(APDU)
