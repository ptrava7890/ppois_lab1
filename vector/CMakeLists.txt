cmake_minimum_required(VERSION 4.0.2)
project(labs)

set(CMAKE_CXX_STANDARD 17)

add_executable(labs
        main.cpp
        Vector3.cpp
)

add_executable(labs_tests
        test.cpp
        Vector3.cpp
)
include(FetchContent)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
set(UTPP_INCLUDE_TESTS_IN_BUILD OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        unittestpp
        URL https://github.com/unittest-cpp/unittest-cpp/archive/refs/tags/v2.0.0.zip
)
FetchContent_MakeAvailable(unittestpp)

target_include_directories(labs_tests PRIVATE "${unittestpp_SOURCE_DIR}")
target_link_libraries(labs_tests PRIVATE UnitTest++)