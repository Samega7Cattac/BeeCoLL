message(STATUS "Configuring Zigbee Frames")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE)

add_subdirectory(ZCL)
add_subdirectory(ZDO)

