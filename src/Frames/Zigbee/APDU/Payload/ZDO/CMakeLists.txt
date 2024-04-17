message(STATUS "Configuring Zigbee Device Object specfic frames")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        ZDOPayload.cpp ZDOPayload.hh
        ZDOSimpleDescriptorRequest.cpp ZDOSimpleDescriptorRequest.hh)