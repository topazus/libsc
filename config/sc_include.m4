
dnl sc_include.m4 - general custom macros
dnl
dnl This file is part of the SC Library.
dnl The SC library provides support for parallel scientific applications.
dnl
dnl Copyright (C) 2008,2009 Carsten Burstedde, Lucas Wilcox.

dnl Documentation for macro names: brackets indicate optional arguments

dnl SC_VERSION(PREFIX)
dnl Expose major, minor, and point version numbers as CPP defines.
dnl Also creates a makefile variable PACKAGE_PREFIX with value PREFIX.
dnl
AC_DEFUN([SC_VERSION],
[
  AX_SPLIT_VERSION
  AC_DEFINE_UNQUOTED([VERSION_MAJOR],[$AX_MAJOR_VERSION],[Package major version])
  AC_DEFINE_UNQUOTED([VERSION_MINOR],[$AX_MINOR_VERSION],[Package minor version])
  AC_DEFINE_UNQUOTED([VERSION_POINT],[$AX_POINT_VERSION],[Package point version])
  AC_SUBST([PACKAGE_PREFIX], [$1])
])

dnl SC_ARG_ENABLE_PREFIX(NAME, COMMENT, TOKEN, PREFIX, HELPEXTRA)
dnl Check for --enable/disable-NAME using shell variable PREFIX_ENABLE_TOKEN
dnl If shell variable is set beforehand it overrides the option
dnl If enabled, define TOKEN to 1 and set conditional PREFIX_ENABLE_TOKEN
dnl Default is disabled
dnl
AC_DEFUN([SC_ARG_ENABLE_PREFIX],
[
AC_ARG_ENABLE([$1],
              [AS_HELP_STRING([--enable-$1$5], [$2])],,
              [enableval=no])
if test "x$enableval" != xno ; then
  AC_DEFINE([$3], 1, [DEPRECATED (use $4_ENABLE_$3 instead)])
  AC_DEFINE([ENABLE_$3], 1, [$2])
fi
AM_CONDITIONAL([$4_ENABLE_$3], [test "x$enableval" != xno])
$4_ENABLE_$3="$enableval"
])
AC_DEFUN([SC_ARG_ENABLE],
         [SC_ARG_ENABLE_PREFIX([$1], [$2], [$3], [SC], [$4])])

dnl SC_ARG_DISABLE_PREFIX(NAME, COMMENT, TOKEN, PREFIX, HELPEXTRA)
dnl Check for --enable/disable-NAME using shell variable PREFIX_ENABLE_TOKEN
dnl If shell variable is set beforehand it overrides the option
dnl If enabled, define TOKEN to 1 and set conditional PREFIX_ENABLE_TOKEN
dnl Default is enabled
dnl
AC_DEFUN([SC_ARG_DISABLE_PREFIX],
[
AC_ARG_ENABLE([$1],
              [AS_HELP_STRING([--disable-$1$5], [$2])],,
              [enableval=yes])
if test "x$enableval" != xno ; then
  AC_DEFINE([$3], 1, [DEPRECATED (use $4_ENABLE_$3 instead)])
  AC_DEFINE([ENABLE_$3], 1, [Undefine if: $2])
fi
AM_CONDITIONAL([$4_ENABLE_$3], [test "x$enableval" != xno])
$4_ENABLE_$3="$enableval"
])
AC_DEFUN([SC_ARG_DISABLE],
         [SC_ARG_DISABLE_PREFIX([$1], [$2], [$3], [SC], [$4])])

dnl SC_ARG_WITH_PREFIX(NAME, COMMENT, TOKEN, PREFIX, HELPEXTRA)
dnl Check for --with/without-NAME using shell variable PREFIX_WITH_TOKEN
dnl If shell variable is set beforehand it overrides the option
dnl If with, define TOKEN to 1 and set conditional PREFIX_WITH_TOKEN
dnl Default is without
dnl
AC_DEFUN([SC_ARG_WITH_PREFIX],
[
AC_ARG_WITH([$1],
            [AS_HELP_STRING([--with-$1$5], [$2])],,
            [withval=no])
if test "x$withval" != xno ; then
  AC_DEFINE([$3], 1, [DEPRECATED (use $4_WITH_$3 instead)])
  AC_DEFINE([WITH_$3], 1, [$2])
fi
AM_CONDITIONAL([$4_WITH_$3], [test "x$withval" != xno])
$4_WITH_$3="$withval"
])
AC_DEFUN([SC_ARG_WITH],
         [SC_ARG_WITH_PREFIX([$1], [$2], [$3], [SC], [$4])])

dnl SC_ARG_WITHOUT_PREFIX(NAME, COMMENT, TOKEN, PREFIX, HELPEXTRA)
dnl Check for --with/without-NAME using shell variable PREFIX_WITH_TOKEN
dnl If shell variable is set beforehand it overrides the option
dnl If with, define TOKEN to 1 and set conditional PREFIX_WITH_TOKEN
dnl Default is with
dnl
AC_DEFUN([SC_ARG_WITHOUT_PREFIX],
[
AC_ARG_WITH([$1],
            [AS_HELP_STRING([--without-$1$5], [$2])],,
            [withval=yes])
if test "x$withval" != xno ; then
  AC_DEFINE([$3], 1, [DEPRECATED (use $4_WITH_$3 instead)])
  AC_DEFINE([WITH_$3], 1, [Undefine if: $2])
fi
AM_CONDITIONAL([$4_WITH_$3], [test "x$withval" != xno])
$4_WITH_$3="$withval"
])
AC_DEFUN([SC_ARG_WITHOUT],
         [SC_ARG_WITHOUT_PREFIX([$1], [$2], [$3], [SC], [$4])])

dnl SC_REQUIRE_LIB(LIBRARY LIST, FUNCTION)
dnl Check for FUNCTION in LIBRARY, exit with error if not found
dnl
AC_DEFUN([SC_REQUIRE_LIB],
    [AC_SEARCH_LIBS([$2], [$1],,
      [AC_MSG_ERROR([Could not find function $2 in $1])])])

dnl Script for linking 'fabs' in GNU(linux) and BSD(mac) systems
dnl Apparantly linking the 'fabs' function requires different scripts for linux, mac and possibly win32
dnl
AC_DEFUN([SC_FABS_LINKTEST],
[
   AC_LINK_IFELSE([AC_LANG_PROGRAM(
   [[
#include <stdio.h>
#include <math.h>
   ]],
   [[
float arg = -4.12;
printf("%f",arg);
   ]])],
   [AC_DEFINE([HAVE_FABS],[1],[Define to 1 if fabs links successfully])
    AC_MSG_RESULT([fabs link successfull])],
   [AC_DEFINE([HAVE_FABS],[0],[Define to 1 if fabs links successfully])
    AC_MSG_RESULT([fabs link unsuccessfull])])
]
)

AC_DEFUN([SC_FABS],
[
   AC_MSG_CHECKING([if we are on a BSD system])
   AC_LINK_IFELSE([AC_LANG_PROGRAM(
   [[
#include<stdlib.h>

#ifndef __cplusplus
#pragma GCC diagnostic error "-Wimplicit-function-declaration"
#endif

int
comparator (void *arg, const void *aa, const void *bb)
{
  const int          *a = (int *) aa, *b = (int *) bb, *p = (int *) arg;
  int                 cmp = *a - *b;
  int                 inv_start = p[0], inv_end = p[1];
  char                norm = (*a < inv_start || *a > inv_end || *b < inv_start
                              || *b > inv_end);
  return norm ? -cmp : cmp;
}
   ]],
   [[
int                 arr[4] = { 4, 3, 2, 1 };
int                 p[] = { 0, 5 };

qsort_r (arr, 4, sizeof (int), p, comparator);
   ]])],
   [AC_MSG_RESULT([yes])
    SC_FABS_LINKTEST
   ],
   [
     AC_MSG_RESULT([no])
     AC_MSG_CHECKING([if we are on a GNU system])
       AC_LINK_IFELSE([AC_LANG_PROGRAM(
   [[
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include<stdlib.h>

#ifdef __cplusplus
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic error "-Wimplicit-function-declaration"
#pragma GCC diagnostic error "-Wincompatible-pointer-types"

int
comparator (const void *aa, const void *bb, void *arg)
{
  const int          *a = (int *) aa, *b = (int *) bb, *p = (int *) arg;
  int                 cmp = *a - *b;
  int                 inv_start = p[0], inv_end = p[1];
  char                norm = (*a < inv_start || *a > inv_end || *b < inv_start
                              || *b > inv_end);
  return norm ? -cmp : cmp;
}
   ]],
   [[
int                 arr[4] = { 4, 3, 2, 1 };
int                 p[] = { 0, 5 };

qsort_r (arr, 4, sizeof (int), comparator, p);
   ]])],
   [AC_MSG_RESULT([yes])
    SC_REQUIRE_LIB([m], [fabs])
   ],
   [AC_MSG_RESULT([We are not on a GNU system or BSD system which only leaves win32 as a possibility, support for that will be added when the situation arises])])
   ])
]
)

dnl SC_CHECK_LIB(LIBRARY LIST, FUNCTION, TOKEN, PREFIX)
dnl Check for FUNCTION first as is, then in each of the libraries.
dnl Set shell variable PREFIX_HAVE_TOKEN to nonempty if found.
dnl Call AM_CONDITIONAL with PREFIX_HAVE_TOKEN:
dnl   This means it must be called outside of any shell if block.
dnl Call AC_DEFINE with HAVE_TOKEN if found.
AC_DEFUN([SC_CHECK_LIB], [
AC_SEARCH_LIBS([$2], [$1])
AM_CONDITIONAL([$4_HAVE_$3], [test "x$ac_cv_search_$2" != xno])
$4_HAVE_$3=
if test "x$ac_cv_search_$2" != xno ; then
AC_DEFINE([HAVE_$3], [1], [Have we found function $2.])
$4_HAVE_$3=yes
fi
])

dnl SC_CHECK_LIB_NOCOND(LIBRARY LIST, FUNCTION, TOKEN, PREFIX)
dnl Check for FUNCTION first as is, then in each of the libraries.
dnl Set shell variable PREFIX_HAVE_TOKEN to nonempty if found.
dnl Does not establish an automake conditional;
dnl   safe to call from within a shell if block.
dnl Call AC_DEFINE with HAVE_TOKEN if found.
AC_DEFUN([SC_CHECK_LIB_NOCOND], [
AC_SEARCH_LIBS([$2], [$1])
$4_HAVE_$3=
if test "x$ac_cv_search_$2" != xno ; then
AC_DEFINE([HAVE_$3], [1], [Have we found function $2.])
$4_HAVE_$3=yes
fi
])

dnl SC_REQUIRE_FUNCS(FUNCTION LIST)
dnl Check for all functions in FUNCTION LIST, exit with error if not found
dnl
AC_DEFUN([SC_REQUIRE_FUNCS],
[
m4_foreach_w([sc_thefunc], [$1],
             [AC_CHECK_FUNC([sc_thefunc], ,
                            [AC_MSG_ERROR([\
Could not find function sc_thefunc])])])
])

dnl SC_DETERMINE_INSTALL(PREFIX)
dnl This function throws an error if the variable PREFIX_DIR does not exist.
dnl Looks for PREFIX_DIR/{include,lib,bin} to determine installation status.
dnl Set the shell variable PREFIX_INSTALL to "yes" or "no".
dnl
AC_DEFUN([SC_DETERMINE_INSTALL],
[
if test ! -d "$$1_DIR" ; then
  AC_MSG_ERROR([Directory "$$1_DIR" does not exist])
fi
if test -d "$$1_DIR/include" || test -d "$$1_DIR/lib" || \
   test -d "$$1_DIR/bin" || test -d "$$1_DIR/share/aclocal" ; then
  $1_INSTALL=yes
else
  $1_INSTALL=no
fi
])

dnl SC_DETERMINE_INCLUDE_PATH(PREFIX, CPPFLAGS)
dnl This function expects the variable PREFIX_DIR to exist.
dnl Looks for PREFIX_DIR/include and then PREFIX_DIR/src.
dnl If neither is found, throws an error.
dnl Otherwise, set the shell variable PREFIX_CPPFLAGS to -I<dir> CPPFLAGS.
dnl
AC_DEFUN([SC_DETERMINE_INCLUDE_PATH],
[
$1_INC="$$1_DIR/include"
if test ! -d "$$1_INC" ; then
  $1_INC="$$1_DIR/src"
fi
if test ! -d "$$1_INC" ; then
  AC_MSG_ERROR([Include directories based on $$1_DIR not found])
fi
$1_CPPFLAGS="-I$$1_INC $2"
])

dnl SC_DETERMINE_LIBRARY_PATH(PREFIX, LIBS)
dnl This function expects the variable PREFIX_DIR to exist.
dnl Looks for PREFIX_DIR/lib and then PREFIX_DIR/src.
dnl If neither is found, throws an error.
dnl Otherwise, set the shell variable PREFIX_LDADD to -L<dir> LIBS.
dnl
AC_DEFUN([SC_DETERMINE_LIBRARY_PATH],
[
$1_LIB="$$1_DIR/lib"
if test ! -d "$$1_LIB" ; then
  $1_LIB="$$1_DIR/src"
fi
if test ! -d "$$1_LIB" ; then
  AC_MSG_ERROR([Library directories based on $$1_DIR not found])
fi
$1_LDADD="-L$$1_LIB $2"
])

dnl SC_DETERMINE_CONFIG_PATH(PREFIX)
dnl This function expects the variable PREFIX_DIR to exist.
dnl Looks for PREFIX_DIR/share/aclocal and then PREFIX_DIR/src.
dnl If neither is found, throws an error.
dnl Sets shell variables PREFIX_CONFIG and PREFIX_AMFLAGS.
dnl
AC_DEFUN([SC_DETERMINE_CONFIG_PATH],
[
$1_CONFIG="$$1_DIR/share/aclocal"
if test ! -d "$$1_CONFIG" ; then
  $1_CONFIG="$$1_DIR/config"
fi
if test ! -d "$$1_CONFIG" ; then
  AC_MSG_ERROR([Config directories based on $$1_DIR not found])
fi
$1_AMFLAGS="-I $$1_CONFIG"
])

dnl dnl SC_CHECK_BLAS_LAPACK(PREFIX)
dnl dnl This function uses the macros SC_BLAS and SC_LAPACK.
dnl dnl It requires previous configure macros for F77 support,
dnl dnl which are called by SC_MPI_CONFIG/SC_MPI_ENGAGE.
dnl dnl
dnl AC_DEFUN([SC_CHECK_BLAS_LAPACK],
dnl [
dnl m4_ifset([SC_CHECK_MPI_F77],[
dnl dgemm=;AC_F77_FUNC(dgemm)
dnl if test "x$dgemm" = xunknown ; then dgemm=dgemm_ ; fi
dnl
dnl AC_MSG_NOTICE([Checking BLAS])
dnl SC_BLAS([$1], [$dgemm],
dnl         [AC_DEFINE([WITH_BLAS], 1, [Define to 1 if BLAS is used])],
dnl         [AC_MSG_ERROR([[\
dnl Cannot find BLAS library, specify a path using LIBS=-L<DIR> (ex.\
dnl  LIBS=-L/usr/path/lib) or a specific library using BLAS_LIBS=DIR/LIB\
dnl  (for example BLAS_LIBS=/usr/path/lib/libcxml.a)]])])
dnl
dnl # at this point $sc_blas_ok is either of: yes disable
dnl if test "x$sc_blas_ok" = xdisable ; then
dnl         AC_MSG_NOTICE([Not using BLAS])
dnl fi
dnl AM_CONDITIONAL([$1_WITH_BLAS], [test "x$sc_blas_ok" = xyes])
dnl
dnl dgecon=;AC_F77_FUNC(dgecon)
dnl if test "x$dgecon" = xunknown ; then dgecon=dgecon_ ; fi
dnl
dnl AC_MSG_NOTICE([Checking LAPACK])
dnl SC_LAPACK([$1], [$dgecon],
dnl           [AC_DEFINE([WITH_LAPACK], 1, [Define to 1 if LAPACK is used])],
dnl           [AC_MSG_ERROR([[\
dnl Cannot find LAPACK library, specify a path using LIBS=-L<DIR> (ex.\
dnl  LIBS=-L/usr/path/lib) or a specific library using LAPACK_LIBS=DIR/LIB\
dnl  (for example LAPACK_LIBS=/usr/path/lib/libcxml.a)]])])
dnl
dnl # at this point $sc_lapack_ok is either of: yes disable
dnl if test "x$sc_lapack_ok" = xdisable ; then
dnl         AC_MSG_NOTICE([Not using LAPACK])
dnl fi
dnl AM_CONDITIONAL([$1_WITH_LAPACK], [test "x$sc_lapack_ok" = xyes])
dnl
dnl # Append the necessary blas/lapack and fortran libraries to LIBS
dnl LIBS="$LAPACK_LIBS $BLAS_LIBS $LIBS $LAPACK_FLIBS $BLAS_FLIBS"
dnl ])
dnl ])

dnl SC_CHECK_LIBRARIES(PREFIX)
dnl This macro bundles the checks for all libraries and link tests
dnl that are required by libsc.  It can be used by other packages that
dnl link to libsc to add appropriate options to LIBS.
dnl
AC_DEFUN([SC_CHECK_LIBRARIES],
[
SC_FABS
dnl SC_REQUIRE_LIB([m], [fabs])
SC_CHECK_LIB([z], [adler32_combine], [ZLIB], [$1])
dnl SC_CHECK_LIB([lua53 lua5.3 lua52 lua5.2 lua51 lua5.1 lua5 lua],
dnl              [lua_createtable], [LUA], [$1])
dnl SC_CHECK_BLAS_LAPACK([$1])
SC_BUILTIN_ALL_PREFIX([$1])
SC_CHECK_PTHREAD([$1])
SC_CHECK_OPENMP([$1])
SC_CHECK_MEMALIGN([$1])
SC_CHECK_V4L2([$1])
dnl SC_CUDA([$1])
])

dnl SC_AS_SUBPACKAGE(PREFIX)
dnl Call from a package that is using libsc as a subpackage.
dnl Sets PREFIX_DIST_DENY=yes if sc is make install'd.
dnl
AC_DEFUN([SC_AS_SUBPACKAGE],
         [SC_ME_AS_SUBPACKAGE([$1], [m4_tolower([$1])], [SC], [sc])])

dnl SC_FINAL_MESSAGES(PREFIX)
dnl This macro prints messages at the end of the configure run.
dnl
AC_DEFUN([SC_FINAL_MESSAGES],
[
if test "x$$1_HAVE_ZLIB" = x ; then
AC_MSG_NOTICE([- $1 -------------------------------------------------
We did not find a recent zlib containing the function adler32_combine.
This is OK if the following does not matter to you:
Calling any sc functions that rely on zlib will abort your program.
These functions include sc_array_checksum and sc_vtk_write_compressed.
You can fix this by compiling a recent zlib and pointing LIBS to it.
])
fi
])
