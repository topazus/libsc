# --- generate pkg-config .pc
set(pc_req_private "")
if(mpi)
  string(APPEND pc_req_private " ompi ompi-c zlib")
elseif(zlib)
  string(APPEND pc_req_private " zlib")
endif()

include(cmake/utils.cmake)
convert_yn(mpi mpi_pc)
convert_yn(openmp openmp_pc)
convert_yn(SC_HAVE_JSON sc_have_json_pc)
convert_yn(zlib zlib_pc)
convert_yn(SC_ENABLE_DEBUG debug_build_pc)

set(pc_filename "libsc-${PROJECT_VERSION}.pc")
configure_file(${CMAKE_CURRENT_LIST_DIR}/pkgconf.pc.in ${pc_filename} @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${pc_filename}
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

set(pc_link libsc.pc)

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
  ${pc_filename}
  ${pc_link}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${pc_link}
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
