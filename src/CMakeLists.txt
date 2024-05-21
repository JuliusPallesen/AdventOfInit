find_package(cpr REQUIRED)

add_executable(AdventOfInit AdventOfInit.cpp)

target_link_libraries(AdventOfInit cpr::cpr)