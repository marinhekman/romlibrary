find_path(CHTTP_INCLUDE_DIR chttp.h
        HINTS
        include
        )

FIND_LIBRARY(CHTTP_LIBRARIES
        NAMES chttp
        HINTS
        PATH_SUFFIXES lib64 lib
        )