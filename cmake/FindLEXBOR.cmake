find_path(LEXBOR_INCLUDE_DIR html.h
        HINTS
        include
        PATH_SUFFIXES
        lexbor/html
        )

FIND_LIBRARY(LEXBOR_LIBRARIES
        NAMES lexbor_static
        HINTS
        lib64 lib
        )