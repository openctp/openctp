cmake_minimum_required(VERSION 3.7.1)

project(atpprint)

message(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
message(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 11)

if (MSVC)
  add_definitions(/MP)
  set(CMAKE_COMPILER_CXX_FLAG "${CMAKE_COMPILER_CXX_FLAG}   -std=c++11")
  add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif (MSVC)


file(GLOB_RECURSE DEMO_INCLUDE "${PROJECT_SOURCE_DIR}/ATP/include/*.h")
source_group("atpprint" FILES  ${DEMO_INCLUDE})
AUX_SOURCE_DIRECTORY(. SIMPLE_TRADE_API_DEMO_SRC_LIST)
add_executable(atpprint  ${DEMO_INCLUDE}  ${SIMPLE_TRADE_API_DEMO_SRC_LIST})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
     file(GLOB_RECURSE LINK_SO "${PROJECT_SOURCE_DIR}/ATP/lib/*.lib")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
     file(GLOB_RECURSE LINK_SO "${PROJECT_SOURCE_DIR}/ATP/lib/*.so")
endif()

target_link_libraries(atpprint  ${LINK_SO})
target_include_directories(atpprint PRIVATE ${PROJECT_SOURCE_DIR}/ATP/include/  ${PROJECT_SOURCE_DIR}/ATP/include/trade )
target_compile_options(atpprint PRIVATE $<$<CXX_COMPILER_ID:MSVC>:  /Zi /Od>)
target_link_options(atpprint PRIVATE $<$<CXX_COMPILER_ID:MSVC>: /DEBUG >)

