# Tau-Argus Rounder: thin C++ dispatch layer that drives the CRP (controlled
# rounding) engine from a single RounderCtrl::DoRound() call.
#
# It links against the CRP shared library (native/crp), which is built against
# the open-source HiGHS solver. The legacy SWIG JNI wrapper (RounderCtrl_wrap)
# has been removed; bindings to the new stack are generated with pybind11
# (see python/cpp/bind_rounder.cpp in the top-level repo).

cmake_minimum_required(VERSION 3.16)

project(tauargus_rounder CXX)

set(ROUNDER_SRC
    src/RounderCtrl.cpp
)

if(WIN32)
    # Compile the Windows version resource (harmless no-op elsewhere).
    list(APPEND ROUNDER_SRC src/Versioninfo.rc)
endif()

option(BUILD_SHARED_LIBS "Build shared native libraries" ON)
add_library(tauargus_rounder ${ROUNDER_SRC})
add_library(tauargus::rounder ALIAS tauargus_rounder)
if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(tauargus_rounder PUBLIC TAUARGUS_STATIC)
endif()

target_include_directories(tauargus_rounder
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

# Link the CRP engine. CRP exposes its src/ (with the canonical WrapCRP.h) as
# a PUBLIC include dir, so RounderCtrl.cpp's #include "WrapCRP.h" resolves
# there. (The rounder's own stale copy of WrapCRP.h was removed.)
target_link_libraries(tauargus_rounder PUBLIC tauargus::crp)

target_compile_features(tauargus_rounder PUBLIC cxx_std_11)

target_compile_options(tauargus_rounder PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -fno-strict-aliasing>
)

if(WIN32)
    target_compile_definitions(tauargus_rounder PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

install(TARGETS tauargus_rounder
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(DIRECTORY src/
    DESTINATION include/tauargus_rounder
    FILES_MATCHING PATTERN "*.h"
)
