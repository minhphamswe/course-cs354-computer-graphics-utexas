bin_PROGRAMS = gl_cube gl_cube_fps

gl_cube_CPPFLAGS = -Wall -I$(top_srcdir)/src -g
gl_cube_SOURCES = gl_cube.cpp

gl_cube_fps_CPPFLAGS = -Wall -I$(top_srcdir)/src -g
gl_cube_fps_SOURCES = gl_cube_fps.cpp

check: all
	./gl_cube
	./gl_cube_fps