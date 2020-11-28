cmake_minimum_required(VERSION 3.10)

set(SOURCES
  derivatives_pricing.m.cpp
  derivatives_pricer.cpp
  vanilla_european_option_pricer.cpp)

add_executable(derivativesPricer ${SOURCES})
target_include_directories(derivativesPricer PRIVATE .)

find_package( Threads )
target_link_libraries( ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} )