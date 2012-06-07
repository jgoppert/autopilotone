cmake_minimum_required(VERSION 2.8)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_SOURCE_DIR}/cmake/arkcmake)

# options
set(AUTOPILOTONE_OS "PC" CACHE STRING "Operating System to Compile For")
set_property(CACHE AUTOPILOTONE_OS PROPERTY STRINGS "PC" "Arduino" "PX4")
option(WITH_BUILD_DEPS "Build dependencies." ON)
option(WITH_BUILD_SHARED "Build shared library." OFF)
option(WITH_PREFER_STATIC "Build preferring static linking." ON)
option(WITH_WARNINGS "Enable warnings." OFF)

# OS
set(OS_ARDUINO CACHE BOOL False)
set(OS_PC CACHE BOOL False)
set(OS_PX4 CACHE BOOL False)
if (${AUTOPILOTONE_OS} STREQUAL "Arduino")
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/arduino-cmake)
    set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake) # Arduino Toolchain
    set(ARDUINO True)
elseif (${AUTOPILOTONE_OS} STREQUAL "PC")
    set(PC True)
elseif (${AUTOPILOTONE_OS} STREQUAL "PX4")
    set(PX4 True)
endif()

project(autopilotone C CXX)

# settings
set(PROJECT_VERSION_MAJOR "0")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
set(PROJECT_CONTACT_EMAIL james.goppert@gmail.com)
set(PROJECT_CONTACT_VENDOR arktools)
set(LIBRARY_VERSION ${PROJECT_VERSION})
set(LIBRARY_SOVERSION "0.0.0")

# third party library version
set(SIMGEAR_REQUIRED_VERSION              1.9.1) 
set(MAVLINK_REQUIRED_VERSION 1.0.4)

# tags
set(SIMGEAR_TAG 9ab31e0d88ef2a09f6a8dd33837ba547366151fa)
set(MAVLINK_TAG 112cad9a4f6dddd0e65472fdc2a0956ab39da0e6)

set(RECURSE_OPTIONS_LIST
    WITH_BUILD_DEPS
    WITH_BUILD_SHARED
    WITH_PREFER_STATIC
    WITH_BUNDLE
    WITH_WARNINGS
    CMAKE_TOOLCHAIN_FILE
    CMAKE_INSTALL_PREFIX
    EP_BASE_DIR
)

# variables
set(ROOT_THREAD TRUE CACHE INTERNAL "Is this the top level of the recursion?")
set(INSTALL_DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}")
if (MINGW)
    set(INSTALL_DATA_DIR "C:/Program Files/${PROJECT_NAME} ${PROJECT_VERSION}/share/${PROJECT_NAME}")
endif()

# modules
include(DefineCMakeDefaults)
include(DefineCompilerFlags)
include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckSymbolExists)
include(CheckLibraryExists)
#include(CheckTypeSize)
#include(CheckPrototypeExists)
#include(CheckCXXSourceCompiles)
#include(CheckCSourceCompiles)
include(ExternalProjectWithFilename)
include(CheckLinkType)

# external projects find path
if(NOT EP_BASE_DIR)
    set(EP_BASE_DIR "${CMAKE_BINARY_DIR}/CMakeExternals")
endif()
set_property(DIRECTORY PROPERTY EP_BASE ${EP_BASE_DIR})
set(EP_INSTALL_DIR "${EP_BASE_DIR}/Install")
list(APPEND CMAKE_FIND_ROOT_PATH ${EP_INSTALL_DIR})

# spawn new cmake to build deps
if (WITH_BUILD_DEPS AND ROOT_THREAD)
    set(CMAKE_RECURSE_ARGS "-DROOT_THREAD=FALSE")
    foreach(OPT ${RECURSE_OPTIONS_LIST})
        list(APPEND CMAKE_RECURSE_ARGS "-D${OPT}=${${OPT}}")
    endforeach()
    execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} ${CMAKE_RECURSE_ARGS}
        RESULT_VARIABLE ERROR)
    if (ERROR)
        message(FATAL_ERROR "error, recursing loop returned error code: ${ERROR}")
    endif()
    message("** Making dependencies")
    execute_process(COMMAND ${CMAKE_MAKE_PROGRAM} "-j4" "-f${CMAKE_BINARY_DIR}/Makefile")
    message("** Configuring ${PROJECT_NAME}")
endif()

# prefer static packages if building static library
message("** Finding libraries")
if (WITH_BUILD_STATIC)
    set(BOOST_USE_STATIC_LIBS ON)
    # prefer static libs
    if(WIN32)
        set(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
    else()
        set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
    endif()
endif()


# find packages
if (ROOT_THREAD)
    set(REQUIRED_IF_ROOT "REQUIRED")
else()
    set(REQUIRED_IF_ROOT)
endif()

find_package(SimGear 2.7.0 ${REQUIRED_IF_ROOT} COMPONENTS
  # core components
    #environment
    #nasal
    #tsync
    #bucket
    route
    io
    #serial
    #math
    #props
    structure
    timing
    #xml
    #misc
    threads
    #debug
    #magvar
  # scene components
    #ephem
    #sky
    #material
    #tgdb
    #model
    #screen
    #bvh
    #util
    #sound
    )
find_package(MAVLink ${MAVLINK_REQUIRED_VERSION} ${REQUIRED_IF_ROOT})

# build dependencies
if (WITH_BUILD_DEPS AND (NOT ROOT_THREAD) )
    message("** Configuring dependencies")

    # add external projects

    set(CMAKE_EP_DEFAULT_ARGS
        -DEP_BASE_DIR=${EP_BASE_DIR}
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
        -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
        )

    if (NOT MAVLINK_FOUND)
        ExternalProjectWithFilename_Add(mavlink
            URL http://nodeload.github.com/mavlink/mavlink/tarball/${MAVLINK_TAG}
            FILENAME mavlink-${MAVLINK_TAG}.tar.gz
            CMAKE_ARGS ${CMAKE_EP_DEFAULT_ARGS}
            INSTALL_COMMAND ${CMAKE_MAKE_PROGRAM} DESTDIR=${EP_INSTALL_DIR} install
            INSTALL_DIR ${EP_INSTALL_DIR}
           )
    endif()

    if (NOT SIMGEAR_FOUND)
        ExternalProjectWithFilename_Add(simgear
            URL http://gitorious.org/fg/jgopperts-simgear/archive-tarball/${SIMGEAR_TAG}
            FILENAME jgoppert-jgopperts-simgear-${SIMGEAR_TAG}.tar.gz
            CMAKE_ARGS ${CMAKE_EP_DEFAULT_ARGS} "-DCMAKE_FIND_ROOT=/opt/local" "-DSIMGEAR_HEADLESS=ON" "-DENABLE_TESTS=OFF"
            INSTALL_COMMAND ${CMAKE_MAKE_PROGRAM} DESTDIR=${EP_INSTALL_DIR} install
            INSTALL_DIR ${E_INSTALL_DIR}
           )
    endif()

    return()

endif()

# configure
#check_include_files(expat_config.h HAVE_EXPAT_CONFIG_H)
#check_function_exists(bcopy HAVE_BCOPY)
#check_symbol_exists(LC_MESSAGES "locale.h" HAVE_LC_MESSAGES) 
#check_library_exists(arkosg  attachNode "" HAVE_ARKOSG)

# config files
configure_file(config.h.in config.h)
install(FILES ${CMAKE_BINARY_DIR}/config.h DESTINATION include/${PROJECT_NAME} COMPONENT Dev)

# build settings
add_definitions(-DAUTOPILOTONE_OS=${AUTOPILOTONE_OS})
if (OS_PC)
    if (MSVC)
        add_definitions(-D_USE_MATH_DEFINES -D"NOMINMAX" -D"XML_STATIC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc" CACHE STRING "Flags used by the compiler during all build types." FORCE)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc" CACHE STRING "Flags used by the compiler during all build types." FORCE)
    elseif(MINGW)
        add_definitions(-D_WIN32_WINNT=0x0501)
    elseif(APPLE)
        set(CMAKE_OSX_ARCHITECTURES "i386;ppc;x86_64" CACHE STRING "Build architectures for OSX" FORCE)
        set(CMAKE_EXE_LINKER_FLAGS "-fvisiblity=hidden -framework cocoa -framework carbon")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    elseif(UNIX)
        add_definitions(-DUSE_X11)
    endif()
    include_directories(. ${SIMGEAR_INCLUDE_DIRS})
    link_libraries(${SIMGEAR_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
    add_definitions(-DOS_PC)
else(OS_ARDUINO)
    add_definitions(-DOS_ARDUINO)
else(OS_PX4)
    add_definitions(-DOS_PX4)
else()
    message(FATAL_ERROR "unknown operating system")
endif()

#if (WITH_WARNINGS)
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -pedantic")
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wshadow -Wmissing-prototypes -Wdeclaration-after-statement")
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wunused -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wformat-security")
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-format-attribute")

    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wformat-security")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-format-attribute")
#endif()

# library
file(GLOB_RECURSE APO_SRC "${CMAKE_SOURCE_DIR}/autopilotone/*")

# test
add_executable(test
    test/test.cpp
    ${APO_SRC})

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
            COMMAND ${CMAKE_COMMAND} -E copy refman.pdf ${CMAKE_BINARY_DIR}/autopilotone.pdf
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

# install library
install(DIRECTORY "autopilotone" DESTINATION include COMPONENT Dev PATTERN "*.git*" EXCLUDE)

# packaging
if (WIN32)
    # set NSIS image, nsis bug requuires atleast one file with 4 slashes to install correctly
    set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}\\\\/cmake/autopilotone-nsis.bmp")
    set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/cmake/autopilotone.ico")
    set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/cmake/autopilotone.ico")
endif()
configure_file("COPYING" "COPYING.txt" COPYONLY) # adding file extensions
configure_file("README.md" "README.txt" COPYONLY)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_BINARY_DIR}/COPYING.txt")
set(CPACK_RESOURCE_FILE_README "${CMAKE_BINARY_DIR}/README.txt")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CPACK_RESOURCE_FILE_README}")
set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_SOURCE_DIR}/cmake/WELCOME.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "autopilotone simplex trimming branch")
set(CPACK_PACKAGE_VENDOR ${PROJECT_CONTACT_VENDOR})
set(CPACK_PACKAGE_CONTACT "${PROJECT_CONTACT_EMAIL}")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_SET_DESTDIR TRUE)
set(CPACK_COMPONENTS_GROUPING "ALL_COMPONENTS_IN_ONE")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libstdc++6, libgcc1, libc6")
set(CPACK_NSIS_MODIFY_PATH ON)
set(CPACK_PACKAGE_EXECUTABLES
    #"autopilotone-cmd" "Command Line"
    )
include(CPack)

# pkgconfig
configure_file(pc.in ${PROJECT_NAME}.pc)
install(FILES
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc
    DESTINATION "lib/pkgconfig" COMPONENT Dev
    )
# vim:sw=4:ts=4:expandtab


