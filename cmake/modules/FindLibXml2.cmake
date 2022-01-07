INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES(PKG_LIBXML2 libxml-2.0)

FIND_PATH(LIBXML2_INCLUDE_DIR libxml/tree.h
    PATHS
    ${PKG_LIBXML2_INCLUDE_DIRS}
    /usr/include
    /usr/local/include
)

FIND_LIBRARY(LIBXML2_LIBRARIES
    NAMES
    xml2
    libxml2_a
    PATHS
    ${PKG_LIBXML2_LIBRARY_DIRS}
    /usr/lib
    /usr/local/lib
)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibXml2 DEFAULT_MSG LIBXML2_LIBRARIES LIBXML2_INCLUDE_DIR)

if(NOT BUILD_SHARED_LIBS)
    find_package(ZLIB)
    if(ZLIB_FOUND)
        list(APPEND LIBXML2_LIBRARIES "${ZLIB_LIBRARIES}")
    endif()

    find_package(LibLZMA)
    if(LIBLZMA_FOUND)
        list(APPEND LIBXML2_LIBRARIES "${LIBLZMA_LIBRARIES}")
    endif()
    
    if(MINGW)
        list(APPEND LIBXML2_LIBRARIES iconv wsock32 ws2_32)
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        list(APPEND LIBXML2_LIBRARIES iconv)
    elseif(MSVC)
        list(APPEND LIBXML2_LIBRARIES ws2_32)
    endif()
endif()
