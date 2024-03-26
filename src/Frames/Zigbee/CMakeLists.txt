message(STATUS "Configuring Zigbee Frames")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        Frame.cpp Frame.hh)

add_subdirectory(APDU)