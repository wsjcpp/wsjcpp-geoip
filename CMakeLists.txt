cmake_minimum_required(VERSION 3.0)

project(wsjcpp-geoip)

include(${CMAKE_CURRENT_SOURCE_DIR}/src.wsjcpp/CMakeLists.txt)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${wsjcpp-geoip_SOURCE_DIR})

# Sources

# include header dirs
list (APPEND WSJCPP_INCLUDE_DIRS "src")

list (APPEND WSJCPP_SOURCES "src/wsjcpp_geoip.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_geoip.h")

list (APPEND WSJCPP_SOURCES "src/main.cpp")

include_directories(${WSJCPP_INCLUDE_DIRS})

add_executable (wsjcpp-geoip ${WSJCPP_SOURCES})

target_link_libraries(wsjcpp-geoip ${WSJCPP_LIBRARIES} )

install(
    TARGETS
        wsjcpp-geoip
    RUNTIME DESTINATION
        /usr/bin
)
