bin_PROGRAMS = triangle_test

triangle_test_CPPFLAGS = -I$(top_srcdir)/lib \
                         -I$(top_srcdir)/src
triangle_test_LDADD = $(top_srcdir)/lib/libUnitTest++.a
triangle_test_SOURCES = main.cpp \
                        triangle_test.cpp \
                        ../triangle.cpp

check: all
	@echo 'Executing unittests for core ...'
	./triangle_test