cmake_minimum_required(VERSION 3.0.0)
project(hdl-dump)
set(CMAKE_CXX_STANDARD 11)

set(VER_MAJOR 0)
set(VER_MINOR 9)
set(VER_PATCH 2)
set(VERSION "${VER_MAJOR}.${VER_MINOR}.${VER_PATCH}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ansi -pedantic -Wno-long-long")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ansi -pedantic -Wno-long-long")

set(SOURCES
        hdl_dump.c
        byteseq.c
        osal_unix.c
        apa.c
        common.c
        progress.c
        isofs.c
        hdl.c
        iin_probe.c
        dict.c
        hio_probe.c
        iin_optical.c
        iin_nero.c
        iin_gi.c
        iin_iso.c
        iin_iml.c
        iin_hio.c
        iin_cdrwin.c
        thd_iin.c
        hio_trace.c
        hio_dbg.c
        aligned.c
        iin_img_base.c
        hio_udpnet.c
        hio_udpnet2.c
        hio_win32.c
        net_common.c
        )

if(UNIX)
    list(APPEND ${SOURCES} "osal_unix.c")
else()
    list(APPEND ${SOURCES} "osal_win32.c")
endif()

add_executable(hdl-dump ${SOURCES})

if (WIN32)
    message(STATUS "Building for Windows")
    target_compile_definitions(hdl-dump PRIVATE VERSION="${VERSION}" _BUILD_WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_BUILD_WIN32 -D_WIN32_WINNT=0x0500 -DUSE_THREADED_IIN")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_BUILD_WIN32 -DUSE_THREADED_IIN")
    target_link_libraries(hdl-dump PRIVATE winmm wsock32)
elseif (UNIX)
    message(STATUS "Building for Unix")
    target_compile_definitions(hdl-dump PRIVATE VERSION="${VERSION}" _BUILD_UNIX _GNU_SOURCE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_BUILD_UNIX -D_GNU_SOURCE -DUSE_THREADED_IIN")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_BUILD_UNIX -D_GNU_SOURCE -DUSE_THREADED_IIN")
    target_link_libraries(hdl-dump PRIVATE pthread)
endif ()
