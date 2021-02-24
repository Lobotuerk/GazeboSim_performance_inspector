cmake_minimum_required(VERSION 3.10)

project(IgnitionDomePerformanceInspector)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ignition-msgs6 REQUIRED)
find_package(ignition-transport9 REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)

add_executable(performance_metrics
  src/main.cc
)

target_include_directories(performance_metrics PUBLIC
  ${Boost_INCLUDE_DIRS}
)

target_link_libraries(performance_metrics
  ${Boost_LIBRARIES}
  ignition-msgs6::ignition-msgs6
  ignition-transport9::ignition-transport9
)
