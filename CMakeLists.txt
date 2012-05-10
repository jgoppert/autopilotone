project(autopilotone C CXX)
cmake_minimum_required(VERSION 2.8)

find_package(Boost 1.42 REQUIRED COMPONENTS thread system)

file(GLOB_RECURSE APO_SRC "apo/*")
include_directories(. ${Boost_INCLUDE_DIRS})
add_executable(test
    test/pc.cpp
    ${APO_SRC})
target_link_libraries(test ${Boost_LIBRARIES})

# doxygen
find_program(DOXYGEN doxygen)
if ( NOT "${DOXYGEN}" STREQUAL "DOXYGEN-NOTFOUND")
    message(STATUS "Found doxygen")
    configure_file(Doxyfile.cmake Doxyfile)
    add_custom_target(doxygen-build
        COMMAND ${DOXYGEN} ${CMAKE_BINARY_DIR}/Doxyfile)
endif()

# doxywizard
find_program(DOXYIWIZARD doxywizard)
if ( NOT "${DOXYIWIZARD}" STREQUAL "DOXYWIZARD-NOTFOUND")
    message(STATUS "Found doxywizard")
    add_custom_target(doxygen-gui
        COMMAND doxywizard ${CMAKE_BINARY_DIR}/Doxyfile)
endif()
