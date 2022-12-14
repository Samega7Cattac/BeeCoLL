message(STATUS "Configuring Nodes")

find_package(serial REQUIRED)

target_link_libraries(${LIBRARY_TARGET_NAME}
    PRIVATE
        serial)

target_link_directories(${LIBRARY_TARGET_NAME}
    PRIVATE
        serial)

target_include_directories(${LIBRARY_TARGET_NAME}
    PRIVATE
        serial)

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        Node.cpp Node.hh
        SerialInterface.cpp SerialInterface.hh
        Serial.cpp Serial.hh
        Coordinator.cpp Coordinator.hh
        NetworkNode.cpp NetworkNode.hh)