message(STATUS "Configuring Zigbee Frames")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        APDUFrame.cpp
        DataFrame.cpp
)

add_subdirectory(Payload)
