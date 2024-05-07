message(STATUS "Configuring AT Commands")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        ATCommand.cpp
        MY.cpp
        ND.cpp
        NT.cpp
        SH.cpp
        SL.cpp
        NI.cpp
)
