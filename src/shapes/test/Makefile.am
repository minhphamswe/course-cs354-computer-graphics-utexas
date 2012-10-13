bin_PROGRAMS = triangle_test

AM_LDFLAGS = --coverage
AM_CPPFLAGS = -I$(top_srcdir)/lib -I$(top_srcdir)/src \
              -g -fprofile-arcs -ftest-coverage \
              --coverage
LDADD = $(top_srcdir)/lib/libUnitTest++.a

triangle_test_SOURCES = main.cpp \
                        triangle_test.cpp \
                        ../triangle.cpp

check: all
	@echo 'Executing unittests for shapes ...'
	./triangle_test

coverage: check
	@echo 'Generating coverage info for core ...'
	lcov --capture --directory ../ --output-file coverage.info
	genhtml coverage.info --output-directory cov-html