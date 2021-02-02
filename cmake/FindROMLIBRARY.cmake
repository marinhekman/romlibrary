find_path(ROMLIBRARY_INCLUDE_DIR romlibrary.h
        HINTS
        include
        )

FIND_LIBRARY(ROMLIBRARY_LIBRARIES
        NAMES romlibrary
        HINTS
        PATH_SUFFIXES lib64 lib
        )