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
        DEPENDS ${APO_SRC}
        COMMAND ${DOXYGEN} ${CMAKE_BINARY_DIR}/Doxyfile)
    add_custom_target(doxygen-clean
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/doc)

    # latex
    find_program(LATEX latex)
    if ( NOT "${LATEX}" STREQUAL "LATEX-NOTFOUND")
        add_custom_target(doxygen-latex
            COMMAND ${CMAKE_MAKE_PROGRAM}
            COMMAND ${CMAKE_COMMAND} -E copy refman.pdf ${CMAKE_BINARY_DIR}/apo.pdf
            COMMAND ${CMAKE_MAKE_PROGRAM} clean
            DEPENDS doxygen-build
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc/latex)
    endif()

    # html
    find_program(FIREFOX firefox)
    if ( NOT "${FIREFOX}" STREQUAL "FIREFOX-NOTFOUND")
        add_custom_target(doxygen-view
            COMMAND ${FIREFOX} index.html
            DEPENDS doxygen-build
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc/html)
    endif()

    # doxygen gui
    find_program(DOXYIWIZARD doxywizard)
    if ( NOT "${DOXYIWIZARD}" STREQUAL "DOXYWIZARD-NOTFOUND")
        message(STATUS "Found doxywizard")
        add_custom_target(doxygen-gui
            COMMAND doxywizard ${CMAKE_BINARY_DIR}/Doxyfile)
    endif()

endif()


