message(STATUS "Configuring Zigbee Device Object specfic frames")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        ZDOPayload.cpp ZDOPayload.hh
        ZDODeviceAnnounce.cpp ZDODeviceAnnounce.hh
        ZDOPermitJoining.cpp ZDOPermitJoining.hh
        ZDOSimpleDescriptorRequest.cpp ZDOSimpleDescriptorRequest.hh
        ZDOSimpleDescriptorResponse.cpp ZDOSimpleDescriptorResponse.hh)