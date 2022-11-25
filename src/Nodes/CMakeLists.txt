message(STATUS "Configuring Nodes")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        Node.cpp Node.hh
        SerialInterface.cpp SerialInterface.hh
        Coordinator.cpp Coordinator.hh
        NetworkNode.cpp NetworkNode.hh)