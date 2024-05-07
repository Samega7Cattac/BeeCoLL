target_sources(${LIBRARY_TARGET_NAME}
    PUBLIC FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/include FILES
            Node.hh
            SerialInterface.hh
            Serial.hh
            NetworkNode.hh
)
