message(STATUS "Configuring Zigbee Device Object specfic frames")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        ZDOPayload.cpp
        ZDODeviceAnnounce.cpp
        ZDOPermitJoining.cpp
        ZDOSimpleDescriptorRequest.cpp
        ZDOSimpleDescriptorResponse.cpp
)
