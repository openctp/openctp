cmake_minimum_required(VERSION 3.15)

project(ctpcmd LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CTPAPI
if(WIN32)
    set(CTPAPI_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/CTPAPI_Win64")
    set(CTPAPI_MD_LIB "${CTPAPI_ROOT}/thostmduserapi_se.lib")
    set(CTPAPI_TD_LIB "${CTPAPI_ROOT}/thosttraderapi_se.lib")
elseif(UNIX AND NOT APPLE)
    set(CTPAPI_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/CTPAPI_Linux")
    set(CTPAPI_MD_LIB "${CTPAPI_ROOT}/thostmduserapi_se.so")
    set(CTPAPI_TD_LIB "${CTPAPI_ROOT}/thosttraderapi_se.so")
elseif(APPLE)
    set(CTPAPI_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/CTPAPI_MacOS")
    set(CTPAPI_MD_LIB "${CTPAPI_ROOT}/libthostmduserapi_se.a")
    set(CTPAPI_TD_LIB "${CTPAPI_ROOT}/libthosttraderapi_se.a")
endif()

# -------------------------- Include --------------------------
include_directories(
    ${CTPAPI_ROOT}
    ${CMAKE_CURRENT_SOURCE_DIR}/CLI
    ${CMAKE_CURRENT_SOURCE_DIR}/nlohmann
    ${CMAKE_CURRENT_SOURCE_DIR}/TinyXML2
)

# -------------------------- Source Code --------------------------
# ctpprice
set(CTPPRICE_SRCS
    ctpprice.cpp
    TinyXML2/tinyxml2.cpp
)

# -------------------------- Compile --------------------------
add_executable(ctpprice ${CTPPRICE_SRCS})

# -------------------------- Link --------------------------
target_link_libraries(ctpprice
    ${CTPAPI_MD_LIB}
)
