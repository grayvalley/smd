project(smd)

set(CMAKE_CXX_STANDARD 17)

include_directories(inc)
include_directories(src)

set(HEADER_FILES
        inc/grayvalley/smd/SMD.hh
        inc/grayvalley/smd/SMDClient.hh
        inc/grayvalley/smd/SMDListener.hh
        inc/grayvalley/smd/SMDParser.hh

        )

set(SOURCE_FILES
        src/SMD.cc
        src/SMDClient.cc
        src/SMDParser.cc
        )

add_library(smd STATIC ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(smd PROPERTIES LINKER_LANGUAGE CXX)

include(FetchContent)
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        )
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
    include_directories(${json_SOURCE_DIR})
endif()
target_link_libraries(smd nlohmann_json::nlohmann_json)
include_directories(${core_SOURCE_DIR}/inc)
target_link_libraries(smd core)
