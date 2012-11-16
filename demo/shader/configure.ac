#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([shader_scene/countof.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([GL], [main])
# FIXME: Replace `main' with a function in `-lGLU':
AC_CHECK_LIB([GLU], [main])
# FIXME: Replace `main' with a function in `-lX11':
AC_CHECK_LIB([X11], [main])
# FIXME: Replace `main' with a function in `-lXi':
AC_CHECK_LIB([Xi], [main])
# FIXME: Replace `main' with a function in `-lXmu':
AC_CHECK_LIB([Xmu], [main])
# FIXME: Replace `main' with a function in `-lcg4cpp':
AC_CHECK_LIB([cg4cpp], [main])
# FIXME: Replace `main' with a function in `-lglu32':
AC_CHECK_LIB([glu32], [main])
# FIXME: Replace `main' with a function in `-lglut':
AC_CHECK_LIB([glut], [main])
# FIXME: Replace `main' with a function in `-lglut32':
AC_CHECK_LIB([glut32], [main])
# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], [main])
# FIXME: Replace `main' with a function in `-lopengl32':
AC_CHECK_LIB([opengl32], [main])
# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB([pthread], [main])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([sqrt])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
