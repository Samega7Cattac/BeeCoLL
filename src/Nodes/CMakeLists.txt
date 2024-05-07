message(STATUS "Configuring Nodes")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        Node.cpp Node.hh
        SerialInterface.cpp SerialInterface.hh
        Serial.cpp Serial.hh
        NetworkNode.cpp NetworkNode.hh)
