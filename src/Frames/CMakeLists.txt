message(STATUS "Configuring Frames")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        Frame.cpp Frame.hh
        ExtendedTransmitStatus.cpp ExtendedTransmitStatus.hh
        ExplicitRxIndicator.cpp ExplicitRxIndicator.hh
        TransmitRequest.cpp TransmitRequest.hh
        LocalATCommandRequest.cpp LocalATCommandRequest.hh
        LocalATCommandResponse.cpp LocalATCommandResponse.hh
        RecievePacket.cpp RecievePacket.hh)
