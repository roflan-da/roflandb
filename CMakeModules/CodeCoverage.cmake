find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)

if (UNIX)

    IF(NOT LCOV_PATH)
        MESSAGE(WARNING "lcov not found!")
    ENDIF() # NOT LCOV_PATH

    IF(NOT GENHTML_PATH)
        MESSAGE(WARNING "genhtml not found!")
    ENDIF() # NOT GENHTML_PATH

    add_custom_target(coverage
            COMMAND "${CMAKE_BINARY_DIR}/bin/tests"
            COMMAND ${LCOV_PATH} --directory ${CMAKE_BINARY_DIR} --capture --output-file ${CMAKE_BINARY_DIR}/coverage.info
            COMMAND ${GENHTML_PATH} -o ${CMAKE_BINARY_DIR}/coverage/ ${CMAKE_BINARY_DIR}/coverage.info
            )

endif (UNIX)