project(autopilotone C CXX)

file(GLOB_RECURSE APO_SRC "apo/*")
include_directories(.)
add_executable(test
    test/linux.cpp
    ${APO_SRC})

add_custom_target(doxygen-build
    COMMAND doxygen ${CMAKE_SOURCE_DIR}/Doxyfile)

add_custom_target(doxygen-view
    COMMAND chromium-browser ${CMAKE_SOURCE_DIR}/doc/html/index.html)

add_custom_target(doxygen-gui
    COMMAND doxywizard ${CMAKE_SOURCE_DIR}/Doxyfile)
