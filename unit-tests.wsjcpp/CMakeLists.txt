cmake_minimum_required(VERSION 3.0)

project(unit-tests)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${unit-tests_SOURCE_DIR})

set (WSJCPP_LIBRARIES "")
set (WSJCPP_INCLUDE_DIRS "")
set (WSJCPP_SOURCES "")

# Sources

# wsjcpp-core:v0.0.4
list (APPEND WSJCPP_INCLUDE_DIRS "../src.wsjcpp/wsjcpp_core/")
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/wsjcpp_core/wsjcpp_core.cpp")
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/wsjcpp_core/wsjcpp_core.h")
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/wsjcpp_core/unit_tests.cpp")
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/wsjcpp_core/unit_tests.h")
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/wsjcpp_core/unit_tests_main.cpp")

# nlohmann/json
list (APPEND WSJCPP_INCLUDE_DIRS "../src.wsjcpp/nlohmann_json/")
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/nlohmann_json/json.hpp")

# wsjcpp-yaml
list (APPEND WSJCPP_SOURCES "../src/wsjcpp_geoip.h")
list (APPEND WSJCPP_SOURCES "../src/wsjcpp_geoip.cpp")

# include header dirs
list (APPEND WSJCPP_INCLUDE_DIRS "../src")
list (APPEND WSJCPP_INCLUDE_DIRS "src")

list (APPEND WSJCPP_SOURCES "./src/unit_test_parser_ip_api_com.h")
list (APPEND WSJCPP_SOURCES "./src/unit_test_parser_ip_api_com.cpp")

# required-pkg-config
## CURL
FIND_PACKAGE(CURL)
IF(CURL_FOUND)
   list (APPEND WSJCPP_INCLUDE_DIRS ${CURL_INCLUDE_DIR})
   list (APPEND WSJCPP_LIBRARIES ${CURL_LIBRARIES})
ELSE(CURL_FOUND)
   MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
ENDIF(CURL_FOUND)


include_directories(${WSJCPP_INCLUDE_DIRS})

add_executable ("unit-tests" ${WSJCPP_SOURCES})

target_link_libraries("unit-tests" -lpthread ${WSJCPP_LIBRARIES} )

install(
    TARGETS
        "unit-tests"
    RUNTIME DESTINATION
        /usr/bin
)