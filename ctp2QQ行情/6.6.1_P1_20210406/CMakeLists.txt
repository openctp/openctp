cmake_minimum_required(VERSION 2.8)

set(mdapi thostmduserapi_se_6.6.1_P1_20210406)
project(${mdapi})

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(boost_include E:/boost_1_73_0)
  set(boost_lib E:/boost_1_73_0/stage/lib)
else()
  set(boost_include /usr/local/include)
  set(boost_lib /usr/local/lib)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  add_definitions(-D ISLIB -D LIB_MD_API_EXPORT -D V6_6_1_P1)
else()
  add_compile_options(-std=c++11 -pthread)
endif()

include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/.. ${boost_include})
link_directories(${boost_lib})

add_library(${mdapi} SHARED ../FtdcMdApiImpl.cpp)
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  target_link_libraries(${mdapi} -lpthread -lboost_system -lboost_thread)
endif()
set_target_properties(${mdapi} PROPERTIES OUTPUT_NAME "thostmduserapi_se")
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
