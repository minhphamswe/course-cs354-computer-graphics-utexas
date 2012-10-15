bin_PROGRAMS = gl_cube gl_cube_fps gl_atom

AM_CPPFLAGS = -Wall -I$(top_srcdir)/src -g

gl_cube_SOURCES = gl_cube.cpp
gl_cube_fps_SOURCES = gl_cube_fps.cpp
gl_atom_SOURCES = gl_atom.cpp \
                  $(top_srcdir)/src/core/point.cpp \
                  $(top_srcdir)/src/core/point.h \
                  $(top_srcdir)/src/core/vector.cpp \
                  $(top_srcdir)/src/core/vector.h \
                  $(top_srcdir)/src/core/matrix.cpp \
                  $(top_srcdir)/src/core/matrix.h \
                  $(top_srcdir)/src/core/transform.cpp \
                  $(top_srcdir)/src/core/transform.h

check: all
	./gl_cube
	./gl_atom
	./gl_cube_fps