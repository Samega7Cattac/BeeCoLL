message(STATUS "Configurating BeeCoLL")

target_include_directories(${LIBRARY_TARGET_NAME}
    PUBLIC
        .)

add_subdirectory(Frames)

add_subdirectory(ATCommands)

add_subdirectory(Nodes)
