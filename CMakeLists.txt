project(autopilotone C CXX)
cmake_minimum_required(VERSION 2.8)

find_package(Boost 1.42 REQUIRED COMPONENTS thread system)


file(GLOB_RECURSE APO_SRC "${PROJECT_SRC_ROOT}/apo/*")

include_directories(. ${Boost_INCLUDE_DIRS})
add_definitions(-DOS=LINUX)
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
    add_custom_target(doxygen-latex
        COMMAND ${CMAKE_MAKE_PROGRAM}
        COMMAND ${CMAKE_COMMAND} -E copy refman.pdf ${CMAKE_BINARY_DIR}/apo.pdf
        COMMAND ${CMAKE_MAKE_PROGRAM} clean
        DEPENDS doxygen-build
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc/latex)
endif()

# doxywizard
find_program(DOXYIWIZARD doxywizard)
if ( NOT "${DOXYIWIZARD}" STREQUAL "DOXYWIZARD-NOTFOUND")
    message(STATUS "Found doxywizard")
    add_custom_target(doxygen-gui
        COMMAND doxywizard ${CMAKE_BINARY_DIR}/Doxyfile)
endif()
