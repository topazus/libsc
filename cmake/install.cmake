# --- BOILERPLATE: install / packaging

include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/config.cmake.in
${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake
INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

write_basic_package_version_file(
${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake
COMPATIBILITY SameMajorVersion
)

install(EXPORT ${PROJECT_NAME}-targets
NAMESPACE ${PROJECT_NAME}::
DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(FILES
${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake
${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake
DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

export(EXPORT ${PROJECT_NAME}-targets
FILE ${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}-targets.cmake
NAMESPACE ${PROJECT_NAME}::
)

# --- CPack
set(CPACK_GENERATOR "TBZ2")
set(CPACK_SOURCE_GENERATOR "TBZ2")
set(CPACK_PACKAGE_VENDOR "Carsten Burstedde")
set(CPACK_PACKAGE_CONTACT "Carsten Burstedde")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README")
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/package)
string(TOLOWER ${CMAKE_SYSTEM_NAME} _sys)
set(CPACK_PACKAGE_FILE_NAME "libsc-${git_version}-${_sys}")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "libsc-${git_version}")

# not .gitignore as its regex syntax is more advanced than CMake
set(CPACK_SOURCE_IGNORE_FILES .git/ .github/ .vscode/ _CPack_Packages/
${CMAKE_BINARY_DIR}/ ${PROJECT_BINARY_DIR}/
Makefile.in
aclocal.m4
autom4te.cache/
build/
build-aux/ar-lib
build-aux/compile
build-aux/config.guess
build-aux/config.sub
build-aux/depcomp
build-aux/install-sh
build-aux/ltmain.sh
build-aux/missing
build-aux/test-driver
config/libtool.m4
config/ltoptions.m4
config/ltsugar.m4
config/ltversion.m4
config/lt~obsolete.m4
configure
)

install(FILES ${CPACK_RESOURCE_FILE_README} ${CPACK_RESOURCE_FILE_LICENSE}
DESTINATION share/docs/${PROJECT_NAME}
)

include(CPack)
