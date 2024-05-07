message(STATUS "Configuring Zigbee Cluster Library specfic frames")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        ZCLPayload.cpp
        ZCLAttribute.cpp
        ZCLWriteAttributeRequest.cpp
        ZCLAttributeReport.cpp
)
