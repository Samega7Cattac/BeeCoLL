message(STATUS "Configuring Zigbee Cluster Library specfic frames")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        ZCLPayload.cpp ZCLPayload.hh
        ZCLAttribute.cpp ZCLAttribute.hh
        ZCLWriteAttributeRequest.cpp ZCLWriteAttributeRequest.hh
        ZCLAttributeReport.cpp ZCLAttributeReport.hh)