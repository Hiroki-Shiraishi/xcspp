cmake_minimum_required(VERSION 3.8)
project(xcspp LANGUAGES CXX)

file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(xcspp STATIC ${sources})

if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

target_compile_features(xcspp PRIVATE cxx_std_17)
if(MSVC)
    target_compile_options(xcspp PRIVATE /W4)
else()
    target_compile_options(xcspp PRIVATE -O2 -Wall)
endif()
target_include_directories(xcspp PUBLIC ${PROJECT_SOURCE_DIR}/include)

if(NOT DEFINED XCSPP_BUILD_TEST)
    if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(XCSPP_BUILD_TEST ON)
    else()
        set(XCSPP_BUILD_TEST OFF)
    endif()
endif()

if(NOT DEFINED XCSPP_BUILD_TOOL)
    if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(XCSPP_BUILD_TOOL ON)
    else()
        set(XCSPP_BUILD_TOOL OFF)
    endif()
endif()

if(XCSPP_BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif()

if(XCSPP_BUILD_TOOL)
    file(GLOB tool_common_sources
        ${PROJECT_SOURCE_DIR}/tool/common/*.cpp)

    foreach(target IN ITEMS xcs xcsr)
        file(GLOB tool_sources
            ${PROJECT_SOURCE_DIR}/tool/${target}/*.cpp)
        add_executable(${target} ${tool_common_sources} ${tool_sources})
        target_compile_features(${target} PRIVATE cxx_std_17)
        if (MSVC)
            target_compile_options(${target} PRIVATE /W4)
        else()
            target_compile_options(${target} PRIVATE -O2 -Wall)
        endif()
        target_include_directories(${target} PRIVATE
            ${PROJECT_SOURCE_DIR}/tool/cxxopts/include
            ${PROJECT_SOURCE_DIR}/tool)
        target_link_libraries(${target} xcspp)
    endforeach()
endif()

export(TARGETS xcspp FILE ${CMAKE_CURRENT_BINARY_DIR}/xcsppConfig.cmake)
