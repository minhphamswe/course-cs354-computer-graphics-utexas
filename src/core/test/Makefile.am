bin_PROGRAMS = testcore

testcore_CPPFLAGS = -I$(top_srcdir)/lib \
                    -I$(top_srcdir)/src

testcore_LDADD = $(top_srcdir)/lib/libUnitTest++.a

testcore_SOURCES = main.cpp \
                   geometry_test.cpp \
                   ../point.cpp \
                   ../vector.cpp

check: all
	@echo 'Executing unittests for core ...'
	./testcore