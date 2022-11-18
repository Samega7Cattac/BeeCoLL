message(STATUS "Configuring AT Commands")

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
        ATCommand.cpp ATCommand.hh
        MY.cpp MY.hh
        ND.cpp ND.hh
        NT.cpp NT.hh
        SH.cpp SH.hh
        SL.cpp SL.hh)
