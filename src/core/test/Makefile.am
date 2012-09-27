bin_PROGRAMS = point_test vector_test point_vector_test

point_test_CPPFLAGS = -I$(top_srcdir)/lib \
                      -I$(top_srcdir)/src
point_test_LDADD = $(top_srcdir)/lib/libUnitTest++.a
point_test_SOURCES = main.cpp \
                     point_test.cpp \
                     ../point.cpp

vector_test_CPPFLAGS = -I$(top_srcdir)/lib \
                       -I$(top_srcdir)/src
vector_test_LDADD = $(top_srcdir)/lib/libUnitTest++.a
vector_test_SOURCES = main.cpp \
                      vector_test.cpp \
                      ../vector.cpp

point_vector_test_CPPFLAGS = -I$(top_srcdir)/lib \
                             -I$(top_srcdir)/src
point_vector_test_LDADD = $(top_srcdir)/lib/libUnitTest++.a
point_vector_test_SOURCES = main.cpp \
                            point_vector_test.cpp \
                            ../point.cpp \
                            ../vector.cpp

check: all
	@echo 'Executing unittests for core ...'
	./point_test
	./vector_test
	./point_vector_test