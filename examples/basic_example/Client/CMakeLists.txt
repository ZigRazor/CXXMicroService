set(EXAMPLE_NAME test_client) 

file( GLOB SRC_FILES "*.cpp" "*.hpp" )

add_executable(    ${EXAMPLE_NAME}
                ${SRC_FILES}
                )

target_include_directories( ${EXAMPLE_NAME}  PUBLIC 
                            ${THIRD_PARTY_INCLUDE_DIR}
                            include/
                            )

target_link_libraries(  ${EXAMPLE_NAME}  PUBLIC
                        ${THIRD_PARTY_LIB}
                        ${PROJECT_NAME}
                        )