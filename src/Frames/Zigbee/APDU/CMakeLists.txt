message(STATUS "Configuring Zigbee Frames")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        APDUFrame.cpp APDUFrame.hh
        DataFrame.cpp DataFrame.hh)

add_subdirectory(Payload)