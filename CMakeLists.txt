project(fornax)
set(CMAKE_CXX_STANDARD 14)

include_directories(inc)
include_directories(src)

set(HEADER_FILES
        inc/laniakea/fornax/SMD.hh
        inc/laniakea/fornax/SMDClient.hh
        inc/laniakea/fornax/SMDListener.hh
        inc/laniakea/fornax/SMDParser.hh
        inc/laniakea/fornax/RFC6455.hh
        inc/laniakea/fornax/sha1/sha1.hh
        )

set(SOURCE_FILES
        src/SMD.cc
        src/SMDClient.cc
        src/SMDParser.cc
         )

add_library(fornax STATIC ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(fornax PROPERTIES LINKER_LANGUAGE CXX)

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
target_link_libraries(fornax nlohmann_json::nlohmann_json)
include_directories(${virgo_SOURCE_DIR}/inc)
target_link_libraries(fornax virgo)
