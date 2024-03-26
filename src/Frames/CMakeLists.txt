message(STATUS "Configuring Frames")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        BaseFrame.cpp BaseFrame.hh)


add_subdirectory(Xbee)
add_subdirectory(Zigbee)
