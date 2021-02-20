cmake_minimum_required(VERSION 3.10)

project(IgnitionDomePerformanceInspector)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(GAZEBO_11 "Use the Ignition dependencies for Gazebo 11" OFF)
option(IGN_DOME "Use the Ignition dependencies for Ignition Dome" OFF)

if(GAZEBO_11 AND IGN_DOME)
  message(FATAL_ERROR "Both GAZEBO_11 and IGN_DOME were set. Please set one to ON.")
elseif(GAZEBO_11)
  find_package(gazebo REQUIRED)
  set(listener_source
    src/Gazebo11Listener.cc
  )
  set(simulation_include_dirs
    ${GAZEBO_INCLUDE_DIRS}
  )
  link_directories(${GAZEBO_LIBRARY_DIRS})
  set(simulation_libraries
    ${GAZEBO_LIBRARIES}
  )
  list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")
elseif(IGN_DOME)
  find_package(ignition-msgs6 REQUIRED)
  find_package(ignition-transport9 REQUIRED)
  set(listener_source
    src/IgnDomeListener.cc
  )
  set(simulation_libraries
    ignition-msgs6::ignition-msgs6
    ignition-transport9::ignition-transport9
  )
else()
  message(FATAL_ERROR "Neither GAZEBO_11 or IGN_DOME were set. Please set one to ON.")
endif()

find_package(Boost COMPONENTS program_options REQUIRED)

add_executable(performance_metrics
  src/main.cc
  ${listener_source}
)

target_include_directories(performance_metrics PUBLIC
  include
  ${Boost_INCLUDE_DIRS}
  ${simulation_include_dirs}
)

target_link_libraries(performance_metrics
  ${Boost_LIBRARIES}
  ${simulation_libraries}
)
