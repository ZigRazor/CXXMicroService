
cmake_minimum_required(VERSION 3.16)

project (CXXMicroservice VERSION "0.0.1" LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory (third_party/libzmq)


option(LOGGER "Enable the LOG4CXX logger" OFF)

set(THIRD_PARTY_INCLUDE_DIR 
    third_party/cppzmq
    third_party/json/single_include/nlohmann
    )

set(THIRD_PARTY_LIB
    libzmq
    )

file( GLOB SRC_FILES "src/*.cpp" "src/*.hpp" )

message ( ERROR "SRC_FILES: ${SRC_FILES}" )

option(DEBUG "Enable Debug" OFF)
if(DEBUG)
	add_compile_options(
		-O0  #no optimization
		-g   #generate debug info
	)

endif(DEBUG)

if(LOGGER)
    add_compile_definitions(MS_LOGGER)    
    add_subdirectory (third_party/logging-log4cxx)
    set(THIRD_PARTY_INCLUDE_DIR 
        ${THIRD_PARTY_INCLUDE_DIR}
        third_party/logging-log4cxx/src/main/include
    )
    set(THIRD_PARTY_LIB
        ${THIRD_PARTY_LIB}
        log4cxx
    )
endif()

message(STATUS ${THIRD_PARTY_INCLUDE_DIR})

add_library(    ${PROJECT_NAME} SHARED
                ${SRC_FILES}
                )

target_include_directories( ${PROJECT_NAME} PUBLIC 
                            ${THIRD_PARTY_INCLUDE_DIR}
                            include/
                            )

target_link_libraries(  ${PROJECT_NAME} PUBLIC
                        ${THIRD_PARTY_LIB}
                        ssl
                        z
                        crypto
                        )

add_subdirectory("examples")