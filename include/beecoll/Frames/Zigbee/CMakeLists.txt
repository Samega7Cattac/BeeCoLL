# Add the header files to the lib
target_sources(${LIBRARY_TARGET_NAME}
    PUBLIC FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/include FILES
            Frame.hh
)
