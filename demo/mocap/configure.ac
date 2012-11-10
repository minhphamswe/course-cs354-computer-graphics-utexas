#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([mocap], [0.1], [minh.pham@utexas.edu])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([bvh.l])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_YACC
AM_PROG_LEX
AM_PROG_CC_C_O

# Checks for libraries.
AC_CHECK_LIB([GL], [main])
AC_CHECK_LIB([GLU], [main])
AC_CHECK_LIB([fl], [main])
AC_CHECK_LIB([glut], [main])
AC_CHECK_LIB([m], [main])

# Checks for header files.
AC_CHECK_HEADERS([inttypes.h stdint.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([floor memset sqrt])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
