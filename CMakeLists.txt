# CMakeList.txt : CMake project for VenomStrike, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project (VenomStrike)

set (CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Build/Libraries)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Build/Libraries)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Build/Binaries)

file(GLOB_RECURSE SOURCES 
    "${PROJECT_SOURCE_DIR}/Framework/Source/*.cpp"
    "${PROJECT_SOURCE_DIR}/Framework/Source/*.h"
)

message(${SOURCES})

# Add source to this project's executable.
add_executable (${PROJECT_NAME} ${SOURCES})

include_directories(external)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/Source
    
    )
 
target_link_directories(${PROJECT_NAME} PUBLIC
)
