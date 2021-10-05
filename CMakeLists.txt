cmake_minimum_required(VERSION 3.0)
project(romlibrary C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_C_STANDARD 99)
set(THREADS_PREFER_PTHREAD_FLAG on)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH true)

# required packages
find_package(CURL REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ACLL REQUIRED)
find_package(CHTTP REQUIRED)
find_package(CLOGGER REQUIRED)
find_package(CSAFESTRING REQUIRED)
find_package(LEXBOR REQUIRED)

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
        ${ACLL_INCLUDE_DIR}
        ${CHTTP_INCLUDE_DIR}
        ${CLOGGER_INCLUDE_DIR}
        ${CSAFESTRING_INCLUDE_DIR}
        ${LEXBOR_INCLUDE_DIR}
        )
include_directories(${INCLUDE_DIRECTORIES})

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
        src/helper/version.c
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
        src/hoster/urlhandling.c
        src/hoster/urlhandling.h
        src/hoster/wowroms/mapping.c
        src/hoster/wowroms/mapping.h
        src/hoster/wowroms/wowroms.c
        src/hoster/wowroms/wowroms.h
        src/results.c
        src/systems.c
        )

if (NOT TARGET romlibrary_shared AND NOT TARGET romlibrary_objects AND NOT TARGET romlibrary_static)
    add_library(romlibrary_objects OBJECT ${SOURCES_LIBRARY})

    set_target_properties(romlibrary_objects
            PROPERTIES
            POSITION_INDEPENDENT_CODE 1
            )

    add_library(romlibrary_static STATIC $<TARGET_OBJECTS:romlibrary_objects>)
    set_target_properties(romlibrary_static PROPERTIES OUTPUT_NAME romlibrary)
    target_link_libraries(romlibrary_static ${OPENSSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${ACLL_LIBRARIES} ${CHTTP_LIBRARIES} ${CSAFESTRING_LIBRARIES} ${LEXBOR_LIBRARIES} ${CURL_LIBRARIES})

    add_library(romlibrary_shared SHARED $<TARGET_OBJECTS:romlibrary_objects>)
    set_target_properties(romlibrary_shared PROPERTIES OUTPUT_NAME romlibrary)
    target_link_libraries(romlibrary_shared ${OPENSSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${ACLL_LIBRARIES} ${CHTTP_LIBRARIES} ${CSAFESTRING_LIBRARIES} ${LEXBOR_LIBRARIES} ${CURL_LIBRARIES})

    # Install
    install(TARGETS romlibrary_shared DESTINATION lib)
    install(TARGETS romlibrary_static DESTINATION lib)
    install(FILES romlibrary.h DESTINATION include)

    include(test/test.cmake)
endif ()

