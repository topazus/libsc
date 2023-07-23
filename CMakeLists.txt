cmake_minimum_required(VERSION 3.14...3.25)

project(SC
LANGUAGES C
HOMEPAGE_URL https://www.p4est.org/
DESCRIPTION "The SC library supports parallel scientific applications."
VERSION 2.8.5)

enable_testing()

include(cmake/init_build_type.cmake)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(debug_build ON)
else()
  set(debug_build OFF)
endif()

include(cmake/options.cmake)
message(STATUS "libsc ${PROJECT_VERSION} "
               "install prefix: ${CMAKE_INSTALL_PREFIX}")

set(PROJECT_MAJOR ${PROJECT_VERSION_MAJOR})
set(PROJECT_MINOR ${PROJECT_VERSION_MINOR})
set(PROJECT_PATCH ${PROJECT_VERSION_PATCH})
# options.cmake before config.cmake to determine user intent
include(cmake/config.cmake)

# compilers.cmake must be AFTER find_package() calls in config.cmake in general
include(cmake/compilers.cmake)

# --- iniparser
add_library(iniparser OBJECT
            iniparser/inistring.c iniparser/dictionary.c iniparser/iniparser.c)
target_include_directories(iniparser PRIVATE iniparser src ${PROJECT_BINARY_DIR}/include)
target_link_libraries(iniparser PRIVATE $<$<BOOL:${SC_ENABLE_MPI}>:MPI::MPI_C>)

# --- libb64
add_library(libb64 OBJECT libb64/cencode.c libb64/cdecode.c)
target_include_directories(libb64 PRIVATE libb64)

# --- sc
add_library(sc $<TARGET_OBJECTS:iniparser> $<TARGET_OBJECTS:libb64>)
target_compile_features(sc PRIVATE c_std_99)
set_target_properties(
    sc PROPERTIES
    EXPORT_NAME SC
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_include_directories(sc
PRIVATE iniparser libb64
PUBLIC
$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/sc_builtin>
$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(sc PUBLIC
$<$<BOOL:${SC_ENABLE_MPI}>:MPI::MPI_C>
$<$<BOOL:${SC_HAVE_ZLIB}>:ZLIB::ZLIB>
$<$<BOOL:${SC_NEED_M}>:m>
)

# imported target, for use from FetchContent
add_library(SC::SC INTERFACE IMPORTED GLOBAL)
target_link_libraries(SC::SC INTERFACE sc)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/ ${PROJECT_BINARY_DIR}/include/
DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
FILES_MATCHING PATTERN "*.h"
PATTERN "sc_builtin" EXCLUDE
)

install(TARGETS sc
  EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_subdirectory(src)
add_subdirectory(example)

if(BUILD_TESTING)
  add_subdirectory(test)
endif(BUILD_TESTING)

# --- packaging

include(cmake/pkgconf.cmake)
include(cmake/install.cmake)

include(FeatureSummary)

add_feature_info(MPI mpi "MPI features of libsc")
add_feature_info(OpenMP openmp "OpenMP features of libsc")
add_feature_info(ZLIB zlib "ZLIB features of libsc")
add_feature_info(shared BUILD_SHARED_LIBS "shared libsc library")

feature_summary(WHAT ENABLED_FEATURES DISABLED_FEATURES)
