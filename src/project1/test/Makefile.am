bin_PROGRAMS = project1_test

project1_test_CPPFLAGS = -I$(top_srcdir)/lib \
                         -I$(top_srcdir)/src \
                         -g

project1_test_LDFLAGS = -lGL -lGLU -lglut

project1_test_LDADD = $(top_srcdir)/lib/libUnitTest++.a

project1_test_SOURCES = main.cpp \
                        turtle_test.cpp \
                        ../turtle.cpp \
                        $(top_srcdir)/src/core/point.cpp \
                        $(top_srcdir)/src/core/vector.cpp \
                        $(top_srcdir)/src/core/color.cpp

check: all
	@echo 'Executing unittests for project 1 ...'
	./project1_test