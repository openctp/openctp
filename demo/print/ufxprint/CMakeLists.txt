cmake_minimum_required(VERSION 3.16)

project(ufx)

set(CMAKE_CXX_FLAGS_DEBUG  "-w -Wextra -ggdb -g -pthread -std=c++11")

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_definitions(-DLINUX)
endif()

include_directories(
        ${PROJECT_SOURCE_DIR}/UFX
)

aux_source_directory(${PROJECT_SOURCE_DIR}/UFX SRC)


link_directories(${PROJECT_SOURCE_DIR}/)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/ufxprint.cpp ${SRC})

target_link_libraries(${PROJECT_NAME} t2sdk)