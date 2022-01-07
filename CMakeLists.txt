cmake_minimum_required(VERSION 3.0.0)
project(hdl-dump)
set(CMAKE_CXX_STANDARD 11)

set(SOURCES
        hdl_dump.c apa.c common.c progress.c hdl.c isofs.c aligned.c
        iin_img_base.c iin_optical.c iin_iso.c iin_cdrwin.c
        iin_nero.c iin_gi.c iin_iml.c iin_probe.c iin_hio.c
        hio_probe.c hio_win32.c hio_dbg.c hio_trace.c
        net_common.c byteseq.c dict.c hio_udpnet2.c
)

add_executable(hdl-dump ${SOURCES})
