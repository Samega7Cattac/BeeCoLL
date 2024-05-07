message(STATUS "Configuring Nodes")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        Node.cpp
        SerialInterface.cpp 
        Serial.cpp
        NetworkNode.cpp
)
