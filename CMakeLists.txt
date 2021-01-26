cmake_minimum_required(VERSION 3.0)
project(romlibrary C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_C_STANDARD 99)
set(CMAKE_INSTALL_PREFIX /usr)
set(THREADS_PREFER_PTHREAD_FLAG on)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH true)

# required packages
find_package(CURL REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

# debug handling for build
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_VERBOSE_MAKEFILE on)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -DCLOGGER_LEVEL=2")
else ()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -DCLOGGER_LEVEL=1")
endif ()

# Header file directories
set(INCLUDE_DIRECTORIES
        ${INCLUDE_DIRECTORIES}
        ${CURL_INCLUDE_DIRS}
        ${OPENSSL_INCLUDE_DIR}
        libs/csafestring
        libs/lexbor
        libs/lexbor/source
        libs/acll
        libs/clogger
        libs/chttp
        )
include_directories(${INCLUDE_DIRECTORIES})

# add submodules to build path
add_subdirectory(libs/csafestring)
add_subdirectory(libs/lexbor)
add_subdirectory(libs/acll)
add_subdirectory(libs/chttp)

# ROM Library Sources
set(SOURCES_LIBRARY
        romlibrary.h
        src/helper/domparsing.c
        src/helper/domparsing.h
        src/helper/md5.c
        src/helper/md5.h
        src/helper/regex.c
        src/helper/regex.h
        src/helper/utils.c
        src/helper/utils.h
        src/hoster.c
        src/hoster/freeroms/freeroms.c
        src/hoster/freeroms/freeroms.h
        src/hoster/freeroms/mapping.c
        src/hoster/freeroms/mapping.h
        src/hoster/romhustler/mapping.c
        src/hoster/romhustler/mapping.h
        src/hoster/romhustler/romhustler.c
        src/hoster/romhustler/romhustler.h
        src/hoster/romsdownload/icon.h
        src/hoster/romsdownload/mapping.c
        src/hoster/romsdownload/mapping.h
        src/hoster/romsdownload/romsdownload.c
        src/hoster/romsdownload/romsdownload.h
        src/hoster/romsemulator/icon.h
        src/hoster/romsemulator/mapping.c
        src/hoster/romsemulator/mapping.h
        src/hoster/romsemulator/romsemulator.c
        src/hoster/romsemulator/romsemulator.h
        src/hoster/romsmania/mapping.c
        src/hoster/romsmania/mapping.h
        src/hoster/romsmania/romsmania.c
        src/hoster/romsmania/romsmania.h
        src/hoster/urlhandling.c
        src/hoster/urlhandling.h
        src/hoster/wowroms/mapping.c
        src/hoster/wowroms/mapping.h
        src/hoster/wowroms/wowroms.c
        src/hoster/wowroms/wowroms.h
        src/results.c
        src/systems.c
        )

if (NOT TARGET romlibrary)
    add_library(romlibrary ${SOURCES_LIBRARY})
    target_link_libraries(romlibrary ${OPENSSL_LIBRARIES} ${CURL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} csafestring lexbor_static acll chttp)

    # Install
    install(TARGETS romlibrary DESTINATION libs)

    include(test/test.cmake)
endif ()

