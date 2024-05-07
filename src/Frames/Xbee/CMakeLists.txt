message(STATUS "Configuring Xbee Frames")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        Frame.cpp
        ExtendedTransmitStatus.cpp
        ExplicitRxIndicator.cpp
        TransmitRequest.cpp
        LocalATCommandRequest.cpp
        LocalATCommandResponse.cpp
        RecievePacket.cpp
)
