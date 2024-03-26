message(STATUS "Configuring Zigbee Frames")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        ZCLPayload.cpp ZCLPayload.hh
        ZCLWriteAttributeRequest.cpp ZCLWriteAttributeRequest.hh
        ZCLAttributeReport.cpp ZCLAttributeReport.hh)

